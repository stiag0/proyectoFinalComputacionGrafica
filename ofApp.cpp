#include "ofApp.h"
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {
	ofEnableDepthTest();
	ofSetVerticalSync(true);
	ofBackground(70, 70, 70);
	cam.setDistance(100);

	ofSetWindowTitle("Bezier3D");
	gui.setup();
	gui.add(accuracy.setup("t", 5555, 1, 15000));
	gui.add(clearBtn.setup("erase"));
	gui.add(drawBtn.setup("draw"));

	ofSetFrameRate(60);
	drawPressed = true;
	//anchor_image.load("targetmin.png");
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.draw();
	cam.begin();
	if (clearBtn) {
		drawPressed = false;
		controlPts.clear();
	}

	if (drawBtn)
		drawPressed = true;

	if (drawPressed) {
		std::vector<ofVec3f> end = bezier_curve(controlPts, accuracy);
		if (end.size() > 1) {
			ofSetColor(ofColor::black);
			for (unsigned int i = 0; i < controlPts.size() - 1; ++i) {
				ofDrawLine(controlPts[i].x, controlPts[i].y, controlPts[i + 1].x, controlPts[i + 1].y);
				//anchor_image.draw(controlPts[i].x, controlPts[i].y);
				ofDrawSphere(controlPts[i].x, controlPts[i].y,10);
			}
			ofSetColor(ofColor::blue);
			for (unsigned int i = 0; i < end.size(); ++i) {
				ofCircle(end[i].x, end[i].y, 1);
			}
		}
	}
	
	cam.end();
}

//-----------M----------------------------------

float ofApp::interpolate(float pos1, float pos2, float accuracy) {
	return (1 - accuracy) * pos1 + accuracy * pos2;
}

vector<ofVec3f> ofApp::bezier_curve(vector<ofVec3f>& anchor, float accuracy) {
	if (anchor.size() <= 2)
		return anchor;

	vector<ofVec3f> end;

	for (float i = 0.f; i < accuracy; ++i) {
		float t = i / accuracy;

		vector<ofVec3f> temp(anchor);

		while (temp.size() > 1) {
			vector<ofVec3f> temp2;
			for (unsigned int j = 1; j < temp.size(); ++j)
				temp2.push_back(ofVec3f(interpolate(temp[j - 1].x, temp[j].x, t),
					interpolate(temp[j - 1].y, temp[j].y, t),
					interpolate(temp[j-1].z,temp[j].z,t))
					);
					
			temp.swap(temp2);
		}
		end.push_back(temp.front());
             	}
	return end;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		pintar = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == ' ') {
		pintar = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (pintar) {
		controlPts.push_back(ofVec3f(x, y, 1.0));
		cout << x << y << " ";
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
