#pragma once
#include "stdafx.h"

class TextRecorder
{
public:
                        TextRecorder(std::string text, int count);
                        TextRecorder(const TextRecorder& tr);
  friend bool           operator <(const TextRecorder& left, const TextRecorder& right);
  friend bool           operator >(const TextRecorder& left, const TextRecorder& right);
  friend bool           operator ==(const TextRecorder& left, const TextRecorder& right);
  friend bool           operator <=(const TextRecorder& left, const TextRecorder& right);
  friend bool           operator >=(const TextRecorder& left, const TextRecorder& right);
  friend bool           operator !=(const TextRecorder& left, const TextRecorder& right);
  int                   Compare(std::string text, int count) const;
  std::string           text() const { return text_; }
  int                   count() const { return count_; }
private:
  std::string           text_;
  int                   count_;
  int                   Compare(const TextRecorder& tr) const;
};