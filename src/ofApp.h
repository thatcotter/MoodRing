#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void drawFboJawn();
    
    ofFbo createChannel(float r, float g, float b);
    void drawChannel(ofFbo img, float x, float y);
    
    ofFbo redImg, greenImg, blueImg;
    ofFbo rgbaFboFloat;
    
    int fadeAmnt;
    
    ofPoint pMouse;
    
    float x0;
    float y0;
    float dmouseX;
    float dmouseY;
    
    float deltaX, deltaY;
    
    float oscNewVal1;
    float oscNewVal2;
    float oscNewVal3;
    float oscNewVal4;
    float oscNewVal5;
    float oscNewVal6;
    float oscNewVal7;
    float oscNewVal8;
    
    
    float oscOldVal1;
    float oscOldVal2;
    float oscOldVal3;
    float oscOldVal4;
    float oscOldVal5;
    float oscOldVal6;
    float oscOldVal7;
    float oscOldVal8;
    
    
    ofxOscReceiver receiver;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
		
};
