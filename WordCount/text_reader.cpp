#include "stdafx.h"

using std::string;
using std::list;

TextReader::TextReader(string filename)
{
	text_file_ = fopen(filename.c_str(), "r");
}

bool TextReader::ReadFile()
{
	if (!text_file_)
	{
		return false;
	}
	bool blank_line = true;
	string word = "";
	while (size_t read_size = fread(buf_, sizeof(char), kBufferSize, text_file_))
	{
		char_count_ += read_size;
		for (int i = 0; i < read_size; i++)
		{
			char c = buf_[i];
			// count line
			if (c == '\n')
			{
				if (!blank_line)
				{
					line_count_++;
				}
				blank_line = true;
			}
			if (!IsBlank(c))
			{
				blank_line = false;
			}
			// record word
			if (IsSplit(c) && IsWord(word))
			{
				HandleWord(word);
				word = "";
			}
		}
	}
	if (!blank_line)
	{
		line_count_++;
	}
}

bool TextReader::IsBlank(char c)
{
	return c == ' ' || c == '\n' || c == '\t';
}

bool TextReader::IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool TextReader::IsAlpha(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool TextReader::IsSplit(char c)
{
	return !IsAlpha(c) && !IsDigit(c);
}

bool TextReader::IsWord(string word)
{
	if (word.length < kAlphaHeadLen)
	{
		return false;
	}
	for (int i = 0; i < kAlphaHeadLen; i++)
	{
		if (!IsAlpha(word[i]))
		{
			return false;
		}
	}
	return true;
}

WordReader::WordReader(string filename) : TextReader(filename) {}

void WordReader::HandleWord(string word)
{
	std::transform(word.begin(), word.end(), word.begin(), ::tolower); // to lowercase
	count_tree_[word]++; // [warning]
}

void WordReader::HandleBreak() {}

PhraseReader::PhraseReader(string filename, int len) : TextReader(filename), phrase_len_(len) {}

void PhraseReader::HandleWord(string word)
{
	std::transform(word.begin(), word.end(), word.begin(), ::tolower); // to lowercase
	if (word_list_.size == phrase_len_)
	{
		word_list_.pop_front();
	}
	word_list_.push_back(word);
	// got phrase
	if (word_list_.size == phrase_len_)
	{
		string phrase = "";
		list<string>::iterator it = word_list_.begin();
		while (it != word_list_.end())
		{
			phrase += *it;
		}
		count_tree_[phrase]++;
	}
}

void PhraseReader::HandleBreak()
{
	word_list_.clear();
}