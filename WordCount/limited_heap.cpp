#include "stdafx.h"

template <class T, class C>
LimitedHeap<T, C>::LimitedHeap(int size, C comp)
{
  if (size <= 0) { size = 1; }
	max_size_ = size;
	cur_size_ = 0;
	heap_.reserve(size + 1);
	comp_ = comp;
}

template <class T, class C>
bool LimitedHeap<T, C>::Push(T ele)
{
	// space exists
	if (cur_size_ < max_size_)
	{
		heap_[cur_size_++] = ele;
		std::push_heap(heap_.begin(), heap_.begin() + cur_size_, comp_);
		return true;
	}
	// full heap
	else if (ele < heap_[0])
	{
		heap_[max_size_] = ele;
		std::push_heap(heap_.begin(), heap_.end(), comp_);
		std::pop_heap(heap_.begin(), heap_.end(), comp_);
		return true;
	}
	return false;
}

template <class T, class C>
std::vector<T> LimitedHeap<T, C>::Sort()
{
	std::sort_heap(heap_.begin(), heap_.begin() + max_size_, comp_);
	return heap_;
}

template <class T, class C>
void LimitedHeap<T, C>::Make()
{
	std::make_heap(heap_.begin(), heap.begin() + max_size_, comp_);
}