#pragma once

#include "stdafx.h"

template <class T, class C>
class LimitedHeap
{
private:
	std::vector<T> heap_;
	int max_size_;
	int cur_size_;
	C comp_;
	
public:
	LimitedHeap(int size, C comp);
	bool Push(T ele);
	std::vector<T> Sort();
	void Make();
};