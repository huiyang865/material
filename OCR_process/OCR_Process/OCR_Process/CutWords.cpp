#include "stdafx.h"
#include "CutWords.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <numeric>
#include <algorithm>
#include <cv.h>
#include <highgui.h>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

CutWords::CutWords() {
	blobList = list<WordBlob>();
	boxList = list<WordBox>();
}

CutWords::~CutWords() {
}

void CutWords::verticalProjection(list<Mat> srcImageList)//垂直积分投影  
{
	list<Mat>::iterator itor;  //定义迭代器
	itor = srcImageList.begin();
	while (itor != srcImageList.end()) {
		Mat srcImageBin = *itor;
		//imshow("二值图", srcImageBin);
		//waitKey(0);
		int *colswidth = new int[srcImageBin.cols];  //申请src.image.cols个int型的内存空间  
		memset(colswidth, 0, srcImageBin.cols * 4);  //数组必须赋初值为零，否则出错。无法遍历数组。  
												  //  memset(colheight,0,src->width*4);    
												  // CvScalar value;   
		int value;
		for (int i = 0; i < srcImageBin.cols; i++)
			for (int j = 0; j < srcImageBin.rows; j++)
			{
				//value=cvGet2D(src,j,i);  
				value = srcImageBin.at<uchar>(j, i);
				if (value == 255)
				{
					colswidth[i]++; //统计每列的白色像素点    
				}
			}

		// 获取每个字符的左右边界
		WordBlob blob = blobList.front();
		blobList.pop_front();
		WordBox box = WordBox();
		for (int i = 0; i < srcImageBin.cols; i++) {
			if (colswidth[i] > 0 && box.top_left_x <= 0) {
				box.top_left_y = blob.top_left_y;
				box.top_left_x = i > 0 ? i - 1 : i;
			}
			if (colswidth[i] == 0 && box.top_left_x > 0) {
				box.bot_right_y = blob.bot_right_y;
				box.bot_right_x = i;
				boxList.push_back(box);
				box = WordBox();
			}
		}
		itor++;
	}
}

Mat CutWords::horizonProjection(Mat srcImage)//水平积分投影  
{
	if (srcImage.channels() > 1)
		cvtColor(srcImage, srcImage, CV_RGB2GRAY);
	Mat srcImageBin;
	threshold(srcImage, srcImageBin, 120, 255, CV_THRESH_BINARY_INV);
	//namedWindow("二值图", 0);
	//imshow("二值图", srcImageBin);
	//waitKey(0);
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

	// 获取每行字符的上下边界
	WordBlob blob = WordBlob();
	for (int i = 0; i < srcImage.rows; i++) {
		if (rowswidth[i] > 0 && blob.top_left_y <= 0) {
			blob.top_left_y = i > 0 ? i-1 : i;
		}
		if (rowswidth[i] == 0 && blob.top_left_y > 0) {
			blob.bot_right_y = i;
			blobList.push_back(blob);
			blob = WordBlob();
		}
	}
	return srcImageBin;
}

// 行切割
list<Mat> CutWords::cutLine(Mat srcImageBin) {
	list<Mat> tempMatList;
	list<WordBlob>::iterator itor;  //定义迭代器
	itor = blobList.begin();
	while (itor != blobList.end()) {
		int lineTop = itor->top_left_y;
		int lineBot = itor->bot_right_y;
		Mat tempMat(lineBot - lineTop+1, srcImageBin.cols, CV_8UC1);
		for (int i = lineTop; i <= lineBot; i++)
			for (int j = 0; j < srcImageBin.cols; j++)
			{ 
				tempMat.at<uchar>(i- lineTop, j) = srcImageBin.at<uchar>(i, j);
			}
		//imshow("行数据", tempMat);
		//waitKey(0);
		tempMatList.push_back(tempMat);
		itor++;
	}
	return tempMatList;
}

// 合并blob
void CutWords::combineBlob() {
	list<WordBlob>::iterator itor;  //定义迭代器
	itor = blobList.begin();
	list<WordBlob>::iterator preItor = itor;
	itor++;
	while (itor != blobList.end()) {
		if (itor->top_left_y - preItor->bot_right_y <= 10 && itor->top_left_y - preItor->bot_right_y >= 0) {
			preItor->bot_right_y = itor->bot_right_y;
			list<WordBlob>::iterator itor1 = itor;
			itor++;
			blobList.erase(itor1);
		}
		else {
			preItor = itor;
			itor++;
		}
	}
}

// 合并box
void CutWords::combineBox() {
	list<WordBox>::iterator itor;  //定义迭代器
	itor = boxList.begin();
	list<WordBox>::iterator preItor = itor;
	itor++;
	while (itor != boxList.end()) {
		if (itor->top_left_x - preItor->bot_right_x <= 30 && itor->top_left_x - preItor->bot_right_x >= 0) {
			preItor->bot_right_x = itor->bot_right_x;
			list<WordBox>::iterator itor1 = itor;
			itor++;
			boxList.erase(itor1);
		}
		else {
			preItor = itor;
			itor++;
		}
	}
}

// box调整
void CutWords::updateWordBox(Mat srcImageBin) {
	list<WordBox>::iterator itor;  //定义迭代器
	itor = boxList.begin();
	while (itor != boxList.end()) {
		int lineTop = itor->top_left_y;
		int lineBot = itor->bot_right_y;
		int wordLeft = itor->top_left_x;
		int wordRight = itor->bot_right_x;
		Mat tempMat(lineBot - lineTop + 1, wordRight - wordLeft + 1, CV_8UC1);
		// 截取box框中的Mat数据
		for (int i = 0; i < wordRight - wordLeft + 1; i++)
			for (int j = 0; j < lineBot - lineTop + 1; j++)
			{
				tempMat.at<uchar>(j, i) = srcImageBin.at<uchar>(j+ lineTop, i + wordLeft);
			}
		imshow("字符图像", tempMat);
		waitKey(0);
		// tempMat水平投影并截框
		int value;
		int *rowswidth = new int[tempMat.rows];
		memset(rowswidth, 0, tempMat.rows * 4);
		for (int i = 0; i<tempMat.rows; i++)
			for (int j = 0; j<tempMat.cols; j++)
			{
				//value=cvGet2D(src,j,i);
				value = tempMat.at<uchar>(i, j);
				if (value == 255)
				{
					rowswidth[i]++; //统计每行的白色像素点    
				}
			}
		//获取每个字符的上下边界，并调整box数据
		//imshow("字符图像", tempMat);
		//waitKey(0);
		for (int i = 0; i < tempMat.rows; i++) {
			if (rowswidth[i] > 0) {
				itor->top_left_y = i + itor->top_left_y;
				break;
			}
		}
		for (int i = tempMat.rows;i >= 0;i--) {
			if (rowswidth[i] > 0) {
				itor->bot_right_y = i + itor->top_left_y;
				break;
			}
		}

		//lineTop = itor->top_left_y;
		//lineBot = itor->bot_right_y;
		//wordLeft = itor->top_left_x;
		//wordRight = itor->bot_right_x;
		//Mat tempMat1(lineBot - lineTop + 1, wordRight - wordLeft + 1, CV_8UC1);
		//// 截取box框中的Mat数据
		//for (int i = 0; i < wordRight - wordLeft + 1; i++)
		//	for (int j = 0; j < lineBot - lineTop + 1; j++)
		//	{
		//		tempMat1.at<uchar>(j, i) = srcImageBin.at<uchar>(j + lineTop, i + wordLeft);
		//	}
		//imshow("字符图像1", tempMat1);
		//waitKey(0);

		itor++;
	}
}

void CutWords::regionLines(Mat srcImage) {
	Mat srcImage1;
	srcImage.copyTo(srcImage1);
	list<WordBlob>::iterator itor1;  //定义迭代器
	itor1 = blobList.begin();
	while (itor1 != blobList.end()) {
		rectangle(srcImage1, Point(1, itor1->top_left_y),
			Point(srcImage1.cols-1, itor1->bot_right_y), Scalar(0, 0, 255), 0.2, 1, 0);
		itor1++;
	}
	imwrite("E:/javaWorkspace/PdfConvertImage/test_data/image_math_data_test1.png", srcImage1);
}

// 原图上画box
void CutWords::regionWords(Mat srcImage) {
	list<WordBox>::iterator itor;  //定义迭代器
	itor = boxList.begin();
	while (itor != boxList.end()) {
		rectangle(srcImage, Point(itor->top_left_x, itor->top_left_y), 
			Point(itor->bot_right_x, itor->bot_right_y), Scalar(0, 0, 255), 0.2, 1, 0);
		//for (int i = itor->top_left_x; i<itor->bot_right_x; i++)
		//	for (int j = itor->top_left_y; j<itor->bot_right_y; j++)
		//	{
		//		rectangle(srcImage, Point(itor->top_left_x, itor->top_left_y), Point(itor->bot_right_x, itor->bot_right_y), Scalar(0, 0, 255), 3, 8, 0);
		//	}
		itor++;
	}
	//imshow(" 截取的图像", srcImage);
	imwrite("../../data/adjust_img_tif/image_math_data.pdf_%d.tif", srcImage);
}

void CutWords::writeBoxFile(String outFile, int page_num, Mat srcImageBin) {
	ofstream outfile;
	int row_lines = srcImageBin.rows;
	outfile.open(outFile); //myfile.bat是存放数据的文件名
	list<WordBox>::iterator itor;  //定义迭代器
	itor = boxList.begin();
	if (outfile.is_open())          //文件打开成功,说明曾经写入过东西  
	{
		while (itor != boxList.end()) {
			outfile << itor->top_left_x << " " << row_lines - itor->bot_right_y
				<< " " << itor->bot_right_x << " " << row_lines - itor->top_left_y << " " << page_num << endl;
			//outfile << itor->top_left_x << " " << itor->top_left_y
			//	<< " " << itor->bot_right_x << " " << itor->bot_right_y << " " << page_num << endl;
			itor++;
		}
		outfile.close();
	}
}

Mat CutWords::adjustBoxLocation(Mat srcImage, int pageNum) {
	Mat newMat(4800, 3600, CV_8UC1, Scalar(255));
	list<WordBox>::iterator itor;  //定义迭代器
	itor = boxList.begin();
	int pageLeft = 110;
	int pageTop = 170;
	int verSpace = 15;
	int horiSpace = 5;
	int preWordRight = 0;
	int preLineBot = 0;
	while (itor != boxList.end()) {
		int boxTop = itor->top_left_y;
		int boxBot = itor->bot_right_y;
		int boxLeft = itor->top_left_x;
		int boxRight = itor->bot_right_x;
		if (boxRight - boxLeft < 35) {
			horiSpace = 2;
		}
		else {
			horiSpace = 5;
		}
		for (int i = boxTop; i < boxBot; i++)
			for (int j = boxLeft; j < boxRight; j++)
			{
				newMat.at<uchar>(i - boxTop + preLineBot + pageTop, j - boxLeft + preWordRight + pageLeft) = 255 - srcImage.at<uchar>(i, j);
			}
		itor->top_left_y = preLineBot + pageTop;
		itor->bot_right_y = itor->top_left_y + boxBot - boxTop;
		itor->top_left_x = preWordRight + pageLeft;
		itor->bot_right_x = itor->top_left_x + boxRight - boxLeft;
		//namedWindow("新页面", 0);
		//imshow("新页面", newMat);
		//waitKey(0);
		itor++;
		if (itor != boxList.end()) {
			preWordRight += boxRight - boxLeft + horiSpace;
			if (itor->top_left_y != boxTop) {
				preLineBot += boxBot - boxTop + verSpace;
				preWordRight = 0;
			}
		}
	}
	//sprintf(newMat, "E:/tess_data/befor_recog_all_words/%d.jpg", pageNum);
	char path[256] = "";
	printf("%d\n", pageNum);
	sprintf(path, "../../data/adjust_img_tif/image_math_data.pdf_%d.tif", pageNum);
	imwrite(path, newMat);
	return newMat;
}