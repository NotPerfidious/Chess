#include"SomeTrivialShit.h"
using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

int alphaToNum(char ch)
{
	if (ch == 'a' || ch == '8')
		return 0;
	else if (ch == 'b' || ch == '7')
		return 1;
	else if (ch == 'c' || ch == '6')
		return 2;
	else if (ch == 'd' || ch == '5')
		return 3;
	else if (ch == 'e' || ch == '4')
		return 4;
	else if (ch == 'f' || ch == '3')
		return 5;
	else if (ch == 'g' || ch == '2')
		return 6;
	else if (ch == 'h'||ch=='1')
		return 7;
	

	return -1;
}

bool cmpstr(const char* str1, const char* str2)
{

	if (strlen(str1) == strlen(str2))
	{
		for (int i = 0; i < (int)strlen(str1); i++)
			if ((str1[i] != str2[i]) && (((str1[i] - 32) != str2[i]) && ((str1[i] + 32) != str2[i])))
				return false;
	}
	else
		return false;
	return true;
}

void space(int count)
{
	for (int i = 0; i < count; i++)
		cout << " ";
}

void copy(char* dest, const char* src)
{
	for (int i = 0; i < (int)strlen(src) + 1; i++)
		dest[i] = src[i];
}

float distanceInPlane(int*&arr)
{
	float b = (float)(arr[0] - arr[2]);
	b = b * b;
	float c = (float)(arr[1] - arr[3]);
	c = c * c;

	return sqrt(b + c);
}


float slope(int*&arr)
{
	float a = (float)(arr[0] - arr[2]),b=(float)(arr[1]-arr[3]);

	return abs(a / b);
}

void switchColor(const char* &colour)
{
	if (cmpstr(colour, "White"))
		colour = "Black";
	else
		colour = "White";
}

void setUserDisplayColour(const char* &colour)
{
	if (cmpstr(colour, "White"))
		cout << RESET;
	else
		cout << CYAN;
}

void skiplines(int k)
{
	for (int i = 0; i < k; i++)
		cout << endl;
}
