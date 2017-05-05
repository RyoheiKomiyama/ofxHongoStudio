//
//  CalibPoints.h
//
//  Created by ryoheikomiyama on 2017/05/05.
//
//
#pragma once

#include <Global.h>
#include "ofMain.h"
#include "ofxCv.h"

namespace ofxHongoStudio
{
    class CalibPoints{
    public:
        
        struct pointset{
            pointset(ofVec3f v): world_point(v),
            world_ori_y(ofVec3f(0, 0, 1)),
            world_ori_z(ofVec3f(0, -1, 0)) {}
            ofVec3f world_point;
            ofVec3f world_ori_y;
            ofVec3f world_ori_z;
            ofVec3f vive_point;
            ofVec3f vive_ori_y;
            ofVec3f vive_ori_z;
            ofVec3f rotvec;
            float angle;
            bool isFinished = false;
        };
        
        vector<pointset> pointsets;
        int target = 0;
        ofMatrix4x4 calibmat;
        bool isCalibrated = false;
        ofColor color = ofColor(127, 127, 127, 127);
        ofColor finished_color = ofColor(0, 255, 0, 127);
        ofColor target_color = ofColor(255, 0, 0, 127);
        
    public:
        CalibPoints() {
            //red
            pointsets.push_back(pointset(ofVec3f(0, 60, -100)/SCALE));
            pointsets.push_back(pointset(ofVec3f(60, 60, -100)/SCALE));
            pointsets.push_back(pointset(ofVec3f(60, 60, -160)/SCALE));
            pointsets.push_back(pointset(ofVec3f(0, 60, -160)/SCALE));
            //yellow
            pointsets.push_back(pointset(ofVec3f(-200, 60, 0)/SCALE));
            pointsets.push_back(pointset(ofVec3f(-140, 60, 0)/SCALE));
            pointsets.push_back(pointset(ofVec3f(-140, 60, -60)/SCALE));
            pointsets.push_back(pointset(ofVec3f(-200, 60, -60)/SCALE));
            //blue
            pointsets.push_back(pointset(ofVec3f(140, 60, 100)/SCALE));
            pointsets.push_back(pointset(ofVec3f(200, 60, 100)/SCALE));
            pointsets.push_back(pointset(ofVec3f(200, 60, 40)/SCALE));
            pointsets.push_back(pointset(ofVec3f(140, 60, 40)/SCALE));
            //ground
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 5; j++) {
                    pointsets.push_back(pointset(ofVec3f(-200 * (1 - i), 0, -100 * (2 - j))/SCALE));
                }
            }
        }
        
        void update(){
            uint64_t t = (ofGetElapsedTimeMillis()/300)%2;
            if(t==0){
                if(pointsets[target].isFinished==true){
                    target_color = finished_color;
                }
                else{
                    target_color = ofColor(255, 0, 0, 127);
                }
            }
            else if(t==1){
                target_color = color;
            }
        }
        
        void draw(){
            for(int i=0; i<pointsets.size(); i++){
                if(i!=target){
                    ofPushStyle();
                    if(pointsets[i].isFinished==true) ofSetColor(finished_color);
                    else ofSetColor(color);
                    ofDrawSphere(pointsets[i].world_point, 5/SCALE);
                    ofPopStyle();
                }
                if(i==target){
                    ofPushStyle();
                    ofSetColor(target_color);
                    ofDrawSphere(pointsets[i].world_point, 5/SCALE);
                    ofPopStyle();
                }
                if (pointsets[i].isFinished == true) {
                    ofPushMatrix();
                    // usual
                    if(!isCalibrated) ofScale(-1, 1, -1);
                    ofTranslate(calibmat*pointsets[i].vive_point);
                    ofRotate(pointsets[i].angle, pointsets[i].rotvec.x,
                             pointsets[i].rotvec.y, pointsets[i].rotvec.z);
                    ofDrawAxis(10/SCALE);
                    ofPopMatrix();
                }
            }
        }
        
        void setValue(ofVec3f pos, ofVec3f rotvec, float angle, ofVec3f ori_y, ofVec3f ori_z) {
            pointsets[target].vive_point = pos;
            pointsets[target].vive_ori_y = ori_y;
            pointsets[target].vive_ori_z = ori_z;
            pointsets[target].rotvec = rotvec;
            pointsets[target].angle = angle;
            pointsets[target].isFinished = true;
            calibrate();
            nextTarget();
        }
        
        void nextTarget(){
            target++;
            if(target==pointsets.size()) target=0;
        }
        
        void calibrate() {
            vector<ofVec3f> ofWps; // world points
            vector<ofVec3f> ofVps; // vive points
            for (int i = 0; i < pointsets.size(); i++) {
                if (pointsets[i].isFinished) {
                    ofWps.push_back(pointsets[i].world_point);
                    ofVps.push_back(pointsets[i].vive_point);
                }
            }
            if (ofWps.size() < 6) return;
            isCalibrated = true;
            
            vector<cv::Point3f> cvWps = ofxCv::toCv(ofWps);
            vector<cv::Point3f> cvVps = ofxCv::toCv(ofVps);
            cv::Mat cvWpsMat(4, cvWps.size(), CV_32F);
            cv::Mat cvVpsMat(4, cvVps.size(), CV_32F);
            for (int i = 0; i < cvWps.size(); i++) {
                cvWpsMat.at<float>(0, i) = cvWps[i].x;
                cvWpsMat.at<float>(1, i) = cvWps[i].y;
                cvWpsMat.at<float>(2, i) = cvWps[i].z;
                cvWpsMat.at<float>(3, i) = 1;
                cvVpsMat.at<float>(0, i) = cvVps[i].x;
                cvVpsMat.at<float>(1, i) = cvVps[i].y;
                cvVpsMat.at<float>(2, i) = cvVps[i].z;
                cvVpsMat.at<float>(3, i) = 1;
            }
            cv::Mat cvVpsMat_t = cvVpsMat.t();
            cv::Mat VVt = cvVpsMat*cvVpsMat_t;
            cv::Mat VVtInv = VVt.inv();
            cv::Mat M = cv::Mat(4, 4, CV_32F);
            M = cvWpsMat*cvVpsMat_t*VVtInv;
            ofMatrix4x4 m((float*)M.data);
            calibmat = m;
            // save calibration matrix
            cv::FileStorage fs(ofToDataPath("")+"calibmat.yml", cv::FileStorage::WRITE);
            fs << "calibmat" << M;
            fs.release();
        }
    };
}
