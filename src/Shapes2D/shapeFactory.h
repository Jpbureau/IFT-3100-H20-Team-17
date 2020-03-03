#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"
#include "point.h"
#include "line.h"
#include "rectangle.h"

enum class ShapeType { none, selection, point, line, rectangle, ellipse, circle, square };

class ShapeFactory {
public:
	GraphPrimitive* createShape(ShapeType type, glm::vec2 p1, glm::vec2 p2, ofColor fillColor, ofColor strokeColor, float strokeWidth, float radius);
};