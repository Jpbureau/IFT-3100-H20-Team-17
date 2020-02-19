#include "textureDrawer.h"

void TextureDrawer::setup()
{
	//Un peu comme on fait dans le cours, on pourrait �ventuellement penser � une meilleure structure de donn�es
	count = 100;

	head = 0;

	stride = sizeof(VectorPrimitive);

	size = count * stride;

	shapes = (VectorPrimitive*)std::malloc(size);

	selectedType = VectorPrimitiveType::line;
}

void TextureDrawer::draw()
{
	for (int index = 0; index < count; index++)
	{
		switch (shapes[index].type)
		{

		case VectorPrimitiveType::point:

			ofFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(
				shapes[index].stroke_color[0],
				shapes[index].stroke_color[1],
				shapes[index].stroke_color[2]);
			draw_point(
				shapes[index].position2[0],
				shapes[index].position2[1],
				shapes[index].radius);
			break;

		case VectorPrimitiveType::line:
			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(
				shapes[index].stroke_color[0],
				shapes[index].stroke_color[1],
				shapes[index].stroke_color[2]);
			draw_line(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		case VectorPrimitiveType::rectangle:

			ofFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(
				shapes[index].fill_color[0],
				shapes[index].fill_color[1],
				shapes[index].fill_color[2],
				shapes[index].fill_color[3]);
			draw_rectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetColor(
				shapes[index].stroke_color[0],
				shapes[index].stroke_color[1],
				shapes[index].stroke_color[2],
				shapes[index].stroke_color[3]);
			draw_rectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		case VectorPrimitiveType::ellipse:

			ofFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetCircleResolution(48);
			ofSetColor(
				shapes[index].fill_color[0],
				shapes[index].fill_color[1],
				shapes[index].fill_color[2]);
			draw_ellipse(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(
				shapes[index].stroke_color[0],
				shapes[index].stroke_color[1],
				shapes[index].stroke_color[2]);
			draw_ellipse(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		default:
			break;
		}
	}


	drawSelectionRectangles();
}

void TextureDrawer::update()
{
	//On pourrait aussi potentiellement l'activer seulement au clique d'un bouton
	for (int i = 0; i < head; i++) {
		if (shapes[i].selected) {
			shapes[i].fill_color[0] = fill_color_r;
			shapes[i].fill_color[1] = fill_color_g;
			shapes[i].fill_color[2] = fill_color_b;
			shapes[i].fill_color[3] = fill_color_a;
			shapes[i].stroke_color[0] = stroke_color_r;
			shapes[i].stroke_color[1] = stroke_color_g;
			shapes[i].stroke_color[2] = stroke_color_b;
			shapes[i].stroke_color[3] = stroke_color_a;
			shapes[i].stroke_width = stroke_width;
			shapes[i].radius = radius;
		}
	}
}

void TextureDrawer::selectPointType()
{
	selectedType = VectorPrimitiveType::point;
}

void TextureDrawer::selectLineType()
{
	selectedType = VectorPrimitiveType::line;
}

void TextureDrawer::selectRectangleType()
{
	selectedType = VectorPrimitiveType::rectangle;
}

void TextureDrawer::selectEllipseType()
{
	selectedType = VectorPrimitiveType::ellipse;
}

void TextureDrawer::selectSelectionType()
{
	selectedType = VectorPrimitiveType::selection;
}

void TextureDrawer::selectShape(int x, int y)
{
	int pressedX;
	int releasedX;
	int pressedY;
	int releasedY;
	int temp;
	bool isAnyShapeSelected = false;

	if (selectedType == VectorPrimitiveType::selection) {
		for (int index = 0; index < count; index++)
		{
			pressedX = shapes[index].position1[0];
			pressedY = shapes[index].position1[1];
			releasedX = shapes[index].position2[0];
			releasedY = shapes[index].position2[1];

			switch (shapes[index].type)
			{
			case VectorPrimitiveType::point:

				if (sqrt((x - releasedX)*(x - releasedX) + (y - releasedY)*(y - releasedY)) < shapes[index].radius) {
					shapes[index].selected = true;
					isAnyShapeSelected = true;
				}

				break;

			default:
				if (releasedX < pressedX) {
					temp = releasedX;
					releasedX = pressedX;
					pressedX = temp;
				}

				if (releasedY < pressedY) {
					temp = releasedY;
					releasedY = pressedY;
					pressedY = temp;
				}

				if (x > pressedX && x < releasedX && y > pressedY && y < releasedY) {
					shapes[index].selected = true;
					isAnyShapeSelected = true;
				}
				break;
			}
		}

		if (!isAnyShapeSelected) {
			resetSelection();
		}
	}
}


void TextureDrawer::add_vector_shape()
{
	shapes[head].type = selectedType;

	shapes[head].position1[0] = mouse_pressed_posX;
	shapes[head].position1[1] = mouse_pressed_posY;

	shapes[head].position2[0] = mouse_current_posX;
	shapes[head].position2[1] = mouse_current_posY;

	shapes[head].stroke_color[0] = stroke_color_r;
	shapes[head].stroke_color[1] = stroke_color_g;
	shapes[head].stroke_color[2] = stroke_color_b;
	shapes[head].stroke_color[3] = stroke_color_a;

	shapes[head].fill_color[0] = fill_color_r;
	shapes[head].fill_color[1] = fill_color_g;
	shapes[head].fill_color[2] = fill_color_b;
	shapes[head].fill_color[3] = fill_color_a;
	
	shapes[head].selected = false;

	switch (shapes[head].type)
	{
	case VectorPrimitiveType::point:
		shapes[head].radius = radius;
		shapes[head].stroke_width = stroke_width;
		break;

	case VectorPrimitiveType::line:
		shapes[head].stroke_width = stroke_width;
		break;

	case VectorPrimitiveType::rectangle:
		shapes[head].stroke_width = stroke_width;
		break;

	case VectorPrimitiveType::ellipse:
		shapes[head].stroke_width = stroke_width;
		break;

	default:
		shapes[head].stroke_width = stroke_width;
		break;
	}

	head = ++head >= count ? 0 : head;
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
	stroke_color_r = color.r;
	stroke_color_g = color.g;
	stroke_color_b = color.b;
	stroke_color_a = color.a;
}

void TextureDrawer::setFillColor(ofColor color)
{
	fill_color_r = color.r;
	fill_color_g = color.g;
	fill_color_b = color.b;
	fill_color_a = color.a;
}

void TextureDrawer::draw_point(float x, float y, float radius) const
{
	ofDrawEllipse(x, y, radius, radius);
}

void TextureDrawer::draw_line(float x1, float y1, float x2, float y2) const
{
	ofDrawLine(x1, y1, x2, y2);
}

void TextureDrawer::draw_rectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}

void TextureDrawer::draw_ellipse(float x1, float y1, float x2, float y2) const
{
	float diameter_x = x2 - x1;
	float diameter_y = y2 - y1;

	ofDrawEllipse(x1 + diameter_x / 2.0f, y1 + diameter_y / 2.0f, diameter_x, diameter_y);
}

void TextureDrawer::drawSelectionRectangles()
{
	int newX1 = 0;
	int newX2 = 0;
	int newY1 = 0;
	int newY2 = 0;
	ofNoFill();
	ofSetColor(200, 200, 255);
	ofSetLineWidth(1);
	for (int i = 0; i < head; ++i) {
		if (shapes[i].selected) {
			switch (shapes[i].type) {
			case VectorPrimitiveType::point:
				newX1 = shapes[i].position2[0] - shapes[i].radius / 2;
				newY1 = shapes[i].position2[1] - shapes[i].radius / 2;
				ofDrawRectangle(newX1, newY1, shapes[i].radius, shapes[i].radius);
				break;
			case VectorPrimitiveType::line:
				newX1 = shapes[i].position1[0];
				newY1 = shapes[i].position1[1];
				newX2 = shapes[i].position2[0];
				newY2 = shapes[i].position2[1];

				if (newX1 < newX2 && newY1 > newY2) {
					ofDrawRectangle(newX1, newY2, newX2 - newX1, newY1 - newY2);
				}
				else if (newX1 < newX2 && newY1 < newY2) {
					ofDrawRectangle(newX2, newY1, newX1 - newX2, newY2 - newY1);
				}
				else if (newX2 < newX1 && newY1 < newY2) {
					ofDrawRectangle(newX2, newY1, newX1 - newX2, newY2 - newY1);
				}
				else {
					ofDrawRectangle(newX1, newY1, newX2 - newX1, newY2 - newY1);
				}
				break;
			case VectorPrimitiveType::rectangle:
				newX1 = shapes[i].position1[0];
				newY1 = shapes[i].position1[1];
				newX2 = shapes[i].position2[0];
				newY2 = shapes[i].position2[1];
				ofDrawRectangle(newX1, newY1, newX2 - newX1, newY2 - newY1);
				break;
			case VectorPrimitiveType::ellipse:

				newX1 = shapes[i].position1[0];
				newY1 = shapes[i].position1[1];
				newX2 = shapes[i].position2[0];
				newY2 = shapes[i].position2[1];
				ofDrawRectangle(newX1, newY1, newX2 - newX1, newY2 - newY1);
				break;

			default:
				break;
			}
		}
	}
}

void TextureDrawer::resetSelection()
{
	for (int i = 0; i < head; ++i) {
		shapes[i].selected = false;
	}
}

void TextureDrawer::deleteSelectedShapes()
{
	for (int i = 0; i < head; ++i) {
		if (shapes[i].selected) {
			shapes[i].type = VectorPrimitiveType::none;
		}
	}
}