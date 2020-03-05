#include "primitivesGeometriquesGui.h"

PrimitivesGeometriquesGui::PrimitivesGeometriquesGui(TextureDrawer3D& drawer) :
	textureDrawer3D(drawer)
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
	textureDrawer3D.updateColors(strokeColorPicker, fillColorPicker);
	textureDrawer3D.updateCoordinates(xCoordinateSlider, yCoordinateSlider, zCoordinateSlider);
	textureDrawer3D.updateRadius(platonSolidRadiusSlider);
	textureDrawer3D.updateDimensions(widthSlider, heightSlider, depthSlider);
	textureDrawer3D.updateNbSides(nbSidesSlider);

}

void PrimitivesGeometriquesGui::draw()
{
	primitivesGeometriquesPanel.draw();
}

void PrimitivesGeometriquesGui::selectTetrahedronType()
{
	selectedType.set("Tetrahedron");
	textureDrawer3D.selectTetrahedronType();
}

void PrimitivesGeometriquesGui::selectHexahedronType()
{
	
	selectedType.set("Hexahedron");
	textureDrawer3D.selectHexahedronType();
}

void PrimitivesGeometriquesGui::selectOctahedronType()
{
	
	selectedType.set("Octahedron");
	textureDrawer3D.selectOctahedronType();
}

void PrimitivesGeometriquesGui::selectDodecahedronType()
{
	
	selectedType.set("Dodecahedron");
	textureDrawer3D.selectDodecahedronType();
}

void PrimitivesGeometriquesGui::selectIcosahedronType()
{
	
	selectedType.set("Icosahedron");
	textureDrawer3D.selectIcosahedronType();
}

void PrimitivesGeometriquesGui::selectSphereType()
{
	
	selectedType.set("Sphere");
	textureDrawer3D.selectSphereType();
}

void PrimitivesGeometriquesGui::selectEllipseType()
{
	
	selectedType.set("Ellipse");
	textureDrawer3D.selectEllipseType();
}

void PrimitivesGeometriquesGui::selectPolygonType()
{
	
	selectedType.set("Polygone");
	textureDrawer3D.selectPolygonType();
}

void PrimitivesGeometriquesGui::selectCylinderType()
{
	
	selectedType.set("Cylindre");
	textureDrawer3D.selectCylinderType();
}

void PrimitivesGeometriquesGui::selectRectangleType()
{
	
	selectedType.set("Rectangle");
	textureDrawer3D.selectRectangleType();
}

void PrimitivesGeometriquesGui::selectConeType()
{
	
	selectedType.set("Cone");
	textureDrawer3D.selectConeType();
}

void PrimitivesGeometriquesGui::selectAction()
{
	selectedType.set("Selection");
}

void PrimitivesGeometriquesGui::deleteAction()
{
	
}

void PrimitivesGeometriquesGui::deselectAction()
{
	
}

void PrimitivesGeometriquesGui::placeObjectAction()
{

}