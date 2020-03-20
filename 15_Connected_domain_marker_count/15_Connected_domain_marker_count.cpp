// 15_Connected_domain_marker_count.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<algorithm>
using namespace std;
using namespace cv;
int main()
{
	//读取本地的一张图片，将图像二值化，连通域标记,将硬币的个数 输出至状态栏.
	cv::Mat srcMat = imread("C:/Users/lenovo/Desktop/数图图片/coin.png");
	int height = srcMat.rows; //行数
	int width = srcMat.cols; //每行元素的总元素数量
	for (int j = 0; j<height; j++)
	{
		for (int i = 0; i<width; i++)
		{
			//-----------------开始处理每个像素-----------------
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] +
				srcMat.at<Vec3b>(j, i)[2]) / 3;
			uchar threshold = 80;
			average > threshold ? average = 255 : average = 0;
			srcMat.at<Vec3b>(j, i)[0] = srcMat.at<Vec3b>(j, i)[1] = srcMat.at<Vec3b>(j, i)[2] = average;

			//-------------结束像素处理------------------------
		} //单行处理结束
	}

	Mat src, src_color, g_src, labels, stats, centroids;
	int num = connectedComponentsWithStats(srcMat, labels, stats, centroids);
	std::cout<< "轮廓数" << num-1 << std::endl;
	for (int i = 0; i < num; i++)
	{
		cv::Rect rect;
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);
		rectangle(srcMat, rect, CV_RGB(0, 255, 0), 1, 8, 0);

	}

	imshow("src", srcMat);
	//等待用户按键
	waitKey(0);
	return 0;
}

