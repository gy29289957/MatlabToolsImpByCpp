#include "opencv2/opencv.hpp"

//============================================================================
//
//	meshgrid
//
//	Cartesian grid, replicates the grid vectors xgv and ygv to
//  produce the coordinates of a rectangular grid (X, Y)
//
//  Input
//		xgv: range of x
//		ygv: range of y
//  Output
//		X: The grid vector xgv is replicated xgv.size times to form the columns of X
//		Y: The grid vector ygv is replicated ygv.size times to form the columns of Y
//
//============================================================================
void meshgrid(const cv::Range &xgv, const cv::Range &ygv, cv::Mat &X, cv::Mat &Y)
{
    std::vector<int> t_x, t_y;
    for(int i = xgv.start; i <= xgv.end; i++) t_x.push_back(i);
    for(int j = ygv.start; j <= ygv.end; j++) t_y.push_back(j);

    cv::repeat(cv::Mat(t_x).t(), t_y.size(), 1, X);
    cv::repeat(cv::Mat(t_y), 1, t_x.size(), Y);
}
