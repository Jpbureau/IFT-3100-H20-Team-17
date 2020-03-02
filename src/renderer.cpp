#include "renderer.h"

void Renderer::setup()
{
	glm::vec2 initialCanvas2dPosition(225, ofGetHeight() / 3.5);
	int initialCanvas2dSize = 600;

	cursor.setup();

	textureDrawer.setup(initialCanvas2dPosition.x, initialCanvas2dPosition.y, initialCanvas2dSize);
	fileManagerGui.setup();
	canvas2dGui.setup(initialCanvas2dPosition.y);
	
	//Il faudra ajuster la position de départ exacte plus tard
	colorHistogram.setup();
	colorHistogramGui.setup(10, 560);
	
}

void Renderer::update()
{
	canvas2dGui.update();
	textureDrawer.update();
	cursor.update();
	colorHistogramGui.update();	
}

void Renderer::draw()
{
	ofSetBackgroundColor(canvas2dGui.backGroundColor);
	textureDrawer.draw();
	cursor.draw();
	fileManagerGui.draw();
	canvas2dGui.draw();
	colorHistogramGui.draw();
}

void Renderer::mousePressed(int x, int y)
{
	textureDrawer.mouse_pressed_posX = x;
	textureDrawer.mouse_pressed_posY = y;
	textureDrawer.selectShape(x, y);
}

void Renderer::mouseReleased(int x, int y)
{
	textureDrawer.mouse_current_posX = x;
	textureDrawer.mouse_current_posY = y;
	textureDrawer.add_vector_shape();
}


