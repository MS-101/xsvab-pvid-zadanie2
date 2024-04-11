# Počítačové videnie - úloha 2

**Autor: Martin Šváb**

## Vstup

Tento obrázok je použitý ako vstup vo všetkých nasledujúcich úlohách. 

![](xsvab-pvid-zadanie2\output\input.jpg)

## Histogram

Pri všetkých experimentoch s normalizáciou histogramov používame totožný algoritmus. Najskôr konvertujeme vstupný obrázok do nášho zvoleného farebného priestoru. Kanály konvertovaného obrázka rozdelíme a individuálne na nich vykonáme histogramovu equalizáciu. Upravenné kanály spojíme a získame tak výstupný obrázok, ktorý spätne konvertujeme do BGR farebného priestoru. z kanálov pôvodného aj upraveného obrázka vypočítame a zobrazíme histogramy. 

	void histogram(cv::Mat input, cv::ColorConversionCodes conversion, cv::ColorConversionCodes inverseConversion,
		std::vector<std::string> channelNames, std::vector<cv::Scalar> colors, bool corrections[], const float* ranges[], OutputArgs outputArgs)
	{
		// convert image from bgr to different color space
		cv::Mat converted;
		cv::cvtColor(input, converted, conversion);
		outputImage(converted, outputArgs);
	
		// split image channels
		std::vector<cv::Mat> channels;
		cv::split(converted, channels);
		int channelCount = channels.size();
	
		// correct channels with histogram equalization
		std::vector<cv::Mat> channelsCorrected(channelCount);
		for (int i = 0; i < channelCount; i++) {
			if (corrections[i])
				cv::equalizeHist(channels[i], channelsCorrected[i]);
			else
				channelsCorrected[i] = channels[i];
		}
	
		// merge corrected channels
		cv::Mat corrected;
		cv::merge(channelsCorrected, corrected);
	
		// display histogram of original image
		std::vector<cv::Mat> hist(channelCount);
		calcHist(channels, hist, ranges);
		displayHist(hist, colors, channelNames, { "hist_" + outputArgs.name, outputArgs.dir, outputArgs.extension });
	
		// display histogram of corrected image
		std::vector<cv::Mat> histCorrected(channelCount);
		calcHist(channelsCorrected, histCorrected, ranges);
		displayHist(histCorrected, colors, channelNames, { "hist_" + outputArgs.name + "_corrected", outputArgs.dir, outputArgs.extension });
	
		// display corrected image
		cv::Mat output;
		cv::cvtColor(corrected, output, inverseConversion);
		outputImage(output, { outputArgs.name + "_corrected", outputArgs.dir, outputArgs.extension });
	
		cv::waitKey();
	}

Výstup všetkých experimentov ekvalizácie histogramov má totožný formát. Horný obrázok obsahuje naľavo histogram pred ekvalizáciou a napravo histogram po ekvalizácii. Spodný obrázok obsahuje naľavo vstupný obrázok a napravo výstupný obrázok.

### Histogram - Grayscale

![](xsvab-pvid-zadanie2\output\histogram\grayscale\histMerged.jpg)

![](xsvab-pvid-zadanie2\output\histogram\grayscale\imagesMerged.jpg)

### Histogram - HSV

![](xsvab-pvid-zadanie2\output\histogram\hsv\histMerged.jpg)

![](xsvab-pvid-zadanie2\output\histogram\hsv\imagesMerged.jpg)

### Histogram - LAB

![](xsvab-pvid-zadanie2\output\histogram\lab\histMerged.jpg)

![](xsvab-pvid-zadanie2\output\histogram\lab\imagesMerged.jpg)

### Histogram - RGB

![](xsvab-pvid-zadanie2\output\histogram\rgb\histMerged.jpg)

![](xsvab-pvid-zadanie2\output\histogram\rgb\imagesMerged.jpg)

### Histogram - XYZ

![](xsvab-pvid-zadanie2\output\histogram\xyz\histMerged.jpg)

![](xsvab-pvid-zadanie2\output\histogram\xyz\imagesMerged.jpg)

### Histogram - YCrCb

![](xsvab-pvid-zadanie2\output\histogram\ycc\histMerged.jpg)

![](xsvab-pvid-zadanie2\output\histogram\ycc\imagesMerged.jpg)
