#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxDelaunay.h"
#include "ofxSimpleGuiToo.h"

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file

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

        void createPoints( );
        void scaleToSize();
        void drawPoints( int x, int y );
    
        void findEdges( ofxCvColorImage * sourceFrame, int thelowThreshold, int theHighThreshold, int theAperture);

        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif

        ofxCvColorImage		colorImg;

        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

        ofxCvGrayscaleImage     thresh_resized;
        ofxDelaunay             triangulator;
    
        ofxCvGrayscaleImage     tempFrame;
    
        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;
    
        int                 thresh_resized_width;
        int                 thresh_resized_height;
        vector<ofPoint>     points;

        int                 low_threshold;
        int                 high_threshold;
        int                 aperature;
};

#endif
