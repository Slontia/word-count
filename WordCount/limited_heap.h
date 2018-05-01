#pragma once
#include "stdafx.h"

template <class T, class C>
class LimitedHeap
{
public:
  LimitedHeap(int size);
  bool                                    Push(T& ele);
  std::vector<T>                          Sort();
  void                                    Make();
  typename std::vector<T>::iterator       begin() { return heap_.begin(); }
  typename std::vector<T>::iterator       end() { return heap_.end(); }
private:
	std::vector<T>                          heap_;
	const int                               max_size_;
};


template <class T, class C>
LimitedHeap<T, C>::LimitedHeap(int size) : max_size_(size > 1 ? size : 1)
{
  heap_.reserve(max_size_ + 1);
}

template <class T, class C>
bool LimitedHeap<T, C>::Push(T& ele)
{
  // space exists
  if (heap_.size() < max_size_)
  {
    heap_.push_back(ele);
    std::push_heap(heap_.begin(), heap_.end(), C());
    return true;
  }
  // full heap
  else if (ele > heap_[0])
  {
    heap_.push_back(ele);
    std::push_heap(heap_.begin(), heap_.end(), C());
    std::pop_heap(heap_.begin(), heap_.end(), C());
    heap_.pop_back();
    return true;
  }
  return false;
}

template <class T, class C>
std::vector<T> LimitedHeap<T, C>::Sort()
{
  std::sort_heap(heap_.begin(), heap_.end(), C());
  return heap_;
}

template <class T, class C>
void LimitedHeap<T, C>::Make()
{
  std::make_heap(heap_.begin(), heap_.end(), C());
}