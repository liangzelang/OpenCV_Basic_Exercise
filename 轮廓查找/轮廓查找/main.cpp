#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage, g_grayImage;
Mat g_CannyOut;
int g_nTreshValue = 10;
vector<vector<Point>> contours;
vector<Vec4i> g_hierarchy;
static void on_ChangeTresh(int, void *);

int main()
{
	g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena_src.png",1);
	imshow("原图", g_srcImage);

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	//创建窗口
	namedWindow("原图", 1);
	imshow("原图", g_srcImage);

	createTrackbar("Canny Treshhold", "原图", &g_nTreshValue, 200, on_ChangeTresh);
	on_ChangeTresh(g_nTreshValue, 0);

	waitKey();
	return 0;
}

static void on_ChangeTresh(int, void *)
{
	//Canny
	Canny(g_grayImage, g_CannyOut, g_nTreshValue, g_nTreshValue*2, 3);
	//find contours
	findContours(g_CannyOut, contours, g_hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros(g_grayImage.size(), CV_8UC3);
	for(int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rand()&255, rand()&255, rand()&255);
		drawContours(drawing, contours, i, color, 2, 8, g_hierarchy, 0, Point());
	}
	imshow("效果图", drawing);
}

