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
// 问题： 由于两张图片的大小不同，导致更改到原图了，有较大问题
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

void on_Trackbar(int, void *)
{
	AlphaValue = (double)trackbarValue / value;
	BetaValue = 1.0-AlphaValue;
	cout << "融合值：" << AlphaValue << " and  " << BetaValue << "\n" << endl;
		
	addWeighted(imageROI, AlphaValue, newbird, BetaValue, 0.0 ,imageROI);
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
	Mat ImageROI = 
	imageROI = learn(Rect(65,560,newbird.cols,newbird.rows));
	//initialize the slider value to 50;
	trackbarValue = 100;
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