#pragma once

#include "ofMain.h"
#include "graphNode.h"
#include "Shapes2D/shapeFactory.h"
#include "sceneGraph2dGui.h"

enum DrawerOptions { draw, select, translate, scale };

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
	bool isTypeSelection();
	bool isTypeTranslation();

	string getCurrentlySelectedType();

	void selectPointType();
	void selectLineType();
	void selectRectangleType();
	void selectSquareType();
	void selectEllipseType();
	void selectCircleType();
	void selectImageType(ofImage image);
	void selectSelectionType();
	void selectTranslateType();
	void selectScaleType();

	void deleteSelectedShapes();
	void groupSelectedShapes();
	void ungroupSelectedGroup();

	void add_vector_shape();

	void updateColors(ofColor stroke, ofColor fill);
	void updateStrokeWeight(float newWeight);
	void updateRadius(float newRadius); 

	void applyToSelected();

	void resetSelection();

	ofImage grabCanvasScreen();

private:
	GraphNode root = GraphNode("Root");
	ShapeFactory shapeFactory;
	SceneGraph2dGui sceneGraph = SceneGraph2dGui(root);

	int drawingCanvasSize;
	int drawingCanvasX;
	int drawingCanvasY;

	float stroke_width;
	float radius;

	ofColor fillColor;
	ofColor strokeColor;

	ofImage currentImage;

	ShapeType selectedType;
	DrawerOptions selectedOption = DrawerOptions::draw;

	void setStrokeColor(ofColor color);
	void setFillColor(ofColor color);

	bool isMouseOutsideCanvas();

	void mousePressed(ofMouseEventArgs & mouse);
	void mouseReleased(ofMouseEventArgs & mouse);
};

