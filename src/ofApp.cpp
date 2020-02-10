#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	boutonDessiner.addListener(this, &ofApp::boutonDessinerPressed);
	x1.addListener(this, &ofApp::paramX1Changed);
	y1.addListener(this, &ofApp::paramY1Changed);
	x2.addListener(this, &ofApp::paramX2Changed);
	y2.addListener(this, &ofApp::paramY2Changed);

	renderer.setup();

	/*groupeLigne.setName("param");
	groupeLigne.add(paramX1.set("x1", 0, 0, 100));
	groupeLigne.add(paramX2.set("x2", 0, 0, 100));
	groupeLigne.add(paramY1.set("y1", 0, 0, 100));
	groupeLigne.add(paramY2.set("y2", 0, 0, 100));

	pannelPrimitive.setup(groupeLigne);*/

	group_primitives.setup("Primitives Vectorielles");
	group_ligne.setup("Ligne");
	group_cercle.setup("Cercle");
	group_rectangle.setup("Rectangle");

	//group_primitives.add(group_ligne);

	group_ligne.add(x1.setup("x1", 5, 3, 90));
	group_ligne.add(y1.setup("y1", 5, 3, 90));
	group_ligne.add(x2.setup("x2", 5, 3, 90));
	group_ligne.add(y2.setup("y2", 5, 3, 90));
	group_ligne.add(boutonDessiner.setup("Dessiner"));

	group_cercle.add(centreX.setup("x", 5, 3, 90));
	group_cercle.add(centreY.setup("y", 5, 3, 90));
	group_cercle.add(boutonDessiner.setup("Dessiner"));

	group_rectangle.add(x1.setup("x", 0, 3, 90));
	group_rectangle.add(y1.setup("y", 0, 3, 90));
	group_rectangle.add(largeur.setup("largeur", 0, 3, 90));
	group_rectangle.add(hauteur.setup("hauteur", 0, 3, 90));
	group_rectangle.add(boutonDessiner.setup("Dessiner"));
	
	pannelPrimitive.setup("Primitives Vectorielles");
	pannelPrimitive.add(&group_ligne);
	pannelPrimitive.add(&group_cercle);
	pannelPrimitive.add(&group_rectangle);
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