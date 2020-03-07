#pragma once

#include "ofxGui.h"
#include "colorHistogram.h"
#include "textureDrawer.h"

class ColorHistogramGui
{
public:

	ColorHistogramGui(ColorHistogram& histogram, TextureDrawer& textureDrawer);

	void setup(int positionXInitiale, int positionYInitiale, int histogramXPosition, int histogramYPosition, int histogramWidth, int histogramHeight);
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

	ofParameter<int> histogramWidthSlider;
	ofParameter<int> histogramHeightSlider;
	ofParameter<int> histogramXPositionSlider;
	ofParameter<int> histogramYPositionSlider;

	bool automaticUpdate = false;
	bool updateOnceBool = false;
	bool histogramShown = false;

	void toggleAutomaticHistogramUpdate();
	void showHistogram();

};




