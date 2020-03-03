#pragma once

#include "ofMain.h"
#include "graphNode.h"
#include "Shapes2D/shapeFactory.h"

// code utilisé pour le dessin des primitives vectorielles:
// https://github.com/philvoyer/IFT3100H19/blob/master/module02/EX04/IFT3100H19_DrawVectorPrimitive

enum class VectorPrimitiveType { none, selection, point, line, rectangle, ellipse, circle, square };

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

	int count;
	int head;
	int stride;
	int size;

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

	VectorPrimitive* shapes;
	VectorPrimitive* selectedShapes;
	ShapeType selectedType = ShapeType::rectangle;

	void setStrokeColor(ofColor color);
	void setFillColor(ofColor color);

	void draw_point(float x, float y, float radius) const;
	void draw_line(float x1, float y1, float x2, float y2) const;
	void draw_rectangle(float x1, float y1, float x2, float y2) const;
	void draw_ellipse(float x1, float y1, float x2, float y2) const;
	void drawSelectionRectangles();

	bool isMouseOutsideCanvas();
	bool isShapeOutsideCanvas(int x1, int x2, int y1, int y2);

	void mousePressed(ofMouseEventArgs & mouse);
	void mouseReleased(ofMouseEventArgs & mouse);
};

