
#include <string>

#include <fstream>

#include <sstream>

#include <iostream>

 

#include <stdlib.h>

using namespace std;

 

 

//���ļ����뵽string��

string readFileIntoString(char * filename)

{

ifstream ifile(filename);

//���ļ����뵽ostringstream����buf��

ostringstream buf;

char ch;

while(buf&&ifile.get(ch))

buf.put(ch);

//������������buf�������ַ���

return buf.str();

}

 

 

int main()

{

//�ļ���

char * fn="a.txt";

string str;

str=readFileIntoString(fn);

cout<<str<<endl;

system("pause");

 

}
