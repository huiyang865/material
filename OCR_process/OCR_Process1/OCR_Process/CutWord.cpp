#include "stdafx.h"
#include <cv.h>
#include <highgui.h>
#include<opencv2\imgproc\imgproc.hpp>

using namespace cv;
Mat VerticalProjection(Mat srcImage)//��ֱ����ͶӰ  
{
	if (srcImage.channels() > 1)
		cvtColor(srcImage, srcImage, CV_RGB2GRAY);
	Mat srcImageBin;
	threshold(srcImage, srcImageBin, 120, 255, CV_THRESH_BINARY_INV);
	imshow("��ֵͼ", srcImageBin);
	int *colswidth = new int[srcImage.cols];  //����src.image.cols��int�͵��ڴ�ռ�  
	memset(colswidth, 0, srcImage.cols * 4);  //������븳��ֵΪ�㣬��������޷��������顣  
											  //  memset(colheight,0,src->width*4);    
											  // CvScalar value;   
	int value;
	for (int i = 0; i < srcImage.cols; i++)
		for (int j = 0; j < srcImage.rows; j++)
		{
			//value=cvGet2D(src,j,i);  
			value = srcImageBin.at<uchar>(j, i);
			if (value == 255)
			{
				colswidth[i]++; //ͳ��ÿ�еİ�ɫ���ص�    
			}
		}
	Mat histogramImage(srcImage.rows, srcImage.cols, CV_8UC1);
	for (int i = 0; i < srcImage.rows; i++)
		for (int j = 0; j < srcImage.cols; j++)
		{
			value = 255;  //��������Ϊ��ɫ��   
			histogramImage.at<uchar>(i, j) = value;
		}
	for (int i = 0; i < srcImage.cols; i++)
		for (int j = 0; j < colswidth[i]; j++)
		{
			value = 0;  //ֱ��ͼ����Ϊ��ɫ  
			histogramImage.at<uchar>(srcImage.rows - 1 - j, i) = value;
		}
	imshow(" ��ֱ����ͶӰͼ", histogramImage);
	return histogramImage;
}
Mat HorizonProjection(Mat srcImage)//ˮƽ����ͶӰ  
{
	if (srcImage.channels() > 1)
		cvtColor(srcImage, srcImage, CV_RGB2GRAY);
	Mat srcImageBin;
	threshold(srcImage, srcImageBin, 120, 255, CV_THRESH_BINARY_INV);
	imshow("��ֵͼ", srcImageBin);
	int *rowswidth = new int[srcImage.rows];  //����src.image.rows��int�͵��ڴ�ռ�  
	memset(rowswidth, 0, srcImage.rows * 4);  //������븳��ֵΪ�㣬��������޷��������顣  
	int value;
	for (int i = 0; i<srcImage.rows; i++)
		for (int j = 0; j<srcImage.cols; j++)
		{
			//value=cvGet2D(src,j,i);  
			value = srcImageBin.at<uchar>(i, j);
			if (value == 255)
			{
				rowswidth[i]++; //ͳ��ÿ�еİ�ɫ���ص�    
			}
		}
	Mat histogramImage(srcImage.rows, srcImage.cols, CV_8UC1);
	for (int i = 0; i<srcImage.rows; i++)
		for (int j = 0; j<srcImage.cols; j++)
		{
			value = 255;  //��������Ϊ��ɫ��   
			histogramImage.at<uchar>(i, j) = value;
		}
	//imshow("d", histogramImage);  
	for (int i = 0; i<srcImage.rows; i++)
		for (int j = 0; j<rowswidth[i]; j++)
		{
			value = 0;  //ֱ��ͼ����Ϊ��ɫ  
			histogramImage.at<uchar>(i, j) = value;
		}
	imshow("ˮƽ����ͶӰͼ", histogramImage);
	delete[] rowswidth;//�ͷ�ǰ������Ŀռ�  
	return histogramImage;
}

//int main()
//{
//	Mat srcImage = imread("E:/jiequ1.png");
//	imshow("ԭͼ", srcImage);
//	Mat HP;
//	HP = HorizonProjection(srcImage);
//	Mat VP;
//	VP = VerticalProjection(srcImage);
//	waitKey(0);
//	return 0;
//
//}