#pragma once
#include<iostream>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include <sstream>

struct Entry
{
    size_t docId = 0, count = 0;

    Entry(size_t inDoc, size_t inCount) : docId(inDoc), count(inCount) {}

    bool operator==(const Entry& other) const {
        return(docId == other.docId && count == other.count);
    }
};

class InvertedIndex {
public:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freqDictionary;

public:
    InvertedIndex() = default;
    
    void UpdateDocumentBase(std::vector<std::string> inputDocs);
    std::vector<Entry> GetWordCount(const std::string& word);
};