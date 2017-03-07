#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

int main()
{
	//图像的载入与显示
	Mat learn = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\learn.jpg",2|4);
	namedWindow("学海无涯苦作舟");
	imshow("学海无涯苦作舟",learn);

	Mat newbird = imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\logo.png",1);
	namedWindow("Newbird.cn");
	imshow("Newbird.cn",newbird);

	//图像融合
	Mat imageROI;
	
	imageROI = learn(Rect(65,560,newbird.cols,newbird.rows));

	addWeighted(imageROI, 0.5,newbird,0.3, 0. ,imageROI);

	namedWindow("Newbird should learn");

	imshow("Newbird should learn", learn);
	
	//图像输出
	imwrite("Neverstop2learn.jpg",learn);

	waitKey();

	return 0 ;
}