#include"CutWords.h"
#include <Windows.h>
#include <cv.h>
#include <highgui.h>
#include<opencv2\imgproc\imgproc.hpp>
using namespace std;

#define MAX_PATH 1024  //最长路径长度  
void find(char* lpPath, vector<string> &fileList)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;

	strcpy(szFind, lpPath);
	strcat(szFind, "\\*.*");

	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)    return;

	while (true)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				char szFile[MAX_PATH];
				strcpy(szFile, lpPath);
				strcat(szFile, "\\");
				strcat(szFile, (char*)(FindFileData.cFileName));
				find(szFile, fileList);
			}
		}
		else
		{
			//std::cout << FindFileData.cFileName << std::endl;  
			fileList.push_back(FindFileData.cFileName);
		}
		if (!FindNextFile(hFind, &FindFileData))    break;
	}
	FindClose(hFind);
}

void dealEachImg(string path) {
	int pageNum = 0;
	cout << path << endl;
	char saveBox[256] = "";
	int begin = path.find("image__") + 7;
	int end = path.find(".tif");
	string subStr = path.substr(path.find("image__") + 7, end - begin);
	stringstream ss;
	ss << subStr;
	ss >> pageNum;
	CutWords cutWords = CutWords();
	Mat srcImage = imread(path);
	//imshow("原图", srcImage);
	Mat srcImageBin;
	srcImageBin = cutWords.horizonProjection(srcImage);
	cutWords.combineBlob();
	//GaussianBlur(srcImage, srcImage, Size(5, 5), 0, 0);
	list<Mat> lineImgs = cutWords.cutLine(srcImageBin);
	//cutWords.regionLines(srcImage);
	cutWords.verticalProjection(lineImgs);
	cutWords.combineBox();
	//cutWords.updateWordBox(srcImageBin);
	//cutWords.regionWords(srcImage);
	//waitKey(0);
	srcImageBin = cutWords.adjustBoxLocation(srcImageBin, pageNum);
	sprintf(saveBox, "../../data/txt_box/boxdata_%d.txt", pageNum);
	cutWords.writeBoxFile(saveBox, pageNum, srcImageBin);
}

/**
输入tif图片：E:/javaWorkspace/PdfConvertImage/test_data/
box存储路径：E:/javaWorkspace/PdfConvertImage/test_box/
tif存储路径：E:/jTessBoxEditorFX/tesseract-ocr/temp_roman/
*/
int main()
{
	vector<string> fileList;
	find("../../data/img_tif/", fileList);
	for (int i = 0; i < fileList.size(); i++) {
		dealEachImg("../../data/img_tif/" + fileList[i]);
	}
	//dealEachImg("E:/javaWorkspace/PdfConvertImage/test_data/image_math_data.pdf_15.tif");
	return 0;

}