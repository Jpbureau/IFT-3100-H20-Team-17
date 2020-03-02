#pragma once

#include "ofxGui.h"
#include "colorHistogram.h"
#include "textureDrawer.h"

class ColorHistogramGui
{
public:

	ColorHistogramGui(ColorHistogram& histogram, TextureDrawer& textureDrawer);

	void setup(int positionXInitiale, int positionYInitiale);
	void update();
	void updateOnce();
	void draw();

	bool getUpdateHistogram();
	bool getAutomaticUpdate();
	bool getHistogramShown();

private:
	ColorHistogram& colorHistogram;
	TextureDrawer& textureDrawer;

	ofParameter<string> histogramCurrentStatus;
	ofxPanel histogramPanel;
	ofxButton histogramUpdate;
	ofxButton histogramUpdateOnce;
	ofxButton histogramShow;
	ofParameter<int> histogramBinSizeSlider;

	bool automaticUpdate = false;
	bool updateOnceBool = false;
	bool histogramShown = false;

	void toggleAutomaticHistogramUpdate();
	void showHistogram();

};




