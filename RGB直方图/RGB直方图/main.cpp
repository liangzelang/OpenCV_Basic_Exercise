#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena_src.png",1);
	imshow("src", srcImage);
	Mat dstRedHist, dstGreenHist, dstBlueHist;
	int dims = 1;
	float hranges[] = {0, 255};
	const float * ranges[] = { hranges};
	int size = 256;
	int channels_r = 0;//这个就标记了需要统计的图像通道数  0通道，为Blue颜色分量
	int channels_g = 1;
	int channels_b = 2;

	//计算红色分量的直方图
	calcHist(&srcImage, 1, &channels_r, Mat(), dstRedHist, dims, &size, ranges, true, false);

	//计算绿色分量的直方图
	calcHist(&srcImage, 1, &channels_g, Mat(), dstGreenHist, dims, &size, ranges, true, false);
	//计算蓝色分量的直方图
	calcHist(&srcImage, 1, &channels_b, Mat(), dstBlueHist, dims, &size, ranges, true, false);
	
	//参数准备
	double maxValue_r, maxValue_g, maxValue_b;
	minMaxLoc(dstRedHist, 0, &maxValue_r, 0, 0);
	minMaxLoc(dstGreenHist, 0, &maxValue_g, 0, 0);
	minMaxLoc(dstBlueHist, 0, &maxValue_b, 0, 0);
	int scale = 1;
	int histHeight = 256;
	Mat histImage  = Mat::zeros(histHeight, 256*3, CV_8UC3);

	//
	for(int i = 0; i < 256; i++)
	{
		float binValue_r = dstRedHist.at<float>(i);
		float binValue_g = dstGreenHist.at<float>(i);
		float binValue_b = dstBlueHist.at<float>(i);
		int intensity_r = cvRound(binValue_r*histHeight/maxValue_r);
		int intensity_g = cvRound(binValue_g*histHeight/maxValue_g);
		int intensity_b = cvRound(binValue_b*histHeight/maxValue_b);
		//red
		rectangle(histImage, Point(i*scale, histHeight-1), Point((i+1)*scale-1, histHeight - intensity_r), Scalar(0, 0,255));
		//green
		rectangle(histImage, Point((i+256)*scale, histHeight-1), Point((i+1+256)*scale-1, histHeight - intensity_g), Scalar(0, 255, 0));
		//blue
		rectangle(histImage, Point( (i+ 256*2)*scale, histHeight - 1), Point((i+256*2+1)*scale-1, histHeight-intensity_b),Scalar(255,0,0 ));
	}

	imshow("dst", histImage);

	waitKey(0);
	return 0;
}