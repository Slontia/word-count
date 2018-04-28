#include "stdafx.h"

template <class T, class C>
LimitedHeap<T, C>::LimitedHeap(int size, C comp)
{
	if (size <= 0) size = 1;
	this->max_size_ = size;
	this->cur_size_ = 0;
	this->heap_.reserve(size + 1);
	this->comp_ = comp;
}

template <class T, class C>
bool LimitedHeap<T, C>::push(T ele)
{
	// space exists
	if (this->cur_size_ < this->max_size_)
	{
		this->heap_[cur_size_++] = ele;
		std::push_heap(this->heap_.begin(), this->heap_.begin() + this->cur_size_, 
			this->comp_);
		return true;
	}
	// full heap
	else if (ele < this->heap_[0])
	{
		this->heap_[max_size_] = ele;
		std::push_heap(this->heap_.begin(), this->heap_.end(), this->comp_);
		std::pop_heap(this->heap_.begin(), this->heap_.end(), this->comp_);
		return true;
	}
	return false;
}

template <class T, class C>
vector<T> LimitedHeap<T, C>::sort()
{
	std::sort_heap(this->heap_.begin(), this->heap_.begin() + this->max_size_, 
		this->comp_);
	return this->heap_;
}

template <class T, class C>
void LimitedHeap<T, C>::make()
{
	std::make_heap(this->heap_.begin(), this->heap.begin() + this->max_size_, 
		this->comp_);
}