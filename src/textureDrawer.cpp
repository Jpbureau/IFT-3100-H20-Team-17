#include "textureDrawer.h"

void TextureDrawer::setup(int drawingCanvasX, int drawingCanvasY, int drawingCanvasSize)
{
	ofAddListener(ofEvents().mousePressed, this, &TextureDrawer::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &TextureDrawer::mouseReleased);

	this->drawingCanvasX = drawingCanvasX;
	this->drawingCanvasY = drawingCanvasY;
	this->drawingCanvasSize = drawingCanvasSize;
}

void TextureDrawer::draw()
{
	ofFill();
	ofSetColor(255);
	ofDrawRectangle(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);

	root.draw();

	//drawSelectionRectangles();
}

void TextureDrawer::update()
{
	root.update();

	//On pourrait aussi potentiellement l'activer seulement au clique d'un bouton
	/*for (int i = 0; i < head; i++) {
		if (shapes[i].selected) {
			shapes[i].stroke_width = stroke_width;
			shapes[i].radius = radius;

			shapes[i].fill_color[0] = fill_color_r;
			shapes[i].fill_color[1] = fill_color_g;
			shapes[i].fill_color[2] = fill_color_b;
			shapes[i].fill_color[3] = fill_color_a;

			shapes[i].stroke_color[0] = stroke_color_r;
			shapes[i].stroke_color[1] = stroke_color_g;
			shapes[i].stroke_color[2] = stroke_color_b;
			shapes[i].stroke_color[3] = stroke_color_a;
		}
	}*/
}

void TextureDrawer::selectPointType()
{
	selectedType = ShapeType::point;
	isSelectionActive = false;
}

void TextureDrawer::selectLineType()
{
	selectedType = ShapeType::line;
	isSelectionActive = false;
}

void TextureDrawer::selectRectangleType()
{
	selectedType = ShapeType::rectangle;
	isSelectionActive = false;
}

void TextureDrawer::selectSquareType()
{
	selectedType = ShapeType::square;
	isSelectionActive = false;
}

void TextureDrawer::selectEllipseType()
{
	selectedType = ShapeType::ellipse;
	isSelectionActive = false;
}

void TextureDrawer::selectCircleType()
{
	selectedType = ShapeType::circle;
	isSelectionActive = false;
}

void TextureDrawer::selectSelectionType()
{
	isSelectionActive = true;
}

void TextureDrawer::selectShape(int x, int y)
{
	//int pressedX;
	//int releasedX;
	//int pressedY;
	//int releasedY;
	//int temp;
	//bool isAnyShapeSelected = false;

	//if (selectedType == ShapeType::selection) {
	//	for (int index = 0; index < count; index++)
	//	{
	//		pressedX = shapes[index].position1[0];
	//		pressedY = shapes[index].position1[1];
	//		releasedX = shapes[index].position2[0];
	//		releasedY = shapes[index].position2[1];

	//		switch (shapes[index].type)
	//		{
	//		case ShapeType::point:

	//			if (sqrt((x - releasedX)*(x - releasedX) + (y - releasedY)*(y - releasedY)) < shapes[index].radius) {
	//				shapes[index].selected = true;
	//				isAnyShapeSelected = true;
	//			}

	//			break;

	//		default: 
	//			//on doit inverser les coordonnées si le clique est plus grand que le release afin d'uniformiser la comparaison plus bas
	//			if (releasedX < pressedX) {
	//				temp = releasedX;
	//				releasedX = pressedX;
	//				pressedX = temp;
	//			}

	//			if (releasedY < pressedY) {
	//				temp = releasedY;
	//				releasedY = pressedY;
	//				pressedY = temp;
	//			}

	//			if (x > pressedX && x < releasedX && y > pressedY && y < releasedY) {
	//				shapes[index].selected = true;
	//				isAnyShapeSelected = true;
	//			}
	//			break;
	//		}
	//	}

	//	if (!isAnyShapeSelected) {
	//		resetSelection();
	//	}
	//}
}


void TextureDrawer::add_vector_shape()
{
	if (isMouseOutsideCanvas()) {
		return;
	}

	glm::vec2 p1(mouse_pressed_posX, mouse_pressed_posY);
	glm::vec2 p2(mouse_current_posX, mouse_current_posY);

	if (selectedType == ShapeType::square || selectedType == ShapeType::circle) {
		glm::vec2 outerCorner = shapeFactory.squaricize(p1, p2);
		if (!isMouseInsideCanvas(outerCorner.x, outerCorner.y)) {
			return;
		}
	}

	root.addChild(shapeFactory.createShape(selectedType, p1, p2, fillColor, strokeColor, stroke_width, radius));
}

void TextureDrawer::updateColors(ofColor stroke, ofColor fill)
{
	setStrokeColor(stroke);
	setFillColor(fill);
}

void TextureDrawer::updateStrokeWeight(float newWeight)
{
	stroke_width = newWeight;
}

void TextureDrawer::updateRadius(float newRadius)
{
	radius = newRadius;
}

void TextureDrawer::setStrokeColor(ofColor color)
{
	strokeColor = color;
}

void TextureDrawer::setFillColor(ofColor color)
{
	fillColor = color;
}

void TextureDrawer::drawSelectionRectangles()
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	ofNoFill();
	ofSetLineWidth(2);
	//couleur pour la sélection (vert)
	ofSetColor(11, 252, 3);

	//for (int index = 0; index < head; ++index) {
	//	if (shapes[index].selected) {
	//		switch (shapes[index].type)
	//		{

	//		case VectorPrimitiveType::point:

	//			x1 = shapes[index].position2[0] - shapes[index].radius / 2;
	//			y1 = shapes[index].position2[1] - shapes[index].radius / 2;
	//			ofDrawRectangle(x1, y1, shapes[index].radius, shapes[index].radius);
	//			break;

	//		case VectorPrimitiveType::line:

	//			x1 = shapes[index].position1[0];
	//			y1 = shapes[index].position1[1];
	//			x2 = shapes[index].position2[0];
	//			y2 = shapes[index].position2[1];

	//			if (x1 < x2 && y1 > y2) {
	//				ofDrawRectangle(x1, y2, x2 - x1, y1 - y2);
	//			}
	//			else if (x1 < x2 && y1 < y2) {
	//				ofDrawRectangle(x2, y1, x1 - x2, y2 - y1);
	//			}
	//			else if (x2 < x1 && y1 < y2) {
	//				ofDrawRectangle(x2, y1, x1 - x2, y2 - y1);
	//			}
	//			else {
	//				ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
	//			}
	//			break;

	//		case VectorPrimitiveType::rectangle:

	//			x1 = shapes[index].position1[0];
	//			y1 = shapes[index].position1[1];
	//			x2 = shapes[index].position2[0];
	//			y2 = shapes[index].position2[1];
	//			ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
	//			break;

	//		case VectorPrimitiveType::ellipse:

	//			x1 = shapes[index].position1[0];
	//			y1 = shapes[index].position1[1];
	//			x2 = shapes[index].position2[0];
	//			y2 = shapes[index].position2[1];
	//			ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}
}

bool TextureDrawer::isMouseInsideCanvas(int x, int y)
{
	return x >= drawingCanvasX && x <= (drawingCanvasX + drawingCanvasSize) &&
		y >= drawingCanvasY && y <= (drawingCanvasY + drawingCanvasSize);
}

bool TextureDrawer::isMouseOutsideCanvas()
{
	int maxValidX = drawingCanvasX + drawingCanvasSize;
	int maxValidY = drawingCanvasY + drawingCanvasSize;

	return mouse_pressed_posX < drawingCanvasX || mouse_pressed_posX > maxValidX ||
		mouse_current_posX < drawingCanvasX || mouse_current_posX > maxValidX ||
		mouse_pressed_posY < drawingCanvasY || mouse_pressed_posY > maxValidY ||
		mouse_current_posY < drawingCanvasY || mouse_current_posY > maxValidY;
}

void TextureDrawer::resetSelection()
{
	//for (int i = 0; i < head; ++i) {
	//	shapes[i].selected = false;
	//}
}

ofImage TextureDrawer::grabCanvasScreen()
{
	ofImage image;
	image.grabScreen(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);
	return image;
}

void TextureDrawer::deleteSelectedShapes()
{
	/*for (int i = 0; i < head; ++i) {
		if (shapes[i].selected) {
			shapes[i].type = VectorPrimitiveType::none;
		}
	}*/
}

void TextureDrawer::mousePressed(ofMouseEventArgs & mouse)
{
	mouse_pressed_posX = mouse.x;
	mouse_pressed_posY = mouse.y;
	selectShape(mouse.x, mouse.y);
}

void TextureDrawer::mouseReleased(ofMouseEventArgs & mouse)
{
	mouse_current_posX = mouse.x;
	mouse_current_posY = mouse.y;
	add_vector_shape();
}