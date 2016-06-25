/*
 * binary search from programing perls
 * this binary search can solve the problem of when there are same value can not return the fisrt match number
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * binary search 
 * return -1 can not find the number    else the position of the number
 */

int binary_search(int in_arr[],int n,int value)
{
	int left,right,middle;
	
	left = -1,right = n;
	
	while(left + 1 != right)
	{
		middle = left + (right - left) / 2; //to prevent the overflow of the int if use middle = (right + left) / 2

		if(value > in_arr[middle])
		{
			left = middle;
		}
		else
		{// delete one compare(but can add compare times) 
			right = middle;
		}
	}

	if(right >= n || in_arr[right] != value)
	{
		right = -1;
	}

	return right;
}


int main()
{
	int i,value,in_arr[10];
	
	memset(in_arr,0,sizeof(in_arr));
	
	for(i = 0; i < 10; i++)
	{
		scanf("%d",&in_arr[i]);
	}
	
	while(1)
	{
		printf("input the value you want to find :\n");
		
		scanf("%d",&value);

		int index = binary_search(in_arr,10,value);

		if(index == -1)
		{
			printf("can not find the value\n");
		}
		else
		{
			printf("the %d at the position %d\n",value,index);
		}
	}
	
	return 0;	
}
