#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
	#else
        vidPlayer.loadMovie("fingers.mov");
        vidPlayer.play();
	#endif

    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
    
    thresh_resized.allocate(320,240);
    
    thresh_resized_width    = 80;
    thresh_resized_height   = 60;
    
	bLearnBakground = true;
	threshold = 80;
    
    ofSetFrameRate(5);
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
        #endif

        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
//		contourFinder.findContours(grayDiff, 20, (340*240)/3, 1, true);	// find holes
        
        createPoints();
	}
    
}

void testApp::createPoints()
{
    points.resize( 0 );
    triangulator.reset();
    
    thresh_resized.resize( grayDiff.width, grayDiff.height );
    thresh_resized = grayDiff;
    thresh_resized.resize( thresh_resized_width, thresh_resized_height );
    
    unsigned char * pixels = thresh_resized.getPixels();
    int length = thresh_resized_width * thresh_resized_height;
    
    for (int i=0; i<length; i++) {
        if (pixels[i] > 0 && ofRandom(0, 1) < .5 ){
            float x = i % thresh_resized_width / (float)thresh_resized_width ;
            float y = i / thresh_resized_width / (float)thresh_resized_height;
            ofPoint point = ofPoint(x,y);
            points.push_back( point );
            
            triangulator.addPoint(x*ofGetWidth(), y*ofGetHeight());
        }
    }
    
    triangulator.addPoint( 0, 0 );
    triangulator.addPoint( ofGetWidth(), 0 );
    triangulator.addPoint( ofGetWidth(), ofGetHeight() );
    triangulator.addPoint( 0, ofGetHeight() );
    
    cout << points.size() << endl;
    
    triangulator.triangulate();
}


void testApp::drawPoints( int x, int y )
{
    ofSetColor(255, 0, 0);
    for (int i=0; i<points.size(); i++) {
        ofCircle(x + points[i].x * grayDiff.width, y + points[i].y * grayDiff.height, 3);
    }
}


//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
//	ofSetColor(0xffffff);
//	colorImg.draw(20,20);
//	grayImage.draw(360,20);
////	grayBg.draw(20,280);
//	grayDiff.draw(360,280);
//
//    thresh_resized.draw(20,280);
//    drawPoints(20,280);
//    
	ofSetColor(0, 255, 0);
    triangulator.drawTriangles();

	// finally, a report:

	ofSetColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i, fps: %f", threshold, contourFinder.nBlobs, ofGetFrameRate());
	ofDrawBitmapString(reportStr, 20, 600);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

