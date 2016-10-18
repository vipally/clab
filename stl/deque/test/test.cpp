// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <deque>
#include "../deque.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	std::deque<int> dq;
	dq.push_back(1);
	dq.push_front(1);
	dq.size();
	return 0;
}

