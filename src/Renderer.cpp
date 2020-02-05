#include "Renderer.h"

Renderer::Renderer(const FileManager & fileManager) :
	fileManager(fileManager)
{
}

void Renderer::setup()
{

	//exportButton.addListener(this, &Renderer::exportButtonPressed);

	//gui.setup("Test");
	//gui.add(exportButton.setup("Export Image"));
	
	/*
	// importer une image située dans ./bin/data
	image.load("scorpion.jpg");

	// redimensionner la fenêtre selon la résolution de l'image
	ofSetWindowShape(image.getWidth(), image.getHeight());*/
}

void Renderer::draw()
{
	// afficher l'image sur toute la surface de la fenêtre d'affichage
	//image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	ofBackgroundGradient(ofColor::white, ofColor::gray);
	ofSetColor(255, 130, 0);
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 50);

	//gui.draw();
}

void Renderer::drawImage(ofImage p_image)
{
	p_image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	cout << "j'ai été dessiné" << endl;
}

/*void Renderer::exportButtonPressed()
{
	fileManager.saveImage();
}*/