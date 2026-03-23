#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs)
    {
        freqDictionary.clear();
        
        docs = std::move(inputDocs);
        std::vector<std::thread> threads;
        std::mutex freqDictionaryMutex;
        std::mutex cerrMutex;

        for (int i = 0; i < docs.size(); i++)
        {
            threads.emplace_back([this, i, &freqDictionaryMutex, &cerrMutex] ()
        {
            std::map<std::string, int> freqDictionaryBuffer;
            int countWord = 0;
            std::istringstream lineWords(docs[i]);
            std::string wordBuffer;

            while (lineWords >> wordBuffer)
            {
                if (countWord++ > 1000)
                {
                    std::lock_guard<std::mutex> lock(cerrMutex);
                    std::cerr << "The document contains more than 1000 words. The search is based on 1000 words" << std::endl;
                    break;
                }
                
                if (wordBuffer.size() > 100)
                {
                    std::lock_guard<std::mutex> lock(cerrMutex);
                    std::cerr << "A word is more than 100 characters long. word: " << wordBuffer << std::endl;
                    continue;
                }
                
                freqDictionaryBuffer[wordBuffer]++;
            }

            std::lock_guard<std::mutex> lock(freqDictionaryMutex);
            for (const auto& [word, countBuffer] : freqDictionaryBuffer)
            {
                auto& keyWord = freqDictionary[word];
                bool found = false;

                for (auto& value : keyWord)
                {
                    if (value.docId == i)
                    {
                        value.count += countBuffer;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    keyWord.emplace_back(static_cast<size_t>(i), static_cast<size_t> (countBuffer));
                }
            }
        });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }
    }

    std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
    {
        auto it = freqDictionary.find(word);

        if (it != freqDictionary.end())
        {
            return it->second;
        }
        
        return {};
    }

    