#include "common.h"


void outputImage(cv::Mat image, OutputArgs outputArgs)
{
	cv::imshow(outputArgs.name, image);
	cv::imwrite(outputArgs.dir + outputArgs.name + outputArgs.extension, image);
}
