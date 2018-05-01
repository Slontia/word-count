#include "stdafx.h"

using std::string;
using std::list;

TextReader::TextReader() {}

/* store words into count tree while reading file */
bool TextReader::ReadFile(string filename)
{
  std::ifstream       ifs(filename, std::ifstream::ios_base::in);
  string              word = "";
  bool                blank_line = true;
  if (!ifs) { return false; }
  while (!ifs.eof())
  {
    ifs.read(buf_, kBufferSize);
    std::streamsize read_size = ifs.gcount();
    char_count_ += read_size;
    for (std::streamsize i = 0; i < read_size; i++)
    {
      char c = buf_[i];
      /* count line */
      if (c == '\n')
      {
        if (!blank_line) { line_count_++; }
        blank_line = true;
      }
      if (!IsBlank(c)) { blank_line = false; }
      /* record word */
      if (IsSplit(c))
      {
        if (IsWord(word))
        {
          word_count_++;
          HandleWord(word);
        }
        word = "";
      }
      else
      {
        word = word + c;
      }
    }
  }
  if (IsWord(word))
  {
    word_count_++;
    HandleWord(word);
  }
  if (!blank_line) { line_count_++; }
  ifs.close();
  return true;
}

bool TextReader::ReadFolder(string foldername)
{
  _finddata_t     fdata; // <io.h>
  intptr_t        fhandle = 0;
  if ((fhandle = _findfirst((foldername + "\\*").c_str(), &fdata)) != -1)
  {
    do
    {
      if (fdata.attrib & _A_SUBDIR)	// is folder
      {
        if (strcmp(fdata.name, ".") != 0 && strcmp(fdata.name, "..") != 0) // not parent or self
        { 
          ReadFolder(foldername + '\\' + fdata.name);
        }
      }
      else
      { 
        ReadFile(foldername + '\\' + fdata.name);
      }
    } while (_findnext(fhandle, &fdata) == 0);
    _findclose(fhandle);
    return true;
  }
  else
  {
    return false;
  }
}

bool TextReader::IsBlank(char c) const
{
  return c == ' ' || c == '\n' || c == '\t';
}

bool TextReader::IsDigit(char c) const
{
  return c >= '0' && c <= '9';
}

bool TextReader::IsAlpha(char c) const
{
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool TextReader::IsSplit(char c) const
{
  return !IsAlpha(c) && !IsDigit(c);
}

bool TextReader::IsWord(string word) const
{
  if (word.length() < kAlphaHeadLen) { return false; }
  for (int i = 0; i < kAlphaHeadLen; i++)
  {
    if (!IsAlpha(word[i])) { return false; }
  }
  return true;
}

WordReader::WordReader() {}

void WordReader::HandleWord(string word)
{
  std::transform(word.begin(), word.end(), word.begin(), ::tolower); // to lowercase
  count_tree_[word]++;
}

void WordReader::HandleBreak() {}

PhraseReader::PhraseReader(int len) : phrase_len_(len) {}

void PhraseReader::HandleWord(string word)
{
  std::transform(word.begin(), word.end(), word.begin(), ::tolower); // to lowercase
  if (word_list_.size() == phrase_len_) { word_list_.pop_front(); }
  word_list_.push_back(word);
  /* got phrase */
  if (word_list_.size() == phrase_len_)
  {
    string phrase = "";
    for (list<string>::iterator it = word_list_.begin(); it != word_list_.end(); it++) 
    { 
      phrase += *it + ' ';
    }
    count_tree_[phrase.substr(0, phrase.length() - 1)]++; // remove the last space
  }
}

void PhraseReader::HandleBreak()
{
  word_list_.clear();
}