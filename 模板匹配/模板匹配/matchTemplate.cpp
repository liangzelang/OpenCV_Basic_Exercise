#include <opencv2\opencv.hpp>

using namespace cv;

Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

void on_Matching(int, void *);

int main()
{
	 g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena.bmp");
	 g_templateImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena_part.png",1);

	 namedWindow("src", 1);
	 namedWindow("result", 1);
	 createTrackbar("method", "src", &g_nMatchMethod, 5, on_Matching);
	 on_Matching(0, 0);
	 waitKey(0);
	 return 0;
}

void on_Matching(int, void *)
{
	Mat srcImage;
	g_srcImage.copyTo(srcImage);
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);

	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1 , Mat());

	//
	double minValue; 
	double maxValue;
	Point minLocation;
	Point maxLocation;
	Point matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

	if(g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED)
	{
		matchLocation = minLocation;
	}
	else
	{
		matchLocation = maxLocation;
	}

	rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),Scalar(0,0,255), 2, 8, 0);
	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),Scalar(0,0,255), 2, 8, 0);
	imshow("src", srcImage);
	imshow("result", g_resultImage);
}