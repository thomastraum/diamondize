#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxDelaunay.h"
#include "ofxSimpleGuiToo.h"
#include "ofxVectorGraphics.h"
#include "ttOfxDelauneyAddOn.h"

class testApp : public ofBaseApp{

public:

    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);

    void addPoint( int x, int y );
    void drawPoints( int x, int y );
    
    ofImage             img;
    ttOfxDelauneyAddOn  triangulator;
    ofxCvGrayscaleImage tempFrame;
    
    vector<ofPoint>     points;
    
//    ttOfxDelauneyAddOn  ttDelauney;
    
    bool                capture;
    bool                painting;
    int                 paint_radius;
    
    bool                show_triangulation;
    bool                show_image;
    bool                drawing_enabled;
};

#endif
