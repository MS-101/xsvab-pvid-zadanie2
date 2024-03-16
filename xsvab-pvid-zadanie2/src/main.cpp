#include <iostream>
#include <opencv2/opencv.hpp>


struct OutputArgs {
	std::string name;
	std::string dir;
	std::string extension;
};


void outputImage(cv::Mat image, OutputArgs outputArgs)
{
	cv::imshow(outputArgs.name, image);
	cv::imwrite(outputArgs.dir + outputArgs.name + outputArgs.extension, image);
}

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

	cv::Mat histImage(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

	// normalize channels
	for (int channelID = 0; channelID < hist.size(); channelID++)
		cv::normalize(hist[channelID], hist[channelID], 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

	// draw lines
	for (int histX = 1; histX < histSize; histX++) {
		for (int channelID = 0; channelID < hist.size(); channelID++) {
			auto channel = hist[channelID];
			auto color = colors[channelID];

			cv::line(histImage,
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

		cv::putText(histImage, channelName, cv::Point(10, 20 + channelID * 20),
			cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 1);
	}

	outputImage(histImage, outputArgs);
}

void histogram(cv::Mat input, cv::ColorConversionCodes conversion, cv::ColorConversionCodes inverseConversion,
	std::vector<std::string> channelNames, std::vector<cv::Scalar> colors, const float* ranges[], OutputArgs outputArgs)
{
	cv::Mat converted;
	cv::cvtColor(input, converted, conversion);
	outputImage(converted, outputArgs);

	std::vector<cv::Mat> channels;
	cv::split(converted, channels);
	int channelCount = channels.size();

	std::vector<cv::Mat> channelsCorrected(channelCount);
	for (int i = 0; i < channelCount; i++)
		cv::equalizeHist(channels[i], channelsCorrected[i]);

	cv::Mat corrected;
	cv::merge(channelsCorrected, corrected);

	std::vector<cv::Mat> hist(channelCount);
	calcHist(channels, hist, ranges);
	displayHist(hist, colors, channelNames, { "hist" + outputArgs.name, outputArgs.dir, outputArgs.extension });

	std::vector<cv::Mat> histCorrected(channelCount);
	calcHist(channelsCorrected, histCorrected, ranges);
	displayHist(histCorrected, colors, channelNames, { "hist" + outputArgs.name + "_corrected", outputArgs.dir, outputArgs.extension});

	cv::Mat output;
	cv::cvtColor(corrected, output, inverseConversion);
	outputImage(output, { outputArgs.name + "_corrected", outputArgs.dir, outputArgs.extension});

	cv::waitKey();
}

void histogramGrayscale(cv::Mat input)
{
	OutputArgs outputArgs = { "grayscale", "output\\histogram\\grayscale\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2GRAY;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_GRAY2BGR;

	std::vector<std::string> channelNames = { "White" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 0, 255) };

	float grayscaleRange[] = { 0, 256 };
	const float* ranges[] = { grayscaleRange };
	
	histogram(input, conversion, inverseConversion, channelNames, colors, ranges, outputArgs);
}

void histogramRGB(cv::Mat input)
{
	OutputArgs outputArgs = { "rgb", "output\\histogram\\rgb\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2RGB;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_RGB2BGR;

	std::vector<std::string> channelNames = { "Red", "Green", "Blue" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0) };

	float rgbRange[] = { 0, 256 };
	const float* ranges[] = { rgbRange, rgbRange, rgbRange };
	
	histogram(input, conversion, inverseConversion, channelNames, colors, ranges, outputArgs);
}

void histogramYCC(cv::Mat input)
{
	OutputArgs outputArgs = { "ycc", "output\\histogram\\ycc\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2YCrCb;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_YCrCb2BGR;

	std::vector<std::string> channelNames = { "Luma", "Chroma blue", "Chroma Red" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0), cv::Scalar(0, 0, 255) };

	float yccRange[] = { 0, 256 };
	const float* ranges[] = { yccRange, yccRange, yccRange };

	histogram(input, conversion, inverseConversion, channelNames, colors, ranges, outputArgs);
}

void histogramHSV(cv::Mat input)
{
	OutputArgs outputArgs = { "hsv", "output\\histogram\\hsv\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2HSV;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_HSV2BGR;

	std::vector<std::string> channelNames = { "Hue", "Saturation", "Value" };
	std::vector<cv::Scalar> colors = { cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0) };
	
	float hRange[] = { 0, 180 };
	float svRange[] = { 0, 256 };
	const float* ranges[] = { hRange, svRange, svRange };

	histogram(input, conversion, inverseConversion, channelNames, colors, ranges, outputArgs);
}

void histogramXYZ(cv::Mat input)
{
	OutputArgs outputArgs = { "xyz", "output\\histogram\\xyz\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2XYZ;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_XYZ2BGR;

	std::vector<cv::Scalar> colors = { cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255) };
	std::vector<std::string> channelNames = { "X", "Y", "Z" };

	float xRange[] = { 0, 95.05 };
	float yRange[] = { 0, 100 };
	float zRange[] = { 0, 108.9 };
	const float* ranges[] = { xRange, yRange, zRange };

	histogram(input, conversion, inverseConversion, channelNames, colors, ranges, outputArgs);
}

void histogramLAB(cv::Mat input)
{
	OutputArgs outputArgs = { "lab", "output\\histogram\\lab\\", ".tif" };

	cv::ColorConversionCodes conversion = cv::COLOR_BGR2Lab;
	cv::ColorConversionCodes inverseConversion = cv::COLOR_Lab2BGR;

	std::vector<cv::Scalar> colors = { cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255) };
	std::vector<std::string> channelNames = { "L", "A", "B" };

	float lRange[] = { 0, 100 };
	float abRange[] = { -128, 128 };
	const float* ranges[] = { lRange, abRange, abRange };

	histogram(input, conversion, inverseConversion, channelNames, colors, ranges, outputArgs);
}

int main()
{
	std::string inputPath = "assets\\Histology nuclei\\TCGA-18-5592-01Z-00-DX1.tif";
	std::string outputDir = "output\\histogram\\";
	std::string outputExtension = ".tif";

	// input

	cv::Mat input = cv::imread(inputPath);
	if (input.empty()) {
		std::cerr << "Error: Unable to load input image" << std::endl;
		return -1;
	}

	cv::resize(input, input, cv::Size(input.cols / 2, input.rows / 2));
	outputImage(input, { "input", outputDir, outputExtension });

	// color correction with histogram

	histogramGrayscale(input);
	histogramRGB(input);
	histogramYCC(input);
	histogramHSV(input);
	histogramXYZ(input);
	histogramLAB(input);

	return 0;
}
