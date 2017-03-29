#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage;
Mat g_grayImage;
int g_nMaxCornerNum = 50;
void on_GoodFeaturesToTrack(int, void *);

int main()
{
	g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	namedWindow("src", 1);
	createTrackbar("最大角点数", "src", &g_nMaxCornerNum, 500, on_GoodFeaturesToTrack);
	on_GoodFeaturesToTrack(0, 0);
	waitKey(0);
	return 0;
}

void on_GoodFeaturesToTrack(int, void *)
{
	if(g_nMaxCornerNum <= 1)
		g_nMaxCornerNum = 1;
	//Shi-Tomasi
	vector<Point2f> corners;
	double qualityLevel = 0.01; //角点检测可接受的最小特征值
	double minDistance = 10;    // 角点之间的最小距离
	int blockSize = 3;   //计算导数自相关矩阵时指定的邻域范围
	double k = 0.04; //权重系数
	Mat copy = g_srcImage.clone();

	//
	goodFeaturesToTrack(g_grayImage, corners, g_nMaxCornerNum, qualityLevel, minDistance, Mat(), blockSize, false, k);
	cout << ">>>此次检测到的角点数为 ： " << corners.size() << endl;
	//drawCorners
	for(unsigned int i = 0; i < corners.size(); i++)
	{
		circle(copy, corners[i], 4, Scalar(0, 10, 255), 2, 8, 0);
	}
	imshow("src", copy);
	//
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001);
	cornerSubPix(g_grayImage, corners, winSize, zeroZone, criteria);
	for(int i = 0; i < corners.size(); i++)
	{
		cout << "\t精确角点坐标 " << corners[i].x << ", " << corners[i].y << endl;
	}
	
}