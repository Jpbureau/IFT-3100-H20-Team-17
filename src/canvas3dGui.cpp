#include "canvas3DGui.h"

Canvas3DGui::Canvas3DGui(TextureDrawer3D& drawer, FileManager& manager) : textureDrawer3D(drawer), fileManager(manager)
{
}

void Canvas3DGui::setup()
{
	optionsPanel.setup("Panneau3D");
	optionsPanel.setPosition(215, 10);

	optionsPanel.add(boiteDelimButton.setup("Boite délimitation"));
	optionsPanel.add(importModelButton.setup("import model"));
	optionsPanel.add(modelColorPicker.set("diffuse color", ofColor(174, 223, 134), ofColor(0, 0), ofColor(255, 255)));

	boiteDelimButton.addListener(this, &Canvas3DGui::boiteDelimButtonClicked);
	importModelButton.addListener(this, &Canvas3DGui::importModelClicked);

}

void Canvas3DGui::update()
{
	textureDrawer3D.updateColors(modelColorPicker);
}

void Canvas3DGui::draw()
{
	optionsPanel.draw();
}

void Canvas3DGui::boiteDelimButtonClicked()
{
	std::cout << "BoiteDelimButtonCLicked" << std::endl;
}

void Canvas3DGui::importModelClicked()
{
	ofxAssimpModelLoader model = fileManager.importModel();
	textureDrawer3D.importModel(model);
}
