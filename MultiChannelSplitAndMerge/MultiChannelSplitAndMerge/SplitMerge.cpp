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
// 作用： 分离颜色通道、多通道图像混合
// 作者： liangzelang@gmail.com
// 时间： 2017/03.15 
#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
const double AlphaValue = 0.3;
const double BetaValue = 1 - AlphaValue;
bool MultiChannelBlending()
{
	Mat srcImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\learn.jpg",1);
	Mat logoImage = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\logo.png",0);
	if((!srcImage.data) && (!logoImage.data))
	{
		cout << "加载图片失败.\n";
		return false;
	}
	imshow("logo原图", logoImage);
	Mat imageBlueChannel;
	vector<Mat> Channels;

	split(srcImage, Channels);

	imageBlueChannel = Channels.at(1);

	addWeighted(imageBlueChannel(Rect(65, 560, logoImage.cols, logoImage.rows)), AlphaValue, logoImage, BetaValue, 0.0, imageBlueChannel(Rect(65, 560, logoImage.cols, logoImage.rows)));

	merge(Channels, srcImage);

	namedWindow("蓝色通道");
	imshow("蓝色通道", srcImage);
	return true;
}

int main()
{
	system("color 5E");
	if(MultiChannelBlending())
	{
		cout << endl << "运行成功， 得到需要的图像.\n" << endl;
	}
	waitKey();
	return 0;
}
