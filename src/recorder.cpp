#include "recorder.h"

void Recorder::listen()
{
	if (isRecording) {
		ofImage frame;
		frame.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		frames.push_back(frame);
	}
}

void Recorder::startRecording()
{
	isRecording = true;
}

void Recorder::stopRecording()
{
	isRecording = false;
	saveFrames();
}

void Recorder::toggleRecording()
{
	if (!isRecording) {
		startRecording();
	}
	else {
		stopRecording();
	}
}

void Recorder::saveFrames()
{
	string time_stamp = ofGetTimestampString("%y%m%d-%H%M%S-%i");
	int i = 0;
	int j = 0;
	for (ofImage frame : frames)
	{
		// On ne conserve qu'une frame sur 3 -> donne 20 fps quand on enregistre a 60 fps
		if (i % 3 == 0) {
			string file_name = "recorder/" + time_stamp + "/" + to_string(j) + ".png";
			frame.save(file_name);
			j++;
		}
		i++;
	}

	frames.clear();
}
