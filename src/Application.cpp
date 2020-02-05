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

// fonction invoqu�e quand une s�lection de fichiers est d�pos�e sur la fen�tre de l'application
void Application::dragEvent(ofDragInfo dragInfo)
{
	ofLog() << "<app::ofDragInfo file[0]: " << dragInfo.files.at(0)
		<< " at : " << dragInfo.position << ">";

	// Path du fichier � importer
	string pathFichierSrc = dragInfo.files.at(0);
	cout << pathFichierSrc << endl;

	// Instance du fichier � importer
	ofFile fileToRead(ofToDataPath(pathFichierSrc));
	cout << fileToRead.getFileName() << endl;
	cout << fileToRead.path() << endl;

	// Copie du fichier image dans le /bin/data
	//fileToRead.copyTo("C:\Users\Brandon Tardif\Developper\of_v0.11.0_vs2017_release\apps\myApps\IFT - 3100 - H20 - Team - 17\bin\data", true, true);
	string pathFichierDest = "..\bin\data";
	fileToRead.copyFromTo(pathFichierSrc, pathFichierDest);


	// importer le premier fichier d�pos� sur la fen�tre si c'est une image (attention : aucune validation du type de fichier)
	//renderer.image.load(pathFichier);
	//renderer.draw();

	// redimensionner la fen�tre selon la r�solution de l'image
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
		cout << "Bouton importation click�" << endl;
	}*/
}

void Application::buttonImportation_pressed()
{
	ofImage image = fileManager.image_import();
	renderer.drawImage(image);
	ofLog() << "Importation button pressed>";
}