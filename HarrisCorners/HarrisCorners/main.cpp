#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\features2d\features2d.hpp>

using namespace cv;

Mat g_srcImage, g_srcImage1, g_dstImage, g_grayImage;
int Max_threshold = 175;
int thresh = 30;

void on_HarrisCorner(int, void *);

int main()
{
	g_srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\1.jpg", 1);
	g_srcImage1 = g_srcImage.clone();

	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);
	namedWindow("src1", 1);
	createTrackbar("thresh", "src1", &thresh, Max_threshold, on_HarrisCorner);
	on_HarrisCorner(0, 0);
	waitKey(0);
	return 0;
}

void on_HarrisCorner(int, void *)
{
	Mat dstImage;
	Mat normImage;
	Mat scaleImage;

	dstImage = Mat::zeros(g_grayImage.size(), CV_32FC1);  //单通道32位
	g_srcImage1 = g_srcImage.clone();

	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	//参数说明
	//cornerHarris(input, output, blocksize, ksize, k, bordertype )
	//blocksize 领域大小，   ksize sobel算子的孔径大小   没有懂
	

	//归一化和转换
	normalize( dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaleImage);  //将单通道32位浮点型图像转换单通道8位整型

	//这里需要特别注意一下，at使用的是rows 和cols  ，但是Point 表示的像素点位置
	for(int i = 0; i < normImage.rows; i++)
	{
		for(int j = 0; j < normImage.cols; j ++)
		{
			if((int)normImage.at<float>(i, j) > thresh +80 )
			{
				circle(g_srcImage1, Point(j, i), 4, Scalar(0, 0, 255), 1, 8, 0);
				circle(scaleImage, Point(j, i), 4, Scalar(0, 0, 255), 1, 8, 0);
			}
		}
	}
	imshow("src1", g_srcImage1);
	imshow("dst", scaleImage);
}