#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(false);
    ofSetFrameRate(90);
    
    shader_simple.load("shader/simple");
    shader_height.load("shader/height.vert", "shader/simple.frag");
    shader_fake_noise.load("shader/fake_noise.vert", "shader/simple.frag");
    shader_color_noise.load("shader/simple.vert", "shader/color_noise.frag");
    
    ofx::ObjLoader::load("model/hongo_studio_bad03.obj", objMesh);

    cam.setNearClip(0.001);
    cam.setFarClip(10000);
    cam.setDistance(3);

    // UI
    ui = new ofxUISuperCanvas("SETTINGS");
    ui->setWidgetFontSize(ofxUIWidgetFontType::OFX_UI_FONT_MEDIUM);
    // ui shader
    ui->addSpacer();
    ui->addLabel("SHADERS", OFX_UI_FONT_MEDIUM);
    vector<string> vec_shader;
    vec_shader.push_back("simple");
    vec_shader.push_back("height");
    vec_shader.push_back("fake_noise");
    vec_shader.push_back("color_noise");
    radio_shader = ui->addRadio("SHADER", vec_shader, OFX_UI_ORIENTATION_HORIZONTAL, OFX_UI_FONT_MEDIUM);
    radio_shader->activateToggle("simple");
    // ui slidebar
    ui->addSpacer();
    ui->addLabel("MODELS", OFX_UI_FONT_MEDIUM);
    ui->addButton("Static CG", false);
    ui->addSlider("Static CG", 0, 1, &alpha_staticCgScene)->setLabelVisible(false);
    ui->addButton("Obj", false);
    ui->addSlider("Obj", 0, 1, &alpha_objMesh)->setLabelVisible(false);
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

    ofShader* shader;
    if(radio_shader->getActiveName()=="simple") shader = &shader_simple;
    else if(radio_shader->getActiveName()=="height") shader = &shader_height;
    else if(radio_shader->getActiveName()=="fake_noise") shader = &shader_fake_noise;
    else if(radio_shader->getActiveName()=="color_noise") shader = &shader_color_noise;
    
    shader->begin();
    shader->setUniformMatrix4f("modelToWorld", modelToWorld);
    shader->setUniformMatrix4f("worldToCamera", worldToCamera);
    shader->setUniformMatrix4f("cameraToView", cameraToView);
    shader->setUniform1f("elapsedTime", ofGetElapsedTimef());
    if(alpha_staticCgScene>0.01){
        shader->setUniform1f("alpha", alpha_staticCgScene);
        staticCgScene.draw();
        staticCgScene.drawBlackWireFrame();
    }
    if(alpha_objMesh>0.01){
        shader->setUniform1f("alpha", alpha_objMesh);
        objMesh.draw();
    }
    shader->end();
    
    ofDisableDepthTest();
    ofDisableAlphaBlending();
    
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 20, ofGetHeight()-20);
    
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    if(kind == OFX_UI_WIDGET_BUTTON)
    {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        if(name=="Static CG" && button->getValue()==0){ // button released
            alpha_staticCgScene = 1;
            alpha_objMesh = 0;
        }
        else if(name=="Obj" && button->getValue()==0){ // button released
            alpha_staticCgScene = 0;
            alpha_objMesh = 1;
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
