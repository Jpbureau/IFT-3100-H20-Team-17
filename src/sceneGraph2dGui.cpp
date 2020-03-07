#include "sceneGraph2dGui.h"

SceneGraph2dGui::SceneGraph2dGui(GraphNode & root) :
	root(root)
{
}

void SceneGraph2dGui::setup()
{
	gui.setup("Graphe de scene");
	gui.setPosition(10, 640);
	gui.add(root.getGuiRepresentation());
}

void SceneGraph2dGui::draw()
{
	gui.draw();
}
