# Počítačové videnie - úloha 2

**Autor: Martin Šváb**

## Vstup

Tento obrázok je použitý ako vstup vo všetkých nasledujúcich úlohách. 

![](xsvab-pvid-zadanie2\output\input.png)

## Histogram

### Histogram - Grayscale

Vstupný obrázok konvertovaný do Grayscale:

![](xsvab-pvid-zadanie2\output\histogram\grayscale\grayscale.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\histogram\grayscale\hist_grayscale.png)

Histogram vstupného obrázka po ekvalizácii:

![](xsvab-pvid-zadanie2\output\histogram\grayscale\hist_grayscale_corrected.png)

Výstupný obrázok

![](xsvab-pvid-zadanie2\output\histogram\grayscale\grayscale_corrected.png)

### Histogram - HSV

Vstupný obrázok konvertovaný do RGB:

![](xsvab-pvid-zadanie2\output\histogram\hsv\hsv.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\histogram\hsv\hist_hsv.png)

Histogram vstupného obrázka po ekvalizácii:

![](xsvab-pvid-zadanie2\output\histogram\hsv\hist_hsv_corrected.png)

Výstupný obrázok

![](xsvab-pvid-zadanie2\output\histogram\hsv\hsv_corrected.png)

### Histogram - LAB

Vstupný obrázok konvertovaný do RGB:

![](xsvab-pvid-zadanie2\output\histogram\lab\lab.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\histogram\lab\hist_lab.png)

Histogram vstupného obrázka po ekvalizácii:

![](xsvab-pvid-zadanie2\output\histogram\lab\hist_lab_corrected.png)

Výstupný obrázok

![](xsvab-pvid-zadanie2\output\histogram\lab\lab_corrected.png)

### Histogram - RGB

Vstupný obrázok konvertovaný do RGB:

![](xsvab-pvid-zadanie2\output\histogram\rgb\rgb.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\histogram\rgb\hist_rgb.png)

Histogram vstupného obrázka po ekvalizácii:

![](xsvab-pvid-zadanie2\output\histogram\rgb\hist_rgb_corrected.png)

Výstupný obrázok

![](xsvab-pvid-zadanie2\output\histogram\rgb\rgb_corrected.png)

### Histogram - XYZ

Vstupný obrázok konvertovaný do XYZ:

![](xsvab-pvid-zadanie2\output\histogram\xyz\xyz.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\histogram\xyz\hist_xyz.png)

Histogram vstupného obrázka po ekvalizácii:

![](xsvab-pvid-zadanie2\output\histogram\xyz\hist_xyz_corrected.png)

Výstupný obrázok

![](xsvab-pvid-zadanie2\output\histogram\xyz\xyz_corrected.png)

### Histogram - YCrCb

Vstupný obrázok konvertovaný do YCrCb:

![](xsvab-pvid-zadanie2\output\histogram\ycc\ycc.png)

Histogram vstupného obrázka:

![](xsvab-pvid-zadanie2\output\histogram\ycc\hist_ycc.png)

Histogram vstupného obrázka po ekvalizácii:

![](xsvab-pvid-zadanie2\output\histogram\ycc\hist_ycc_corrected.png)

Výstupný obrázok

![](xsvab-pvid-zadanie2\output\histogram\ycc\ycc_corrected.png)

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