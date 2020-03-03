#include "colorHistogramGui.h"

//ColorHistogramGui::ColorHistogramGui(Renderer* renderer) : ptrRenderer(renderer)
ColorHistogramGui::ColorHistogramGui(ColorHistogram& histogram) 
	: colorHistogram(histogram)
{

}

void ColorHistogramGui::setup(int positionXInitiale, int positionYInitiale)
{
	histogramPanel.setup("Histogramme de couleurs");
	histogramPanel.setPosition(positionXInitiale, positionYInitiale);
	histogramBinSizeSlider.set("Couleurs par groupe", 64, 32, 128);
	histogramCurrentStatus.setName("MAJ auto.: ");
	histogramCurrentStatus.set("Non");

	histogramPanel.add(histogramShow.setup("Afficher Histogramme"));
	histogramPanel.add(histogramCurrentStatus);
	histogramPanel.add(histogramUpdate.setup("Activer MAJ auto."));
	histogramPanel.add(histogramUpdateOnce.setup("MAJ histogramme"));
	histogramPanel.add(histogramBinSizeSlider);

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

void ColorHistogramGui::update(ofPixels& p_pixels)
{
	colorHistogram.showHistogram(p_pixels, histogramBinSizeSlider);
	updateOnceBool = false;
	
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
	histogramPanel.draw();
	if (histogramShown)
	{
		colorHistogram.draw();
	}
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
