#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	renderer.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	ofLog() << "<app::keyReleased: " << key << ">";

	// valider si la touche du clavier est la barre d'espacement (spacebar)
	if (key == '1')
		fileManager.image_export("render", "png", "high");
	else if (key == '2') {
		fileManager.image_export("render", "png", "medium");
	}
	else if (key == '3') {
		fileManager.image_export("render", "png", "low");
	} else {
		fileManager.image_export("render", "png", "");
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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
