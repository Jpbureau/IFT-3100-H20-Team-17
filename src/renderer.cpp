#include "renderer.h"

void Renderer::setup()
{
	glm::vec2 initialCanvas2dPosition(225, 200);
	int initialCanvas2dSize = 600;

	glm::vec2 initialCanvas3dposition(850, 100);
	int initialCanvas3dSize = 800;

	cursor.setup();

	textureDrawer.setup(initialCanvas2dPosition.x, initialCanvas2dPosition.y, initialCanvas2dSize);
	fileManagerGui.setup();
	canvas2dGui.setup(initialCanvas2dPosition.y);
	
	//Il faudra ajuster la position de départ exacte plus tard
	const int HISTOGRAM_WIDTH = 600;
	const int HISTOGRAM_HEIGHT = 200;
	const int HISTOGRAM_X_POSITION = initialCanvas2dPosition.x;
	const int HISTOGRAM_Y_POSITION = initialCanvas2dPosition.y + initialCanvas2dSize + HISTOGRAM_HEIGHT + 1;
	colorHistogram.setup(HISTOGRAM_WIDTH, HISTOGRAM_HEIGHT, HISTOGRAM_X_POSITION, HISTOGRAM_Y_POSITION);
	colorHistogramGui.setup(10, 70);

	const int PRIMITIVES_GEOMETRIQUES_GUI_POSITION_X = ofGetWidth() - 210;
	const int PRIMITIVES_GEOMETRIQUES_GUI_POSITION_Y = 100;
	primitivesGeometriquesGui.setup(PRIMITIVES_GEOMETRIQUES_GUI_POSITION_X, PRIMITIVES_GEOMETRIQUES_GUI_POSITION_Y);

	const int CAMERA_GUI_POSITION_X = ofGetWidth() - 210;
	const int CAMERA_GUI_POSITION_Y = 500;
	cameraGui.setup(CAMERA_GUI_POSITION_X, CAMERA_GUI_POSITION_Y);

	textureDrawer3D.setup(initialCanvas3dposition.x, initialCanvas3dposition.y, initialCanvas3dSize);
	canvas3DGui.setup(initialCanvas3dposition.x, initialCanvas3dposition.y, initialCanvas3dSize);
	
}

void Renderer::update()
{
	canvas2dGui.update();
	textureDrawer.update();
	colorHistogramGui.update();	
	canvas3DGui.update();
	textureDrawer3D.update();
	cursor.update();
}

void Renderer::draw()
{
	ofSetBackgroundColor(canvas2dGui.backGroundColor);
	textureDrawer.draw();
	fileManagerGui.draw();
	canvas2dGui.draw();
	colorHistogramGui.draw();
	canvas3DGui.draw();
	textureDrawer3D.draw();
	cursor.draw();
}
