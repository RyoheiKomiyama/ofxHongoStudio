#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shader/simple");

    cam.setNearClip(0.01);
    cam.setFarClip(10000);
    cam.setDistance(3);

    ofEnableDepthTest();
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
    // update camera
    cam.begin();
    cam.end();
    
    // update matrix
    modelToWorld.makeIdentityMatrix();
    worldToCamera = cam.getModelViewMatrix();
    cameraToView = cam.getProjectionMatrix();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    shader.begin();
    shader.setUniformMatrix4f("modelToWorld", modelToWorld);
    shader.setUniformMatrix4f("worldToCamera", worldToCamera);
    shader.setUniformMatrix4f("cameraToView", cameraToView);
    staticCgScene.draw();
    staticCgScene.drawBlackWireFrame();
    shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
