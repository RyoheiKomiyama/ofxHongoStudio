#pragma once

#include "ofMain.h"
#include "ofxHongoStudio.h"

class ofApp : public ofBaseApp{
    
    ofShader shader;
    ofxHongoStudio::StaticCGScene staticCgScene;
    ofEasyCam cam;
    
    ofMatrix4x4 modelToWorld;
    ofMatrix4x4 worldToCamera;
    ofMatrix4x4 cameraToView;

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
		
};
