#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage, testImage1, testImage2;
	Mat srcHsvImage, testHsvImage1, testHsvImage2;

	srcImage = imread("L:\\手形模式识别\\7.bmp",1);
	testImage1 = imread("L:\\手形模式识别\\1.bmp",1);
	testImage2 = imread("L:\\手形模式识别\\9.bmp",1);

	imshow("src", srcImage);
	imshow("dst1", testImage1);
	imshow("dst2", testImage2);

	//
	cvtColor(srcImage, srcHsvImage, COLOR_BGR2HSV);
	cvtColor(testImage1, testHsvImage1, COLOR_BGR2HSV);
	cvtColor(testImage2, testHsvImage2, COLOR_BGR2HSV);

	int h_bins = 30;
	int s_bins = 32;
	int histSize[] = {h_bins, s_bins};
	float h_ranges[] = {0, 256};
	float s_ranges[] = {0, 180};
	const float * ranges[] = { h_ranges, s_ranges};
	int channels[] = {0, 1};
	Mat srcHist, testHist1, testHist2;

	calcHist(&srcHsvImage, 1, channels, Mat(), srcHist, 2, histSize, ranges, true, false);
	calcHist(&testHsvImage1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false);
	calcHist(&testHsvImage2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false);

	normalize(srcHist, srcHist, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat());

	for(int i = 0; i < 4; i++)
	{
		int compare_method = i;
		double base_src = compareHist(srcHist, srcHist, i);
		double base_test1 = compareHist(srcHist, testHist1, i);
		double base_test2 = compareHist(srcHist, testHist2, i);
		printf("方法[%d]的匹配结果如下：\n\n [基准图-基准图]： %f\n[基准图-测试图1]: %f\n[基准图-测试图2]: %f\n\n", i, base_src, base_test1, base_test2);
	}
	printf("检测结束");
	waitKey(0);
	return 0;
}
//这个和毕设简直了