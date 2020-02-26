#include "colorHistogram.h"
#include "ofMain.h"

void ColorHistogram::setup()
{
	//Un peu comme on fait dans le cours, on pourrait éventuellement penser à une meilleure structure de données
	count = 48;

	head = 0;

	stride = sizeof(RectangleHistogramme);

	size = count * stride;

	shapes = (RectangleHistogramme*)std::malloc(size);

}

void ColorHistogram::update()
{

}

void ColorHistogram::draw()
{
	cout << "What?" << endl;

	for (int index = 0; index < head; index++)
	{
		ofFill();
		ofSetLineWidth(1);
		ofSetColor(
			shapes[head].fill_color[0],
			shapes[head].fill_color[1],
			shapes[head].fill_color[2],
			shapes[head].fill_color[3]);
		draw_rectangle(
			shapes[head].position1[0],
			shapes[head].position1[1],
			shapes[head].position2[0],
			shapes[head].position2[1]);
		ofNoFill();
		ofSetColor(0);
		draw_rectangle(
			shapes[head].position1[0],
			shapes[head].position1[1],
			shapes[head].position2[0],
			shapes[head].position2[1]);
	}
}

void ColorHistogram::showHistogram(ofPixels p_pixels, int binSize)
{
	
	head = 0;

	const int maxColors = 256; //0 - 255
	const int nbBins = maxColors / binSize;

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

	//unsigned int histogram[nbBins][nbBins][nbBins] = { 0 };

	unsigned int i = 0;
	ofColor color;

	unsigned int maxBin = 0;

	while (i < p_pixels.size())
	{
		color = p_pixels.getColor(i);
		
		rBin = color.r / binSize;
		gBin = color.g / binSize;
		bBin = color.b / binSize;
		histogram[rBin][gBin][bBin]++;
		if (histogram[rBin][gBin][bBin] > maxBin)
		{
			maxBin++;
		}
		i++;
	}

	unsigned char averageRedColor;
	unsigned char averageGreenColor;
	unsigned char averageBlueColor;
	int binWidth = 200 / nbBins;
	int binHeight;
	int positionX = 825;
	int positionY = ofGetHeight() / 3.5 + 600;

	//Affichage Histogramme ici
	for (int r = 0; r < nbBins; r++)
	{
		for (int g = 0; g < nbBins; g++)
		{
			for (int b = 0; b < nbBins; b++)
			{
				averageRedColor = (r * binSize + (r + 1) * binSize - 1) / 2;
				averageGreenColor = (g * binSize + (g + 1) * binSize - 1) / 2;
				averageBlueColor = (b * binSize + (b + 1) * binSize - 1) / 2;
				binHeight = (histogram[r][g][b] * 600) / maxBin;

				//int horizontalDistance = abs(mouse_current_posX - mouse_pressed_posX);
				//int verticalDistance = abs(mouse_current_posY - mouse_pressed_posY);

				//shapes[head].type = selectedType;

				shapes[head].fill_color[0] = averageRedColor;
				shapes[head].fill_color[1] = averageGreenColor;
				shapes[head].fill_color[2] = averageBlueColor;
				shapes[head].fill_color[3] = 255; //Max alpha

				shapes[head].position1[0] = positionX + binWidth*head;
				shapes[head].position1[1] = positionY;
				shapes[head].position2[0] = positionX + binWidth * (head + 1);
				shapes[head].position2[1] = positionY - binHeight;

				ofFill();
				ofSetLineWidth(1);
				ofSetColor(
					shapes[head].fill_color[0],
					shapes[head].fill_color[1],
					shapes[head].fill_color[2],
					shapes[head].fill_color[3]);
				draw_rectangle(
					shapes[head].position1[0],
					shapes[head].position1[1],
					shapes[head].position2[0],
					shapes[head].position2[1]);
				ofNoFill();
				ofSetColor(0);
				draw_rectangle(
					shapes[head].position1[0],
					shapes[head].position1[1],
					shapes[head].position2[0],
					shapes[head].position2[1]);

				head++;

				//cout << "Rouge (" << r * binSize << "-" << (r + 1) * binSize - 1 << ") ";
				//cout << "Vert(" << g * binSize << "-" << (g + 1) * binSize - 1 << ") ";
				//cout << "Bleu(" << b * binSize << "-" << (b + 1) * binSize - 1 << "): "; 
				//cout << histogram[r][g][b] << endl;
			}
		}
	}
	
}

void ColorHistogram::draw_rectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}
