# Počítačové videnie - úloha 2

**Autor: Martin Šváb**

## Vstup

Tento obrázok je použitý ako vstup vo všetkých nasledujúcich úlohách. 

![](xsvab-pvid-zadanie2\output\input.png)

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

## Gamma

Gamma = -0.5:

![](xsvab-pvid-zadanie2\output\gamma\gamma0.png)

Gamma = 0.5:

![](xsvab-pvid-zadanie2\output\gamma\gamma1.png)

Gamma = 1.5:

![](xsvab-pvid-zadanie2\output\gamma\gamma2.png)

Gamma = 2.5:

![](xsvab-pvid-zadanie2\output\gamma\gamma3.png)

## CDF

Tento obrázok je použitý ako cieľový obrázok pri korekcii farieb pomocou cdf:

![](xsvab-pvid-zadanie2\output\cdf\target.png)

### CDF - RGB

Vstupný obrázok konvertovaný do RGB:

![](xsvab-pvid-zadanie2\output\cdf\rgb\rgb_input.png)

Cieľový obrázok konvertovaný do RGB:

![](xsvab-pvid-zadanie2\output\cdf\rgb\rgb_target.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\cdf\rgb\hist_rgb_input.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\cdf\rgb\hist_rgb_target.png)

CDF vstupného obrázka:

![](xsvab-pvid-zadanie2\output\cdf\rgb\cdf_rgb_input.png)

CDF cieľového obrázka:

![](xsvab-pvid-zadanie2\output\cdf\rgb\cdf_rgb_target.png)

Výstupný obrázok (po konverzii do BGR):

![](xsvab-pvid-zadanie2\output\cdf\rgb\rgb_corrected.png)

### CDF - YCrCb

Vstupný obrázok konvertovaný do YCrCb:

![](xsvab-pvid-zadanie2\output\cdf\ycc\ycc_input.png)

Cieľový obrázok konvertovaný do YCrCb:

![](xsvab-pvid-zadanie2\output\cdf\ycc\ycc_target.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\cdf\ycc\hist_ycc_input.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\cdf\ycc\hist_ycc_target.png)

CDF vstupného obrázka:

![](xsvab-pvid-zadanie2\output\cdf\ycc\cdf_ycc_input.png)

CDF cieľového obrázka:

![](xsvab-pvid-zadanie2\output\cdf\ycc\cdf_ycc_target.png)

Výstupný obrázok (po konverzii do BGR):

![](xsvab-pvid-zadanie2\output\cdf\ycc\ycc_corrected.png)

## Segmentácia

Vstupný obrázok konvertovaný do Lab:

![](xsvab-pvid-zadanie2\output\segmentation\input_lab.png)

Maska pre nukleid:

![](xsvab-pvid-zadanie2\output\segmentation\nuclei.png)

Delta lab:

![](xsvab-pvid-zadanie2\output\segmentation\delta_lab.png)

Threshold vypočítaný z delta lab:

![](xsvab-pvid-zadanie2\output\segmentation\threshold.png)

Výstupný obrázok:

![](xsvab-pvid-zadanie2\output\segmentation\output.png)