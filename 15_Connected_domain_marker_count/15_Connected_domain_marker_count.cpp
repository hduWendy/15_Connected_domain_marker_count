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
	//读取本地的一张图片，将图像二值化，连通域标记,将硬币的个数 输出至状态栏!！！！
	cv::Mat srcMat = imread("C:/Users/lenovo/Desktop/数图图片/coin.png");
	//二值化
	Mat g_src, labels, stats, centroids, erode_src;
	threshold(srcMat, g_src, 90, 255, THRESH_BINARY);
	//设置结构元素+形态操作
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(g_src, erode_src, MORPH_ERODE, element, Point(-1, -1), BORDER_CONSTANT);
	//三通道分离
	std::vector<cv::Mat>erode_src_part(erode_src.channels());//生成与通道数数目相等的图像容器
	cv::split(erode_src, erode_src_part);//分解与通道数数目相等的图像容器
	//连通域标记
	int num = cv::connectedComponentsWithStats(erode_src_part[0], labels, stats, centroids);
	std::cout<< "轮廓数" << num-1 << std::endl;
	//画框
	for (int i = 1; i <= num-1; i++)
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

