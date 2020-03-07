#include "colorHistogramGui.h"

//ColorHistogramGui::ColorHistogramGui(Renderer* renderer) : ptrRenderer(renderer)
ColorHistogramGui::ColorHistogramGui(ColorHistogram& histogram, TextureDrawer& textureDrawer) 
	: colorHistogram(histogram), textureDrawer(textureDrawer)
{

}

void ColorHistogramGui::setup(int positionXInitiale, int positionYInitiale, int histogramXPosition, int histogramYPosition, int histogramWidth, int histogramHeight)
{
	histogramPanel.setup("Histogramme de couleurs");
	histogramPanel.setPosition(positionXInitiale, positionYInitiale);
	histogramBinSizeSlider.set("Couleurs par groupe", 64, 32, 128);
	histogramCurrentStatus.setName("MAJ auto.: ");
	histogramCurrentStatus.set("Non");

	histogramWidthSlider.set("Largeur", histogramWidth, 200, 1000);
	histogramHeightSlider.set("Hauteur", histogramHeight, 100, 600);
	histogramXPositionSlider.set("Position X", histogramXPosition, 0, ofGetWidth());
	histogramYPositionSlider.set("Position Y", histogramYPosition, 0, ofGetHeight());

	histogramPanel.add(histogramShow.setup("Afficher Histogramme"));
	histogramPanel.add(histogramCurrentStatus);
	histogramPanel.add(histogramUpdate.setup("Activer MAJ auto."));
	histogramPanel.add(histogramUpdateOnce.setup("MAJ histogramme"));
	histogramPanel.add(histogramBinSizeSlider);
	histogramPanel.add(histogramWidthSlider);
	histogramPanel.add(histogramHeightSlider);
	histogramPanel.add(histogramXPositionSlider);
	histogramPanel.add(histogramYPositionSlider);

	histogramShow.addListener(this, &ColorHistogramGui::showHistogram);
	histogramUpdate.addListener(this, &ColorHistogramGui::toggleAutomaticHistogramUpdate);
	histogramUpdateOnce.addListener(this, &ColorHistogramGui::updateOnce);

}

bool ColorHistogramGui::getUpdateHistogram()
{
	
	return (histogramShown && (updateOnceBool || automaticUpdate));
	
	//return (histogramShown && updateOnceBool);

	
}

bool ColorHistogramGui::getHistogramShown()
{
	return (histogramShown);
}

void ColorHistogramGui::update()
{
	if (getUpdateHistogram())
	{
		colorHistogram.updateProperties(histogramWidthSlider, histogramHeightSlider, histogramXPositionSlider, histogramYPositionSlider);

		ofPixels pixels = textureDrawer.grabCanvasScreen().getPixels();
		colorHistogram.showHistogram(pixels, histogramBinSizeSlider);
		updateOnceBool = false;
	}
}

bool ColorHistogramGui::getAutomaticUpdate()
{
	return automaticUpdate;
}

void ColorHistogramGui::updateOnce()
{
	updateOnceBool = true;
}

void ColorHistogramGui::draw()
{
	if (histogramShown)
	{
		colorHistogram.draw();
	}
	histogramPanel.draw();
}

void ColorHistogramGui::toggleAutomaticHistogramUpdate()
{
	automaticUpdate = !automaticUpdate;
	if (automaticUpdate)
	{
		histogramCurrentStatus.set("Oui");
	}
	else
	{
		histogramCurrentStatus.set("Non");
	}
}

void ColorHistogramGui::showHistogram()
{
	histogramShown = !histogramShown;
	if (histogramShown)
	{
		updateOnceBool = true;
	}
}
