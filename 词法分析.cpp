/*如果第一个是符号，会直接填入字母或其他的
解决方案1 一次只填入一个符号 一组符号单独判断 
*/

#include "head.h"

using namespace std;

struct Word{
	int typenum;
	string word;
	int num;
};

list<string> word;
list<Word> Two_tuples;


string readFileIntoString(char * filename){
	ifstream ifile(filename);//将文件读入到ostringstream对象buf中
	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch))buf.put(ch);//返回与流对象buf关联的字符串
	return buf.str();
}


//TPOK typenum of keyword
int getTPOK(string word)
{
	if(word=="begin") return 1;
	if(word=="if") return 2;
	if(word=="then") return 3;
	if(word=="while")  return 4;
	if(word=="do")  return 5;
	if(word=="end")  return 6;
	return 10;
}

//TPOO typenum of op
int getTPOO(string op)
{
	if(op=="+")  return 13;
	if(op=="-")  return 14;
	if(op=="*")  return 15;
	if(op=="/")  return 16;
	if(op==":")  return 17;
	if(op==":=")  return 18;
	if(op=="<")  return 20;
	if(op=="<>")  return 21;
	if(op=="<=")  return 22;
	if(op==">")  return 23;
	if(op==">=")  return 24;
	if(op=="=")  return 25;
	if(op==";")  return 26;
	if(op=="(")  return 27;
	if(op==")")  return 28;
	if(op=="#")  return 0;
	return -1;
}

//convert string into int
int getDigit(string digit)
{
	int len = digit.size();
	int num;
	int tot = 0;
	for(int i=0;i<len;i++)
	{
		num = digit.at(len-1-i)-48;
		for(int j=0;j<i;j++)
		{
			num = num*10;
		}
		tot+=num;
	}
	return tot;
}

void scan(string str)
{
	int i = 0;
	string tstr="";
	while(i<str.size())//扫描整个序列 
	{
		while(str.at(i) == '\n' ||str.at(i) =='\t' ||str.at(i) =='\r'){
			i++;
			if (i>=str.size()) break;
		}
		if(i>=str.size()) break;
		while(isalpha(str.at(i))!=0||isdigit(str.at(i))!=0)//扫描变量名 
		{
			tstr.push_back(str.at(i));
			if(isalpha(tstr.at(0)) == 0){//如果第一位是数字，退出 
				tstr.clear(); 
				break;
			}
			
			if(tstr.size()>=2){
				if(isalpha(str.at(i))!=0 && isdigit(str.at(i-1))!=0){
					i--;
					tstr.erase(tstr.end()-1);
					break;
				}
			}
			i++;
			if(i>=str.size()) break;
		}

		if(tstr.size()>0) {
			word.push_back(tstr);
			Word newone;
			newone.typenum = getTPOK(tstr);
			newone.word.append(tstr);
			Two_tuples.push_back(newone);
			tstr.clear();
		}
		
		if(i>=str.size()) break;
		while(isdigit(str.at(i))!=0){//扫描数字 
			tstr.push_back(str.at(i));
			i++;
			if(i>=str.size()) break;
			
		}
		
		if(tstr.size()>0) {
			word.push_back(tstr);
			Word newone;
			newone.typenum = 11;
			newone.num=getDigit(tstr);
			Two_tuples.push_back(newone); 
			tstr.clear();
		}
		
		if(i>=str.size()) break;
		int tag = 0;
		if(str.at(i) != ' ' && isalpha(str.at(i))==0 && isdigit(str.at(i))==0){
			tag = 1;
			if (str.at(i) == ':'){
				tstr.push_back(str.at(i));
				i++;
				if(i>=str.size()) break;
				if(str.at(i) == '=') {
					tstr.push_back(str.at(i));
					i++;
				}
			}
			
			else if (str.at(i) == '<'){
				tstr.push_back(str.at(i));
				i++;
				if(i<str.size()){
					if(str.at(i) == '='||str.at(i) == '>') {
					tstr.push_back(str.at(i));
					i++;
					}
				}
			}
			
			else if (str.at(i) == '>'){
				tstr.push_back(str.at(i));
				i++;
				if(i<str.size()){
					if(str.at(i) == '=') {
					tstr.push_back(str.at(i));
					i++;
					}	
				}
			}
			
			else {
				tstr.push_back(str.at(i));
				i++;
			}
		}
		
/*		
		while(str.at(i) !=' '&& isalpha(str.at(i))==0 && isdigit(str.at(i))==0) {
			tag = 1;
			if(str.at(i) == '\n') {
				i++;
				break;
			}
			
			if(str.at(i) == '('){
				tstr.push_back(str.at(i));
				i++;
				break;
			}

			if(str.at(i) == ')'){
				tstr.push_back(str.at(i));
				i++;
				break;
			}
						
			cout<<5<<endl;
			tstr.push_back(str.at(i));
			i++;
			if(i>=str.size()) break;
		}*/
		
		if(tstr.size()>0) {
			word.push_back(tstr);
			Word newone;
			newone.typenum =getTPOO(tstr);
			if(newone.typenum==-1) newone.word.append("error");
			else newone.word.append(tstr);
			Two_tuples.push_back(newone); 
			tstr.clear();
		}
		if(i<str.size()){
			if(tag==1 && (str.at(i))!=0||isdigit(str.at(i))!=0) i--;
		}
		i++;
		
	}
}

void run()
{
	char * fn="a.txt";
	string str;
	str=readFileIntoString(fn);
	scan(str);
}

/*
int main()
{
	char * fn="a.txt";
	string str;
	str=readFileIntoString(fn);
	scan(str);
	while(Two_tuples.size()!=0){
		Word temp;
		temp = Two_tuples.front();
		cout<<temp.typenum<<" ";
		if(temp.word.size() == 0) cout<<temp.num<<endl;
		else cout<<temp.word<<endl;
		Two_tuples.pop_front();
	}
}*/
