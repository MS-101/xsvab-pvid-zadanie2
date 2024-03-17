#include "hist.h"


void calcHist(std::vector<cv::Mat> channels, std::vector<cv::Mat>& hist, const float* histRanges[])
{
	int histSize = 256;
	for (int channelID = 0; channelID < channels.size(); channelID++)
		cv::calcHist(&channels[channelID], 1, 0, cv::Mat(), hist[channelID], 1, &histSize, &histRanges[channelID]);
}

void displayHist(std::vector<cv::Mat> hist, std::vector<cv::Scalar> colors, std::vector<std::string> channelNames, OutputArgs outputArgs)
{
	int width = 600, height = 500;
	int histSize = hist[0].rows;
	int binWidth = cvRound((double)width / histSize);

	cv::Mat image(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

	// normalize channels
	for (int channelID = 0; channelID < hist.size(); channelID++)
		cv::normalize(hist[channelID], hist[channelID], 0, image.rows, cv::NORM_MINMAX, -1, cv::Mat());

	// draw lines
	for (int channelID = 0; channelID < hist.size(); channelID++) {
		cv::Mat channel = hist[channelID];
		cv::Scalar color = colors[channelID];

		for (int histX = 1; histX < histSize; histX++) {
			cv::line(image,
				cv::Point(binWidth * (histX - 1), height - cvRound(channel.at<float>(histX - 1))),
				cv::Point(binWidth * histX, height - cvRound(channel.at<float>(histX))),
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

void hist(cv::Mat input, cv::ColorConversionCodes conversion, cv::ColorConversionCodes inverseConversion,
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

void histGrayscale(cv::Mat input)
{
	OutputArgs outputArgs = { "grayscale", "output\\histogram\\grayscale\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2GRAY;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_GRAY2BGR;

	std::vector<std::string> channelNames = { "White" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 0, 255) };
	bool corrections[] = { true };

	float grayscaleRange[] = { 0, 256 };
	const float* ranges[] = { grayscaleRange };

	hist(input, conversion, inverseConversion, channelNames, colors, corrections, ranges, outputArgs);
}

void histRGB(cv::Mat input)
{
	OutputArgs outputArgs = { "rgb", "output\\histogram\\rgb\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2RGB;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_RGB2BGR;

	std::vector<std::string> channelNames = { "Red", "Green", "Blue" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0) };
	bool corrections[] = { true, true, true };

	float rgbRange[] = { 0, 256 };
	const float* ranges[] = { rgbRange, rgbRange, rgbRange };

	hist(input, conversion, inverseConversion, channelNames, colors, corrections, ranges, outputArgs);
}

void histYCC(cv::Mat input)
{
	OutputArgs outputArgs = { "ycc", "output\\histogram\\ycc\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2YCrCb;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_YCrCb2BGR;

	std::vector<std::string> channelNames = { "Luma", "Chroma blue", "Chroma Red" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0), cv::Scalar(0, 0, 255) };
	bool corrections[] = { true, false, false };

	float yccRange[] = { 0, 256 };
	const float* ranges[] = { yccRange, yccRange, yccRange };

	hist(input, conversion, inverseConversion, channelNames, colors, corrections, ranges, outputArgs);
}

void histHSV(cv::Mat input)
{
	OutputArgs outputArgs = { "hsv", "output\\histogram\\hsv\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2HSV;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_HSV2BGR;

	std::vector<std::string> channelNames = { "Hue", "Saturation", "Value" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0) };
	bool corrections[] = { false, false, true };

	float hRange[] = { 0, 180 };
	float svRange[] = { 0, 256 };
	const float* ranges[] = { hRange, svRange, svRange };

	hist(input, conversion, inverseConversion, channelNames, colors, corrections, ranges, outputArgs);
}

void histXYZ(cv::Mat input)
{
	OutputArgs outputArgs = { "xyz", "output\\histogram\\xyz\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2XYZ;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_XYZ2BGR;

	std::vector<cv::Scalar> colors = { cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255) };
	std::vector<std::string> channelNames = { "X", "Y", "Z" };
	bool corrections[] = { false, true, false };

	float xRange[] = { 0, 95.05 };
	float yRange[] = { 0, 100 };
	float zRange[] = { 0, 108.9 };
	const float* ranges[] = { xRange, yRange, zRange };

	hist(input, conversion, inverseConversion, channelNames, colors, corrections, ranges, outputArgs);
}

void histLAB(cv::Mat input)
{
	OutputArgs outputArgs = { "lab", "output\\histogram\\lab\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2Lab;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_Lab2BGR;

	std::vector<cv::Scalar> colors = { cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255) };
	std::vector<std::string> channelNames = { "L", "A", "B" };
	bool corrections[] = { true, false, false };

	float lRange[] = { 0, 100 };
	float abRange[] = { -128, 128 };
	const float* ranges[] = { lRange, abRange, abRange };

	hist(input, conversion, inverseConversion, channelNames, colors, corrections, ranges, outputArgs);
}
