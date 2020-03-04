#include "primitivesGeometriquesGui.h"

PrimitivesGeometriquesGui::PrimitivesGeometriquesGui()
{

}

void PrimitivesGeometriquesGui::setup(int positionX, int positionY)
{
	primitivesGeometriquesPanel.setup("Primitives geometriques");
	primitivesGeometriquesPanel.setPosition(positionX, positionY);

	selectedType.setName("Type choisi:");

	strokeColorPicker.set("Couleur du contour/trait", ofColor::darkCyan, ofColor(0, 0), ofColor(255, 255));
	fillColorPicker.set("Couleur du remplissage", ofColor::crimson, ofColor(0, 0), ofColor(255, 255));

	xCoordinateSlider.set("Coordonnees X", 0.0f, -500.0f, 500.0f);
	yCoordinateSlider.set("Coordonnees Y ", 0.0f, -500.0f, 500.0f);
	zCoordinateSlider.set("Coordonnees Z", 0.0f, -500.0f, 500.0f);

	heightSlider.set("Hauteur Y", 10.0f, 1.0f, 500.0f);
	widthSlider.set("Largeur X ", 10.0f, 1.0f, 500.0f);
	depthSlider.set("Profondeur Z", 10.0f, 1.0f, 500.0f);
	nbSidesSlider.set("Nombre de cotes", 6, 3, 20);

	platonSolidRadiusSlider.set("Rayon", 10.0f, 1.0f, 500.0f);

	primitivesGeometriquesPanel.add(selectedType);

	optionsGeneral.setup("General");
	optionsGeneral.add(strokeColorPicker);
	optionsGeneral.add(fillColorPicker);
	optionsGeneral.add(xCoordinateSlider);
	optionsGeneral.add(yCoordinateSlider);
	optionsGeneral.add(zCoordinateSlider);
	
	optionsPlatonSolid.setup("Polyedres reguliers");
	optionsPlatonSolid.add(platonSolidRadiusSlider);
	optionsPlatonSolid.add(drawTetrahedronType.setup("Tetrahedron"));
	optionsPlatonSolid.add(drawHexahedronType.setup("Hexahedron"));
	optionsPlatonSolid.add(drawOctahedronType.setup("Octahedron"));
	optionsPlatonSolid.add(drawDodecahedronType.setup("Dodecahedron"));
	optionsPlatonSolid.add(drawIcosahedronType.setup("Icosahedron"));
	optionsPlatonSolid.add(drawSphereType.setup("Sphere"));

	optionsOtherShapes.setup("Autres formes");
	optionsOtherShapes.add(widthSlider);
	optionsOtherShapes.add(heightSlider);
	optionsOtherShapes.add(depthSlider);
	optionsOtherShapes.add(nbSidesSlider);
	optionsOtherShapes.add(drawPolygonType.setup("Polygone"));
	optionsOtherShapes.add(drawCylinderType.setup("Cylindre"));
	optionsOtherShapes.add(drawConeType.setup("Cone"));
	optionsOtherShapes.add(drawEllipseType.setup("Ellipse"));
	optionsOtherShapes.add(drawRectangleType.setup("Prisme rectangulaire"));

	optionsAction.setup("Actions");
	optionsAction.add(selectButton.setup("Selectionner"));
	optionsAction.add(deselectButton.setup("Deselectionner"));
	optionsAction.add(deleteButton.setup("Supprimer"));
	optionsAction.add(placeObjectButton.setup("Placer objet"));
	
	primitivesGeometriquesPanel.add(&optionsGeneral);
	primitivesGeometriquesPanel.add(&optionsPlatonSolid);
	primitivesGeometriquesPanel.add(&optionsOtherShapes);
	primitivesGeometriquesPanel.add(&optionsAction);

	optionsPlatonSolid.minimize();
	optionsOtherShapes.minimize();
	
	drawTetrahedronType.addListener(this, &PrimitivesGeometriquesGui::selectTetrahedronType);
	drawHexahedronType.addListener(this, &PrimitivesGeometriquesGui::selectHexahedronType);
	drawOctahedronType.addListener(this, &PrimitivesGeometriquesGui::selectOctahedronType);
	drawDodecahedronType.addListener(this, &PrimitivesGeometriquesGui::selectDodecahedronType);
	drawIcosahedronType.addListener(this, &PrimitivesGeometriquesGui::selectIcosahedronType);
	drawSphereType.addListener(this, &PrimitivesGeometriquesGui::selectSphereType);

	drawPolygonType.addListener(this, &PrimitivesGeometriquesGui::selectPolygonType);
	drawCylinderType.addListener(this, &PrimitivesGeometriquesGui::selectCylinderType);
	drawConeType.addListener(this, &PrimitivesGeometriquesGui::selectConeType);
	drawEllipseType.addListener(this, &PrimitivesGeometriquesGui::selectEllipseType);
	drawRectangleType.addListener(this, &PrimitivesGeometriquesGui::selectRectangleType);

	placeObjectButton.addListener(this, &PrimitivesGeometriquesGui::placeObjectAction);
	selectButton.addListener(this, &PrimitivesGeometriquesGui::selectAction);
	deselectButton.addListener(this, &PrimitivesGeometriquesGui::deselectAction);
	deleteButton.addListener(this, &PrimitivesGeometriquesGui::deleteAction);
}

void PrimitivesGeometriquesGui::update()
{

}

void PrimitivesGeometriquesGui::draw()
{
	primitivesGeometriquesPanel.draw();
}

void PrimitivesGeometriquesGui::selectTetrahedronType()
{
	//textureDrawer.selectTetrahedronType();
	selectedType.set("Tetrahedron");
}

void PrimitivesGeometriquesGui::selectHexahedronType()
{
	//textureDrawer.selectHexahedronType();
	selectedType.set("Hexahedron");
}

void PrimitivesGeometriquesGui::selectOctahedronType()
{
	//textureDrawer.selectOctahedronType();
	selectedType.set("Octahedron");
}

void PrimitivesGeometriquesGui::selectDodecahedronType()
{
	//textureDrawer.selectDodecahedronType();
	selectedType.set("Dodecahedron");
}

void PrimitivesGeometriquesGui::selectIcosahedronType()
{
	//textureDrawer.selectIcosahedronType();
	selectedType.set("Icosahedron");
}

void PrimitivesGeometriquesGui::selectSphereType()
{
	//textureDrawer.selectSphereType();
	selectedType.set("Sphere");
}

void PrimitivesGeometriquesGui::selectEllipseType()
{
	//textureDrawer.selectEllipseType();
	selectedType.set("Ellipse");
}

void PrimitivesGeometriquesGui::selectPolygonType()
{
	//textureDrawer.selectPolygonType();
	selectedType.set("Polygone");
}

void PrimitivesGeometriquesGui::selectCylinderType()
{
	//textureDrawer.selectCylinderType();
	selectedType.set("Cylindre");
}

void PrimitivesGeometriquesGui::selectRectangleType()
{
	//textureDrawer.selectRectangleType();
	selectedType.set("Rectangle");
}

void PrimitivesGeometriquesGui::selectConeType()
{
	//textureDrawer.selectConeType();
	selectedType.set("Cone");
}

void PrimitivesGeometriquesGui::selectAction()
{
	//textureDrawer.selectSelectionType();
	selectedType.set("Selection");
}

void PrimitivesGeometriquesGui::deleteAction()
{
	//textureDrawer.deleteSelectedShapes();
}

void PrimitivesGeometriquesGui::deselectAction()
{
	//textureDrawer.resetSelection();
}

void PrimitivesGeometriquesGui::placeObjectAction()
{

}