#include "stdafx.h"
#include <cv.h>
#include <highgui.h>
#include<opencv2\imgproc\imgproc.hpp>

using namespace cv;
Mat VerticalProjection(Mat srcImage)//垂直积分投影  
{
	if (srcImage.channels() > 1)
		cvtColor(srcImage, srcImage, CV_RGB2GRAY);
	Mat srcImageBin;
	threshold(srcImage, srcImageBin, 120, 255, CV_THRESH_BINARY_INV);
	imshow("二值图", srcImageBin);
	int *colswidth = new int[srcImage.cols];  //申请src.image.cols个int型的内存空间  
	memset(colswidth, 0, srcImage.cols * 4);  //数组必须赋初值为零，否则出错。无法遍历数组。  
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
				colswidth[i]++; //统计每列的白色像素点    
			}
		}
	Mat histogramImage(srcImage.rows, srcImage.cols, CV_8UC1);
	for (int i = 0; i < srcImage.rows; i++)
		for (int j = 0; j < srcImage.cols; j++)
		{
			value = 255;  //背景设置为白色。   
			histogramImage.at<uchar>(i, j) = value;
		}
	for (int i = 0; i < srcImage.cols; i++)
		for (int j = 0; j < colswidth[i]; j++)
		{
			value = 0;  //直方图设置为黑色  
			histogramImage.at<uchar>(srcImage.rows - 1 - j, i) = value;
		}
	imshow(" 垂直积分投影图", histogramImage);
	return histogramImage;
}
Mat HorizonProjection(Mat srcImage)//水平积分投影  
{
	if (srcImage.channels() > 1)
		cvtColor(srcImage, srcImage, CV_RGB2GRAY);
	Mat srcImageBin;
	threshold(srcImage, srcImageBin, 120, 255, CV_THRESH_BINARY_INV);
	imshow("二值图", srcImageBin);
	int *rowswidth = new int[srcImage.rows];  //申请src.image.rows个int型的内存空间  
	memset(rowswidth, 0, srcImage.rows * 4);  //数组必须赋初值为零，否则出错。无法遍历数组。  
	int value;
	for (int i = 0; i<srcImage.rows; i++)
		for (int j = 0; j<srcImage.cols; j++)
		{
			//value=cvGet2D(src,j,i);  
			value = srcImageBin.at<uchar>(i, j);
			if (value == 255)
			{
				rowswidth[i]++; //统计每行的白色像素点    
			}
		}
	Mat histogramImage(srcImage.rows, srcImage.cols, CV_8UC1);
	for (int i = 0; i<srcImage.rows; i++)
		for (int j = 0; j<srcImage.cols; j++)
		{
			value = 255;  //背景设置为白色。   
			histogramImage.at<uchar>(i, j) = value;
		}
	//imshow("d", histogramImage);  
	for (int i = 0; i<srcImage.rows; i++)
		for (int j = 0; j<rowswidth[i]; j++)
		{
			value = 0;  //直方图设置为黑色  
			histogramImage.at<uchar>(i, j) = value;
		}
	imshow("水平积分投影图", histogramImage);
	delete[] rowswidth;//释放前面申请的空间  
	return histogramImage;
}

//int main()
//{
//	Mat srcImage = imread("E:/jiequ1.png");
//	imshow("原图", srcImage);
//	Mat HP;
//	HP = HorizonProjection(srcImage);
//	Mat VP;
//	VP = VerticalProjection(srcImage);
//	waitKey(0);
//	return 0;
//
//}