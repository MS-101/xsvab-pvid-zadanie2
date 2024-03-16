#include "cdf.h"
#include "hist.h"


void calcCDF(std::vector<cv::Mat> hist, std::vector<cv::Mat>& cdf)
{
	int histSize = 256;

	for (int histID = 0; histID < hist.size(); histID++) {
		cv::Mat curHist = hist[histID];

		for (int i = 1; i < histSize; i++)
			curHist.at<float>(i) += curHist.at<float>(i - 1);
		curHist /= curHist.at<float>(histSize - 1);

		cdf[histID] = curHist;
	}
}

void displayCDF(std::vector<cv::Mat> cdf)
{

}

cv::Mat createLookupTable(cv::Mat inputCDF, cv::Mat targetCDF)
{
	cv::Mat lookupTable(1, 256, CV_8U);

	for (int i = 0; i < 256; ++i) {
		int j = 0;

		while (j < 256 && inputCDF.at<float>(i) > targetCDF.at<float>(j))
			++j;

		lookupTable.at<uchar>(i) = cv::saturate_cast<uchar>(j);
	}

	return lookupTable;
}

void cdf(cv::Mat input, cv::Mat target, std::vector<std::string> channelNames, std::vector<cv::Scalar> colors, const float* ranges[], OutputArgs outputArgs)
{
	// split image channels

	std::vector<cv::Mat> inputChannels;
	cv::split(input, inputChannels);

	std::vector<cv::Mat> targetChannels;
	cv::split(target, targetChannels);

	int channelCount = inputChannels.size();

	// calculate histograms

	std::vector<cv::Mat> inputHist(channelCount);
	calcHist(inputChannels, inputHist, ranges);
	displayHist(inputHist, colors, channelNames, { "hist_" + outputArgs.name + "_input", outputArgs.dir, outputArgs.extension });

	std::vector<cv::Mat> targetHist(channelCount);
	calcHist(targetChannels, targetHist, ranges);
	displayHist(targetHist, colors, channelNames, { "hist_" + outputArgs.name + "_target", outputArgs.dir, outputArgs.extension });

	// calculate cdf

	std::vector<cv::Mat> inputCDF(channelCount);
	calcCDF(inputHist, inputCDF);
	displayCDF(inputCDF);

	std::vector<cv::Mat> targetCDF(channelCount);
	calcCDF(targetHist, targetCDF);
	displayCDF(targetCDF);

	// create lookup table



	// correct image


}

void cdfRGB(cv::Mat input, cv::Mat target)
{
	OutputArgs outputArgs = { "rgb", "output\\ecdf\\rgb\\", ".tif" };

	float rgbRange[] = { 0, 256 };
	const float* ranges[] = { rgbRange, rgbRange, rgbRange };

	std::vector<cv::Scalar> colors = { cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0) };
	std::vector<std::string> channelNames = { "R", "G", "B" };

	cdf(input, target, channelNames, colors, ranges, outputArgs);
}

void cdfYCC(cv::Mat input, cv::Mat target)
{

}
