// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <deque>
#include <vector>
#include <queue>
#include "../deque.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	std::deque<int> dq;
	std::vector<int> vec;
	std::queue<int> q;
	dq.push_back(1);
	dq.push_front(1);
	dq.begin();
	dq.size();
	return 0;
}

