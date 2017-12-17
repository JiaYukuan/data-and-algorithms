#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
	string a,b;
	string c="0";
	cin>>a;
	cin>>b;

	int alen=0,blen=0;
	alen=a.length();
	blen=b.length();

	int n=abs(alen-blen);
	string str(n,'0');
	if(alen>blen) {b=str+b;blen=alen;}
	else {a=str+a;alen=blen;}

	//防止连续进位的出现
	a=c+a;
	b=c+b;

	string s;
	int t;
	int flag=0;		//是否进位
	for(int i=0;!(i>alen&&flag==0);i++)
	{
		t=a[alen-i]+b[alen-i]-96+flag;	//所得位
		if(t>9) {t-=10;flag=1;}				//是否进位
		else flag=0;
		c[0]=t+48;
		if(!(i==alen&&t==0))
			s=c+s;
	}

	cout<<s;
	return 0;
}
