#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_MedianBlurdstImage, g_BilateralFilterdstImage;
int g_nMedianBlurValue = 10;
int g_nBilateralFilterValue = 10;

static void on_MedianBlur(int, void * );
static void on_BilateralFilter(int, void *);

int main()
{
	g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena_src.png",1);
	g_MedianBlurdstImage = g_srcImage.clone();
	g_BilateralFilterdstImage = g_srcImage.clone();

	namedWindow("原图", 1);
	imshow("原图", g_srcImage);
	
	//中值滤波
	namedWindow("中值滤波", 1);
	createTrackbar("Kernal", "中值滤波", &g_nMedianBlurValue, 40, on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue, 0);
	//双边滤波
	namedWindow("双边滤波",1);
	createTrackbar("Kernal", "双边滤波", &g_nBilateralFilterValue, 40, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);
	
	cout << "调整TrackBar，查看不同滤波效果\n" << endl;

	waitKey();
	return 0;
}

static void on_MedianBlur(int, void *)
{
	medianBlur(g_srcImage, g_MedianBlurdstImage,g_nMedianBlurValue*2+1);
	imshow("中值滤波", g_MedianBlurdstImage);
}

static void on_BilateralFilter(int, void *)
{
	bilateralFilter(g_srcImage, g_BilateralFilterdstImage, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2);
	imshow("双边滤波", g_BilateralFilterdstImage);
}