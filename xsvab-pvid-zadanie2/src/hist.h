#pragma once

#include <opencv2/opencv.hpp>
#include "common.h"


void calcHist(std::vector<cv::Mat> channels, std::vector<cv::Mat>& hist, const float* histRanges[]);
void displayHist(std::vector<cv::Mat> hist, std::vector<cv::Scalar> colors, std::vector<std::string> channelNames, OutputArgs outputArgs);
void hist(cv::Mat input, cv::ColorConversionCodes conversion, cv::ColorConversionCodes inverseConversion,
	std::vector<std::string> channelNames, std::vector<cv::Scalar> colors, bool corrections[], const float* ranges[], OutputArgs outputArgs);
void histGrayscale(cv::Mat input);
void histRGB(cv::Mat input);
void histYCC(cv::Mat input);
void histHSV(cv::Mat input);
void histXYZ(cv::Mat input);
void histLAB(cv::Mat input);
