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
	
	void setup(int width, int height, int positionX, int positionY);
	void update();
	void draw();

	void showHistogram(ofPixels& p_pixels, int binSize);

private:
	unsigned int histogram[8][8][8];
	unsigned int histogramBlack;
	unsigned int histogramWhite;

	int m_positionX;
	int m_positionY;

	int m_width;
	int m_height;

	int count;
	int head;
	int stride;
	int size;
	RectangleHistogramme* shapes;
	void draw_rectangle(float x1, float y1, float x2, float y2) const;

};
