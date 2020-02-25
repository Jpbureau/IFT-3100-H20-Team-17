#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetWindowPosition(0, 30);
	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight() - 30);
	renderer.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();
	recorder.listen();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'r':
		recorder.toggleRecording();
		break;
	default:
		break;
	}
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
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}