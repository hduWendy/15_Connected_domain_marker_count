// 15_Connected_domain_marker_count.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<algorithm>
using namespace std;
using namespace cv;
int main()
{
	//��ȡ���ص�һ��ͼƬ����ͼ���ֵ������ͨ����,��Ӳ�ҵĸ��� �����״̬��.
	cv::Mat srcMat = imread("C:/Users/lenovo/Desktop/��ͼͼƬ/coin.png");
	int height = srcMat.rows; //����
	int width = srcMat.cols; //ÿ��Ԫ�ص���Ԫ������
	for (int j = 0; j<height; j++)
	{
		for (int i = 0; i<width; i++)
		{
			//-----------------��ʼ����ÿ������-----------------
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] +
				srcMat.at<Vec3b>(j, i)[2]) / 3;
			uchar threshold = 80;
			average > threshold ? average = 255 : average = 0;
			srcMat.at<Vec3b>(j, i)[0] = srcMat.at<Vec3b>(j, i)[1] = srcMat.at<Vec3b>(j, i)[2] = average;

			//-------------�������ش���------------------------
		} //���д������
	}

	Mat src, src_color, g_src, labels, stats, centroids;
	int num = connectedComponentsWithStats(srcMat, labels, stats, centroids);
	std::cout<< "������" << num-1 << std::endl;
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
	//�ȴ��û�����
	waitKey(0);
	return 0;
}

