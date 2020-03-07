#pragma once

#include "ofMain.h"

class Recorder {
public:
	void setup();
	void listen();

	ofParameter<bool>& getIsRecording();

private:
	ofParameter<bool> isRecording;
	void recordingTogglePressed(bool& r);

	vector<ofImage> frames;

	void saveFrames();
};