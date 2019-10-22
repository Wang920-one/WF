////////////////////////////////
#include<iostream>
#include<string.h>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;

struct Letter
{
	int num = 0;
	char words;
};

Letter str[26];
int sum = 0;

bool cmp(Letter a, Letter b)
{
	return a.num > b.num;
}

void countnum(FILE*fp)
{

	char letter = 0;
	int num = 0, ret;
	while (!feof(fp))
	{

		letter = fgetc(fp);
		//cout << letter << " " << endl;
		if ((letter >= 'a'&&letter <= 'z') || (letter >= 'A'&&letter <= 'Z'))
		{
			str[letter - 'a'].num++;
			str[letter - 'a'].words = letter;
			//cout << str[letter - 'a'].num << endl;
		}
	}
	sort(str, str + 26, cmp);
	return;
}

int main()
{
	FILE *fp;
	int sl;
	int allwords = 0;
	if ((fp = fopen("1.txt", "r")) == NULL) {
		printf("Cannot open the file!\n");
		exit(0);
	}

	str[0].words = 'a';

	//for (sum = 0; sum<26; sum++) {
	//	str[sum].words = 'a' + sum;
	countnum(fp);
	//rewind(fp);
	//}
	fclose(fp);
	for (int i = 0; i < 26; i++)
	{
		allwords += str[i].num;
	}
	for (int i = 0; i < 26; i++)
	{
		
		printf("%c出现%d次,概率是：%.2f%%\n", str[i].words, str[i].num, (double)str[i].num / allwords);
	}
	cin >> sl;
	return 0;
}