/*
 * PhraseImpl.cpp
 *
 *  Created on: 23 Oct 2015
 *      Author: hieu
 */
#include <vector>
#include "Phrase.h"
#include "Word.h"
#include "moses/Util.h"
#include "MemPool.h"

using namespace std;

PhraseImpl *PhraseImpl::CreateFromString(MemPool &pool, Moses::FactorCollection &vocab, const std::string &str)
{
	vector<string> toks = Moses::Tokenize(str);
	size_t size = toks.size();
	PhraseImpl *ret;

	ret = new (pool.Allocate<PhraseImpl>()) PhraseImpl(pool, size);

	ret->CreateFromString(vocab, toks);
	return ret;
}

void PhraseImpl::CreateFromString(Moses::FactorCollection &vocab, const std::vector<std::string> &toks)
{
	for (size_t i = 0; i < m_size; ++i) {
		Word &word = (*this)[i];
		word.CreateFromString(vocab, toks[i]);
	}
}

PhraseImpl::PhraseImpl(MemPool &pool, size_t size)
:m_size(size)
{
  m_words = new (pool.Allocate<Word>(size)) Word[size];

}

PhraseImpl::~PhraseImpl() {

}

SubPhrase PhraseImpl::GetSubPhrase(size_t start, size_t end) const
{
	SubPhrase ret(*this, start, end);
	return ret;
}

std::ostream& operator<<(std::ostream &out, const Phrase &obj)
{
	if (obj.GetSize()) {
		out << obj[0];
		for (size_t i = 1; i < obj.GetSize(); ++i) {
			const Word &word = obj[i];
			out << " " << word;
		}
	}
	return out;
}


////////////////////////////////////////////////////////////
SubPhrase::SubPhrase(const PhraseImpl &origPhrase, size_t start, size_t end)
:m_origPhrase(&origPhrase)
,m_start(start)
,m_end(end)
{

}


std::ostream& operator<<(std::ostream &out, const SubPhrase &obj)
{
	if (obj.GetSize()) {
		out << obj[0];
		for (size_t i = 1; i < obj.GetSize(); ++i) {
			const Word &word = obj[i];
			out << " " << word;
		}
	}
	return out;
}
