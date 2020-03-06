#include "fileManagerGui.h"



FileManagerGui::FileManagerGui(FileManager & manager, TextureDrawer & textureDrawer) :
	fileManager(manager), textureDrawer(textureDrawer)
{
}

void FileManagerGui::setup()
{
	exportButton.addListener(this, &FileManagerGui::exportButtonPressed);
	importButton.addListener(this, &FileManagerGui::importButton_pressed);

	menuPanel.setup("Menu");
	menuPanel.add(importButton.setup("Import Image"));
	menuPanel.add(exportButton.setup("Export Image"));
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