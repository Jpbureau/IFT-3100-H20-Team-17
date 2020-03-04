#pragma once

#include "ofMain.h"
#include "graphNode.h"
#include "Shapes2D/shapeFactory.h"

class TextureDrawer
{
public:
	void setup(int drawingCanvasX, int drawingCanvasY, int drawingCanvasSize);
	void draw();
	void update();

	int mouse_pressed_posX;
	int mouse_pressed_posY;
	int mouse_current_posX;
	int mouse_current_posY;

	bool isMouseInsideCanvas(int x, int y);

	void selectPointType();
	void selectLineType();
	void selectRectangleType();
	void selectSquareType();
	void selectEllipseType();
	void selectCircleType();
	void selectSelectionType();
	void deleteSelectedShapes();

	void selectShape(int x, int y);

	void add_vector_shape();

	void updateColors(ofColor stroke, ofColor fill);
	void updateStrokeWeight(float newWeight);
	void updateRadius(float newRadius); 

	void resetSelection();

	ofImage grabCanvasScreen();

private:
	GraphNode root;
	ShapeFactory shapeFactory;

	int drawingCanvasSize;
	int drawingCanvasX;
	int drawingCanvasY;

	float stroke_width;
	float radius;

	unsigned char stroke_color_r;
	unsigned char stroke_color_g;
	unsigned char stroke_color_b;
	unsigned char stroke_color_a;

	unsigned char fill_color_r;
	unsigned char fill_color_g;
	unsigned char fill_color_b;
	unsigned char fill_color_a;

	ShapeType selectedType = ShapeType::rectangle;

	void setStrokeColor(ofColor color);
	void setFillColor(ofColor color);

	void drawSelectionRectangles();

	bool isMouseOutsideCanvas();

	void mousePressed(ofMouseEventArgs & mouse);
	void mouseReleased(ofMouseEventArgs & mouse);
};

