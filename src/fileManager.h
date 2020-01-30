#pragma once

#include "ofMain.h"

class FileManager
{
public:
	void image_export(const string name, const string extension, const string option) const;
	void saveImage();
};