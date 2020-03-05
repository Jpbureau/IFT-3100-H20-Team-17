#include "canvasGui.h"

CanvasGui::CanvasGui(TextureDrawer & drawer) :
	textureDrawer(drawer)
{
}

void CanvasGui::setup(int drawingCanvasY)
{
	drawingOptionsPanel.setup("Outils de dessin");
	drawingOptionsPanel.setPosition(10, drawingCanvasY);
	selectedType.setName("Type choisi:");

	backGroundColor.set("Couleur du fond", ofColor::burlyWood, ofColor(0, 0), ofColor(255, 255));
	strokeColorPicker.set("Couleur du contour/trait", ofColor::darkCyan, ofColor(0, 0), ofColor(255, 255));
	fillColorPicker.set("Couleur du remplissage", ofColor::crimson, ofColor(0, 0), ofColor(255, 255));
	strokeWeightSlider.set("Largeur de la ligne", 1.0f, 0.0f, 5.0f);

	drawingOptionsPanel.add(backGroundColor);
	drawingOptionsPanel.add(strokeColorPicker);
	drawingOptionsPanel.add(fillColorPicker);
	drawingOptionsPanel.add(strokeWeightSlider);
	drawingOptionsPanel.add(selectedType);

	shapeSelectionGroup.setup("Formes");

	radiusSlider.set("LRayon", 1.0f, 0.0f, 40.0f);
	optionsPoint.setup("Point");
	optionsPoint.add(radiusSlider);
	optionsPoint.add(drawPointButton.setup("point"));
	shapeSelectionGroup.add(&optionsPoint);

	shapeSelectionGroup.add(drawLineButton.setup("Ligne"));
	shapeSelectionGroup.add(drawRectangleButton.setup("Rectangle"));
	shapeSelectionGroup.add(drawSquareButton.setup("Carre"));
	shapeSelectionGroup.add(drawEllipseButton.setup("Ellipse"));
	shapeSelectionGroup.add(drawCircleButton.setup("Cercle"));
	drawingOptionsPanel.add(&shapeSelectionGroup);

	drawingOptionsPanel.add(selectButton.setup("Selectionner"));
	drawingOptionsPanel.add(deselectButton.setup("Deselectionner"));
	drawingOptionsPanel.add(deleteButton.setup("Supprimer"));
	drawingOptionsPanel.add(groupButton.setup("Grouper"));

	drawPointButton.addListener(this, &CanvasGui::selectPointType);
	drawLineButton.addListener(this, &CanvasGui::selectLineType);
	drawRectangleButton.addListener(this, &CanvasGui::selectRectangleType);
	drawSquareButton.addListener(this, &CanvasGui::selectSquareType);
	drawEllipseButton.addListener(this, &CanvasGui::selectEllipseType);
	drawCircleButton.addListener(this, &CanvasGui::selectCircleType);
	selectButton.addListener(this, &CanvasGui::selectAction);
	deselectButton.addListener(this, &CanvasGui::deselectAction);
	deleteButton.addListener(this, &CanvasGui::deleteAction);
	groupButton.addListener(this, &CanvasGui::groupAction);

	selectRectangleType();
}

void CanvasGui::update()
{
	textureDrawer.updateColors(strokeColorPicker, fillColorPicker);
	textureDrawer.updateStrokeWeight(strokeWeightSlider);
	textureDrawer.updateRadius(radiusSlider);
}

void CanvasGui::draw()
{
	drawingOptionsPanel.draw();
}

//Malheureusement nécessaire pour l'instant si on veut déclencher une action avec le listener
void CanvasGui::selectPointType()
{
	textureDrawer.selectPointType();
	selectedType.set("Point");
}
void CanvasGui::selectLineType()
{
	textureDrawer.selectLineType();
	selectedType.set("Ligne");
}
void CanvasGui::selectRectangleType()
{
	textureDrawer.selectRectangleType();
	selectedType.set("Rectangle");
}
void CanvasGui::selectSquareType()
{
	textureDrawer.selectSquareType();
	selectedType.set("Carre");
}
void CanvasGui::selectEllipseType()
{
	textureDrawer.selectEllipseType();
	selectedType.set("Ellipse");
}

void CanvasGui::selectCircleType()
{
	textureDrawer.selectCircleType();
	selectedType.set("Cercle");
}

void CanvasGui::selectAction()
{
	textureDrawer.selectSelectionType();
	selectedType.set("Selection");
}

void CanvasGui::deleteAction()
{
	textureDrawer.deleteSelectedShapes();
}

void CanvasGui::deselectAction()
{
	textureDrawer.resetSelection();
}

void CanvasGui::groupAction()
{
	textureDrawer.groupSelectedShapes();
}
