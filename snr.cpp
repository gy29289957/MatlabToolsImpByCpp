#include "opencv2/opencv.hpp"

float snr(cv::Mat const &imgSrc1)
{
	cv::Mat 		mean;
	cv::Mat 		stddev;

	cv::meanStdDev(imgSrc1, mean, stddev);

	return (float)(stddev.at<double>(0,0) == 0 ? -1 : mean.at<double>(0,0)/stddev.at<double>(0,0));
}
