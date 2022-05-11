#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	ofNoFill();
	ofColor color;
	for (int k = 0; k < 350; k++) {

		ofPushMatrix();
		ofRotateZ(ofRandom(360));
		ofRotateY(ofRandom(360));
		ofRotateX(ofRandom(360));

		auto location = glm::vec3(0, 0, 250);
		int max_radius = ofRandom(130, 180);
		auto radius = (int)(ofRandom(1000) + ofGetFrameNum() * 1) % max_radius - 100;

		if (radius > 0) {

			ofMesh mesh;
			mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

			for (int deg = 0; deg < 144 * 5; deg += 144) {

				auto vertex = location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
				vertex = glm::normalize(vertex) * 250;

				mesh.addVertex(vertex);

				color.setHsb(ofRandom(255), 180, 255);
				color = ofColor(color, radius > 25 ? ofMap(radius, 25, max_radius - 100, 255, 0) : 255);
				
				mesh.addColor(color);

				if (deg > 0) {

					mesh.addIndex(mesh.getNumVertices() - 1);
					mesh.addIndex(mesh.getNumVertices() - 2);
				}
			}

			mesh.addIndex(0);
			mesh.addIndex(mesh.getNumVertices() - 1);

			mesh.drawWireframe();
		}
		else {

			for (int deg = 0; deg < 144 * 5; deg += 144) {

				color.setHsb(ofRandom(255), 255, 255);
				color = ofColor(color, radius > 25 ? ofMap(radius, 25, 80, 255, 0) : 255);
			}
		}

		ofPopMatrix();
	}

	ofFill();
	ofSetColor(0);
	ofDrawSphere(245);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}