#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shader/simple");

    cam.setNearClip(0.01);
    cam.setFarClip(10000);
    cam.setDistance(3);

    // UI
    ui = new ofxUISuperCanvas("SETTINGS");
    ui->setWidgetFontSize(ofxUIWidgetFontType::OFX_UI_FONT_MEDIUM);
    ui->addSpacer();
    ui->addButton("Sample Button", false);
    ui->addSpacer();
    ui->addLabel("SHADER", OFX_UI_FONT_MEDIUM);
    vector<string> vec_shader;
    vec_shader.push_back("simple");
    vec_shader.push_back("time");
    radio_shader = ui->addRadio("SHADER", vec_shader, OFX_UI_ORIENTATION_HORIZONTAL, OFX_UI_FONT_MEDIUM);
    radio_shader->activateToggle("simple");
    ui->setColorBack(ofxUIColor(100, 100, 100, 128));
    ui->autoSizeToFitWidgets();
    ofAddListener(ui->newGUIEvent, this, &ofApp::guiEvent);
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
    
    ofEnableDepthTest();
    ofEnableAlphaBlending();

    if(radio_shader->getActiveName()=="simple"){
        shader.begin();
        shader.setUniformMatrix4f("modelToWorld", modelToWorld);
        shader.setUniformMatrix4f("worldToCamera", worldToCamera);
        shader.setUniformMatrix4f("cameraToView", cameraToView);
        staticCgScene.draw();
        staticCgScene.drawBlackWireFrame();
        shader.end();
    }
    
    ofDisableAlphaBlending();
    ofDisableDepthTest();
    
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    if (kind == OFX_UI_WIDGET_BUTTON)
    {
        ofxUIButton *button = (ofxUIButton *)e.widget;
        if (name == "Sample Button" && button->getValue() == 0) { // button released
            cout << "Sample Button" << endl;
        }
    }
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
