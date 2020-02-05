#pragma once

#include "ofMain.h"

class FileManager
{
public:
	void image_export(const string name, const string extension, const string option) const;
	void saveImage() const;

	void image_import1(const string name, const string extension) const;

	ofImage image_import() const;
};

