#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main()
{
    try
    {
        ConverterJSON converter;
        InvertedIndex inverIndex;
        
        inverIndex.UpdateDocumentBase(converter.GetTextDocuments());

        SearchServer server(inverIndex);
        
        converter.putAnswers(server.search(converter.GetRequests(), converter.GetResponsesLimit()));
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Erorr: " << e.what() << std::endl;
    }
    


    return 0;
}
