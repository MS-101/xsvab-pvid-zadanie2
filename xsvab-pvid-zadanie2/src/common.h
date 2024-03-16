#pragma once

#include <opencv2/opencv.hpp>


struct OutputArgs {
	std::string name;
	std::string dir;
	std::string extension;
};

void outputImage(cv::Mat image, OutputArgs outputArgs);
