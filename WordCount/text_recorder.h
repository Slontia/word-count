#pragma once
#include "stdafx.h"

class TextRecorder
{
public:
                TextRecorder(std::string text, int count);
  bool          operator <(const TextRecorder& tr);
  bool          operator >(const TextRecorder& tr);
  bool          operator =(const TextRecorder& tr);
  bool          operator <=(const TextRecorder& tr);
  bool          operator >=(const TextRecorder& tr);
  bool          operator !=(const TextRecorder& tr);
  int           Compare(std::string text, int count);
  std::string   text() { return text_; }
  int           count() { return count_; }
private:
  std::string   text_;
  int           count_ = 0;
  int           Compare(const TextRecorder& tr);
};