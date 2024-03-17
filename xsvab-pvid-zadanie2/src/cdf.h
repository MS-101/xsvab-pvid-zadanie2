#pragma once

#include <opencv2/opencv.hpp>
#include "common.h"


void calcCDF(std::vector<cv::Mat> hist, std::vector<cv::Mat>& cdf);
void displayCDF(std::vector<cv::Mat> cdf, std::vector<cv::Scalar> colors, std::vector<std::string> channelNames, OutputArgs outputArgs);
void calcLookUpTable(std::vector<cv::Mat> inputCDF, std::vector<cv::Mat> targetCDF, std::vector<cv::Mat>& lookUpTable);
void cdf(cv::Mat input, cv::Mat target, cv::ColorConversionCodes conversion, cv::ColorConversionCodes inverseConversion,
	std::vector<std::string> channelNames, std::vector<cv::Scalar> colors, const float* ranges[], OutputArgs outputArgs);
void cdfRGB(cv::Mat input, cv::Mat target);
void cdfYCC(cv::Mat input, cv::Mat target);
