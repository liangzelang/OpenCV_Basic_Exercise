#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;
static void on_contrastTrackbar(int , void * );
Mat srcImage;
Mat dstImage;
int g_contrastValue;
int g_brightValue;
int main()
{
	srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\lena_src.png",1);
	if(!srcImage.data)
	{
		cout << "Sorry Sir, No Element.\n";
		return 0;
	} 
	dstImage = Mat::zeros(srcImage.size(), srcImage.type());
	g_contrastValue = 80;
	g_brightValue = 50;

	
	namedWindow("原图",1);
	namedWindow("效果图",1);
	createTrackbar("对比度 : ", "效果图", &g_contrastValue, 300, on_contrastTrackbar);
	createTrackbar("亮度   : ", "效果图", &g_brightValue, 200, on_contrastTrackbar);
	on_contrastTrackbar(g_contrastValue,0);
	on_contrastTrackbar(g_brightValue, 0);

	waitKey();
	return 0;	
}

static void on_contrastTrackbar(int, void*)
{
	for(int i = 0; i< srcImage.rows; i++)
	{
		for(int j = 0; j < srcImage.cols; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				dstImage.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(g_contrastValue*0.01*(srcImage.at<Vec3b>(i,j)[k]) + g_brightValue);
			}
		}
	}
	
	imshow("原图", srcImage);
	imshow("效果图", dstImage);

}