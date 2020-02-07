#include "fileManager.h"

void FileManager::saveImage() const
{
	ofFileDialogResult result = ofSystemSaveDialog("render.png", "Image Export");

	if (result.bSuccess) {
		filesystem::path path = result.getPath();

		if (!path.has_extension()) {
			path += ".png";
		}

		ofImage image;
		image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		image.save(path);

		ofLog() << "<export image: " << path << ">";
	}
}