#include "opencv2/opencv.hpp"

float entropy(cv::Mat const &imgSrc)
{
	int 			high		= 255;
	int				low			= 0;
	float 			fHRanges[2] = {(float)low, (float)high};
	const float 	*fRanges[1] = {fHRanges};
	int 			iChannels;
	int 			iHistSize;
	float			fEntropy;
	float			fProbabiliityOfPixelIntensity;
	cv::MatND		sparseMat;

	iChannels = 0;
	iHistSize = high-low+1;
	fEntropy = 0;

	cv::calcHist(&imgSrc, 1, &iChannels, cv::Mat(), sparseMat, 1, &iHistSize, fRanges);

	for(int i = 0; i < iHistSize; i++)
	{
		fProbabiliityOfPixelIntensity = sparseMat.at<float>(i) / imgSrc.total();
		if(fProbabiliityOfPixelIntensity > 0)
			fEntropy = fEntropy + fProbabiliityOfPixelIntensity * log2(fProbabiliityOfPixelIntensity);
	}

	return -fEntropy;
}
