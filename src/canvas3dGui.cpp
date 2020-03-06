#include "canvas3DGui.h"

Canvas3DGui::Canvas3DGui(TextureDrawer3D& drawer, FileManager& manager) : textureDrawer3D(drawer), fileManager(manager)
{
}

void Canvas3DGui::setup(int canvasPositionX, int canvasPositionY, int canvasSize)
{
	optionsPanel.setup("Panneau3D");
	optionsPanel.setPosition(canvasPositionX + canvasSize + 50, canvasPositionY + 100);
	animationOptions.setup("Options d'animation");
	shaderType.setup("Type choisi de shader");

	optionsPanel.add(boiteDelimButton.setup("Boite delimitation"));
	optionsPanel.add(importModelButton.setup("import model"));
	optionsPanel.add(modelColorPicker.set("diffuse color", ofColor(174, 223, 134), ofColor(0, 0), ofColor(255, 255)));
	optionsPanel.add(modelScale.set("Volume du modele", 0.3f, 0.1f, 0.375f));

	animationOptions.add(rotationAnimationToggle.set("Rotation du modele", false));
	animationOptions.add(levitationAnimationToggle.set("Effet de levitation", false));
	animationOptions.add(rotationSpeed.set("Vitesse de rotation", 1.0f, 0.1f, 5.0f));
	animationOptions.add(waveIntensity.set("Intensité de levitation", 10.0f, 20.0f, 4.0f));
	optionsPanel.add(&animationOptions);
	
	selectedShaderType.setName("Type choisi");
	shaderType.add(noShaderSelectedButton.setup("Aucun"));
	shaderType.add(lambertShaderSelectedButton.setup("Shader de lambert"));
	shaderType.add(selectedShaderType.set("Aucun"));
	optionsPanel.add(&shaderType);

	noShaderSelectedButton.addListener(this, &Canvas3DGui::noShaderSelected);
	lambertShaderSelectedButton.addListener(this, &Canvas3DGui::lambertShaderSelected);

	boiteDelimButton.addListener(this, &Canvas3DGui::boiteDelimButtonClicked);
	importModelButton.addListener(this, &Canvas3DGui::importModelClicked);
}

void Canvas3DGui::update()
{
	textureDrawer3D.updateModelParameters(modelColorPicker, modelScale);
	textureDrawer3D.updateAnimationParameters(rotationSpeed, waveIntensity, rotationAnimationToggle, levitationAnimationToggle);
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

void Canvas3DGui::lambertShaderSelected()
{
	selectedShaderType.set("lambert");
	textureDrawer3D.updateShaderSelection(ShaderType::lambert);
}

void Canvas3DGui::noShaderSelected()
{
	selectedShaderType.set("Aucun");
	textureDrawer3D.updateShaderSelection(ShaderType::none);
}
