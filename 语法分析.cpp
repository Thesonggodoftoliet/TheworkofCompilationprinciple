#include "´Ê·¨·ÖÎö.cpp"

using namespace std;

Word tempword;
int kk = 0;

void Irparser();
void yucu();
void statement();
void expression();
void term();
void factor();

Word scanner()
{
	Word temp = Two_tuples.front();
	Two_tuples.pop_front();
	return temp;
}

void factor()
{
	if(tempword.typenum==10||tempword.typenum==11)
	{
		tempword = scanner();
	}
	else if(tempword.typenum==27)
	{
		tempword = scanner();
		expression();
		if(tempword.typenum==28)
		{
			tempword = scanner();
		}
		else 
		{
			cout<<"')'é”™è¯¯"<<endl;
			kk=1;
		}
	}
	else
	{
		cout<<"è¡¨è¾¾å¼é”™è¯¯"<<endl;
		kk=1;
	}
}

void term()
{
	factor();
	while(tempword.typenum==15||tempword.typenum==16)
	{
		tempword = scanner();
		factor();
	}
}

void expression()
{
	term();
	while(tempword.typenum==13||tempword.typenum==14)
	{
		tempword = scanner();
		term();
	}
}

void statement()
{
	if(tempword.typenum == 10)
	{
		tempword = scanner();
		if(tempword.typenum == 18)
		{
			tempword = scanner();
			expression();
		}
		else 
		{
			cout<<"èµ‹å€¼å·é”™è¯¯"<<endl;
			kk=1;
		}
	}
	else
	{
		cout<<"è¯­å¥é”™è¯¯"<<endl;
		kk=1;
	}
}

void yucu()
{
	statement();
	while(tempword.typenum==26)
	{
		tempword=scanner();
		statement();	
	}	
} 

void Irparser()
{
	if(tempword.typenum == 1)
	{
		tempword=scanner();
		yucu();
		if (tempword.typenum == 6)
		{
			if(Two_tuples.size()==0)
				cout<<"#é”™è¯¯"<<endl;
			else
			{
				tempword=scanner();
				if(tempword.typenum == 0 && (kk == 0))
				cout<<"success"<<endl;
			}
		}
		else
		{
			if(kk!=1) cout<<"endé”™è¯¯"<<endl;
			kk=1;
		}
	}
	else 
	{
		cout<<"beginé”™è¯¯"<<endl;
		kk=1;
	}
}

int main()
{
	run();
	tempword = scanner();
	Irparser();
	return 0;
	
}
