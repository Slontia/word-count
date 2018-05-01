#pragma once

#include "stdafx.h"

class TextReader
{
 public:
  typedef std::unordered_map<std::string, int> CountTree;
	static const int      kBufferSize = 1024;
	static const int      kAlphaHeadLen = 4;
                        TextReader();
	bool                  ReadFile(std::string filename);
	bool                  ReadFolder(std::string foldname);

 protected:
   CountTree            count_tree_;

 private:
	char                  buf_[kBufferSize];
	int                   char_count_ = 0;
	int                   line_count_ = 0;
	inline bool           IsSplit(char c);
	inline bool           IsAlpha(char c);
	inline bool           IsDigit(char c);
	inline bool           IsBlank(char c);
	bool                  IsWord(std::string word);
	virtual void          HandleWord(std::string word) = 0;
	virtual void          HandleBreak() = 0;
};


class WordReader : TextReader
{
 public:
	          WordReader();

 private:
	void      HandleWord(std::string word);
	void      HandleBreak();
};


class PhraseReader : TextReader
{
public:
                              PhraseReader(int len);

private:
	int                         phrase_len_;
	std::list<std::string>      word_list_;
	void                        HandleWord(std::string word);
	void                        HandleBreak();
};