#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat g_srcImage, g_hsvImage, g_hueImage;
int g_bins = 30;
void on_BinChanges(int, void *);

int main()
{
	g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\58.bmp",1);
	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = {0, 0};
	mixChannels( &g_hsvImage, 1, &g_hueImage, 1, ch, 1);

	namedWindow("src", 1);
	createTrackbar("色调组距", "src", &g_bins, 180, on_BinChanges);
	on_BinChanges(g_bins, 0);

	imshow("src", g_srcImage);
	
	waitKey(0);
	return 0;
}

void on_BinChanges(int, void *)
{
	Mat hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = {0, 180};
	const float * ranges  = {hue_range};
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	//
	Mat backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);
	imshow("backproj", backproj);
	int w = 400;
	int h = 400;
	int bin_w = cvRound((double)w/histSize);
	Mat histImage = Mat::zeros(w, h, CV_8UC3);
	for(int i = 0; i < g_bins; i++)
	{
		rectangle(histImage, Point(i*bin_w, h), Point((i+1)*bin_w, h-cvRound(hist.at<float>(i)*h/255.0)), Scalar(100, 123, 255), -1, 8, 0);
	}
	imshow("hist", histImage);
}