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

void displayCDF(std::vector<cv::Mat> cdf, std::vector<cv::Scalar> colors, std::vector<std::string> channelNames, OutputArgs outputArgs)
{
	int width = 600, height = 500;
	int histSize = 256;

	cv::Mat image(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

	// draw lines
	for (int cdfID = 0; cdfID < cdf.size(); cdfID++) {
		cv::Mat curCDF = cdf[cdfID];
		cv::Scalar color = colors[cdfID];

		for (int x = 1; x < histSize; ++x) {
			cv::line(image,
				cv::Point((x - 1) * 2, height - curCDF.at<float>(x - 1) * height),
				cv::Point(x * 2, height - curCDF.at<float>(x) * height),
				color
			);
		}
	}

	// add legend
	for (int channelID = 0; channelID < colors.size(); channelID++) {
		auto color = colors[channelID];
		auto channelName = channelNames[channelID];

		cv::putText(image, channelName, cv::Point(10, 20 + channelID * 20),
			cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 1);
	}

	outputImage(image, outputArgs);
}

void calcLookUpTable(std::vector<cv::Mat> inputCDF, std::vector<cv::Mat> targetCDF, std::vector<cv::Mat>& lookUpTable)
{
	for (int channelID = 0; channelID < lookUpTable.size(); channelID++) {
		cv::Mat curInput = inputCDF[channelID];
		cv::Mat curTarget = targetCDF[channelID];

		for (int i = 0; i < 256; ++i) {
			int j = 0;

			while (j < 256 && curInput.at<float>(i) > curTarget.at<float>(j))
				++j;

			lookUpTable[channelID].at<uchar>(i) = cv::saturate_cast<uchar>(j);
		}
	}
}

void cdf(cv::Mat input, cv::Mat target, cv::ColorConversionCodes conversion, cv::ColorConversionCodes inverseConversion,
	std::vector<std::string> channelNames, std::vector<cv::Scalar> colors, const float* ranges[], OutputArgs outputArgs)
{
	// convert images from bgr to different color space

	cv::Mat convertedInput;
	cv::cvtColor(input, convertedInput, conversion);
	outputImage(convertedInput, { outputArgs.name + "_input", outputArgs.dir, outputArgs.extension});

	cv::Mat convertedTarget;
	cv::cvtColor(target, convertedTarget, conversion);
	outputImage(convertedTarget, { outputArgs.name + "_target", outputArgs.dir, outputArgs.extension });

	// split image channels

	std::vector<cv::Mat> inputChannels;
	cv::split(convertedInput, inputChannels);

	std::vector<cv::Mat> targetChannels;
	cv::split(convertedTarget, targetChannels);

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
	displayCDF(inputCDF, colors, channelNames, { "cdf_" + outputArgs.name + "_input", outputArgs.dir, outputArgs.extension });

	std::vector<cv::Mat> targetCDF(channelCount);
	calcCDF(targetHist, targetCDF);
	displayCDF(targetCDF, colors, channelNames, { "cdf_" + outputArgs.name + "_target", outputArgs.dir, outputArgs.extension });

	// calculate lookup table
	
	std::vector<cv::Mat> lookUpTable;
	for (int channelID = 0; channelID < channelCount; channelID++) {
		cv::Mat lut(1, 256, CV_8U);
		lookUpTable.push_back(lut);
	}

	calcLookUpTable(inputCDF, targetCDF, lookUpTable);

	// correct image

	std::vector<cv::Mat> correctedChannels(channelCount);
	for (int channelID = 0; channelID < channelCount; channelID++)
		cv::LUT(inputChannels[channelID], lookUpTable[channelID], correctedChannels[channelID]);

	cv::Mat corrected;
	cv::merge(correctedChannels, corrected);

	// display image

	cv::Mat output;
	cv::cvtColor(corrected, output, inverseConversion);
	outputImage(output, { outputArgs.name + "_corrected", outputArgs.dir, outputArgs.extension });

	cv::waitKey();
}

void cdfRGB(cv::Mat input, cv::Mat target)
{
	OutputArgs outputArgs = { "rgb", "output\\cdf\\rgb\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2RGB;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_RGB2BGR;

	std::vector<cv::Scalar> colors = { cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0) };
	std::vector<std::string> channelNames = { "R", "G", "B" };

	float rgbRange[] = { 0, 256 };
	const float* ranges[] = { rgbRange, rgbRange, rgbRange };

	cdf(input, target, conversion, inverseConversion, channelNames, colors, ranges, outputArgs);
}

void cdfYCC(cv::Mat input, cv::Mat target)
{
	OutputArgs outputArgs = { "ycc", "output\\cdf\\ycc\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2YCrCb;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_YCrCb2BGR;

	std::vector<std::string> channelNames = { "Luma", "Chroma blue", "Chroma Red" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0), cv::Scalar(0, 0, 255) };

	float yccRange[] = { 0, 256 };
	const float* ranges[] = { yccRange, yccRange, yccRange };

	cdf(input, target, conversion, inverseConversion, channelNames, colors, ranges, outputArgs);
}
