#pragma once

#include "ofMain.h"
#define CONVOLUTION_MAT_SIZE 49

class ofApp : public ofBaseApp {
	public:

            ofImage testPattern;
            ofImage palette;
            ofImage rectangle;

            float convolutionMatrix[CONVOLUTION_MAT_SIZE];

            ofShader paletteShader;
            ofShader convolutionShader;
            
            ofFbo screen;
            ofFbo backFbo;
            ofFbo frontFbo;
            
            bool changed = true;
		
            void normalizeConvolution();
            void randomChangeConvolution();
            void randomizeConvolution();
            
            void setup();
            void update();
            void draw();

            void keyPressed(int key);
            void keyReleased(int key);
            void mouseMoved(int x, int y);
            void mouseDragged(int x, int y, int button);
            void mousePressed(int x, int y, int button);
            void mouseReleased(int x, int y, int button);
            void mouseEntered(int x, int y);
            void mouseExited(int x, int y);
            void windowResized(int w, int h);
            void dragEvent(ofDragInfo dragInfo);
            void gotMessage(ofMessage msg);

};
