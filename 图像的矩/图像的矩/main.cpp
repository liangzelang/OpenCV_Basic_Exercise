#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_grayImage, g_dstImage;
int g_nTreshValue = 10;
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
static void on_ChangeThresh(int, void *);

int main()
{
	system("color 1E");

	g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\58.bmp", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));  //均值滤波

	namedWindow("原图", 1);
	imshow("原图", g_srcImage);

	createTrackbar("TreshValue","原图", &g_nTreshValue, 255, on_ChangeThresh);
	on_ChangeThresh(0, 0);

	waitKey(0);
	return 0;
}

static void on_ChangeThresh(int, void *)
{
	
	Canny(g_grayImage, g_dstImage, g_nTreshValue, g_nTreshValue*2, 3, false);
	findContours(g_dstImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//计算矩
	vector<Moments> mu(contours.size());
	for(int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);  //第二参数为是否为二值化图像
	}
	//计算中心距
	vector<Point2f> mc(contours.size());
	for(int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10/mu[i].m00), static_cast<float>(mu[i].m01/mu[i].m00));
	}
	//绘制轮廓
	Mat drawing = Mat::zeros( g_dstImage.size(), CV_8UC3);
	for(int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rand()&255, rand()&255, rand()&255);
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point(0, 0));
		circle(drawing, mc[i], 4, color, 1, 8, 0);
	}

	imshow("效果图", drawing);

//	cout << "输出内容： 面积和轮廓长度" << endl;

//	for(int i = 0; i < contours.size(); i++)
//	{
		//cout << "通过m00计算出轮廓的面积 （M_00） = "<< mu[i].m00 << "OpenCV库函数计算得到轮廓面积为： " << contourArea(contours[i]) << "长度为： " << arcLength(contours[i], true) << endl;
		//Scalar color = Scalar(rand()&255, rand()&255, rand()&255);
		//drawContours(drawing, contours, i, color, 1, 8, hierarchy, 0, Point(0, 0));
		//circle(drawing, mc[i], 4, color, -1, 8, 0);
//	}
}