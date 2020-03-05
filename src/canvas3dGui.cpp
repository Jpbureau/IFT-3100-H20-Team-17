#include "canvas3DGui.h"

Canvas3DGui::Canvas3DGui()
{

}

void Canvas3DGui::setup()
{
	optionsPanel.setup("Panneau3D");
	optionsPanel.setPosition(215, 10);

	optionsPanel.add(boiteDelimButton.setup("Boite délimitation"));

	boiteDelimButton.addListener(this, &Canvas3DGui::boiteDelimButtonClicked);
}

void Canvas3DGui::update()
{

}

void Canvas3DGui::draw()
{
	optionsPanel.draw();
}

void Canvas3DGui::boiteDelimButtonClicked()
{
	std::cout << "BoiteDelimButtonCLicked" << std::endl;
}
