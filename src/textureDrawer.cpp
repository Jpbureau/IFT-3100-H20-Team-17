#include "textureDrawer.h"

void TextureDrawer::setup(int drawingCanvasX, int drawingCanvasY, int drawingCanvasSize)
{
	ofAddListener(ofEvents().mousePressed, this, &TextureDrawer::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &TextureDrawer::mouseReleased);

	this->drawingCanvasX = drawingCanvasX;
	this->drawingCanvasY = drawingCanvasY;
	this->drawingCanvasSize = drawingCanvasSize;

	sceneGraph.setup();
}

void TextureDrawer::draw()
{
	ofFill();
	ofSetColor(255);
	ofDrawRectangle(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);

	root.draw();
	sceneGraph.draw();
}

void TextureDrawer::update()
{
	root.update();
}

void TextureDrawer::selectPointType()
{
	selectedType = ShapeType::point;
	selectedOption = DrawerOptions::draw;
}

void TextureDrawer::selectLineType()
{
	selectedType = ShapeType::line;
	selectedOption = DrawerOptions::draw;
}

void TextureDrawer::selectRectangleType()
{
	selectedType = ShapeType::rectangle;
	selectedOption = DrawerOptions::draw;
}

void TextureDrawer::selectSquareType()
{
	selectedType = ShapeType::square;
	selectedOption = DrawerOptions::draw;
}

void TextureDrawer::selectEllipseType()
{
	selectedType = ShapeType::ellipse;
	selectedOption = DrawerOptions::draw;
}

void TextureDrawer::selectCircleType()
{
	selectedType = ShapeType::circle;
	selectedOption = DrawerOptions::draw;
}

void TextureDrawer::selectImageType(ofImage image)
{
	currentImage = image;
	selectedType = ShapeType::image;
	selectedOption = DrawerOptions::draw;
}

void TextureDrawer::selectSelectionType()
{
	selectedOption = DrawerOptions::select;
}

void TextureDrawer::selectTranslateType()
{
	selectedOption = DrawerOptions::translate;
}

void TextureDrawer::selectScaleType()
{
	selectedOption = DrawerOptions::scale;
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

	root.addChild(shapeFactory.createShape(selectedType, p1, p2, fillColor, strokeColor, stroke_width, radius, currentImage));
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

void TextureDrawer::applyToSelected()
{
	root.updateCommonAttributes(fillColor, strokeColor, stroke_width);
}

void TextureDrawer::setStrokeColor(ofColor color)
{
	strokeColor = color;
}

void TextureDrawer::setFillColor(ofColor color)
{
	fillColor = color;
}

bool TextureDrawer::isMouseInsideCanvas(int x, int y)
{
	return x >= drawingCanvasX && x <= (drawingCanvasX + drawingCanvasSize) &&
		y >= drawingCanvasY && y <= (drawingCanvasY + drawingCanvasSize);
}


string TextureDrawer::getCurrentlySelectedType()
{
	switch (selectedOption)
	{
	case select:
		return "Selection";
	case translate:
		return "Deplacer";
	case scale:
		return "Proportion";
	case DrawerOptions::draw:
		switch (selectedType)
		{
		case ShapeType::point:
			return "Point";
		case ShapeType::line:
			return "Ligne";
		case ShapeType::rectangle:
			return "Rectangle";
		case ShapeType::square:
			return "Carre";
		case ShapeType::ellipse:
			return "Ellipse";
		case ShapeType::circle:
			return "Cercle";
		case ShapeType::image:
			return "Image";
		default:
			break;
		}
		break;
	default:
		break;
	}
}

bool TextureDrawer::isTypeSelection()
{
	return selectedOption == DrawerOptions::select;
}

bool TextureDrawer::isTypeTranslation()
{
	return selectedOption == DrawerOptions::translate;
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
	root.unselect();
}

ofImage TextureDrawer::grabCanvasScreen()
{
	ofImage image;
	image.grabScreen(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);
	return image;
}

void TextureDrawer::deleteSelectedShapes()
{
	root.deleteSelectedPrimitives();
}

void TextureDrawer::groupSelectedShapes()
{
	root.createGroupWithSelectedPrimitives();
}

void TextureDrawer::ungroupSelectedGroup()
{
	root.ungroupSelected();
}

void TextureDrawer::mousePressed(ofMouseEventArgs & mouse)
{
	mouse_pressed_posX = mouse.x;
	mouse_pressed_posY = mouse.y;

	if (selectedOption == DrawerOptions::select) root.selectChildsAtPoint(mouse.x, mouse.y);
}

void TextureDrawer::mouseReleased(ofMouseEventArgs & mouse)
{
	mouse_current_posX = mouse.x;
	mouse_current_posY = mouse.y;
	
	if (selectedOption == DrawerOptions::draw) add_vector_shape();
	else if (selectedOption == DrawerOptions::translate && !isMouseOutsideCanvas()) {
		root.translate(mouse_current_posX - mouse_pressed_posX, mouse_current_posY - mouse_pressed_posY);
	}
	else if (selectedOption == DrawerOptions::scale && !isMouseOutsideCanvas()) {
		root.scale((glm::vec2(mouse_current_posX, mouse_current_posY) - glm::vec2(mouse_pressed_posX, mouse_pressed_posY)));
	}
}