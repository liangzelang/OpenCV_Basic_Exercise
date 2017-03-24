#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena_src.png",1);
	imshow("src", srcImage);
	Mat dstHist;
	int dims = 1;
	float hranges[] = {0, 255};
	const float * ranges[] = { hranges};
	int size = 256;
	int channels = 0;//这个就标记了需要统计的图像通道数  0通道，为Blue颜色分量

	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	int scale = 1;
	Mat dstImage = Mat(size*scale, size, CV_8U, Scalar(0));
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	int hpt = saturate_cast<int>(0.9*size);
	for(int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt/maxValue);
		rectangle(dstImage, Point(i*scale, size -1 ), Point((i+1)*scale-1, size-realValue), Scalar(255));
	}
	imshow("dst", dstImage);
	waitKey(0);
	return 0;
}