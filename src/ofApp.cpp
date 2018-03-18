#include "ofApp.h"
#include <algorithm>


std::string getFrameFilename() {
    static int frame_n = 0;
    if(frame_n > 9999)
        return "";
    
    std::string filename = "frames/frame" + ofToString(frame_n) + ".png";
    frame_n++;
    return filename;
}


void createTestPattern(ofImage& img) {
    ofVec2f middle(img.getWidth()/2 -0.5, img.getHeight()/2 -0.5);
    for(int y=0; y<img.getHeight(); y++) {
        for(int x=0; x<img.getWidth(); x++) {
            float r = (ofVec2f(x,y) - middle).length() / (img.getWidth()/2);
            r *= 255;
            ofColor c(r,r,r);
            img.setColor(x, y, c);
        }
    }
    img.update();
}

void createPalette(ofImage& img) {
    for(int x=0; x<img.getWidth(); x++) {
        float val = (float)x / img.getWidth();
        
        float r = ofClamp(pow(val, 0.5), 0, 1);
        float g = ofClamp(val, 0, 1);
        float b = ofClamp(0.3 + pow(0.7*val, 1.5), 0, 1);

        ofColor c(r*255, g*255, b*255);
        img.setColor(x, 0, c);
    }
    img.update();
}


void drawRandomCircle(int x, int y) {
    ofDrawCircle(x, y, ofRandom(5) );
}


void ofApp::normalizeConvolution() {
    float sum = 0;
    for(int i=0; i < CONVOLUTION_MAT_SIZE; i++) {
        sum += convolutionMatrix[i];
    }
    
    float factor = 1 / sum;

    for(int i=0; i < CONVOLUTION_MAT_SIZE; i++) {
        convolutionMatrix[i] *= factor;
    }
}


void ofApp::randomizeConvolution() {
    for(int i=0; i<CONVOLUTION_MAT_SIZE; i++) {
        convolutionMatrix[i] = ofRandom(-1,1);
    }
    normalizeConvolution();
}


void ofApp::randomChangeConvolution() {
    int n = ofRandom(1, 3);
    
    for(int j=0; j<n; j++){
        int i = ofRandom(0, CONVOLUTION_MAT_SIZE);
        convolutionMatrix[i] += ofRandom(-0.03, 0.03);
        convolutionMatrix[i] = ofClamp(convolutionMatrix[i], -1, 1);
    }
    normalizeConvolution();
}


//--------------------------------------------------------------
void ofApp::setup(){

    testPattern.load("testPattern.png");
    palette.load("palette.png");
    
    int w = 640;
    int h = 479;
    
    screen.allocate(w,h);    
    backFbo.allocate(w,h);
    frontFbo.allocate(w,h);

    paletteShader.load("default.vertexShader", "palette.fragmentShader");
    convolutionShader.load("default.vertexShader", "convolution.fragmentShader");
    
    paletteShader.begin();
        paletteShader.setUniformTexture("palette", palette, 2);
    paletteShader.end();
        
    
    randomizeConvolution();
    
    ofSetBackgroundAuto(false);
    ofSetFrameRate(60);
    ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::update(){    
    randomChangeConvolution();
    if(ofRandom(5000) <= 1)
        randomizeConvolution();

    convolutionShader.begin();
        convolutionShader.setUniform1fv("convolutionMatrix", convolutionMatrix, CONVOLUTION_MAT_SIZE);
    convolutionShader.end();
    
    backFbo.begin();
    convolutionShader.begin();
        convolutionShader.setUniformTexture("tex", frontFbo.getTextureReference(), 1);
        frontFbo.draw(0, 0);
    convolutionShader.end();
    drawRandomCircle(backFbo.getWidth()/2, backFbo.getHeight()/2);
    backFbo.end();
    
    frontFbo.begin();
    convolutionShader.begin();
        convolutionShader.setUniformTexture("tex", backFbo.getTextureReference(), 1);
        backFbo.draw(0, 0);
    convolutionShader.end();
    frontFbo.end();    

    screen.begin();
    paletteShader.begin();
        paletteShader.setUniformTexture("tex", frontFbo.getTextureReference(), 1);
        frontFbo.draw(0, 0, screen.getWidth(), screen.getHeight() );
    paletteShader.end();
    screen.end();

}

//--------------------------------------------------------------
void ofApp::draw(){
    screen.draw(0,0,ofGetWidth(), ofGetHeight() );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    randomizeConvolution();
    changed = true;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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