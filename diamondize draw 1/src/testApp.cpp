#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    ofSetFrameRate(60);
    ofSetFullscreen(true);
    
    
    img.loadImage( "test.jpg" );
    
    show_triangulation  = false;
    drawing_enabled     = false;
    
    // 'gui' is a global variable declared in ofxSimpleGuiToo.h
	gui.addTitle("General");//    gui.addSlider( "aperature", aperature, 1,10 );
    gui.addToggle( "Show Triangluation", show_triangulation );
    gui.addToggle( "Drawing", drawing_enabled );
    gui.show();
}


//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

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
    
    img.draw(0,0, ofGetWidth(), ofGetHeight() );
    
    if ( show_triangulation ) {
        ofSetColor(255, 255, 255, 100);
        triangulator.drawTriangles();        
    }

	gui.draw();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
        case 'd':
            drawing_enabled = !drawing_enabled;
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
    
    addPoint( x, y );
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

