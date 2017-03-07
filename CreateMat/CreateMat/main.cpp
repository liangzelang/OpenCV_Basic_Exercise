#include <opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	/*方法1：使用Mat（）构造函数*/
	Mat M(2, 2, CV_8UC3, Scalar(0,0,255));
	cout << "M = " << endl << " " << M << endl;

	//way2 没有太懂，由于这是多维的数组，使用cout出错
	int sz[3] = {2, 2, 2};
	Mat L(3, sz, CV_8UC3, Scalar::all(0));
	
	//way3 为IplImage创建信息头
	IplImage* img = cvLoadImage("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\learn.jpg",1);
	Mat mtx(img);
	
	//namedWindow("【学无止境】",1);
	//imshow("【学无止境】", mtx);

	//way4 使用Create()函数
	Mat K;
	K.create(4,4,CV_8UC(2));
	cout << "K = " << endl << " " << K << endl << endl;
	//way5 Matlab大法好
	Mat E = Mat::eye(4,4,CV_64F);
	cout << "E = " << endl << " " << E << endl << endl;

	Mat O = Mat::ones(2,2,CV_32F);
	cout << "O = " << endl << " " << O << endl << endl;

	Mat Z = Mat::zeros(3,3,CV_8UC1);
	cout << "Z = " << endl << " " << Z << endl << endl;

	//way6 
	Mat C = (Mat_<double>(3,3) << 0, -1, 2, -1, 5, -1, 0, -1, 0);
	cout << "C = " << endl << " " << C << endl << endl;

	//way7 为已存在的对象创建新的信息头
	Mat RowClone = C.row(0).clone();
	cout << "RowClone = " << endl << " " << RowClone << endl << endl;

	system("pause");
	return 0;
}