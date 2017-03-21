#include <opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	system("color 5E");
	Mat r = Mat(3, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));
	//OpenCV格式化输出
	//way1 Opencv默认输出格式
	cout << "r 默认输出格式: " << endl << r << endl;

	//way2 python风格思密达
	cout << "r Python风格: " << endl << format(r, "python") << endl;

	//way3 CSV风格
	cout << "r CSV风格: "  << endl << format(r, "csv") << endl;

	//way4 Numpy风格
	cout << "r Numpy风格: " << endl << format(r, "numpy") << endl;

	//way5 C style
	cout << "r C style: " << endl << format(r, "C") << endl;

	//waitKey(27);
	system("pause");
	return 0;

}