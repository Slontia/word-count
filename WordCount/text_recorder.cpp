#include "stdafx.h"

using std::string;

TextRecorder::TextRecorder(string text, int count) : text_(text), count_(count) {}

TextRecorder::TextRecorder(const TextRecorder& cpy) : text_(cpy.text_), count_(cpy.count_) {}

int TextRecorder::Compare(string text, int count) const
{
  if (this->count_ > count ||
    (this->count_ == count && strcmp(this->text_.c_str(), text.c_str()) < 0))
  { 
    return 1; 
  }
  else if (this->count_ == count && strcmp(this->text_.c_str(), text.c_str()) == 0)
  { 
    return 0; 
  }
  else
  { 
    return -1; 
  }
}

int TextRecorder::Compare(const TextRecorder& tr) const
{
  return Compare(tr.text_, tr.count_);
}

bool operator <(const TextRecorder& left, const TextRecorder& right)
{
  return left.Compare(right) == -1;
}

bool operator ==(const TextRecorder& left, const TextRecorder& right)
{
  return left.Compare(right) == 0;
}

bool operator >(const TextRecorder& left, const TextRecorder& right)
{
  return left.Compare(right) == 1;
}

bool operator >=(const TextRecorder& left, const TextRecorder& right)
{
  return left.Compare(right) != -1;
}

bool operator !=(const TextRecorder& left, const TextRecorder& right)
{
  return left.Compare(right) != 0;
}

bool operator <=(const TextRecorder& left, const TextRecorder& right)
{
  return left.Compare(right) != 1;
}