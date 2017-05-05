#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shader/simple");
    
    ofx::ObjLoader::load("model/hongo_studio_bad03.obj", objMesh);

    cam.setNearClip(0.001);
    cam.setFarClip(10000);
    cam.setDistance(3);

    // UI
    ui = new ofxUISuperCanvas("SETTINGS");
    ui->setWidgetFontSize(ofxUIWidgetFontType::OFX_UI_FONT_MEDIUM);
    ui->addSpacer();
    ui->addButton("Sample Button", false);
    ui->addSpacer();
    // ui shader
    ui->addLabel("SHADER", OFX_UI_FONT_MEDIUM);
    vector<string> vec_shader;
    vec_shader.push_back("simple");
    vec_shader.push_back("time");
    radio_shader = ui->addRadio("SHADER", vec_shader, OFX_UI_ORIENTATION_HORIZONTAL, OFX_UI_FONT_MEDIUM);
    radio_shader->activateToggle("simple");
    // ui slidebar
    ui->addSlider("Static CG", 0, 1, &alpha_staticCgScene);
    ui->addSlider("Obj", 0, 1, &alpha_objMesh);
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
    
    ofEnableAlphaBlending();
    ofEnableDepthTest();

    if(radio_shader->getActiveName()=="simple"){
        if(alpha_staticCgScene>0.01){
            shader.begin();
            shader.setUniformMatrix4f("modelToWorld", modelToWorld);
            shader.setUniformMatrix4f("worldToCamera", worldToCamera);
            shader.setUniformMatrix4f("cameraToView", cameraToView);
            shader.setUniform1f("alpha", alpha_staticCgScene);
            staticCgScene.draw();
            staticCgScene.drawBlackWireFrame();
            shader.end();
        }
        if(alpha_objMesh>0.01){
            shader.begin();
            shader.setUniformMatrix4f("modelToWorld", modelToWorld);
            shader.setUniformMatrix4f("worldToCamera", worldToCamera);
            shader.setUniformMatrix4f("cameraToView", cameraToView);
            shader.setUniform1f("alpha", alpha_objMesh);
            objMesh.draw();
            shader.end();
        }
    }
    
    ofDisableDepthTest();
    ofDisableAlphaBlending();
    
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
