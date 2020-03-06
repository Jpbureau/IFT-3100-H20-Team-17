#include "fileManager.h"

ofImage FileManager::image_import() const
{
	ofImage image;
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		cout << path << endl;
		image.load(path);
	}
	return image;
}

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

ofxAssimpModelLoader FileManager::importModel() const
{
	ofxAssimpModelLoader model;
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		cout << path << endl;
		model.loadModel(path);
	}
	return model;
}
