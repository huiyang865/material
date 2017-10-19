#pragma once
#include "WordBlob.h"
#include <list>
#include <cv.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;
class CutWords
{
public:
	void verticalProjection(list<Mat> srcImageList);
	Mat horizonProjection(Mat srcImage);
	list<Mat> cutLine(Mat srcImage);
	void combineBlob();
	void regionWords(Mat srcImage);
	void writeBoxFile(String outFile, int page_num, Mat srcImageBin);
	Mat adjustBoxLocation(Mat srcImage, int pageNum);
	void combineBox();
	void updateWordBox(Mat srcImageBin);
	void regionLines(Mat srcImage);
	list<WordBlob> blobList;
	list<WordBox> boxList;
	CutWords();
	~CutWords();
};

