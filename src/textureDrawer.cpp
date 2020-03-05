#include "textureDrawer.h"

void TextureDrawer::setup(int drawingCanvasX, int drawingCanvasY, int drawingCanvasSize)
{
	ofAddListener(ofEvents().mousePressed, this, &TextureDrawer::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &TextureDrawer::mouseReleased);

	this->drawingCanvasX = drawingCanvasX;
	this->drawingCanvasY = drawingCanvasY;
	this->drawingCanvasSize = drawingCanvasSize;

	//Un peu comme on fait dans le cours, on pourrait éventuellement penser à une meilleure structure de données
	count = 100;

	head = 0;

	stride = sizeof(VectorPrimitive);

	size = count * stride;

	shapes = (VectorPrimitive*)std::malloc(size);

	selectedType = VectorPrimitiveType::line;
}

void TextureDrawer::draw()
{
	ofFill();
	ofSetColor(255);
	ofDrawRectangle(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);

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

void TextureDrawer::selectSquareType()
{
	selectedType = VectorPrimitiveType::square;
}

void TextureDrawer::selectEllipseType()
{
	selectedType = VectorPrimitiveType::ellipse;
}

void TextureDrawer::selectCircleType()
{
	selectedType = VectorPrimitiveType::circle;
}

void TextureDrawer::selectSelectionType()
{
	selectedType = VectorPrimitiveType::selection;
}

void TextureDrawer::selectShapeZone()
{
	bool isAnyShapeSelected = false;

	int start_selectX = min(mouse_pressed_posX, mouse_current_posX);
	int start_selectY = min(mouse_pressed_posY, mouse_current_posY);

	int stop_selectX = max(mouse_pressed_posX, mouse_current_posX);
	int stop_selectY = max(mouse_pressed_posY, mouse_current_posY);

	for (int index = 0; index < count; index++)
	{
		int shape_pos1X = shapes[index].position1[0];
		int shape_pos1Y = shapes[index].position1[1];
		int shape_pos2X = shapes[index].position2[0];
		int shape_pos2Y = shapes[index].position2[1];

		if (isShapeInSelection(start_selectX, start_selectY, stop_selectX, stop_selectY, shape_pos1X, shape_pos1Y, shape_pos2X, shape_pos2Y))
		{
			shapes[index].selected = true;
			isAnyShapeSelected = true;
		}
	}
	if (!isAnyShapeSelected) {
		resetSelection();
	}
}

void TextureDrawer::selectShapeDot(int mouseX, int mouseY)
{
	bool isAnyShapeSelected = false;
	int temp;
	int shape_pos1X;
	int shape_pos1Y;
	int shape_pos2X;
	int shape_pos2Y;

	for (int index = 0; index < count; index++)
	{
		shape_pos1X = shapes[index].position1[0];
		shape_pos1Y = shapes[index].position1[1];
		shape_pos2X = shapes[index].position2[0];
		shape_pos2Y = shapes[index].position2[1];

		if (shape_pos2X < shape_pos1X) {
			temp = shape_pos1X;
			shape_pos1X = shape_pos2X;
			shape_pos2X = temp;
		}

		if (shape_pos2Y < shape_pos1Y) {
			temp = shape_pos1Y;
			shape_pos1Y = shape_pos2Y;
			shape_pos2Y = temp;
		}

		if (isSelectionInShape(mouseX, mouseY, shape_pos1X, shape_pos1Y, shape_pos2X, shape_pos2Y))
		{
			shapes[index].selected = true;
			isAnyShapeSelected = true;
		}

	}

	if (!isAnyShapeSelected) {
		resetSelection();
	}
}

void TextureDrawer::add_vector_shape()
{
	if (isMouseOutsideCanvas()) {
		return;
	}

	int horizontalDistance = abs(mouse_current_posX - mouse_pressed_posX);
	int verticalDistance = abs(mouse_current_posY - mouse_pressed_posY);

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
	
	case VectorPrimitiveType::square:
		

		if (horizontalDistance > verticalDistance) {
			if (mouse_pressed_posY < mouse_current_posY) {
				shapes[head].position2[1] = mouse_pressed_posY + horizontalDistance;
			}
			else {
				shapes[head].position2[1] = mouse_pressed_posY - horizontalDistance;
			}
		}
		else {
			if (mouse_pressed_posX < mouse_current_posX) {
				shapes[head].position2[0] = mouse_pressed_posX + verticalDistance;
			}
			else {
				shapes[head].position2[0] = mouse_pressed_posX - verticalDistance;
			}
		}

		if (isShapeOutsideCanvas(shapes[head].position1[0], shapes[head].position2[0], shapes[head].position1[1], shapes[head].position2[1])) {
			cout << "should return" << endl;
			return;
		}

		shapes[head].type = VectorPrimitiveType::rectangle;
		shapes[head].stroke_width = stroke_width;
		break;

	case VectorPrimitiveType::ellipse:
		shapes[head].stroke_width = stroke_width;
		break;
	
	case VectorPrimitiveType::circle:

		if (horizontalDistance > verticalDistance) {
			if (mouse_pressed_posY < mouse_current_posY) {
				shapes[head].position2[1] = mouse_pressed_posY + horizontalDistance;
			}
			else {
				shapes[head].position2[1] = mouse_pressed_posY - horizontalDistance;
			}
		}
		else {
			if (mouse_pressed_posX < mouse_current_posX) {
				shapes[head].position2[0] = mouse_pressed_posX + verticalDistance;
			}
			else {
				shapes[head].position2[0] = mouse_pressed_posX - verticalDistance;
			}
		}

		if (isShapeOutsideCanvas(shapes[head].position1[0], shapes[head].position2[0], shapes[head].position1[1], shapes[head].position2[1])) {
			cout << "should return" << endl;
			return;
		}

		shapes[head].type = VectorPrimitiveType::ellipse;
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
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	ofNoFill();
	ofSetLineWidth(2);
	//couleur pour la sélection (vert)
	ofSetColor(11, 252, 3);

	for (int index = 0; index < head; ++index) {
		if (shapes[index].selected) {
			switch (shapes[index].type)
			{

			case VectorPrimitiveType::point:

				x1 = shapes[index].position2[0] - shapes[index].radius / 2;
				y1 = shapes[index].position2[1] - shapes[index].radius / 2;
				ofDrawRectangle(x1, y1, shapes[index].radius, shapes[index].radius);
				break;

			case VectorPrimitiveType::line:

				x1 = shapes[index].position1[0];
				y1 = shapes[index].position1[1];
				x2 = shapes[index].position2[0];
				y2 = shapes[index].position2[1];

				if (x1 < x2 && y1 > y2) {
					ofDrawRectangle(x1, y2, x2 - x1, y1 - y2);
				}
				else if (x1 < x2 && y1 < y2) {
					ofDrawRectangle(x2, y1, x1 - x2, y2 - y1);
				}
				else if (x2 < x1 && y1 < y2) {
					ofDrawRectangle(x2, y1, x1 - x2, y2 - y1);
				}
				else {
					ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
				}
				break;

			case VectorPrimitiveType::rectangle:

				x1 = shapes[index].position1[0];
				y1 = shapes[index].position1[1];
				x2 = shapes[index].position2[0];
				y2 = shapes[index].position2[1];
				ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
				break;

			case VectorPrimitiveType::ellipse:

				x1 = shapes[index].position1[0];
				y1 = shapes[index].position1[1];
				x2 = shapes[index].position2[0];
				y2 = shapes[index].position2[1];
				ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
				break;

			default:
				break;
			}
		}
	}
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

bool TextureDrawer::isShapeOutsideCanvas(int x1, int x2, int y1, int y2)
{
	int maxValidX = drawingCanvasX + drawingCanvasSize;
	int maxValidY = drawingCanvasY + drawingCanvasSize;

	return x1 < drawingCanvasX || x1 > maxValidX ||
		x2 < drawingCanvasX || x2 > maxValidX ||
		y1 < drawingCanvasY || y1 > maxValidY ||
		y2 < drawingCanvasY || y2 > maxValidY;
}

bool TextureDrawer::isShapeInSelection(int start_posX, int start_posY, int stop_posX, int stop_posY, int shape_pos1X, int shape_pos1Y, int shape_pos2X, int shape_pos2Y)
{
	return shape_pos1X >= start_posX && shape_pos1X <= stop_posX && shape_pos2X >= start_posX && shape_pos2X <= stop_posX
		&& shape_pos1Y >= start_posY && shape_pos1Y <= stop_posY && shape_pos2Y >= start_posY && shape_pos2Y <= stop_posY;
}

bool TextureDrawer::isSelectionInShape(int select_posX, int select_posY, int shape_pos1X, int shape_pos1Y, int shape_pos2X, int shape_pos2Y)
{
	return select_posX >= shape_pos1X && select_posX <= shape_pos2X
		&& select_posY >= shape_pos1Y && select_posY <= shape_pos2Y;
}

void TextureDrawer::resetSelection()
{
	for (int i = 0; i < head; ++i) {
		shapes[i].selected = false;
	}
}

ofImage TextureDrawer::grabCanvasScreen()
{
	ofImage image;
	image.grabScreen(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);
	return image;
}

void TextureDrawer::deleteSelectedShapes()
{
	for (int i = 0; i < head; ++i) {
		if (shapes[i].selected) {
			shapes[i].type = VectorPrimitiveType::none;
		}
	}
}

void TextureDrawer::mousePressed(ofMouseEventArgs & mouse)
{
	mouse_pressed_posX = mouse.x;
	mouse_pressed_posY = mouse.y;
}

void TextureDrawer::mouseReleased(ofMouseEventArgs & mouse)
{
	mouse_current_posX = mouse.x;
	mouse_current_posY = mouse.y;

	if (selectedType == VectorPrimitiveType::selection) {
		if (mouse_pressed_posX == mouse_current_posX && mouse_pressed_posY == mouse_current_posY)
			selectShapeDot(mouse_current_posX, mouse_current_posY);
		else selectShapeZone();
	}
	
	add_vector_shape();
}