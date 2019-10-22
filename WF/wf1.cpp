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
struct words
{
	int n;
	char c[30];
}w[10000];

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
void countWord(FILE*fp)
{
	char b[30], ch;
	int ij = 0, m = 1, j = 0, k = 0, t = 0, flag = 0;
	while ((ch = fgetc(fp)) != EOF)
	{
		if ('A' <= ch&&ch <= 'Z')
			ch = ch + 32;
		if ('a' <= ch&&ch <= 'z')
		{
			b[ij] = ch;
			ij++;
			flag = 1;//开始写入b
		}
		else
		{
			if (ch == '-' && (ch = fgetc(fp)) == '\n')//非字母。非空格
			{
				flag = 0;
			}
			else
			{
				if (flag == 1)//空格
				{
					b[ij] = '\0';
					ij = 0;
					flag = 0;
					m = 0;//写入b完成+'\0'
					for (j = 0; j < k; j++)
					{
						if (strcmp(b, w[j].c) == 0)
						{
							m = 1;//标志  前有单词相同
							break;
						}
					}
					if (m)
						w[j].n++;
					else//存入结构体
					{
						w[k].n = 1;
						strcpy(w[k].c, b);
						k++;
					}
				}
			}

		}
	}

	/*输入 前5 */
	printf("输出前5个最常出现的单词：");

	for (ij = 0; ij < k&&ij < 5; ij++)
	{
		t = 0;
		while (w[t].n == 0)
			t++;
		for (j = 1; j<k; j++)
		{
			if (w[j].n>w[t].n) t = j;//选 大的
			else
				if (w[j].n == w[t].n)
				{
					if (strcmp(w[j].c, w[t].c) < 0)
						t = j;
				}
		}
		printf("%s %d\n", w[t].c, w[t].n);
		w[t].n = 0;//t 已输出，令n=0;
	}

}

int main()
{
	FILE *fp;
	fp = fopen("1.txt", "r");
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
	countWord(fp);
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