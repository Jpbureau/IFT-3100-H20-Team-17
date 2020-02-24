#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "fileManager.h"
#include "recorder.h"

class ofApp : public ofBaseApp{
public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void boutonDessinerPressed();
	void paramX1Changed(int & p_x1);
	void paramY1Changed(int & p_y1);
	void paramX2Changed(int & p_x2);
	void paramY2Changed(int & p_y2);

private:
	Renderer renderer;
	Recorder recorder;

	ofxPanel pannelPrimitive;
	ofxGuiGroup group_primitives;
	ofxGuiGroup group_ligne;
	ofxGuiGroup group_cercle;
	ofxGuiGroup group_rectangle;

	ofParameter<string> ligne;
	ofParameter<string> cercle;
	ofParameter<string> rectangle;

	ofParameter<int> paramX1;
	ofParameter<int> paramY1;
	ofParameter<int> paramX2;
	ofParameter<int> paramY2;

	ofxIntField x1;
	ofxIntField y1;
	ofxIntField x2;
	ofxIntField y2;
	ofxIntField centreX;
	ofxIntField centreY;
	ofxIntField rayon;
	ofxIntField largeur;
	ofxIntField hauteur;

	string typePrimitive;

	ofxButton boutonDessiner;
};
