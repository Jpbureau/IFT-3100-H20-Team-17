#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"
#include "point.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "imagePrimitive.h"

enum class ShapeType { point, line, rectangle, square, ellipse, circle, image };

class ShapeFactory {
public:
	GraphPrimitive* createShape(ShapeType type, glm::vec2 p1, glm::vec2 p2, ofColor fillColor, ofColor strokeColor, float strokeWidth, float radius, ofImage image);
	glm::vec2 squaricize(const glm::vec2& p1, const glm::vec2& p2);
};