#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class FileManager
{
public:
	ofImage image_import() const;
	void saveImage() const;

	string importModel() const;
};