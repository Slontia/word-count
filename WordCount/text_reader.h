#pragma once

#include "stdafx.h"

class TextReader
{
public:
	static const int kBufferSize = 1024;
	static const int kAlphaHeadLen = 4;

	TextReader(std::string filename);
	bool ReadFile();	// store words into count tree while reading file

protected:
	std::unordered_map<std::string, int> count_tree_;

private:
	FILE* text_file_ = nullptr;
	char buf_[kBufferSize];
	int char_count_ = 0;
	int line_count_ = 0;
	
	inline bool IsSplit(char c);
	inline bool IsAlpha(char c);
	inline bool IsDigit(char c);
	inline bool IsBlank(char c);
	bool IsWord(std::string word);
	virtual void HandleWord(std::string word) = 0;
	virtual void HandleBreak();
};

class WordReader : TextReader
{
public:
	WordReader(std::string filename);

private:
	void HandleWord(std::string word);
	void HandleBreak();
};

class PhraseReader : TextReader
{
public:
	PhraseReader(std::string filename, int len);

private:
	int phrase_len_;
	std::list<std::string> word_list_;

	void HandleWord(std::string word);
	void HandleBreak();
};