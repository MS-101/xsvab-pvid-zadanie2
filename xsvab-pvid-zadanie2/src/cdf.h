#pragma once

#include <opencv2/opencv.hpp>
#include "common.h"


void calcCDF(std::vector<cv::Mat> hist, std::vector<cv::Mat>& cdf);
void displayCDF(std::vector<cv::Mat> cdf);
cv::Mat createLookupTable(cv::Mat inputCDF, cv::Mat targetCDF);
void cdf(cv::Mat input, cv::Mat target, std::vector<std::string> channelNames, std::vector<cv::Scalar> colors, const float* ranges[], OutputArgs outputArgs);
void cdfRGB(cv::Mat input, cv::Mat target);
void cdfYCC(cv::Mat input, cv::Mat target);
