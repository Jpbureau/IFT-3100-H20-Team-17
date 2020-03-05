#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetWindowPosition(0, 30);
	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight() - 30);

	//Initialisation des touches pour le mouvement de la caméra
	is_key_press_up = false;
	is_key_press_down = false;
	is_key_press_left = false;
	is_key_press_right = false;

	is_key_press_a = false;
	is_key_press_s = false;
	is_key_press_d = false;
	is_key_press_w = false;

	renderer.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

	camera.is_camera_move_forward = is_key_press_up || is_key_press_w;
	camera.is_camera_move_backward = is_key_press_down || is_key_press_s;
	camera.is_camera_move_left = is_key_press_left || is_key_press_a;
	camera.is_camera_move_right = is_key_press_right || is_key_press_d;

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

	case 'a':
		is_key_press_a = true;
		break;

	case 's':
		is_key_press_s = true;
		break;

	case 'd':
		is_key_press_d = true;
		break;

	case 'w':
		is_key_press_w = true;
		break;
		
	case OF_KEY_LEFT:
		is_key_press_left = true;
		break;

	case OF_KEY_UP:
		is_key_press_up = true;
		break;

	case OF_KEY_RIGHT:
		is_key_press_right = true;
		break;

	case OF_KEY_DOWN:
		is_key_press_down = true;
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key)
	{
	case 'a':
		is_key_press_a = false;
		break;

	case 's':
		is_key_press_s = false;
		break;

	case 'd':
		is_key_press_d = false;
		break;

	case 'w':
		is_key_press_w = false;
		break;

	case OF_KEY_LEFT:
		is_key_press_left = false;
		break;

	case OF_KEY_UP:
		is_key_press_up = false;
		break;

	case OF_KEY_RIGHT:
		is_key_press_right = false;
		break;

	case OF_KEY_DOWN:
		is_key_press_down = false;
		break;

	default:
		break;
	}
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
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}