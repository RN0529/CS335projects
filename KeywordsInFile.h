#ifndef KEYWORDS_IN_FILE_
#define KEYWORDS_IN_FILE_
#include <string>
#include <unordered_map> 
#include <fstream> 
#include <iostream>
#include <iterator>

class KeywordsInFile
{
    public:
        //constructor
        KeywordsInFile() = delete;
        KeywordsInFile( std::string filename_with_keywords, std::string filename_with_text);
        //big 5
        ~KeywordsInFile()=default;
        KeywordsInFile(const KeywordsInFile &trg)=default;
        KeywordsInFile(KeywordsInFile &&trg)=default;
        KeywordsInFile & operator=(const KeywordsInFile &trg)=default;
        KeywordsInFile & operator=( KeywordsInFile &&trg)=default;

        bool KeywordFound(std::string keyword);
        int KeywordInLine(std::string keyword, int line_number);
        int TotalOccurrences(std::string keyword);

        friend std::ostream& operator<<(std::ostream &out, const KeywordsInFile& KeywordsInFileVar);

    private:
        std::unordered_map<std::string, int> keywordCount; 
        std::unordered_map<int, std::unordered_map<std::string, int>> keywordsInLineHolder;
};
// end KeywordsInFile
#endif