#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void Bubble_Sort(int* arr1, int* arr2, int size);
void Selection_Sort(int* arr1, int* arr2, int size);
void Linear_Search(int* arr1, int* arr2, int value, int size);
int Binary_Search(int* arr, int value, int size);

int main()
{
    FILE* randlist;
    FILE* sortedlist;
    int indexarr[20];
    for (int i = 0; i < 20; i++)
    {
        indexarr[i] = i + 1;
    }
    //step1������20��1-15���������txt�ļ�
    srand((unsigned)time(NULL));    //����
    //�����ɵ������д��txt�ļ�
    for (int i = 0; i < 20; i++)
    {
        int j = 1 + rand() % 15;
        fopen_s(&randlist, "C:/Users/cloud/Desktop/RandList.txt", "a");
        if (randlist == NULL)
        {
            return 0;
        }
        fprintf(randlist, "%d;", j);
        fclose(randlist);
    }


    //step2�������ɺõ�txt�ļ��е����ݴ浽����numlist�з����������,���ҽ�numlist�Ķ�ӦԪ��������ŵ�indexarr�У������������numlist��Ԫ�ص�����
    int numlist[20];
    fopen_s(&randlist, "C:/Users/cloud/Desktop/RandList.txt", "r");
    if (randlist == NULL)
    {
        return 0;
    }
    //����numlist����,���ں����������㷨����
    for (int k = 0; k < 20; k++)
    {
        fscanf_s(randlist, "%d;", &numlist[k]);
    }


    //step3���Զ���ѡ�����򷽷�
    int method1;
    printf("��ѡ�����򷽷����ţ�1-ð������2-ѡ�����򣩣�");
    scanf_s("%d", &method1);
    if (method1 == 1)
    {
        Bubble_Sort(numlist, indexarr, 20);
    }
    else if (method1 == 2)
    {
        Selection_Sort(numlist, indexarr, 20);
    }


    //step4���������Ľ����ӡ�����sortedlist�ļ���
    fopen_s(&sortedlist, "C:/Users/cloud/Desktop/SortedList.txt", "a");
    if (sortedlist == NULL)
    {
        return 0;
    }
    for (int i = 0; i < 20; i++)
    {
        fprintf(sortedlist, "%d\n", numlist[i]);
    }

    //step5����ѯδ���������ӦԪ�ص�����
    int method2, searchnum;
    printf("��ѡ�����򷽷����ţ�1-���Բ��ң�2-���ֲ��ң���");
    scanf_s("%d", &method2);
    printf("��������Ҫ��ѯ���������֣�");
    scanf_s("%d", &searchnum);
    if (method2 == 1)
    {
         Linear_Search(numlist, indexarr, searchnum, 20);
    }
    else if (method2 == 2)
    {
         int left = 0 ;
         int right = 0;
         int mid = Binary_Search(numlist, searchnum, 20);
         for (int i = mid - 1; i >= 0; i--)
         {
             if (numlist[i] != searchnum)
             {
                 left = i + 1;
                 break;
             }
         }
         for (int i = mid + 1; i < 20; i++)
         {
             if (numlist[i] != searchnum)
             {
                 right = i - 1;
                 break;
             }
         }
         for (int i = left; i <= right; i++)
         {
             printf("%d\t", indexarr[i]);
         }
    }
}



//ð������
void Bubble_Sort(int* arr1, int* arr2, int size)
{
    int i, j, s, z, tmp,tempindex;
    s = 0;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr1[j] > arr1[j + 1])
            {
                tmp = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = tmp;
                tempindex = arr2[j];
                arr2[j] = arr2[j + 1];
                arr2[j + 1] = tempindex;
                s = s + 1;
                printf("��%d��ð������Ľ��Ϊ:", s);
                for (z = 0; z < size; z++)
                {
                    printf("%d,", arr1[z]);
                }
                printf("\n");
            }
        }
    }
}

//ѡ������
void Selection_Sort(int* arr1, int* arr2, int size)
{
    int i, j, k, s, z, tmp,tempindex;
    s = 0;
    for (i = 0; i < size - 1; i++) 
    {
        k = i;
        for (j = i + 1; j < size; j++) 
        {
            if (arr1[j] < arr1[k])
            {
                k = j;
            }
        }
        tmp = arr1[k];
        arr1[k] = arr1[i];
        arr1[i] = tmp;
        tempindex = arr2[k];
        arr2[k] = arr2[i];
        arr2[i] = tempindex;
        s = s + 1;
        printf("��%d��ѡ������Ľ��Ϊ:", s);
        for (z = 0; z < size; z++)
        {
            printf("%d,", arr1[z]);
        }
        printf("\n");
    }
}

//���Բ�ѯ
void Linear_Search(int* arr1, int* arr2, int value, int size)
{
    printf("%d��ԭ�ļ��е������", value);
    for (int i = 0; i < size; i++)
        if (arr1[i] == value)
            printf("%d\t",arr2[i]);
}

//���ֲ�ѯ
int Binary_Search(int* arr, int value, int size)
{
    int left = 0;
    int right = size -1;
    int mid;
    printf("%d��ԭ�ļ��е������", value);
    while(left <= right)
    {
        mid = (left+right)/2;
        if(value < arr[mid])
        {
            right = mid-1;
        }
        else if(value > arr[mid])
        {
            left = mid+1;
        }
        else
            return mid;
    }
}

void findindex(char ch, char str[6][100], char position[100])
{
    int i = 0, j = 0, num = 0;
    char ch1, ch2, ch3 = '0', ch;
    if (ch = str[i][j])
    {
        num++;
        itoa(i, &ch1, 10);
        itoa(j, &ch2, 10);
        if (j < 9)
        {

        }
    }
}