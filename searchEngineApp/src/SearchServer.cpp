#include "SearchServer.h"


std::vector<std::vector<RelativeIndex>> SearchServer::search (const std::vector<std::string>& queries_input, const int& responsesLimit)
{
    std::vector<std::vector<RelativeIndex>> result;
    result.reserve(queries_input.size());

    for (const auto& request : queries_input)
    {
        std::istringstream wordsLine(request);
        std::string word;
        std::map<std::string, size_t> uniqWords;
        bool foundWord = false;
        int countWord = 0;


        while (wordsLine >> word)
        {
            if (countWord++ >= 10)
            {
                std::cerr << "More than 10 words in the query. Search for the first 10 " << std::endl;
                break;
            }

            if (uniqWords.find(word) == uniqWords.end())
            {
                const auto& dataWord = _index.GetWordCount(word);
                if (dataWord.empty()) continue;
                size_t totalCount = 0;

                for (const auto& value : dataWord)
                {
                    totalCount += value.count;
                    foundWord = true;
                }

                uniqWords[word] = totalCount;
            }
        }

        if (!foundWord)
        {
            result.emplace_back();
            continue;
        }

        std::vector<std::pair<std::string, size_t>> sortedWords (begin(uniqWords), end(uniqWords));
        std::sort(begin(sortedWords), end(sortedWords), 
        [] (const auto& firstWord, const auto& secondWord) 
        {
            return firstWord.second < secondWord.second;
        });

        std::unordered_set<size_t> docs;

        const auto& rarestWordEntries = _index.GetWordCount(sortedWords[0].first);
        for (const auto& object : rarestWordEntries)
        {
            docs.insert(object.docId);
        }

        for (int i = 1; i < sortedWords.size(); i++)
        {
            const auto& entries = _index.GetWordCount(sortedWords[i].first);
            std::unordered_set<size_t> docsWithWords;

            for (const auto& object : entries)
            {
                docsWithWords.insert(object.docId);
            }

            std::unordered_set<size_t> intersection;

            for (size_t docId : docs)
            {
                if (docsWithWords.find(docId) != docsWithWords.end())
                {
                    intersection.insert(docId);
                }
            }

            docs.swap(intersection);

            if (docs.empty()) break;
        }

        if (docs.empty())
        {
            result.emplace_back();
            continue;
        }

        std::map<size_t, size_t> absoluteRelevance;

        for (const auto& [word, count] : sortedWords)
        {
            const auto& entries = _index.GetWordCount(word);
            for (const auto& object : entries)
            {
                if (docs.find(object.docId) != docs.end())
                {
                    absoluteRelevance[object.docId] += object.count;
                }
            }
        }

        size_t maxAbsRelevanse = 0;
       
        for (const auto& [word, absRelevance] : absoluteRelevance)
        {
            if (maxAbsRelevanse < absRelevance) maxAbsRelevanse = absRelevance;
        }

        std::vector<RelativeIndex> buffer;

        for (const auto& [docId, absRelevance] : absoluteRelevance)
        {
            float rank = static_cast<float>(absRelevance) / maxAbsRelevanse;
            buffer.push_back({docId, rank});
        }

        std::sort(begin(buffer), end(buffer), [](const RelativeIndex& firstObject, const RelativeIndex& secondObject)
        {
            if (firstObject.rank != secondObject.rank) 
            {
                return firstObject.rank > secondObject.rank;
            }
                return firstObject.docId < secondObject.docId;
        });

        if (buffer.size() > responsesLimit) 
        {
            buffer.resize(responsesLimit);
        }

        result.emplace_back(std::move(buffer));
    }
    
    return result;
}
