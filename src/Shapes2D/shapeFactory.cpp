#include "shapeFactory.h"

GraphPrimitive * ShapeFactory::createShape(ShapeType type, glm::vec2 p1, glm::vec2 p2, ofColor fillColor, ofColor strokeColor, float strokeWidth, float radius)
{
	switch (type)
	{
	case ShapeType::point:
		return new Point(p2, radius, strokeColor);

	case ShapeType::line:
		return new Line(p1, p2, strokeWidth, strokeColor);

	case ShapeType::rectangle:
		return new Rectangle2D(p1, p2, strokeWidth, fillColor, strokeColor);

	case ShapeType::square:
		p2 = squaricize(p1, p2);
		return new Rectangle2D(p1, p2, strokeWidth, fillColor, strokeColor);


	//	if (horizontalDistance > verticalDistance) {
	//		if (mouse_pressed_posY < mouse_current_posY) {
	//			shapes[head].position2[1] = mouse_pressed_posY + horizontalDistance;
	//		}
	//		else {
	//			shapes[head].position2[1] = mouse_pressed_posY - horizontalDistance;
	//		}
	//	}
	//	else {
	//		if (mouse_pressed_posX < mouse_current_posX) {
	//			shapes[head].position2[0] = mouse_pressed_posX + verticalDistance;
	//		}
	//		else {
	//			shapes[head].position2[0] = mouse_pressed_posX - verticalDistance;
	//		}
	//	}

	//	if (isShapeOutsideCanvas(shapes[head].position1[0], shapes[head].position2[0], shapes[head].position1[1], shapes[head].position2[1])) {
	//		cout << "should return" << endl;
	//		return;
	//	}

	//	shapes[head].type = ShapeType::rectangle;
	//	shapes[head].stroke_width = stroke_width;
	//	break;

	//case ShapeType::ellipse:
	//	shapes[head].stroke_width = stroke_width;
	//	break;

	//case ShapeType::circle:

	//	if (horizontalDistance > verticalDistance) {
	//		if (mouse_pressed_posY < mouse_current_posY) {
	//			shapes[head].position2[1] = mouse_pressed_posY + horizontalDistance;
	//		}
	//		else {
	//			shapes[head].position2[1] = mouse_pressed_posY - horizontalDistance;
	//		}
	//	}
	//	else {
	//		if (mouse_pressed_posX < mouse_current_posX) {
	//			shapes[head].position2[0] = mouse_pressed_posX + verticalDistance;
	//		}
	//		else {
	//			shapes[head].position2[0] = mouse_pressed_posX - verticalDistance;
	//		}
	//	}

	//	if (isShapeOutsideCanvas(shapes[head].position1[0], shapes[head].position2[0], shapes[head].position1[1], shapes[head].position2[1])) {
	//		cout << "should return" << endl;
	//		return;
	//	}

	//	shapes[head].type = ShapeType::ellipse;
	//	shapes[head].stroke_width = stroke_width;
	//	break;

	default:
		return nullptr;
	}	
}

glm::vec2 ShapeFactory::squaricize(glm::vec2 p1, glm::vec2 p2)
{
	glm::vec2 diago = p2 - p1;
	glm::vec2 direction(diago.x / abs(diago.x), diago.y / abs(diago.y));
	int maxLength = max(abs(diago.x), abs(diago.y));
	return p1 + maxLength * direction;
}

