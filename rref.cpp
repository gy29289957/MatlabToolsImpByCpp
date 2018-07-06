#include "opencv2/opencv.hpp"

//============================================================================
//
//	rref
//
//	Reduced row echelon form
//
//	Input
//		src: Matrix source
//
//	Return 
//    The calculation results
//
//	Reference:
//	MATLAB\MATLAB Production Server\R2015a\toolbox\matlab\matfun\rref.m
//
//============================================================================
cv::Mat rref(const cv::Mat &src)
{
	cv::Mat dst, temp;
	int 	i, j;
	int 	k;		// max index
	double	p;		// max value
	double	tol;

	// Compute the default tolerance if none was provided.
	tol = std::max(src.rows, src.cols) * DBL_EPSILON * cv::norm(src, cv::NORM_INF);

	dst = src.clone();
	i = 0;
	j = 0;

	while (i < dst.rows && j < dst.cols)
	{
		// Find value and index of largest element in the remainder of column j.
		cv::minMaxIdx(cv::abs(dst(cv::Range(i, dst.rows), cv::Range(j, j+1))), NULL, &p, NULL, &k);
		k = k + i;

		if (p <= tol)
		{
			// The column is negligible, zero it out.
			dst(cv::Range(i, dst.rows), cv::Range(j, j+1)) = cv::Mat::zeros(dst.rows-i+1, 1, dst.type())*1;
			j++;
		}
		else
		{
			// Swap i-th and k-th rows.
			temp.release();
			temp = dst(cv::Range(i, i+1), cv::Range(j, dst.cols))*1;	// *1 very important!
			dst(cv::Range(i, i+1), cv::Range(j, dst.cols)) = dst(cv::Range(k, k+1), cv::Range(j, dst.cols))*1;
			dst(cv::Range(k, k+1), cv::Range(j, dst.cols)) = temp*1;

			// Divide the pivot row by the pivot element.
			if(dst.at<double>(i, j) == 0)
			{
				printf("dst.at<double>(%d, %d) is 0\n", i, j);
			}
			dst(cv::Range(i, i+1), cv::Range(j, dst.cols)) /= dst.at<double>(i, j);

			// Subtract multiples of the pivot row from all the other rows.
			for(k = 0; k < dst.rows; k++)
			{
				if(k == i)
					continue;
				dst(cv::Range(k, k+1), cv::Range(j, dst.cols)) -= dst.at<double>(k, j)*dst(cv::Range(i, i+1), cv::Range(j, dst.cols));
			}

			i++;
			j++;
		}
	}

	return dst;
}
