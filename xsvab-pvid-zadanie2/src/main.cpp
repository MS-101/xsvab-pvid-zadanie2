#include "common.h"
#include "hist.h"
#include "gamma.h"
#include "cdf.h"


int main()
{
	// load input image

	cv::Mat input = cv::imread("assets\\Histology nuclei\\TCGA-18-5592-01Z-00-DX1.tif");
	if (input.empty()) {
		std::cerr << "Error: Unable to load input image" << std::endl;
		return -1;
	}

	cv::resize(input, input, cv::Size(input.cols / 2, input.rows / 2));
	outputImage(input, { "input", "output\\", ".tif" });

	// color correction with histogram

	histGrayscale(input);
	histRGB(input);
	histYCC(input);
	histHSV(input);
	histXYZ(input);
	histLAB(input);

	// color correction with gamma
	
	std::vector<double> gammas = { -0.5, 0.5, 1.5, 2.5 };
	gammaCorrection(input, gammas);

	// color correction with cdf

	cv::Mat target = cv::imread("assets\\Histology nuclei\\TCGA-21-5784-01Z-00-DX1.tif");
	if (target.empty()) {
		std::cerr << "Error: Unable to load target image" << std::endl;
		return -1;
	}

	cv::resize(target, target, cv::Size(target.cols / 2, target.rows / 2));
	outputImage(target, { "target", "output\\cdf\\", ".tif" });

	cdfRGB(input, target);
	cdfYCC(input, target);

	return 0;
}
