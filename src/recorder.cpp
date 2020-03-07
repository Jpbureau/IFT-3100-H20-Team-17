#include "recorder.h"

void Recorder::setup()
{
	isRecording.addListener(this, &Recorder::recordingTogglePressed);
}

void Recorder::listen()
{
	// On ne conserve qu'une frame sur 3 -> donne 20 fps quand on enregistre a 60 fps
	if (isRecording && ofGetFrameNum() % 3 == 0) {
		ofImage frame;
		frame.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		frames.push_back(frame);
	}
}

ofParameter<bool>& Recorder::getIsRecording()
{
	return isRecording;
}

void Recorder::recordingTogglePressed(bool & r)
{
	if (!r && frames.size() != 0) {
		saveFrames();
	}
}

void Recorder::saveFrames()
{
	string time_stamp = ofGetTimestampString("%y%m%d-%H%M%S-%i");
	int i = 0;
	for (ofImage frame : frames)
	{
		string file_name = "recorder/" + time_stamp + "/" + to_string(i) + ".png";
		frame.save(file_name);
		i++;
	}

	frames.clear();
}
