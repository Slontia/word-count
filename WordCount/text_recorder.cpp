#include "stdafx.h"

using std::string;

TextRecorder::TextRecorder(string text, int count) : text_(text), count_(count) {}

int TextRecorder::Compare(string text, int count)
{
  if (this->count_ > count ||
    (this->count_ == count && strcmp(this->text_.c_str, text.c_str) < 0))
  { 
    return 1; 
  }
  else if (this->count_ == count && strcmp(this->text_.c_str, text.c_str) == 0)
  { 
    return 0; 
  }
  else
  { 
    return -1; 
  }
}

int TextRecorder::Compare(const TextRecorder& tr)
{
  return Compare(tr.text_, tr.count_);
}

bool TextRecorder::operator <(const TextRecorder& tr)
{
  return Compare(tr) == -1;
}

bool TextRecorder::operator =(const TextRecorder& tr)
{
  return Compare(tr) == 0;
}

bool TextRecorder::operator >(const TextRecorder& tr)
{
  return Compare(tr) == 1;
}

bool TextRecorder::operator >=(const TextRecorder& tr)
{
  return Compare(tr) != -1;
}

bool TextRecorder::operator !=(const TextRecorder& tr)
{
  return Compare(tr) != 0;
}

bool TextRecorder::operator <=(const TextRecorder& tr)
{
  return Compare(tr) != 1;
}