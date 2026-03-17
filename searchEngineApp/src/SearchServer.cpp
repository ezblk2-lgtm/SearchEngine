#include "SearchServer.h"


std::vector<std::vector<RelativeIndex>> SearchServer::search (const std::vector<std::string>& queries_input, const int& responsesLimit)
{
    std::vector<std::vector<RelativeIndex>> result;

    for (int i = 0; i < queries_input.size(); i++)
    {
        std::istringstream wordLine(queries_input[i]);
        std::string word;
        std::set<std::string> uniqWord;
        std::map<size_t, float> absoluteRelevance;
        int countWord = 0;
        int totalCount = 0;

        while (wordLine >> word)
        {
            if (countWord++ > 10)
            {
                std::cerr << "More than 10 words in the query. Search for the first 10 " << std::endl;
                break;
            }

            if (uniqWord.find(word) == uniqWord.end())
            {
                const auto& dataWord = _index.GetWordCount(word);

                if (dataWord.empty()) continue;

                for (auto& value : dataWord)
                {
                    totalCount += value.count;
                    absoluteRelevance[value.docId] += value.count;
                }
            }
        }

        if (totalCount == 0)
        {
            result.emplace_back();
            continue;
        }

        float maxAbsoluteRelevance = 0;

        for (auto& relevance : absoluteRelevance)
        {
            if (relevance.second > maxAbsoluteRelevance )
            {
                maxAbsoluteRelevance = relevance.second;
            }
        }

        std::vector<RelativeIndex> buffer;

        for (const auto& [docId, relevance] : absoluteRelevance)
        {
            float currentRank = (relevance / maxAbsoluteRelevance);
            buffer.push_back({docId, currentRank});
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

        result.emplace_back(buffer);
    }
    
    return result;
}