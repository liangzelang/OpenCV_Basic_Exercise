#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "PIC1"
#define WINDOW_NAME2 "PIC2"
#define WINDOW_WIDTH 600

void DrawEllipse( Mat img, double angle);
void DrawFilledCircle( Mat img, Point center);
void DrawPolygon( Mat img);
void DrawLine( Mat img, Point start, Point end);


int main()
{
	//创建空白的Mat图像
	Mat atomImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//--------pic1 原子结构示意图---------------
	DrawEllipse( atomImage, 90);
	DrawEllipse( atomImage, 0);
	DrawEllipse( atomImage, 45);
	DrawEllipse( atomImage, -45);

	DrawFilledCircle( atomImage, Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));
	
	//---------pic2 多边形---------------------
	DrawPolygon( rookImage );

	//
	namedWindow(WINDOW_NAME1);
	namedWindow(WINDOW_NAME2);
	imshow( WINDOW_NAME1, atomImage );
	moveWindow( WINDOW_NAME1, 0, 200);
	imshow( WINDOW_NAME2, rookImage );
	moveWindow( WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
	return 0;
}



void DrawEllipse( Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(
		img,
		Point( WINDOW_WIDTH/2, WINDOW_WIDTH/2),
		Size( WINDOW_WIDTH/4, WINDOW_WIDTH/16),   //轴的长度
		angle,
		0,
		360,
		Scalar(255, 129, 0),
		thickness,
		lineType
		);
}
void DrawFilledCircle( Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;
	circle( 
		img,
		center,
		WINDOW_WIDTH/32,
		Scalar(0,0,255),
		thickness,
		lineType
		);
}
void DrawPolygon( Mat img)
{
	int lineType = 8;
	//创建一些点
	Point rookPoints[1][4];
	rookPoints[0][0] = Point(20, 20);
	rookPoints[0][1] = Point(20, 100);
	rookPoints[0][2] = Point(120, 100);
	rookPoints[0][3] = Point(120, 20);

	int npt[] = {4};
	const Point * ppt[1] = { rookPoints[0]};

	fillPoly(
		img,
		ppt,
		npt,
		1,
		Scalar(255,255,255),
		lineType);
}
void DrawLine( Mat img, Point start, Point end)
{
	line(img, start, end, Scalar(0, 0, 0), 2, 8);
}