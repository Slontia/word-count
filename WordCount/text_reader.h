#pragma once

#include "stdafx.h"

class TextReader
{
public:
  typedef std::unordered_map<std::string, int> CountTree;
	static const int        kBufferSize = 1024 * 1024;
	static const int        kAlphaHeadLen = 4;
                          TextReader();
	bool                    ReadFile(std::string filename);
	bool                    ReadFolder(std::string foldname);
  int                     char_count() const { return char_count_; }
  int                     word_count() const { return word_count_; }
  int                     line_count() const { return line_count_; }
  CountTree::iterator     begin() { return count_tree_.begin(); }
  CountTree::iterator     end() { return count_tree_.end(); }
protected:
  CountTree               count_tree_;
private:
	char                    buf_[kBufferSize];
	int                     char_count_ = 0;
  int                     word_count_ = 0;
	int                     line_count_ = 0;
	inline bool             IsSplit(char c) const;
	inline bool             IsAlpha(char c) const;
	inline bool             IsDigit(char c) const;
	inline bool             IsBlank(char c) const;
	bool                    IsWord(std::string word) const;
	virtual void            HandleWord(std::string word) = 0;
	virtual void            HandleBreak() = 0;
};

class WordReader : public TextReader
{
public:
	          WordReader();
private:
	void      HandleWord(std::string word);
	void      HandleBreak();
};

class PhraseReader : public TextReader
{
public:
                              PhraseReader(int len);
private:
	int                         phrase_len_;
	std::list<std::string>      word_list_;
	void                        HandleWord(std::string word);
	void                        HandleBreak();
};