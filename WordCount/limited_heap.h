#pragma once
#include "stdafx.h"

template <class T, class C>
class LimitedHeap
{
public:
  LimitedHeap(int size, C comp);
  bool                                    Push(T& ele);
  std::vector<T>                          Sort();
  void                                    Make();
  typename std::vector<T>::iterator       begin() { return heap_.begin(); }
  typename std::vector<T>::iterator       end() { return heap_.end(); }
private:
	std::vector<T>                          heap_;
	const int                               max_size_;
	int                                     cur_size_ = 0;
	const C                                 comp_;
};


template <class T, class C>
LimitedHeap<T, C>::LimitedHeap(int size, C comp) : 
  max_size_(size > 1 ? size : 1), comp_(comp)
{
  heap_.reserve(max_size_ + 1);
}

template <class T, class C>
bool LimitedHeap<T, C>::Push(T& ele)
{
  // space exists
  if (cur_size_ < max_size_)
  {
    heap_[cur_size_++] = std::move(ele);
    std::push_heap(heap_.begin(), heap_.begin() + cur_size_, comp_);
    return true;
  }
  // full heap
  else if (ele < heap_[0])
  {
    heap_[max_size_] = std::move(ele);
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