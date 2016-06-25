/*
 *binary search 
 *just return a value position equals the find but may not the first one
 *we should caution the left open right close or left close and right close rules to not happen the boundary error
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *binary search
 *return -1 can not find the number else the position of the number
 */

int binary_search(int in_arr[],int n,int value)
{
	int left,right,middle;
	left = 0,right = n - 1;

	while(left <= right)
	{
		middle = left + (right - left) / 2; //can solve the number overflow error
		
		if(value > in_arr[middle])
		{
			left = middle + 1;
		}
		else if(value < in_arr[middle])
		{
			right = middle - 1;
		}
		else
		{
			return middle;
		}
	}

	return -1;
}

int main()
{
	int i,value,in_arr[10];

	for(i = 0; i < 10; i++)
	{
		scanf("%d",&in_arr[i]);
	}
	
	while(1)
	{
		printf("input the value to find\n");

		scanf("%d",&value);

		int index = binary_search(in_arr,10,value);

		if(index == -1)
		{
			printf("can not find the number %d \n",value);
		}
		else
		{
			printf("the value %d is at the position %d\n",value,index);
		}
	}
}
