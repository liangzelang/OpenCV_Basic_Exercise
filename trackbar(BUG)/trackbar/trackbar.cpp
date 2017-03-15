////////////////////////////////////////////////////////////////////
//                          _ooOoo_                               //
//                         o8888888o                              //
//                         88" . "88                              //
//                         (| ^_^ |)                              //
//                         O\  =  /O                              //
//                      ____/`---'\____                           //
//                    .'  \\|     |//  `.                         //
//                   /  \\|||  :  |||//  \                        //
//                  /  _||||| -:- |||||-  \                       //
//                  |   | \\\  -  /// |   |                       //
//                  | \_|  ''\---/''  |   |                       //
//                  \  .-\__  `-`  ___/-. /                       //
//                ___`. .'  /--.--\  `. . ___                     //
//              ."" '<  `.___\_<|>_/___.'  >'"".                  //
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 //
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 //
//      ========`-.____`-.___\_____/___.-`____.-'========         //
//                           `=---='                              //
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //
//         佛祖保佑       永无BUG     永不修改                    //
////////////////////////////////////////////////////////////////////
// 作用： TrackBar实现图像的线性融合
// 作者： liangzelang@gmail.com
// 时间： 2017/02.26
// 问题： 由于两张图片的大小不同，导致更改到原图了，有较大问题 #1
// 修改信息： #1 2017/03/15 修改完成，定义一个和ROI同样大小的矩阵，复制原图信息，融合时用新定义的原图矩阵融合，不会导致图像叠加 
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
#define WINDOW_NAME "【Newbird无心学术】"

const int value = 100;
int trackbarValue;
double AlphaValue;
double BetaValue;

Mat imageROI;	
Mat learn;
Mat newbird;
Mat NewbirdLearn;
Mat srcImage_ROI;

void on_Trackbar(int, void *)
{
	AlphaValue = (double)trackbarValue / value;
	BetaValue = 1.0-AlphaValue;
	cout << "融合值：" << AlphaValue << " and  " << BetaValue << "\n" << endl;
		
	addWeighted(srcImage_ROI, AlphaValue, newbird, BetaValue, 0.0 ,imageROI);
	//addWeighted(learn, AlphaValue, newbird, BetaValue, 0.0, NewbirdLearn);
	imshow(WINDOW_NAME, learn);
}

int main()
{
	learn = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\learn.jpg",2|4);
	newbird = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\logo.png",2|4);

	if( !learn.data || !newbird.data)
	{
		printf("读取Newbird学海无涯苦作舟图片错误，请确定目录下是否有指定图片。\n");
		return -1;
	}
	imageROI = learn(Rect(65,560,newbird.cols,newbird.rows));
	//srcImage_ROI.copyTo(imageROI);  //调用复制构造函数，得到最初的原图
	imageROI.copyTo(srcImage_ROI);
	//initialize the slider value to 50;
	trackbarValue = 50;
	namedWindow(WINDOW_NAME,1);
	// create a trackbar
	char TrackbarName[50];
	sprintf(TrackbarName, "透明值%d:", value);
	createTrackbar( TrackbarName, WINDOW_NAME, &trackbarValue, value, on_Trackbar);
	on_Trackbar(trackbarValue, 0);
	waitKey(0);
	//system("pause");
	return 0;
		
}