#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage, hsvImage;
	srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena_src.png");
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

	//参数准备
	int hueBinNum = 30;
	int saturationBinNum = 32;
	int histSize[] ={hueBinNum, saturationBinNum};
	float hueRanges[] = {0, 180};
	float saturationRanges[] = {0, 256};
	const float * ranges[] = { hueRanges, saturationRanges};
	
	//typedef cv::Mat cv::MatND
	MatND dstHist;

	int channels[] = {0,1};

	calcHist(&hsvImage, 1, channels, Mat(), dstHist, 2, histSize, ranges, true, false);
	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);
	int scale = 10;
	Mat histImage = Mat::zeros(saturationBinNum*scale, hueBinNum*scale, CV_8UC3);
	for(int hue = 0; hue < hueBinNum; hue++)
	{
		for(int saturation = 0; saturation < saturationBinNum; saturation++)
		{
			float binValue = dstHist.at<float>(hue, saturation);
			int intensity = cvRound(binValue*255/maxValue);
			rectangle(histImage, Point(hue*scale, saturation*scale), Point((hue+1)*scale-1, (saturation+1)*scale-1), Scalar::all(intensity));

		}
	}

	imshow("src", srcImage);
	imshow("dst", histImage);

	waitKey();
	return 0;

}