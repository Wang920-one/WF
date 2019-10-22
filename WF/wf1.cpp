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
			flag = 1;//��ʼд��b
		}
		else
		{
			if (ch == '-' && (ch = fgetc(fp)) == '\n')//����ĸ���ǿո�
			{
				flag = 0;
			}
			else
			{
				if (flag == 1)//�ո�
				{
					b[ij] = '\0';
					ij = 0;
					flag = 0;
					m = 0;//д��b���+'\0'
					for (j = 0; j < k; j++)
					{
						if (strcmp(b, w[j].c) == 0)
						{
							m = 1;//��־  ǰ�е�����ͬ
							break;
						}
					}
					if (m)
						w[j].n++;
					else//����ṹ��
					{
						w[k].n = 1;
						strcpy(w[k].c, b);
						k++;
					}
				}
			}

		}
	}

	/*���� ǰ5 */
	printf("���ǰ5������ֵĵ��ʣ�");

	for (ij = 0; ij < k&&ij < 5; ij++)
	{
		t = 0;
		while (w[t].n == 0)
			t++;
		for (j = 1; j<k; j++)
		{
			if (w[j].n>w[t].n) t = j;//ѡ ���
			else
				if (w[j].n == w[t].n)
				{
					if (strcmp(w[j].c, w[t].c) < 0)
						t = j;
				}
		}
		printf("%s %d\n", w[t].c, w[t].n);
		w[t].n = 0;//t ���������n=0;
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
		printf("%c����%d��,�����ǣ�%.2f%%\n", str[i].words, str[i].num, (double)str[i].num / allwords);
	}
	cin >> sl;
	return 0;
}