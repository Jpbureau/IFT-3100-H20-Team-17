#include "fileManager.h"

void FileManager::saveImage() const
{
	ofFileDialogResult result = ofSystemSaveDialog("render.png", "Image Export");

	if (result.bSuccess) {
		ofImage image;
		image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		image.save(result.getPath());

		ofLog() << "<export image: " << result.getPath() << ">";
	}
}