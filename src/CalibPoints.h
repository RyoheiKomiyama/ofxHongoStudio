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
	class CalibColorBox {

		ofMesh mesh;
		ofFloatColor color;
		ofVec3f pos;

	public:
		CalibColorBox(ofFloatColor color, ofVec3f pos, float box_size = 5 / SCALE) {

			// color, pos
			this->color = color;
			this->pos = pos;

			// vertices
			float half_box_size = box_size / 2;
			vector<ofVec3f> vertices = {
				ofVec3f(-half_box_size, -half_box_size, -half_box_size) + pos,
				ofVec3f(-half_box_size, half_box_size, -half_box_size) + pos,
				ofVec3f(half_box_size, half_box_size, -half_box_size) + pos,
				ofVec3f(half_box_size, -half_box_size, -half_box_size) + pos,
				ofVec3f(-half_box_size, -half_box_size, half_box_size) + pos,
				ofVec3f(-half_box_size, half_box_size, half_box_size) + pos,
				ofVec3f(half_box_size, half_box_size, half_box_size) + pos,
				ofVec3f(half_box_size, -half_box_size, half_box_size) + pos
			};
			mesh.addVertices(vertices);

			vector<ofFloatColor> colors;
			for (int i = 0; i < vertices.size(); i++) {
				colors.push_back(color);
			}
			mesh.addColors(colors);

			// triangle
			mesh.addTriangle(0, 1, 2);
			mesh.addTriangle(0, 2, 3);
			mesh.addTriangle(4, 5, 1);
			mesh.addTriangle(4, 1, 0);
			mesh.addTriangle(7, 6, 5);
			mesh.addTriangle(7, 5, 4);
			mesh.addTriangle(3, 2, 6);
			mesh.addTriangle(3, 6, 7);
			mesh.addTriangle(1, 5, 6);
			mesh.addTriangle(1, 6, 2);
			mesh.addTriangle(4, 0, 3);
			mesh.addTriangle(4, 3, 7);
		}

		void update() {}

		void draw() {
			mesh.draw();
		}

		void drawWireFrame() {
			mesh.drawWireframe();
		}

	};


	static void drawAxis(float length = 12, float size = 2)
	{
		ofxHongoStudio::CalibColorBox(ofFloatColor(1, 1, 1, 1), ofVec3f(0, 0, 0) / SCALE, size / SCALE).draw();
		ofxHongoStudio::CalibColorBox(ofFloatColor(1, 0, 0, 1), ofVec3f(length, 0, 0) / SCALE, size / SCALE).draw();
		ofxHongoStudio::CalibColorBox(ofFloatColor(0, 1, 0, 1), ofVec3f(0, length, 0) / SCALE, size / SCALE).draw();
		ofxHongoStudio::CalibColorBox(ofFloatColor(0, 0, 1, 1), ofVec3f(0, 0, length) / SCALE, size / SCALE).draw();
		ofxHongoStudio::CalibColorBox(ofFloatColor(1, 0, 0, 1), ofVec3f(length, 0, 0) / SCALE / 2, size / SCALE).draw();
		ofxHongoStudio::CalibColorBox(ofFloatColor(0, 1, 0, 1), ofVec3f(0, length, 0) / SCALE / 2, size / SCALE).draw();
		ofxHongoStudio::CalibColorBox(ofFloatColor(0, 0, 1, 1), ofVec3f(0, 0, length) / SCALE / 2, size / SCALE).draw();
	}


    class CalibPoints{
    public:
        
        struct pointset{
            pointset(ofVec3f v): world_point(v){}
            ofVec3f world_point;
            ofVec3f vive_point;
			ofMatrix4x4 posemat;
            bool isFinished = false;
        };
        
        vector<pointset> pointsets;
        int target = 0;
		ofMatrix4x4 calibmat_before;
        ofMatrix4x4 calibmat_after;
        bool isCalibrated = false;
        ofFloatColor color = ofFloatColor(0.5, 0.5, 0.5, 0.5);
        ofFloatColor finished_color = ofFloatColor(0, 1, 0, 0.5);
        ofFloatColor target_color = ofFloatColor(1, 0, 0, 0.5);
        
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

			// calibmat_before
			ofMatrix4x4 rx;
			rx.makeRotationMatrix(90, 1, 0, 0);
			ofMatrix4x4 ry;
			ry.makeRotationMatrix(180, 0, 1, 0);
			calibmat_before = rx * ry;
        }
        
        void update(){
            uint64_t t = (ofGetElapsedTimeMillis()/300)%2;
            if(t==0){
                if(pointsets[target].isFinished==true){
                    target_color = finished_color;
                }
                else{
                    target_color = ofFloatColor(1, 0, 0, 0.5);
                }
            }
            else if(t==1){
                target_color = color;
            }
        }
        
        void draw(ofShader& shader){
            for(int i=0; i<pointsets.size(); i++){
				if (i != target) {
					if (pointsets[i].isFinished == true) {
						shader.setUniformMatrix4f("modelToWorld", ofMatrix4x4());
						ofxHongoStudio::CalibColorBox(finished_color, pointsets[i].world_point).draw();
					}
					else {
						shader.setUniformMatrix4f("modelToWorld", ofMatrix4x4());
						ofxHongoStudio::CalibColorBox(color, pointsets[i].world_point).draw();
					}
				}
                if(i==target){
					shader.setUniformMatrix4f("modelToWorld", ofMatrix4x4());
					ofxHongoStudio::CalibColorBox(target_color, pointsets[i].world_point).draw();
				}
                if (pointsets[i].isFinished == true) { //axis
					shader.setUniformMatrix4f("modelToWorld", calibmat_before*pointsets[i].posemat*calibmat_after);
					//shader.setUniformMatrix4f("modelToWorld", pointsets[i].posemat*calibmat_after);
					ofxHongoStudio::drawAxis();
                }
            }
        }
        
        void setValue(ofMatrix4x4 posemat, ofVec3f pos) {
			pointsets[target].posemat = posemat;
            pointsets[target].vive_point = pos;
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
					// pos
                    ofWps.push_back(pointsets[i].world_point);
					ofVps.push_back((ofVec3f(0, 0, 0) / SCALE)*pointsets[i].posemat);
                    //ofVps.push_back(pointsets[i].vive_point);
					// x
					ofWps.push_back(pointsets[i].world_point + (ofVec3f(1, 0, 0) / SCALE));
					ofVps.push_back((ofVec3f(-1, 0, 0) / SCALE)*pointsets[i].posemat);
					// y
					ofWps.push_back(pointsets[i].world_point + (ofVec3f(0, 1, 0) / SCALE));
					ofVps.push_back((ofVec3f(0, 1, 0) / SCALE)*pointsets[i].posemat);
					// z
					ofWps.push_back(pointsets[i].world_point + (ofVec3f(0, 0, 1) / SCALE));
					ofVps.push_back((ofVec3f(0, 0, 1) / SCALE)*pointsets[i].posemat);
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
			M = M.t();
            ofMatrix4x4 m((float*)M.data);
            calibmat_after = m;
            // save calibration matrix
            cv::FileStorage fs(ofToDataPath("")+"calibmat.yml", cv::FileStorage::WRITE);
            fs << "calibmat_after" << M;
            fs.release();
        }
    };
}
