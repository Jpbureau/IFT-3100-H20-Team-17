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
	// importer une image situ�e dans ./bin/data
	image.load("scorpion.jpg");

	// redimensionner la fen�tre selon la r�solution de l'image
	ofSetWindowShape(image.getWidth(), image.getHeight());*/
}

void Renderer::draw()
{
	// afficher l'image sur toute la surface de la fen�tre d'affichage
	//image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	ofBackgroundGradient(ofColor::white, ofColor::gray);
	ofSetColor(255, 130, 0);
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 50);

	//gui.draw();
}

void Renderer::drawImage(ofImage p_image)
{
	p_image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	cout << "j'ai �t� dessin�" << endl;
}

/*void Renderer::exportButtonPressed()
{
	fileManager.saveImage();
}*/