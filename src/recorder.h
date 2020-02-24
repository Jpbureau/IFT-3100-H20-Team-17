#pragma once

#include "ofMain.h"

class Recorder {
public:
	void listen();
	void startRecording();
	void stopRecording();
	void toggleRecording();

private:
	bool isRecording = false;
	vector<ofImage> frames;

	void saveFrames();
};