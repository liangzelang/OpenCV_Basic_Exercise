#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;
int g_Mode = 0;
// 0: 腐蚀 1： 膨胀 2： 开运算 3：闭运算 4：顶帽 5： 黑帽
int g_nValue = 10;
static void on_ChangeMode(int , void *);
static void on_ChangeValue(int, void *);
void process();
int main()
{
	g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\learn.jpg",1);
	if(!g_srcImage.data)
	{
		cout << "Sorry Sir, No element.\n" << endl;
		return 0;
	}
	namedWindow("原图",1);
	imshow("原图", g_srcImage);
	namedWindow("效果图", 1);
	//模式选择TrackBar
	createTrackbar("Mode", "效果图", &g_Mode, 5, on_ChangeMode);
	on_ChangeMode(g_Mode, 0);
	//核大小
	createTrackbar("Value", "效果图", &g_nValue, 40, on_ChangeValue);
	on_ChangeValue(g_nValue, 0);

	cout << "please choose what you want.\n" << endl;
	waitKey();
	return 0;
}

static void on_ChangeMode(int, void *)
{
	process();
}

static void on_ChangeValue(int , void *)
{
	process();
}

void process()
{
	switch(g_Mode)
	{
	case 0: //腐蚀
		{
			Mat element = getStructuringElement(MORPH_RECT, Size(g_nValue*2+1,g_nValue*2+1));
			erode(g_srcImage,g_dstImage, element);
			imshow("效果图", g_dstImage);
			break;
		}
	case 1: //膨胀
		{
			Mat element = getStructuringElement(MORPH_RECT, Size(g_nValue*2+1,g_nValue*2+1));
			dilate(g_srcImage,g_dstImage, element);
			imshow("效果图", g_dstImage);
			break;
		}
	case 2: //开运算
		{
			Mat element = getStructuringElement(MORPH_RECT, Size(g_nValue*2+1,g_nValue*2+1));
			morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
			imshow("效果图", g_dstImage);
			break;
		}
		
	case 3: //闭运算
		{
			Mat element = getStructuringElement(MORPH_RECT, Size(g_nValue*2+1,g_nValue*2+1));
			morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, element);
			imshow("效果图", g_dstImage);
			break;
		}
	case 4: //顶帽
		{
			Mat element = getStructuringElement(MORPH_RECT, Size(g_nValue*2+1, g_nValue*2+1));
			morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
			imshow("效果图", g_dstImage);
			break;
		}
	case 5: //黑帽
		{
			Mat element = getStructuringElement(MORPH_RECT, Size(g_nValue*2+1, g_nValue*2+1));
			morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
			imshow("效果图", g_dstImage);
			break;
		}
	default:
		cout << "Sorry Sir, NO This Mode" << endl;
		break;
	}
}