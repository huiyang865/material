#pragma once
#include "WordBox.h"
#include <list>
using namespace std;

class WordBlob
{
public:
	list<WordBox> boxList;
	int top_left_x;
	int top_left_y;
	int bot_right_x;
	int bot_right_y;
	WordBlob();
	~WordBlob();
};

