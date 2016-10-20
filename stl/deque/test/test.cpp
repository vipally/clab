// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <deque>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include "../deque.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	const int MAX_SIZE=100000;
	do 
	{
		clock_t s=clock();
		srand(1);
		ext::deque<int> dq;
		int i = 0;
		for (i=0;true;i++)
		{
			if (dq.size()>=MAX_SIZE)
			{
				break;
			}
			int n = rand();
			int m = n % 10000;
			if (dq.size()<10||m < 3000){
				dq.push_back(n);
			}else if (m < 6000){
				dq.push_front(n);
			}else if (m < 8000){
				dq.pop_front();
			}else if (m < 10000){
				dq.pop_back();
			} 
		}
		clock_t e=clock()-s;
		printf("mydq loop=%d, t=%d, size=%d cap=%d\n",i, e, dq.size(), dq.capacity());
		for(;dq.size()>MAX_SIZE/4;dq.pop_back());
		int ok=dq.shrink();
		printf("mydq  after shrink %d, size=%d cap=%d\n",ok, dq.size(), dq.capacity());
	} while (0);

	do 
	{
		clock_t s=clock();
		srand(1);
		std::deque<int> dq;
		int i = 0;
		for (i=0;true;i++)
		{
			if (dq.size()>=MAX_SIZE)
			{
				break;
			}
			int n = rand();
			int m = n % 10000;
			if (dq.size()<10|| m< 3000){
				dq.push_back(n);
			}else if (m < 6000){
				dq.push_front(n);
			}else if (m < 8000){
				dq.pop_front();
			}else if (m < 10000){
				dq.pop_back();
			} 
		}
		clock_t e=clock()-s;
		printf("stddq loop=%d, t=%d, size=%d cap=?\n",i, e, dq.size());
	} while (0);
	
	
	
	//std::deque<int> dq;
	//std::vector<int> vec;
	//std::queue<int> q;
	//dq.push_back(1);
	//dq.push_front(1);
	//dq.begin();
	//dq.size();
	return 0;
}

