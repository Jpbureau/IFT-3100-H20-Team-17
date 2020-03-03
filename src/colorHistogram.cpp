#include "colorHistogram.h"
#include "ofMain.h"

void ColorHistogram::setup(int width, int height, int positionX, int positionY)
{
	//Un peu comme on fait dans le cours, on pourrait éventuellement penser à une meilleure structure de données
	count = 515;

	head = 0;

	stride = sizeof(RectangleHistogramme);

	size = count * stride;

	shapes = (RectangleHistogramme*)std::malloc(size);

	m_width = width;
	m_height = height;
	m_positionX = positionX;
	m_positionY = positionY;
}

void ColorHistogram::update()
{

}

void ColorHistogram::draw()
{
	
	for (int index = 0; index < head; index++)
	{
		ofFill();
		ofSetLineWidth(1);
		ofSetColor(
			shapes[index].fill_color[0],
			shapes[index].fill_color[1],
			shapes[index].fill_color[2],
			shapes[index].fill_color[3]);
		draw_rectangle(
			shapes[index].position1[0],
			shapes[index].position1[1],
			shapes[index].position2[0],
			shapes[index].position2[1]);
		if (head < (m_width/3)) //S'Il y a trop de colonnes, on ne met pas les outlines.
		{
			ofNoFill();
			ofSetColor(0);
			draw_rectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
		}
		
		
	}
}

void ColorHistogram::showHistogram(ofPixels& p_pixels, int binSize)
{
	
	head = 0;

	const int maxColors = 256; //0 - 255
	const int nbBins = ((maxColors - 1) / binSize) + 1;

	const int width = p_pixels.getWidth();
	const int height = p_pixels.getHeight();

	int rBin = 0;
	int gBin = 0;
	int bBin = 0;

	for (int r = 0; r < nbBins; r++)
	{
		for (int g = 0; g < nbBins; g++)
		{
			for (int b = 0; b < nbBins; b++)
			{
				histogram[r][g][b] = 0; // Réinitialisation de l'histogramme
			}
		}
	}
	histogramBlack = 0;
	histogramWhite = 0;


	unsigned int i = 0;
	ofColor color;

	unsigned int maxBin = 0;
	int imageSize = p_pixels.size();

	for (int yIndex = 0; yIndex < height; yIndex++)
	{
		for (int xIndex = 0; xIndex < width; xIndex++)
		{
			color = p_pixels.getColor(xIndex, yIndex);

			//Noir
			if (color.r == 0 && color.g == 0 && color.b == 0)
			{
				histogramBlack++;
				if (histogramBlack > maxBin)
				{
					maxBin++;
				}
			}
			//Blanc
			else if (color.r == maxColors - 1 && color.g == maxColors - 1 && color.b == maxColors - 1)
			{
				histogramWhite++;
				if (histogramWhite > maxBin)
				{
					maxBin++;
				}
			}
			//Autre
			else
			{
				rBin = color.r / binSize;
				gBin = color.g / binSize;
				bBin = color.b / binSize;
				histogram[rBin][gBin][bBin]++;
				if (histogram[rBin][gBin][bBin] > maxBin)
				{
					maxBin++;
				}
			}
		}
	}

	unsigned char averageRedColor;
	unsigned char averageGreenColor;
	unsigned char averageBlueColor;
	int binWidth = m_width / ((nbBins * nbBins * nbBins) + 2);
	int binHeight;

	//À vérifier: Où placer l'histogramme dans l'application.
	//Faudrait-il créer une nouvelle fenêtre?
	//positionX et positionY sont présentement défini dans colorHistogram.h
	//int positionX = 825;
	//int positionY = ofGetHeight() / 3.5 + 600;

	//Noir
	binHeight = (histogramBlack * m_height) / maxBin;

	shapes[head].fill_color[0] = 0;
	shapes[head].fill_color[1] = 0;
	shapes[head].fill_color[2] = 0;
	shapes[head].fill_color[3] = 255; //Max alpha

	shapes[head].position1[0] = m_positionX + binWidth * head;
	shapes[head].position1[1] = m_positionY;
	shapes[head].position2[0] = m_positionX + binWidth * (head + 1);
	shapes[head].position2[1] = m_positionY - binHeight;

	head++;
	
	//Couleur
	for (int r = 0; r < nbBins; r++)
	{
		for (int g = 0; g < nbBins; g++)
		{
			for (int b = 0; b < nbBins; b++)
			{
				averageRedColor = (r * binSize + min(maxColors - 1, (r + 1) * binSize - 1)) / 2;
				averageGreenColor = (g * binSize + min(maxColors - 1, (g + 1) * binSize - 1)) / 2;
				averageBlueColor = (b * binSize + min(maxColors - 1, (b + 1) * binSize - 1)) / 2;
				binHeight = (histogram[r][g][b] * m_height) / maxBin;

				shapes[head].fill_color[0] = averageRedColor;
				shapes[head].fill_color[1] = averageGreenColor;
				shapes[head].fill_color[2] = averageBlueColor;
				shapes[head].fill_color[3] = 255; //Max alpha

				shapes[head].position1[0] = m_positionX + binWidth*head;
				shapes[head].position1[1] = m_positionY;
				shapes[head].position2[0] = m_positionX + binWidth * (head + 1);
				shapes[head].position2[1] = m_positionY - binHeight;

				head++;

				//cout << "Rouge (" << r * binSize << "-" << (r + 1) * binSize - 1 << ") ";
				//cout << "Vert(" << g * binSize << "-" << (g + 1) * binSize - 1 << ") ";
				//cout << "Bleu(" << b * binSize << "-" << (b + 1) * binSize - 1 << "): "; 
				//cout << histogram[r][g][b] << endl;
			}
		}
	}

	//Blanc
	binHeight = (histogramWhite * m_height) / maxBin;

	shapes[head].fill_color[0] = maxColors - 1;
	shapes[head].fill_color[1] = maxColors - 1;
	shapes[head].fill_color[2] = maxColors - 1;
	shapes[head].fill_color[3] = 255; //Max alpha

	shapes[head].position1[0] = m_positionX + binWidth * head;
	shapes[head].position1[1] = m_positionY;
	shapes[head].position2[0] = m_positionX + binWidth * (head + 1);
	shapes[head].position2[1] = m_positionY - binHeight;

	head++;

}

void ColorHistogram::draw_rectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}
