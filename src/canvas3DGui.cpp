#include "canvas3DGui.h"

void Canvas3DGui::setup()
{
	optionsPanel.setup("Panneau3D");
	optionsPanel.setPosition(10, 400);

	optionsPanel.add(boiteDelimButton.setup("Boite délimitation"));

	//boiteDelimButton.addListener(this, &)
}