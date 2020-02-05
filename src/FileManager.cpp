#include <fstream>
#include "FileManager.h"
#include "Renderer.h"

// fonction qui exporte une image � partir de son nom et de son extension, � partir du r�pertoire ./bin/data ou d'un chemin absolue
void FileManager::image_export(const string name, const string extension, const string option) const
{
	ofImage image;
	string qualityOption;

	// g�n�rer un nom de fichier unique et ordonn�
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
	Entr�e : Une r�f�rence vers un fichier image existant (chemin d'acc�s local ou URL)
	Sortie : Une texture g�n�r�e � partir de l'image, charg�e en m�moire GPU, ad�quatement configur�e et pr�te � l'utilisation
*/
void FileManager::image_import1(const string name, const string extension) const
{
	// Ouvrir le fichier image en mode lecture et en extraire les propri�t�s
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

	// Calculer le nombre d'octets � allouer en m�moire pour contenir l'image
	image_size = image_pixel_count * image_component;

	// D�clarer un pointeur vers un espace m�moire qui servira � stocker les pixels de l'image
	GLubyte* pixels;

	// Allocation d'un espace m�moire suffisament grand pour contenir tous les pixels de l'image
	pixels = (GLubyte*)std::malloc(image_size * sizeof(GLubyte));

	// Lire le contenu de l'image et copier ses pixels en m�moire (RAM)


	// D�clarer un identifiant pour r�f�rencer la texture
	GLuint texture_id;

	// Cr�ation d'un identifiant pour une nouvelle texture
	glGenTextures(1, &texture_id);

	// S�lectionner cette nouvelle texture comme texture active
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// D�finir les param�tres d'enveloppement aux extr�mit�s de la texture active
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// D�finir les param�tres d'interpolation des texels de la texture active (m�moire GPU)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Copier les pixels de l'image(m�moire RAM) vers la texture active (m�moire GPU)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	
	// G�n�rer les diff�rents niveaux de mipmapping de la texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// La copie de l'image en m�moire RAM peut maintenant �tre supprim�e car une copie exite maintenant en m�moire GPU
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
