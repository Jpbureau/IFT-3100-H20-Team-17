#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetBackgroundColor(31);
	renderer.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();
	pannelPrimitive.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	renderer.cursor.setPosition(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	renderer.cursor.setPosition(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	renderer.cursor.setPosition(x, y);
	renderer.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	renderer.cursor.setPosition(x, y);
	renderer.mouseReleased(x, y);
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

void ofApp::paramX1Changed(int &p_x1) {
	//ofSetCircleResolution(p_x1);
	cout << this->x1 << endl;
	//cout << p_x1 << endl;
}

void ofApp::paramY1Changed(int &p_y1) {
	//ofSetCircleResolution(p_x1);
	//cout << this->x1 << endl;
	//cout << p_x1 << endl;
}

void ofApp::paramX2Changed(int &p_x2) {
	//ofSetCircleResolution(p_x1);
	//cout << this->x1 << endl;
	//cout << p_x1 << endl;
}

void ofApp::paramY2Changed(int &p_y2) {
	//ofSetCircleResolution(p_x1);
	//cout << this->x1 << endl;
	//cout << p_x1 << endl;
}

void ofApp::boutonDessinerPressed() {
	ofDrawLine(x1, y1, x2, y2);
	//renderer.draw();
	if (typePrimitive.compare("Ligne") == 0)
	{
		ofDrawLine(x1, y1, x2, y2);
	}

	//ofSetCircleResolution(p_x1);
	//cout << this->x1 << endl;
	//cout << p_x1 << endl;
}