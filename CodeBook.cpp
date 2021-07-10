#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable : 4996)

int findindex(char ch, char[6][100], int[100]);
int encryption(char[6][100], int[100]);
int decryption(char[6][100]);

int main()
{
	//��ȡcodebook�Լ������뱾���ݴ����ά����
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
	//����̨����1��2�������Ǽ��ܻ��ǽ���
	printf("%s", "Please choose the function of you want.\n 1.Encryption 2.Decryption\n");//ѡ����ܻ����
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
	//����ĳ���ַ���str��ά���������λ�ã��������һ����λ������������ַ��ļ��ܺ������
	int i = 0, j = 0, num = 0, random;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//�������뱾������Ǵ�д����Сд������������ַ��������λ�����
			if (ch == str[i][j] || (ch == str[i][j] - 32 && ch <= 90 && ch >= 65) || (ch == str[i][j] + 32 && ch <= 122 && ch >= 97))
			{
				num++;
				srand((unsigned)time(NULL));
				if (ch <= 90 && ch >= 65) //�ַ������Ǵ�д
				{
					random = 1 + rand() % 4;
					if ((i + 1 + (j + 1) % 10 + (j + 1) / 10) % 2 != 0) //�ж���λ������λ������������������ż����Ȼ����ȷ����λ����λ�������������������ż��
					{
						position[num - 1] = 2 * random * 10000 + (i + 1) * 100 + (j + 1); //��дΪ��������λ��Ϊ��������ż��
					}
					else
					{
						position[num - 1] = (2 * random - 1) * 10000 + (i + 1) * 100 + (j + 1); // ��дΪ��������λ��Ϊż����������
					}
				}
				else if (ch <= 122 && ch >= 97) //�ַ�������Сд
				{
					random = 1 + rand() % 4;
					if ((i + 1 + (j + 1) % 10 + (j + 1) / 10) % 2 == 0) //�ж���λ������λ������������������ż����Ȼ����ȷ����λ����λ�������������������ż��
					{
						position[num - 1] = 2 * random * 10000 + (i + 1) * 100 + (j + 1) * 1;//СдΪż������λ��Ϊż������ż��
					}
					else
					{
						position[num - 1] = (2 * random - 1) * 10000 + (i + 1) * 100 + (j + 1) * 1;// СдΪż������λ��Ϊ������������
					}
				}
			}
		}
	}
	//�������position��������λ���е�һ��
	srand((unsigned)time(NULL));
	int randomindex = rand() % num;
	return position[randomindex];
}

int encryption(char str[6][100], int position[100]) //���ܳ���
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
		if ((ch <= 90 && ch >= 65) || (ch <= 122 && ch >= 97)) //������ĸһ�������Ҵ������λ����������������ļ���
		{
			temp = findindex(ch, str, position);
			fprintf(complex, "%d", temp);
		}
		else//���������ַ������ֵȵ�һ���������ҵ���λ���������λ��ȡ��������ASCII����ȷ����Ȼ������������ļ��
		{
			int random = 410 + rand() % 90;
			fprintf(complex, "%d%d", random, ch);
		}
	}
	fclose(clear);
	fclose(complex);
}

int decryption(char str[6][100]) //���ܳ���
{
	char tempstr, ch1, ch2, ch3, ch4, ch5;
	int n1, n2, n3, n4, n5;
	FILE* complex = fopen("../File/complextext.txt", "r");
	if (complex == NULL)
	{
		return -1;
	}
	printf("-----------------�ָ���-----------------\n");
	while (fscanf(complex, "%c%c%c%c%c", &ch1, &ch2, &ch3, &ch4, &ch5) != EOF) //һ�ζ�ȡ����ַ����Ϳ���ʵ��Դ�ļ��е�һ���ַ��Ľ��ܲ���
	{
		//����ȡ������ַ���Ϊ�������ֱ��ڲ���
		n1 = atof(&ch1);
		n2 = atof(&ch2);
		n3 = atof(&ch3);
		n4 = atof(&ch4);
		n5 = atof(&ch5);
		if (n2 >= 1) //�����־�����������λ��ԭ�����ַ���һ����26����ĸ�Ĵ�Сд�����԰���ASCII��ֱ�Ӵ�ӡ�Ϳ��ԣ�ǰ��λ��������ɵ�һ����λ���������Ի󿴼��ܺ��ļ�
		{
			tempstr = 10 * n4 + n5;
			printf("%c", tempstr);
		}
		else //��������Ǵ�����ԭ����λ���������һ��26����ĸ�Ĵ�Сд�е�һ��
		{
			int n = 10 * n4 + n5;
			if ((n1 + n2 + n3 + n4 + n5) % 2 != 0) //����ָ���Ǹ�λ����Ϊ�����������д��ĸ
			{
				if (str[n3 - 1][n - 1] <= 90 && str[n3 - 1][n - 1] >= 65) //���������Ǵ�д��ĸ����ӡn3��n4�еĶ�ά�����Ӧ���ַ��Ϳ���
				{
					tempstr = str[n3 - 1][n - 1];
					printf("%c", tempstr);
				}
				else //���������Сд��ĸ�����������λ����Ķ�ά���鱾���Ԫ��ASCII��ǰ32λ��Ԫ��
				{
					tempstr = str[n3 - 1][n - 1] - 32;
					printf("%c", tempstr);
				}
			}
			else if ((n1 + n2 + n3 + n4 + n5) % 2 == 0) //����ָ���Ǹ�λ����Ϊż��������Сд��ĸ
			{
				if (str[n3 - 1][n - 1] <= 90 && str[n3 - 1][n - 1] >= 65)  //��������Ǵ�д��ĸ�����������λ����Ķ�ά���鱾���Ԫ��ASCII���32λ��Ԫ��
				{
					tempstr = str[n3 - 1][n - 1] + 32;
					printf("%c", tempstr);
				}
				else //����������Сд��ĸ����ӡn3��n4�еĶ�ά�����Ӧ���ַ��Ϳ���
				{
					tempstr = str[n3 - 1][n - 1];
					printf("%c", tempstr);
				}
			}
		}
	}
}