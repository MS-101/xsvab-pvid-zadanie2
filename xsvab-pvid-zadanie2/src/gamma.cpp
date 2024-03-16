#include "gamma.h"
#include "common.h"


void gammaCorrection(cv::Mat input, std::vector<double> gammas)
{
	std::string outputDir = "output\\gamma\\";
	std::string outputExtension = ".tif";

	cv::Mat converted = input;
	input.convertTo(converted, CV_32F);

	for (int gammaID = 0; gammaID < gammas.size(); gammaID++)
	{
		double gamma = gammas[gammaID];
		std::string outputName = "gamma" + std::to_string(gammaID);

		cv::Mat corrected;
		cv::pow(converted, gamma, corrected);

		cv::Mat normalized;
		cv::normalize(corrected, normalized, 0, 255, cv::NORM_MINMAX);

		cv::Mat output;
		normalized.convertTo(output, CV_8U);

		outputImage(output, { outputName, outputDir, outputExtension });
	}

	cv::waitKey();
}
