#pragma once

#include "ofMain.h"

struct RectangleHistogramme
{
	float                  position1[2];
	float                  position2[2];
	unsigned char          fill_color[4];
};

class ColorHistogram
{
public:
	
	void setup();
	void update();
	void draw();

	void showHistogram(ofPixels& p_pixels, int binSize);

private:
	unsigned int histogram[8][8][8];
	unsigned int histogramBlack;
	unsigned int histogramWhite;

	int positionX = 825;
	int positionY = 800;

	int count;
	int head;
	int stride;
	int size;
	RectangleHistogramme* shapes;
	void draw_rectangle(float x1, float y1, float x2, float y2) const;

};
