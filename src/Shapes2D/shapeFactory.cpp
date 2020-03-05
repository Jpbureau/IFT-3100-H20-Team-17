#include "shapeFactory.h"

GraphPrimitive * ShapeFactory::createShape(ShapeType type, glm::vec2 p1, glm::vec2 p2, ofColor fillColor, ofColor strokeColor, float strokeWidth, float radius)
{
	switch (type)
	{
	case ShapeType::point:
		return new Point(p2, radius, strokeColor, "Point");

	case ShapeType::line:
		return new Line(p1, p2, strokeWidth, strokeColor, "Ligne");

	case ShapeType::rectangle:
		return new Rectangle2D(p1, p2, strokeWidth, fillColor, strokeColor, "Rectangle");

	case ShapeType::square:
		p2 = squaricize(p1, p2);
		return new Rectangle2D(p1, p2, strokeWidth, fillColor, strokeColor, "Carre");

	case ShapeType::ellipse:
		return new Ellipse2D(p1, p2, strokeWidth, fillColor, strokeColor, "Ellipse");

	case ShapeType::circle:
		p2 = squaricize(p1, p2);
		return new Ellipse2D(p1, p2, strokeWidth, fillColor, strokeColor, "Cercle");
	default:
		throw exception("Illegal Shape Type");
	}
}

glm::vec2 ShapeFactory::squaricize(const glm::vec2& p1, const glm::vec2& p2)
{
	glm::vec2 diago = p2 - p1;
	glm::vec2 direction(diago.x / abs(diago.x), diago.y / abs(diago.y));
	int maxLength = max(abs(diago.x), abs(diago.y));
	return p1 + maxLength * direction;
}

