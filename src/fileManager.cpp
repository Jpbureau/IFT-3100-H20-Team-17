#include "fileManager.h"

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