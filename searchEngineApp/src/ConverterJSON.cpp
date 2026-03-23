#include "ConverterJSON.h"
#include "appVersion.h"


std::vector<std::string> ConverterJSON::GetTextDocuments()
    {
        std::ifstream fileConfig("config.json");
        std::vector<std::string> result;

        if (!fileConfig.is_open())
        {
            throw std::runtime_error("config file is missing");
        }

        nlohmann::json configInfo;
        fileConfig >> configInfo;

        if (!configInfo.contains("config"))
        {
            throw std::runtime_error("config file is empty");
        }

        auto config = configInfo["config"];

        if (config["version"] != appVersion)
        {
            throw std::runtime_error("config.json has incorrect file version");
        }

        std::cout << "Starting: " << config["name"] << std::endl;

        auto filePathArray = configInfo["files"];

        for(std::string filePath : filePathArray)
        {
            std::ifstream file(filePath);

            if (!file.is_open())
            {
                std::cerr << "Cannot open file " << filePath << std::endl;
                continue;
            }

            std::string strTemp;
            std::string fileContent;

            while (std::getline(file, strTemp))
            {
                fileContent += strTemp + "\n";
            }
            
            file.close();

            result.emplace_back(fileContent);
        }

        fileConfig.close();

        return result;
    }

int ConverterJSON::GetResponsesLimit()
    {
        std::ifstream fileConfig("config.json");

        if (!fileConfig.is_open())
        {
            throw std::runtime_error("config file is missing");
        }

        nlohmann::json configInfo;
        fileConfig >> configInfo;

        if (!configInfo.contains("config"))
        {
            throw std::runtime_error("config file is empty");
        }

        auto config = configInfo["config"];

        if (!config.contains("max_responses"))
        {
            return 5;
        }

        if (!config["max_responses"].is_number())
        {
            return 5;
        }

        int result = config["max_responses"];
        fileConfig.close();

        if (result <= 0)
        {
            return 5;
        }

        return result;
    }

std::vector<std::string> ConverterJSON::GetRequests()
    {
        std::ifstream fileRequests("requests.json");

        if (!fileRequests.is_open())
        {
            throw std::runtime_error("requests file is missing");
        }

        nlohmann::json requestsJson;
        fileRequests >> requestsJson;

        if(!requestsJson.contains("requests"))
        {
            throw std::runtime_error("requests file is empty");
        }

        std::vector<std::string> result;

        for (std::string requestsContent : requestsJson["requests"])
        {
            result.emplace_back(requestsContent);
        }

        fileRequests.close();

        return result;
    }

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers)
    {
        nlohmann::ordered_json jsonAnswer;
        jsonAnswer["answers"] = nlohmann::ordered_json::object();
        for (int i = 0; i < answers.size(); i++)
        {
            std::string number = std::to_string(i + 1);
            if (i < 9)  
            {
                number = "00" + number;
            }
            else if (i < 99)  
            {
                number = "0" + number;
            }
            
            std::string request = "request" + number;

            if (answers[i].empty())
            {
                jsonAnswer["answers"][request]["result"] = false;
            }
            else 
            {
                jsonAnswer["answers"][request]["result"] = true;
                jsonAnswer["answers"][request]["relevance"] = nlohmann::ordered_json::array();
               

                for (auto& docRank : answers[i])
                {
                    nlohmann::ordered_json doc;
                    doc["docid"] = docRank.docId;
                    doc["rank"] = docRank.rank;
                    jsonAnswer["answers"][request]["relevance"].push_back(doc);
                }
            }
        }
        
        std::ofstream fileAnswer ("answer.json", std::ios::trunc);
        
        fileAnswer << std::setw(4) << jsonAnswer;
    }