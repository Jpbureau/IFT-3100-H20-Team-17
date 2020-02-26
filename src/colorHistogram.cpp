#include "colorHistogram.h"
#include "ofMain.h"

void ColorHistogram::setup()
{
	//Un peu comme on fait dans le cours, on pourrait éventuellement penser à une meilleure structure de données
	count = 512;

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
		ofNoFill();
		ofSetColor(0);
		draw_rectangle(
			shapes[index].position1[0],
			shapes[index].position1[1],
			shapes[index].position2[0],
			shapes[index].position2[1]);
		
	}
}

void ColorHistogram::showHistogram(ofPixels p_pixels, int binSize)
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

	//unsigned int histogram[nbBins][nbBins][nbBins] = { 0 };

	unsigned int i = 0;
	ofColor color;

	unsigned int maxBin = 0;
	int imageSize = p_pixels.size();

	while (i < imageSize)
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
	
	
	//Test
	/*
	maxBin = 512;
	for (int r = 0; r < nbBins; r++)
	{
		for (int g = 0; g < nbBins; g++)
		{
			for (int b = 0; b < nbBins; b++)
			{
				histogram[r][g][b] = 512; // Réinitialisation de l'histogramme
			}
		}
	}
	*/

	unsigned char averageRedColor;
	unsigned char averageGreenColor;
	unsigned char averageBlueColor;
	int binWidth = 600 / (nbBins * nbBins * nbBins);
	int binHeight;
	int positionX = 825;
	int positionY = ofGetHeight() / 3.5 + 600;


	int total = 0;
	
	for (int r = 0; r < nbBins; r++)
	{
		for (int g = 0; g < nbBins; g++)
		{
			for (int b = 0; b < nbBins; b++)
			{
				averageRedColor = (r * binSize + min(maxColors - 1, (r + 1) * binSize - 1)) / 2;
				averageGreenColor = (g * binSize + min(maxColors - 1, (g + 1) * binSize - 1)) / 2;
				averageBlueColor = (b * binSize + min(maxColors - 1, (b + 1) * binSize - 1)) / 2;
				binHeight = (histogram[r][g][b] * 600) / maxBin;

				shapes[head].fill_color[0] = averageRedColor;
				shapes[head].fill_color[1] = averageGreenColor;
				shapes[head].fill_color[2] = averageBlueColor;
				shapes[head].fill_color[3] = 255; //Max alpha

				shapes[head].position1[0] = positionX + binWidth*head;
				shapes[head].position1[1] = positionY;
				shapes[head].position2[0] = positionX + binWidth * (head + 1);
				shapes[head].position2[1] = positionY - binHeight;

				head++;

				total += histogram[r][g][b];

				//cout << "Rouge (" << r * binSize << "-" << (r + 1) * binSize - 1 << ") ";
				//cout << "Vert(" << g * binSize << "-" << (g + 1) * binSize - 1 << ") ";
				//cout << "Bleu(" << b * binSize << "-" << (b + 1) * binSize - 1 << "): "; 
				//cout << histogram[r][g][b] << endl;
			}
		}
	}
	cout << "Total: " << total << endl;
	cout << "Image Size: " << imageSize << endl;
}

void ColorHistogram::draw_rectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}
