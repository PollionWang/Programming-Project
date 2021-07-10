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
    //step1：生成20个1-15的随机数的txt文件
    srand((unsigned)time(NULL));    //播种
    //将生成的随机数写入txt文件
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


    //step2：将生成好的txt文件中的数据存到数组numlist中方便后续排序,并且将numlist的对应元素索引存放到indexarr中，方便后续查找numlist的元素的索引
    int numlist[20];
    fopen_s(&randlist, "C:/Users/cloud/Desktop/RandList.txt", "r");
    if (randlist == NULL)
    {
        return 0;
    }
    //存入numlist数组,便于后续的排序算法操作
    for (int k = 0; k < 20; k++)
    {
        fscanf_s(randlist, "%d;", &numlist[k]);
    }


    //step3：自定义选择排序方法
    int method1;
    printf("请选择排序方法代号（1-冒泡排序，2-选择排序）：");
    scanf_s("%d", &method1);
    if (method1 == 1)
    {
        Bubble_Sort(numlist, indexarr, 20);
    }
    else if (method1 == 2)
    {
        Selection_Sort(numlist, indexarr, 20);
    }


    //step4：将排序后的结果打印输出到sortedlist文件中
    fopen_s(&sortedlist, "C:/Users/cloud/Desktop/SortedList.txt", "a");
    if (sortedlist == NULL)
    {
        return 0;
    }
    for (int i = 0; i < 20; i++)
    {
        fprintf(sortedlist, "%d\n", numlist[i]);
    }

    //step5：查询未排序数组对应元素的索引
    int method2, searchnum;
    printf("请选择排序方法代号（1-线性查找，2-二分查找）：");
    scanf_s("%d", &method2);
    printf("请输入需要查询索引的数字：");
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



//冒泡排序
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
                printf("第%d次冒泡排序的结果为:", s);
                for (z = 0; z < size; z++)
                {
                    printf("%d,", arr1[z]);
                }
                printf("\n");
            }
        }
    }
}

//选择排序
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
        printf("第%d次选择排序的结果为:", s);
        for (z = 0; z < size; z++)
        {
            printf("%d,", arr1[z]);
        }
        printf("\n");
    }
}

//线性查询
void Linear_Search(int* arr1, int* arr2, int value, int size)
{
    printf("%d在原文件中的序号是", value);
    for (int i = 0; i < size; i++)
        if (arr1[i] == value)
            printf("%d\t",arr2[i]);
}

//二分查询
int Binary_Search(int* arr, int value, int size)
{
    int left = 0;
    int right = size -1;
    int mid;
    printf("%d在原文件中的序号是", value);
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