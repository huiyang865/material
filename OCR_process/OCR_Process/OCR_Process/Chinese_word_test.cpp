#include <iostream>  

#include <cstring>  

#include <string>  

#include <fstream>
#include <cstdlib>  

#include <vector>  

using namespace std;



class str {

	char *c;

	typedef struct {

		int start;

		bool isChinese;

	} counter;

	int cLen;

	vector<counter> cs;

	void calculate() {

		cLen = sizeof("��") - 1;

		int size = 0;

		for (int i = 0; i < getlen();) {

			counter ic;

			ic.start = i;

			//���ݵ�һ���ַ��Ƿ�Ϊ�����ж��Ƿ�Ϊ���ġ��������֪���ǲ�������ͣ����Ǵ�������Ӧ�ÿ���Ӧ����  

			if (c[i] < 0) {

				ic.isChinese = true;

				i += cLen;

			}
			else {

				ic.isChinese = false;

				i++;

			}

			cs.push_back(ic);

		}

	}

public:

	str(const char *cc) {

		cout << "����" << endl;

		c = new char[strlen(cc) + 1];

		strcpy(c, cc);

		calculate();

	}

	str(const str& s) {//copy  

		cout << "copy" << endl;

		c = new char[s.getlen() + 1];

		strcpy(c, s.getstr());

		calculate();

	}

	const str& operator =(const str& s) {

		cout << "= operator" << endl;

		if (&s == this) return s;

		cs.clear();

		delete[]c;

		c = new char[s.getlen() + 1];

		strcpy(c, s.getstr());

		calculate();

		return *this;

	}

	//��ȡԴ�ַ���  

	const char *getstr() const { return c; }

	//Դ�ַ��� �ֽ�����������'\0'  

	int getlen() const {

		return strlen(c);

	}

	//�����ַ�������������Ӣ�ġ�������'\0'  

	int getsize() const {

		return cs.size();

	}

	//��ȡ��i���ַ�������Ϊ���Ļ�Ӣ�ġ�  

	const char* get(int i) const {

		if (i > getsize()) {

			cout << "error in get " << endl;

			return NULL;

		}

		const counter &cc = cs[i];

		char *r = NULL;

		int len = 0;

		if (cc.isChinese) {

			r = new char[cLen + 1];

			len = cLen;

		}
		else {

			r = new char[2];

			len = 1;

		}

		memcpy(r, c + cc.start, len);

		r[len] = '\0';

		string rs = r;

		delete[]r;

		return rs.c_str();

	}



	void printBytes(const char *start, const char *end) const {//debug  

		int i = 0;

		do {

			cout << (int)*(start + i) << "\t";

		} while (start + (++i) < end);

		cout << endl;

	}

	//����  

	void traversal() const {//debug  

		for (int i = 0; i < getsize(); i++) {

			cout << get(i) << " ";
			ofstream outfile;
			outfile.open("E:/boxdata.txt");
			//printBytes(get(i), get(i) + strlen(get(i)));  

		}

		cout << endl;

	}

	virtual ~str() {

		delete[]c;

	}



};



//int main() {
//
//	//construct  
//
//	str s("13,4?!��á�����sda");
//
//	s.traversal();
//
//
//
//	str s1 = s;//copy  
//
//	cout << s1.getlen() << endl;
//
//	s1.traversal();
//
//
//
//	s1 = s;//oeprator =  
//
//	cout << s1.getlen() << endl;
//
//	s1.traversal();
//
//	return 0;
//
//}