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
	//��ȡ���ص�һ��ͼƬ����ͼ���ֵ������ͨ����,��Ӳ�ҵĸ��� �����״̬��!������
	cv::Mat srcMat = imread("C:/Users/lenovo/Desktop/��ͼͼƬ/coin.png");
	//��ֵ��
	Mat g_src, labels, stats, centroids, erode_src;
	threshold(srcMat, g_src, 90, 255, THRESH_BINARY);
	//���ýṹԪ��+��̬����
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(g_src, erode_src, MORPH_ERODE, element, Point(-1, -1), BORDER_CONSTANT);
	//��ͨ������
	std::vector<cv::Mat>erode_src_part(erode_src.channels());//������ͨ������Ŀ��ȵ�ͼ������
	cv::split(erode_src, erode_src_part);//�ֽ���ͨ������Ŀ��ȵ�ͼ������
	//��ͨ����
	int num = cv::connectedComponentsWithStats(erode_src_part[0], labels, stats, centroids);
	std::cout<< "������" << num-1 << std::endl;
	//����
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
	//�ȴ��û�����
	waitKey(0);
	return 0;
}

