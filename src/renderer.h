#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManagerGui.h"
#include "cursor.h"
#include "textureDrawer.h"
#include "canvasGui.h"
#include "colorHistogramGui.h"
#include "colorHistogram.h"
#include "textureDrawer3D.h"
#include "canvas3DGui.h"

class Renderer
{
public:
	void setup();
	void update();
	void draw();

private:

	ofImage image;

	FileManagerGui fileManagerGui;

	TextureDrawer textureDrawer;
	CanvasGui canvas2dGui = CanvasGui(textureDrawer);

	TextureDrawer3D textureDrawer3D;
	Canvas3DGui canvas3DGui = Canvas3DGui();

	ColorHistogram colorHistogram;
	ColorHistogramGui colorHistogramGui = ColorHistogramGui(colorHistogram, textureDrawer);

	Cursor cursor = Cursor(textureDrawer);
};