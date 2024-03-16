#pragma once

#include <opencv2/opencv.hpp>


void gammaCorrection(cv::Mat input, std::vector<double> gammas);
