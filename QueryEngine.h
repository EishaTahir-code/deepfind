#pragma once
#include "Trie.h"
#include "set.h"
#include "Types.h"
#include "Indexer.h"

void buildTrie(CustomTrie& trie);
CustomVector<SearchResult> findCandidates(const std::string& query,
                                          const CustomSet<std::string>& stopWords,  Indexer& indexer);

                                        