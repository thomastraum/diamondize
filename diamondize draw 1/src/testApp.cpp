#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    ofSetFrameRate(10);

    img.loadImage( "pics/Underwater Landscapes  Wallpaper (79).jpg" ); //"Tiger Face.jpg" );
    
    show_triangulation  = false;
    show_image          = true;
    drawing_enabled     = false;
    
    painting            = false;
    paint_radius        = 10;
    
	gui.addTitle("General");//    gui.addSlider( "aperature", aperature, 1,10 );
    gui.addToggle( "Show Image", show_image );
    gui.addToggle( "Show Triangluation", show_triangulation );
    gui.addToggle( "Drawing", drawing_enabled );
    gui.addSlider( "Paint Radius", paint_radius, 0, 100 );
    
    gui.show();

    // ofxVectorGraphics //
	capture = false;
    
    triangulator.init( 100000 );
}


//--------------------------------------------------------------
void testApp::update(){
    
	ofBackground(100,100,100);
    
    if (painting && drawing_enabled ) {
        
        addPoint( mouseX + ofRandom(0, 1) * paint_radius, mouseY + ofRandom(0,1) * paint_radius );
    } 
        triangulator.triangulate();
}

void testApp::addPoint(int x, int y)
{
    if (!drawing_enabled) return;
    
    ofPoint point = ofPoint( x, y );
    points.push_back( point );
    triangulator.addPoint(x, y );
}

//--------------------------------------------------------------
void testApp::drawPoints( int x, int y )
{
    ofSetColor(255, 0, 0);
}

void testApp::draw(){
    
    ofSetColor(255, 255, 255);
    
    if (show_image) {
        
        if (img.width >= img.height) {
            float scale = ofGetWidth()/(float)img.width;
            img.draw(0,0, ofGetWidth(),  scale * img.height );    
        } else  {
            float scale = ofGetHeight()/(float)img.height;
            img.draw(0,0, scale * img.width, ofGetHeight() );    
        }
        
    }
    
    if ( show_triangulation ) {
        ofSetColor(255, 255, 255, 100);
        triangulator.drawTriangles();        
    }

	gui.draw();
    
    if (capture) {
        triangulator.exportToEps();
        capture = false;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

	switch (key){
        case 'd':
            drawing_enabled = !drawing_enabled;
            break;
        case 'c':
            capture = true;
            break;
        case ' ':
            gui.toggleDraw();
            break;
        case 'f':
            ofToggleFullscreen();
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
void testApp::mousePressed(int x, int y, int button)
{
    painting = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{    
    painting = false;    
//    addPoint( x, y );
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

