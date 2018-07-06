#include "opencv2/opencv.hpp"
//============================================================================
//
//	kron
//
//	Kronecker tensor product
//
//	Input
//		A: matrix A
//		B: matrix B
//	
//	Return the calculation result
//
//============================================================================
cv::Mat kron(const cv::Mat& A, const cv::Mat& B)
{
    CV_Assert(A.channels() == 1 && B.channels() == 1);
    cv::Mat K;
    cv::Mat1d Ad, Bd, Kd;

    A.convertTo(Ad, MAT_PRECISION);
    B.convertTo(Bd, MAT_PRECISION);

    Kd = cv::Mat1d(Ad.rows * Bd.rows, Ad.cols * Bd.cols, 0.0);

    for (int ra = 0; ra < Ad.rows; ++ra)
    {
        for (int ca = 0; ca < Ad.cols; ++ca)
        {
            Kd(cv::Range(ra*Bd.rows, (ra + 1)*Bd.rows), cv::Range(ca*Bd.cols, (ca + 1)*Bd.cols)) = Bd.mul(Ad(ra, ca));
    	}
    }

    Kd.convertTo(K, A.type());
    return K;
}
