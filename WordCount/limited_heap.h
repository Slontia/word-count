#pragma once
#include "stdafx.h"

template <class T, class C>
class LimitedHeap
{
public:
  LimitedHeap(int size, C comp);
  bool                          Push(T ele);
  std::vector<T>                Sort();
  void                          Make();
  std::vector<T>::iterator      begin() { return heap_.begin(); }
  std::vector<T>::iterator      end() { return heap_.end(); }
private:
	std::vector<T>                heap_;
	int                           max_size_;
	int                           cur_size_;
	C                             comp_;
};