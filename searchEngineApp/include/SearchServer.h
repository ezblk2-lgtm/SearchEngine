#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <unordered_set>
#include "InvertedIndex.h"

struct  RelativeIndex
{
    size_t docId;
    float rank;

    RelativeIndex() = default;
    RelativeIndex(size_t inDocID, float inRank) : docId(inDocID), rank(inRank) {}

    bool operator==(const RelativeIndex& other) const{
        return(docId == other.docId && rank==other.rank);
    }
};

class SearchServer
{
    InvertedIndex& _index;
public: 
    SearchServer(InvertedIndex& idx) : _index(idx) {};

    std::vector<std::vector<RelativeIndex>> search (const std::vector<std::string>& queries_input, const int& resposesLimit);
};