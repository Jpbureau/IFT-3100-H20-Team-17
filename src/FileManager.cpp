#include <fstream>
#include "FileManager.h"
#include "Renderer.h"

// fonction qui exporte une image à partir de son nom et de son extension, à partir du répertoire ./bin/data ou d'un chemin absolue
void FileManager::image_export(const string name, const string extension, const string option) const
{
	ofImage image;
	string qualityOption;

	// générer un nom de fichier unique et ordonné
	string file_name = name + option + "." + extension;

	// capturer le contenu du framebuffer actif
	image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	if (qualityOption == "high") {
		image.save(file_name, OF_IMAGE_QUALITY_HIGH);
	}
	else if (qualityOption == "medium") {
		image.save(file_name, OF_IMAGE_QUALITY_MEDIUM);
	}
	else if (qualityOption == "low") {
		image.save(file_name, OF_IMAGE_QUALITY_LOW);
	}
	else if ("worst") {
		image.save(file_name, OF_IMAGE_QUALITY_WORST);
	}
	else {
		image.save(file_name);
	}

	ofLog() << "<export image: " << file_name << ">";
}

void FileManager::saveImage() const
{
	ofFileDialogResult result = ofSystemSaveDialog("render.png", "Image Export");

	if (result.bSuccess) {
		ofImage image;
		image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		image.save(result.getPath());

		ofLog() << "<export image: " << result.getPath() << ">";
	}
}

/**
	Entrée : Une référence vers un fichier image existant (chemin d'accès local ou URL)
	Sortie : Une texture générée à partir de l'image, chargée en mémoire GPU, adéquatement configurée et prête à l'utilisation
*/
void FileManager::image_import1(const string name, const string extension) const
{
	// Ouvrir le fichier image en mode lecture et en extraire les propriétés
	ofstream monFichier;
	monFichier.open(name + "." + extension);

	if (monFichier.is_open())
	{

	}

	int image_width;
	int image_height;
	int image_component;
	int image_pixel_count;
	int image_size;
	
	// Calculer le nombre total de pixels de l'image
	image_pixel_count = image_width * image_height;

	// Calculer le nombre d'octets à allouer en mémoire pour contenir l'image
	image_size = image_pixel_count * image_component;

	// Déclarer un pointeur vers un espace mémoire qui servira à stocker les pixels de l'image
	GLubyte* pixels;

	// Allocation d'un espace mémoire suffisament grand pour contenir tous les pixels de l'image
	pixels = (GLubyte*)std::malloc(image_size * sizeof(GLubyte));

	// Lire le contenu de l'image et copier ses pixels en mémoire (RAM)


	// Déclarer un identifiant pour référencer la texture
	GLuint texture_id;

	// Création d'un identifiant pour une nouvelle texture
	glGenTextures(1, &texture_id);

	// Sélectionner cette nouvelle texture comme texture active
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// Définir les paramètres d'enveloppement aux extrémités de la texture active
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Définir les paramètres d'interpolation des texels de la texture active (mémoire GPU)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Copier les pixels de l'image(mémoire RAM) vers la texture active (mémoire GPU)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	
	// Générer les différents niveaux de mipmapping de la texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// La copie de l'image en mémoire RAM peut maintenant être supprimée car une copie exite maintenant en mémoire GPU
	std::free(pixels);
}

ofImage FileManager::image_import() const
{
	ofImage image;
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		cout << path << endl;
		image.load(path);
	}
	return image;
}
