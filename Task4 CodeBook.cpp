#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable : 4996)

int findindex(char ch, char[6][100], int[100]);
int encryption(char[6][100], int[100]);
int decryption(char[6][100]);

int main()
{
	//读取codebook自己的密码本内容存入二维数组
	char ch, str[6][100] = { 0 };
	int position[100];
	int s, i = 0, j = 0;
	FILE* codebook = fopen("../File/mycodebook.txt", "r");
	if (codebook == NULL)
	{
		return -1;
	}
	while (fscanf(codebook, "%c", &ch) != EOF)
	{
		if (ch == 10)
		{
			i++;
			j = 0;
		}
		else if ((ch <= 90 && ch >= 65) || (ch <= 122 && ch >= 97))
		{
			str[i][j] = ch;
			j++;
		}
	}
	//控制台输入1或2来控制是加密还是解密
	printf("%s", "Please choose the function of you want.\n 1.Encryption 2.Decryption\n");//选择加密或解密
	scanf("%d", &s);
	if (s != 1 && s != 2)
	{
		printf("Wrong input number! Check it!");
	}
	else if (s == 1)
	{
		encryption(str, position);
	}
	else if (s == 2)
	{
		decryption(str);
	}
}

int findindex(char ch, char str[6][100], int position[100])
{
	//查找某个字符在str二维数组里面的位置，并且输出一个五位数来代表这个字符的加密后的内容
	int i = 0, j = 0, num = 0, random;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//不论密码本里面的是大写还是小写，都记作这个字符本身的四位数标记
			if (ch == str[i][j] || (ch == str[i][j] - 32 && ch <= 90 && ch >= 65) || (ch == str[i][j] + 32 && ch <= 122 && ch >= 97))
			{
				num++;
				srand((unsigned)time(NULL));
				if (ch <= 90 && ch >= 65) //字符本身是大写
				{
					random = 1 + rand() % 4;
					if ((i + 1 + (j + 1) % 10 + (j + 1) / 10) % 2 != 0) //判断四位数各个位数加起来是奇数还是偶数，然后再确定五位数首位的随机数的是奇数还是偶数
					{
						position[num - 1] = 2 * random * 10000 + (i + 1) * 100 + (j + 1); //大写为奇数，四位和为奇数，加偶数
					}
					else
					{
						position[num - 1] = (2 * random - 1) * 10000 + (i + 1) * 100 + (j + 1); // 大写为奇数，四位和为偶数，加奇数
					}
				}
				else if (ch <= 122 && ch >= 97) //字符本身是小写
				{
					random = 1 + rand() % 4;
					if ((i + 1 + (j + 1) % 10 + (j + 1) / 10) % 2 == 0) //判断四位数各个位数加起来是奇数还是偶数，然后再确定五位数首位的随机数的是奇数还是偶数
					{
						position[num - 1] = 2 * random * 10000 + (i + 1) * 100 + (j + 1) * 1;//小写为偶数，四位和为偶数，加偶数
					}
					else
					{
						position[num - 1] = (2 * random - 1) * 10000 + (i + 1) * 100 + (j + 1) * 1;// 小写为偶数，四位和为奇数，加奇数
					}
				}
			}
		}
	}
	//随机返回position的所有五位数中的一个
	srand((unsigned)time(NULL));
	int randomindex = rand() % num;
	return position[randomindex];
}

int encryption(char str[6][100], int position[100]) //加密程序
{
	int temp;
	char ch;
	FILE* clear = fopen("../FIle/cleartext.txt", "r");
	FILE* complex = fopen("../File/complextext.txt", "a+");
	if (clear == NULL)
	{
		return -1;
	}
	srand((unsigned)time(NULL));
	while (fscanf(clear, "%c", &ch) != EOF)
	{
		if ((ch <= 90 && ch >= 65) || (ch <= 122 && ch >= 97)) //所有字母一起处理，查找代表的五位数并且输出到加密文件中
		{
			temp = findindex(ch, str, position);
			fprintf(complex, "%d", temp);
		}
		else//其余所有字符和数字等等一起处理，将查找的五位数的最后两位获取，单独由ASCII码来确定，然后输出到加密文件里；
		{
			int random = 410 + rand() % 90;
			fprintf(complex, "%d%d", random, ch);
		}
	}
	fclose(clear);
	fclose(complex);
}

int decryption(char str[6][100]) //解密程序
{
	char tempstr, ch1, ch2, ch3, ch4, ch5;
	int n1, n2, n3, n4, n5;
	FILE* complex = fopen("../File/complextext.txt", "r");
	if (complex == NULL)
	{
		return -1;
	}
	printf("-----------------分割线-----------------\n");
	while (fscanf(complex, "%c%c%c%c%c", &ch1, &ch2, &ch3, &ch4, &ch5) != EOF) //一次读取五个字符，就可以实现源文件中的一个字符的解密操作
	{
		//将读取的五个字符变为整型数字便于操作
		n1 = atof(&ch1);
		n2 = atof(&ch2);
		n3 = atof(&ch3);
		n4 = atof(&ch4);
		n5 = atof(&ch5);
		if (n2 >= 1) //这个标志代表着这个五位数原本的字符是一个非26个字母的大小写，所以按照ASCII码直接打印就可以，前三位是随机生成的一个三位数，用于迷惑看加密后文件
		{
			tempstr = 10 * n4 + n5;
			printf("%c", tempstr);
		}
		else //其余情况是代表着原本五位数代表的是一个26个字母的大小写中的一个
		{
			int n = 10 * n4 + n5;
			if ((n1 + n2 + n3 + n4 + n5) % 2 != 0) //这里指的是各位数和为奇数，代表大写字母
			{
				if (str[n3 - 1][n - 1] <= 90 && str[n3 - 1][n - 1] >= 65) //如果本身就是大写字母，打印n3行n4列的二维数组对应的字符就可以
				{
					tempstr = str[n3 - 1][n - 1];
					printf("%c", tempstr);
				}
				else //如果本身是小写字母，则输出后四位代表的二维数组本身的元素ASCII码前32位的元素
				{
					tempstr = str[n3 - 1][n - 1] - 32;
					printf("%c", tempstr);
				}
			}
			else if ((n1 + n2 + n3 + n4 + n5) % 2 == 0) //这里指的是各位数和为偶数，代表小写字母
			{
				if (str[n3 - 1][n - 1] <= 90 && str[n3 - 1][n - 1] >= 65)  //如果本身是大写字母，则输出后四位代表的二维数组本身的元素ASCII码后32位的元素
				{
					tempstr = str[n3 - 1][n - 1] + 32;
					printf("%c", tempstr);
				}
				else //如果本身就是小写字母，打印n3行n4列的二维数组对应的字符就可以
				{
					tempstr = str[n3 - 1][n - 1];
					printf("%c", tempstr);
				}
			}
		}
	}
}
