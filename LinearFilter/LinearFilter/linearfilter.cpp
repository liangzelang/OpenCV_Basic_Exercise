#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int g_nBoxFilterValue = 10;
int g_nMeanBlurValue = 10;
int g_nGaussianBlurValue = 10;
Mat g_srcImage, g_BoxFilterdstImage, g_MeanBlurdstImage, g_GaussianBlurdstImage;

static void on_BoxFilter(int , void *);
static void on_MeanBlur(int, void *);
static void on_GaussianBlur(int, void *);

int main()
{
	system("color5E");
	g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena_src.png",1);
	g_BoxFilterdstImage = g_srcImage.clone();
	g_MeanBlurdstImage = g_srcImage.clone();
	g_GaussianBlurdstImage = g_srcImage.clone();

	namedWindow("原图",1);
	imshow("原图", g_srcImage);

	//方框滤波
	namedWindow("方框滤波", 1);
	createTrackbar("核" ,"方框滤波", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	//均值滤波
	namedWindow("均值滤波", 1);
	createTrackbar("核", "均值滤波", &g_nMeanBlurValue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);
	//高斯滤波
	namedWindow("高斯滤波", 1);
	createTrackbar("核", "高斯滤波", &g_nGaussianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	cout << "调整滚动条可以查看不同内核大小的滤波效果" << endl;

	waitKey(0);
	return 0;
}

static void on_BoxFilter(int, void *)
{
	boxFilter(g_srcImage, g_BoxFilterdstImage, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1), Point(-1, -1),true, 4);
	imshow("方框滤波", g_BoxFilterdstImage);

}
static void on_MeanBlur(int, void *)
{
	blur(g_srcImage, g_MeanBlurdstImage, Size(g_nMeanBlurValue +1, g_nMeanBlurValue + 1));
	imshow("均值滤波", g_MeanBlurdstImage);
}
static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImage, g_GaussianBlurdstImage, Size(g_nGaussianBlurValue*2 + 1, g_nGaussianBlurValue*2 + 1),0,0);  //the kernal of GaussianBlur should be odd and positive
	imshow("高斯滤波", g_GaussianBlurdstImage);
}