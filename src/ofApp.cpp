#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    
    ofBackground(0);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    #ifdef TARGET_OPENGLES
        rgbaFboFloat.allocate(400, 400, GL_RGBA ); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
        ofLogWarning("ofApp") << "GL_RGBA32F_ARB is not available for OPENGLES.  Using RGBA.";
    #else
        rgbaFboFloat.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
    #endif
    
    redImg.begin();
    ofClear(255, 255, 255, 0);
    redImg.end();
    redImg = createChannel(0, 255, 255);
    
    greenImg.begin();
    ofClear(255, 255, 255, 0);
    greenImg.end();
    greenImg = createChannel(255, 0, 255);
    
    blueImg.begin();
    ofClear(255, 255, 255, 0);
    blueImg.end();
    blueImg = createChannel(255, 255, 0);
    
    rgbaFboFloat.begin();
    ofClear(255,255,255, 0);
    rgbaFboFloat.end();

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        oscNewVal1 = m.getArgAsFloat(0);
        oscNewVal2 = m.getArgAsFloat(1);
        oscNewVal3 = m.getArgAsFloat(2);
        oscNewVal4 = m.getArgAsFloat(3);
        
        oscNewVal5 = m.getArgAsFloat(4);
        oscNewVal6 = m.getArgAsFloat(5);
        oscNewVal7 = m.getArgAsFloat(6);
        oscNewVal8 = m.getArgAsFloat(7);
        
        cout << oscNewVal1 << endl;
    }
    
    ofBackground(255, 255, 255);
    
    x0 = 0.5 * ofGetWidth();
    y0 = 0.5 * ofGetHeight();
    
    dmouseX = mouseX - pMouse.x;
    dmouseY = mouseY - pMouse.y;
    
    pMouse = ofPoint( mouseX, mouseY );
    
    deltaX = ((oscNewVal1 - oscOldVal1) + (oscNewVal3 - oscOldVal3) + (oscNewVal5 - oscOldVal5) + (oscNewVal7 - oscOldVal7)) /4;
    deltaY = (oscNewVal2 - oscOldVal2) + (oscNewVal4 - oscOldVal4) + (oscNewVal6 - oscOldVal6) + (oscNewVal8 - oscOldVal8) / 4;
    
    deltaX *= 0.0125;
    deltaY *= 0.0125;
    
    
    oscOldVal1 = oscNewVal1;
    oscOldVal2 = oscNewVal2;
    oscOldVal3 = oscNewVal3;
    oscOldVal4 = oscNewVal4;
    oscOldVal5 = oscNewVal5;
    oscOldVal6 = oscNewVal6;
    oscOldVal7 = oscNewVal7;
    oscOldVal8 = oscNewVal8;
    
    
    rgbaFboFloat.begin();
    drawFboJawn();
    rgbaFboFloat.end();

}

//function from fbo example
void ofApp::drawFboJawn(){
    //we clear the fbo if c is pressed.
    //this completely clears the buffer so you won't see any trails
    if( ofGetKeyPressed('c') ){
        ofClear(255,255,255, 0);
    }
    
    //some different alpha values for fading the fbo
    //the lower the number, the longer the trails will take to fade away.
    fadeAmnt = 128;
    if(ofGetKeyPressed('1')){
        fadeAmnt = 1;
    }else if(ofGetKeyPressed('2')){
        fadeAmnt = 5;
    }else if(ofGetKeyPressed('3')){
        fadeAmnt = 15;
    }
    else if(ofGetKeyPressed('4')){
        fadeAmnt = 150;
    }
    
    //1 - Fade Fbo
    
    //this is where we fade the fbo
    //by drawing a rectangle the size of the fbo with a small alpha value, we can slowly fade the current contents of the fbo.
    ofFill();
    ofSetColor(255,255,255, fadeAmnt);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    //2 - Draw graphics
    
    for (int i = 0; i < 20; i++) {
//        drawChannel(redImg, x0 - dmouseX, y0 - dmouseY);
//        drawChannel(greenImg, x0, y0);
//        drawChannel(blueImg, x0 + dmouseX, y0 + dmouseY);
        drawChannel(redImg, x0 - deltaX, y0 - deltaY);
        drawChannel(greenImg, x0, y0);
        drawChannel(blueImg, x0 + deltaX, y0 + deltaY);
    }
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
//    ofEnableAlphaBlending();
//    OF_BLENDMODE_ADD;
    
    rgbaFboFloat.draw(0, 0);
    
//    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
ofFbo ofApp::createChannel(float r, float g, float b){
    
    ofFbo fbo;
    
    fbo.allocate(300, 300);
    
    fbo.begin();

    ofSetColor(r, g, b);
    ofSetLineWidth(255);
    ofNoFill();
    ofSetCircleResolution(256);
    
    
    ofDrawEllipse(0.5 * fbo.getWidth(), 0.5 * fbo.getHeight(), fbo.getWidth() - 22, fbo.getHeight() - 22);
    

    fbo.end();
    
    
    return fbo;
    
}

void ofApp::drawChannel(ofFbo img, float x, float y){
    
    float u = img.getWidth();
    float v = img.getHeight();
    img.draw( x - 0.5 * u, y - 0.5 * v, u, v );
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
//    redImg.begin();
//    ofClear(255, 255, 255, 0);
//    redImg.end();
//    redImg = createChannel(255, 0, 0);
//    
//    greenImg.begin();
//    ofClear(255, 255, 255, 0);
//    greenImg.end();
//    greenImg = createChannel(0, 255, 0);
//    
//    blueImg.begin();
//    ofClear(255, 255, 255, 0);
//    blueImg.end();
//    blueImg = createChannel(0, 0, 255);
    
    redImg.begin();
    ofClear(255, 255, 255, 0);
    redImg.end();
    redImg = createChannel(0, 255, 255);
    
    greenImg.begin();
    ofClear(255, 255, 255, 0);
    greenImg.end();
    greenImg = createChannel(255, 0, 255);
    
    blueImg.begin();
    ofClear(255, 255, 255, 0);
    blueImg.end();
    blueImg = createChannel(255, 255, 0);
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
