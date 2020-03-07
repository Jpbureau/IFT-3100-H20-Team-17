#include "fileManagerGui.h"



FileManagerGui::FileManagerGui(FileManager & manager, TextureDrawer & textureDrawer, Recorder & recorder) :
	fileManager(manager), textureDrawer(textureDrawer), recorder(recorder)
{
}

void FileManagerGui::setup()
{
	exportButton.addListener(this, &FileManagerGui::exportButtonPressed);
	importButton.addListener(this, &FileManagerGui::importButton_pressed);

	menuPanel.setup("Menu");
	menuPanel.add(importButton.setup("Importer Image"));
	menuPanel.add(exportButton.setup("Exporter Image"));
	menuPanel.add(recorder.getIsRecording().set("Enregistrer Sequence", false));
}

void FileManagerGui::draw()
{
	menuPanel.draw();
}

void FileManagerGui::importButton_pressed()
{
	ofImage image = fileManager.image_import();
	
	textureDrawer.selectImageType(image);
}

void FileManagerGui::exportButtonPressed()
{
	fileManager.saveImage();
}