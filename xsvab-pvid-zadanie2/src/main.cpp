#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
	cv::Mat foo = cv::imread("assets\\HMRegistred.png");
	cv::imshow("foo", foo);

	cv::waitKey();

	return 0;
}
