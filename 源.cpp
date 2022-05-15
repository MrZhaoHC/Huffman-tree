#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
#define MAX 100

//typedef struct 
//{
//	int weight;
//	int lch; int rch; int parent;
//}HTree,*Tree;
//
//void selsct(Tree& T, int e, int& s1, int& s2)
//{
//	int m1 = 9999; int m2 = 9999;
//	for (int i = 1; i <= e; i++)
//	{
//		if (T[i].parent == 0 && T[i].weight < m1)
//		{
//			m1 = T[i].weight;
//			s1 = i;
//		}
//	}
//	int temp = T[s1].weight;
//	T[s1].weight = 9999;
//	for (int i = 1; i <= e; i++)
//	{
//		if (T[i].parent == 0 && T[i].weight < m2 )
//		{
//			m2 = T[i].weight;
//			s2 = i;
//		}
//	}
//	T[s1].weight = temp;
//}
//
//void CreatTree(Tree& T, int n)
//{
//	if (n <= 1)return;
//	int m = 2 * n - 1;
//	T = (HTree*)malloc((m+1) * sizeof(HTree));
//	for (int i = 1; i <= m; i++)
//	{
//		T[i].lch = 0;
//		T[i].rch = 0;
//		T[i].parent = 0;
//	}
//	for (int i = 1; i <= n; i++)
//	{
//		cin >> T[i].weight;
//	}
//	for (int i = n + 1; i <= m; i++)
//	{
//		int s1, s2;
//		selsct(T,i-1, s1, s2);
//		T[i].weight = T[s1].weight + T[s2].weight;
//		T[s1].parent = i;
//		T[s2].parent = i;
//		T[i].lch = s1;
//		T[i].rch = s2;
//	}
//
//
//
//}
//
//int main()
//{
//	int n;
//	cin >> n;
//	Tree T;
//	CreatTree(T, n);
//	for (int i = 1; i <= 2*n+1; i++)
//	{
//		cout << T[i].weight << " " << T[i].parent << " " << T[i].lch << " " << T[i].rch << endl;
//	}
//}






typedef struct
{
	int weight;
	int parent; int lch; int rch;
}BiTree,*Tree;

void selsct(Tree& t, int e, int& s1, int& s2)
{
	int m1 = 9999; int m2 = 9999;//建立两个最大值
	for (int i = 1; i <= e; i++)
	{
		if (t[i].parent == 0 && t[i].weight < m1)//双亲为0且权值最小
		{
			m1 = t[i].weight;
			s1 = i;
		}
	}
	for (int i=1;i<=e;i++)
	{
		if (t[i].parent == 0 && t[i].weight < m2 &&i!=s1)//找到第二个双亲为0且权值最小的下标，且不能重复找到第一个
		{
			m2 = t[i].weight;
			s2 = i;
		}
	}
}

//创建哈夫曼树
void creatTree(Tree& t, int n)
{
	if (n <= 1)return;//如果n<=1则直接返回
	int m = 2 * n -1;//哈夫曼树节点总数是2*n-1
	t = (BiTree*)malloc(sizeof(BiTree) * (m + 1));//给树分配m+1个空间，因为0号空间不用
	for (int i = 1; i <= m; i++)//初始化哈夫曼树，使左右孩子和双亲值为0
	{
		t[i].lch = 0; t[i].rch = 0; t[i].parent = 0;
	}
	for (int i = 1; i <= n; i++)//从键盘输入创建哈夫曼树的所有数字
	{
		cin >> t[i].weight;
	}
	for (int i = n + 1; i <= m; i++)//从n+1位置开始创建哈夫曼树
	{
		int s1, s2;
		selsct(t, i - 1, s1, s2);//返回从i-1位置找到两个双亲为0且权值最小的两个数的下标s1，s2
		t[i].weight = t[s1].weight + t[s2].weight;//第i位置的权值
		t[i].lch = s1; t[i].rch = s2;//给与i位置数字左孩子和有孩子
		t[s1].parent = i; t[s2].parent = i;//标记双亲
	}
}

void Code(Tree& t, char** hc, int n)
{
	char* cd; cd = (char*)malloc(sizeof(char)*n);
	cd[n - 1] = '\0';
	
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1;
		int c = i;
		int f = t[i].parent;
		while (f != 0)
		{
			start--;
			if (t[f].lch == c)cd[start] = '0';
			else
				cd[start] = '1';
			c = f, f = t[f].parent;
		}
		hc[i]= (char*)malloc((n - start) * sizeof(char));
		strcpy(hc[i], &cd[start]);
	}
}

int sum=0;
void quanzhi(Tree t, int n, int& sum)
{
	for (int i = 1; i <= n; i++)
	{
		int c = i; int f = t[i].parent; int count = 0;
		while (f != 0)
		{
			count++;
			c = f;
			f = t[f].parent;
		}
		sum = sum + count * t[i].weight;
	}
}


int main()
{
	int n;//建立哈夫曼树叶子节点个数
	cin >> n;
	Tree t;
	creatTree(t, n);
		for (int i = 1; i <= 2*n+1; i++)//输出哈夫曼树的权值，双亲，左孩子，右孩子
	{
		cout << t[i].weight << " " << t[i].parent << " " << t[i].lch << " " << t[i].rch << endl;
	}
		char **hc=(char**)malloc((n+1)*sizeof(char*));
		Code(t,hc, n);
		for (int i = 1; i <= n; i++)
		{
			cout << t[i].weight << " " << hc[i] << endl;
		}
 					quanzhi(t, n, sum);
cout << sum << endl;
}

