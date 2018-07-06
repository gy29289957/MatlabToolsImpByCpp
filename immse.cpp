#include "opencv2/opencv.hpp"

float immse(cv::Mat const &imgSrc1, cv::Mat const &imgSrc2)
{
	cv::Mat 		difference;
	cv::Scalar 	s;

	if(imgSrc1.size() != imgSrc2.size())
		printf("calcMSE error: image size inconsistent\n");

	cv::absdiff(imgSrc1, imgSrc2, difference);		//--- difference = |frame - background|
	difference = difference.mul(difference);		//--- difference = difference^2
	s = cv::sum(difference);						//--- sum

	return (float)(s.val[0] / imgSrc1.total());
}
