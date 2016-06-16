#include "stdlib.h"
#include "iostream"
#include <string.h>
using namespace std;

//边界判断
bool isout(int i,int j,int n,int m)
{
	if(i<0||i>=n||j<0||j>=m)
	{
		return true;
	}
	return false;
}


void visit(int i,int j,int n,int m,int** isvisit,int** grid){
	isvisit[i][j]=1;//当前visit
	if(!isout(i+1,j,n,m)&&!isvisit[i+1][j]&&grid[i+1][j]==1){
		visit(i+1,j,n,m,isvisit,grid);
	}
	if(!isout(i-1,j,n,m)&&!isvisit[i-1][j]&&grid[i-1][j]==1){
		visit(i-1,j,n,m,isvisit,grid);
	}
	if(!isout(i,j+1,n,m)&&!isvisit[i][j+1]&&grid[i][j+1]==1){
		visit(i,j+1,n,m,isvisit,grid);
	}
	if(!isout(i,j-1,n,m)&&!isvisit[i][j-1]&&grid[i][j-1]==1){
		visit(i,j-1,n,m,isvisit,grid);
	}
}


int countHomes(int **grid,int n ,int m)
{
	int **isvisit=(int **)malloc(n*sizeof(int *));
	for(int i=0;i<n;i++)
	{
		isvisit[i]=(int*)malloc(m*sizeof(int));
		memset(isvisit[i],0,sizeof(int)*m);
	}
	int count=0;
	for (int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(!isvisit[i][j]&&grid[i][j]==1)
			{
				count++;
				visit(i,j,n,m,isvisit,grid);
			}
		}
	}
	//销毁
	for(int i=0;i<n;i++)
	{
		free(isvisit[i]);
	}
	free(isvisit);
	return count;
}

int main()
{
	int **grid=new int *[10];

	for(int i=0;i<10;i++)
	{
		grid[i]=new int[5];
		memset(grid[i],0,sizeof(int)*5);
	}
	/*int grad[10][5]={0};*/
	grid[1][3]=1;
	grid[2][3]=1;
	grid[2][4]=1;
	grid[3][4]=1;

	grid[8][2]=1;

	// grid[6][4]=1;
	// grid[6][5]=1;
	cout<<countHomes(grid,10,5)<<endl;

	// system("pause");
	return 0;
}
