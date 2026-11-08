#pragma once
#include <string>
#include "Vector.h"

using namespace std;

const int TOP_K = 10;

struct Occurrence {
    int lineNumber = 0;
    int timesOnLine = 0;
};

struct FileInfo {
    string path;
    int totalWords = 0;
    CustomVector<string> lines;
};

struct FilePosting {
    int fileId = 0;
    int wordCount = 0;
    CustomVector<Occurrence> occurrences;
};

struct SearchResult {
    int fileId = 0;
    int wordCount = 0;
    int termsMatched = 0;
    double score = 0.0;
    CustomVector<Occurrence> occurrences;
};

inline bool ranksHigher(const SearchResult& a, const SearchResult& b) {
    if (a.score != b.score) return a.score > b.score;
    if (a.termsMatched != b.termsMatched) return a.termsMatched > b.termsMatched;
    return a.fileId < b.fileId;
}