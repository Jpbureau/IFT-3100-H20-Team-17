#include "textureDrawer.h"

void TextureDrawer::setup(int drawingCanvasX, int drawingCanvasY, int drawingCanvasSize)
{
	ofAddListener(ofEvents().mousePressed, this, &TextureDrawer::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &TextureDrawer::mouseReleased);

	this->drawingCanvasX = drawingCanvasX;
	this->drawingCanvasY = drawingCanvasY;
	this->drawingCanvasSize = drawingCanvasSize;

	//Un peu comme on fait dans le cours, on pourrait �ventuellement penser � une meilleure structure de donn�es
	//count = 100;

	//head = 0;

	//stride = sizeof(VectorPrimitive);

	//size = count * stride;

	//shapes = (VectorPrimitive*)std::malloc(size);

	//selectedType = VectorPrimitiveType::line;
}

void TextureDrawer::draw()
{
	ofFill();
	ofSetColor(255);
	ofDrawRectangle(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);

	root.draw();

	/*for (int index = 0; index < count; index++)
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


	drawSelectionRectangles();*/
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
}

void TextureDrawer::selectLineType()
{
	selectedType = ShapeType::line;
}

void TextureDrawer::selectRectangleType()
{
	selectedType = ShapeType::rectangle;
}

void TextureDrawer::selectSquareType()
{
	selectedType = ShapeType::square;
}

void TextureDrawer::selectEllipseType()
{
	selectedType = ShapeType::ellipse;
}

void TextureDrawer::selectCircleType()
{
	selectedType = ShapeType::circle;
}

void TextureDrawer::selectSelectionType()
{
	selectedType = ShapeType::selection;
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
	//			//on doit inverser les coordonn�es si le clique est plus grand que le release afin d'uniformiser la comparaison plus bas
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
	ofColor fill(fill_color_r, fill_color_g, fill_color_b, fill_color_a);
	ofColor stroke(stroke_color_r, stroke_color_g, stroke_color_b, stroke_color_a);


	root.addChild(shapeFactory.createShape(selectedType, p1, p2, fill, stroke, stroke_width, radius));

	/*int horizontalDistance = abs(mouse_current_posX - mouse_pressed_posX);
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
	case ShapeType::point:
		shapes[head].radius = radius;
		shapes[head].stroke_width = stroke_width;
		break;

	case ShapeType::line:
		shapes[head].stroke_width = stroke_width;
		break;

	case ShapeType::rectangle:
		shapes[head].stroke_width = stroke_width;
		break;
	
	case ShapeType::square:
		

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

		shapes[head].type = ShapeType::rectangle;
		shapes[head].stroke_width = stroke_width;
		break;

	case ShapeType::ellipse:
		shapes[head].stroke_width = stroke_width;
		break;
	
	case ShapeType::circle:

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

		shapes[head].type = ShapeType::ellipse;
		shapes[head].stroke_width = stroke_width;
		break;

	default:
		shapes[head].stroke_width = stroke_width;
		break;
	}

	head = ++head >= count ? 0 : head;*/
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
	//couleur pour la s�lection (vert)
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