#include "segmentation.h"
#include "common.h"


void segmentation(cv::Mat input, cv::Mat mask)
{
	std::string outputDir = "output\\segmentation\\";
	std::string outputExtension = ".png";

	// convert to lab color space

	cv::Mat inputLab;
	cv::cvtColor(input, inputLab, cv::COLOR_BGR2Lab);
	outputImage(inputLab, { "input_lab", outputDir, outputExtension });

	// split channels

	std::vector<cv::Mat> inputChannels;
	cv::split(inputLab, inputChannels);
	int channelCount = inputChannels.size();

	// compute target

	std::vector<cv::Scalar> targetChannels(channelCount);
	for (int channelID = 0; channelID < channelCount; channelID++)
		targetChannels[channelID] = cv::mean(inputChannels[channelID], mask);

	// compute delta lab

	cv::Mat delta_l, delta_a, delta_b;
	cv::absdiff(inputChannels[0], targetChannels[0], delta_l);
	cv::absdiff(inputChannels[1], targetChannels[1], delta_a);
	cv::absdiff(inputChannels[2], targetChannels[2], delta_b);

	delta_l.convertTo(delta_l, CV_32F);
	delta_a.convertTo(delta_a, CV_32F);
	delta_b.convertTo(delta_b, CV_32F);

	cv::Mat delta_lab;
	cv::sqrt(delta_l.mul(delta_l) + delta_a.mul(delta_a) + delta_b.mul(delta_b), delta_lab);
	delta_lab.convertTo(delta_lab, CV_8U);
	outputImage(delta_lab, { "delta_lab", outputDir, outputExtension });

	// perform thresholding

	cv::Mat threshold;
	cv::threshold(delta_lab, threshold, 30, 255, cv::THRESH_BINARY);
	outputImage(threshold, { "threshold", outputDir, outputExtension });
	threshold.convertTo(threshold, CV_8U);

	// display output

	cv::Mat output;
	input.copyTo(output, threshold);
	outputImage(output, { "output", outputDir, outputExtension });

	cv::waitKey();
}
