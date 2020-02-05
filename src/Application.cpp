#include "Application.h"

void Application::setup()
{
	ofSetWindowTitle("Travail pratique 1");

	//boutonImportation = gui->addButton("Importation");
	//gui->onButtonEvent(this, &Application::onButtonEvent);

	ofLog() << "<app::setup>";

	renderer.setup();

	gui.setup("interface");
	importButton.setup("Importation");
	importButton.addListener(this, &Application::buttonImportation_pressed);
	gui.add(&importButton);
}

void Application::draw()
{
	renderer.draw();
	gui.draw();
}

/*void Application::windowResized(int w, int h)
{
	ofLog() << "<app::windowResized to: (" << w << ", " << h << ")>";
}*/

// fonction invoquée quand une sélection de fichiers est déposée sur la fenêtre de l'application
void Application::dragEvent(ofDragInfo dragInfo)
{
	ofLog() << "<app::ofDragInfo file[0]: " << dragInfo.files.at(0)
		<< " at : " << dragInfo.position << ">";

	// Path du fichier à importer
	string pathFichierSrc = dragInfo.files.at(0);
	cout << pathFichierSrc << endl;

	// Instance du fichier à importer
	ofFile fileToRead(ofToDataPath(pathFichierSrc));
	cout << fileToRead.getFileName() << endl;
	cout << fileToRead.path() << endl;

	// Copie du fichier image dans le /bin/data
	//fileToRead.copyTo("C:\Users\Brandon Tardif\Developper\of_v0.11.0_vs2017_release\apps\myApps\IFT - 3100 - H20 - Team - 17\bin\data", true, true);
	string pathFichierDest = "..\bin\data";
	fileToRead.copyFromTo(pathFichierSrc, pathFichierDest);


	// importer le premier fichier déposé sur la fenêtre si c'est une image (attention : aucune validation du type de fichier)
	//renderer.image.load(pathFichier);
	//renderer.draw();

	// redimensionner la fenêtre selon la résolution de l'image
	if (renderer.image.getWidth() > 0 && renderer.image.getHeight() > 0)
		ofSetWindowShape(renderer.image.getWidth(), renderer.image.getHeight());
}

void Application::exit()
{
	ofLog() << "<app::exit>";
}

void Application::onButtonEvent(ofxDatGuiButtonEvent e)
{
	/*if (e.target == boutonImportation)
	{
		cout << "Bouton importation clické" << endl;
	}*/
}

void Application::buttonImportation_pressed()
{
	ofImage image = fileManager.image_import();
	renderer.drawImage(image);
	ofLog() << "Importation button pressed>";
}