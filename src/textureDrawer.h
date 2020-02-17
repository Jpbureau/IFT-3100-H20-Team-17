#pragma once

#include "ofMain.h"

// code utilisé pour le dessin des primitives vectorielles:
// https://github.com/philvoyer/IFT3100H19/blob/master/module02/EX04/IFT3100H19_DrawVectorPrimitive

enum class VectorPrimitiveType { none, selection, point, line, rectangle, ellipse };

struct VectorPrimitive
{
	VectorPrimitiveType type;
	float                  position1[2];
	float                  position2[2];
	float                  stroke_width;
	unsigned char          stroke_color[4];
	unsigned char          fill_color[4];
	float				   radius;
	bool				   selected;
};

class TextureDrawer
{
public:
	void setup();
	void draw();

	int mouse_pressed_posX;
	int mouse_pressed_posY;
	int mouse_current_posX;
	int mouse_current_posY;

	void selectPointType();
	void selectLineType();
	void selectRectangleType();
	void selectEllipseType();

	void add_vector_shape();

	void updateColors(ofColor stroke, ofColor fill);

private:
	int count;
	int head;
	int stride;
	int size;

	float stroke_width_default;
	float radius;

	unsigned char stroke_color_r;
	unsigned char stroke_color_g;
	unsigned char stroke_color_b;
	unsigned char stroke_color_a;

	unsigned char fill_color_r;
	unsigned char fill_color_g;
	unsigned char fill_color_b;
	unsigned char fill_color_a;

	VectorPrimitive* shapes;
	VectorPrimitiveType selectedType;

	void setStrokeColor(ofColor color);
	void setFillColor(ofColor color);

	void draw_point(float x, float y, float radius) const;
	void draw_line(float x1, float y1, float x2, float y2) const;
	void draw_rectangle(float x1, float y1, float x2, float y2) const;
	void draw_ellipse(float x1, float y1, float x2, float y2) const;
};

