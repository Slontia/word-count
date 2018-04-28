#pragma once

#include "stdafx.h"

template <class T, class C>
class LimitedHeap
{
private:
	vector<T> heap_;
	int max_size_;
	int cur_size_;
	C comp_;
	
public:
	LimitedHeap(int size, C comp);
	int push(T ele);
	vector<T> sort();
	void make();
};