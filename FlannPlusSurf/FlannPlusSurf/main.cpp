#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main()
{
	//
	system("color 6f");

	Mat trainImage;
	Mat a= imread("D:\\C++程序联系文件夹（可选择性删除）\\OpenCV_Exercise\\test.jpg",1);
	resize(a, trainImage, Size(640, 480));
	Mat trainGrayImage;
	imshow("src", trainImage);

	//surf 检测和提取特征
	cvtColor(trainImage, trainGrayImage, COLOR_BGR2GRAY);
	vector<KeyPoint> trainKeyPoint;
	Mat trainDescriptor;
	SurfFeatureDetector featureDetector(80);
	featureDetector.detect(trainGrayImage, trainKeyPoint);
	SurfDescriptorExtractor featureExtractor;
	featureExtractor.compute(trainGrayImage, trainKeyPoint, trainDescriptor);

	//FLANN 特征匹配
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, trainDescriptor);
	matcher.add(train_desc_collection);
	matcher.train();

	VideoCapture cap(0);
	unsigned int frameCount  = 0;

	while(char(waitKey(1)) != 'q')
	{
		int64 time0 = getTickCount();
		Mat testImage, testGrayImage;
		cap >> testImage;
		if(testImage.empty())
		{
			continue;
		}
		cvtColor(testImage, testGrayImage, COLOR_BGR2GRAY);
		vector<KeyPoint> testKeyPoint;
		Mat testDescriptor;
		featureDetector.detect(testGrayImage, testKeyPoint, Mat());
		featureExtractor.compute(testGrayImage, testKeyPoint, testDescriptor);

		//匹配训练和测试描述符
		vector<vector<DMatch>> matches;   //这个是什么鬼
		matcher.knnMatch(testDescriptor, matches,2);


		//根据劳式算法 Low's algorithm , 得到优秀的匹配点
		vector<DMatch> goodMatches;
		for(unsigned int i = 0; i < matches.size(); i++)
		{
			if(matches[i][0].distance < 0.6 * matches[i][1].distance)
				goodMatches.push_back(matches[i][0]);
		}

		//绘制
		Mat dstImage;
		drawMatches(testImage, testKeyPoint, trainImage, trainKeyPoint, goodMatches, dstImage);
		imshow("dst", dstImage);
		cout << "当前帧率为： " << getTickFrequency()/(getTickCount() - time0) << endl;
	
	}
	waitKey();
	return 0;
}