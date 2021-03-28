#include "KeywordsInFile.h"

KeywordsInFile::KeywordsInFile(std::string filename_with_keywords, std::string filename_with_text){
    //opening the two files
    std::ifstream keywordsFile(filename_with_keywords);
    if(keywordsFile.fail()){
        std::cout<<"FAIL TO OPEM";
        return;
    }
    std::ifstream textFile(filename_with_text);
    if(textFile.fail()){
        std::cout<<"FAIL TO OPEM";
        return;
    }

    std::string stringToAddToMap="";
    char getchar;

    //declaring iterators
    std::unordered_map<std::string,int>::const_iterator searchIt;
    std::unordered_map<std::string,int>::iterator incrementSearchIt;
    int lineCount=1;
    //parsing the keywords file and scan by char
    while(keywordsFile.good()){
        keywordsFile.get(getchar);
        if(getchar=='\n'){


        }
        //if char is alphebetical add it to temp string to be added once a non alphebtical char is reached
        //but if youre at the end of the file then add the tempstring for the last word.
        if(isalpha(getchar)){
            if(keywordsFile.eof()){
                searchIt = keywordCount.find(stringToAddToMap);
                if(searchIt == keywordCount.end()){
                    keywordCount.insert(make_pair(stringToAddToMap,0));
                    stringToAddToMap="";
                }
            }
            
            stringToAddToMap += getchar;

        }else{
            searchIt = keywordCount.find(stringToAddToMap);
            if(searchIt == keywordCount.end() && !stringToAddToMap.empty()){
                keywordCount.insert(make_pair(stringToAddToMap,0));
                stringToAddToMap="";
            }
        }        
    }




    //empty map of keywords
    std::unordered_map<std::string, int> EmptyKeywordMap(keywordCount);
    //map that will be added to keep track of words per line number
    std::unordered_map<std::string, int> mapToBeAdded(EmptyKeywordMap);

    stringToAddToMap="";


    //parsing the text file with same algorithem as the first however, just increment the maps instead of adding
    //in addition once you reach a new line (char = \n) than add the mapt to be added into the keyword line holder map
    while(textFile.good()){
        textFile.get(getchar);
        if(getchar== '\n'){
            keywordsInLineHolder.insert(make_pair(lineCount,mapToBeAdded));
            lineCount++;
            mapToBeAdded = EmptyKeywordMap;
        }

         if(isalpha(getchar)){
            if(textFile.eof()){
                if(keywordCount.count(stringToAddToMap)>0){
                    incrementSearchIt = keywordCount.find(stringToAddToMap);
                    incrementSearchIt->second++;
                    incrementSearchIt = mapToBeAdded.find(stringToAddToMap);
                    incrementSearchIt->second++;
                    stringToAddToMap="";
                }   
            }
            stringToAddToMap += getchar;
        }else{

            if(keywordCount.count(stringToAddToMap)>0){
                
                incrementSearchIt = keywordCount.find(stringToAddToMap);
                incrementSearchIt->second++;
                incrementSearchIt = mapToBeAdded.find(stringToAddToMap);
                incrementSearchIt->second++;
            }
            stringToAddToMap="";
        }        
    }
        //add the last map (last line)
            keywordsInLineHolder.insert(make_pair(lineCount,mapToBeAdded));
            lineCount++;
            mapToBeAdded = EmptyKeywordMap;   
            
    //close files         
    keywordsFile.close();
    textFile.close();
}


bool KeywordsInFile::KeywordFound(std::string keyword){
    if(keywordCount.count(keyword)>0){
        return true;
    }else{
        return false;
    }

}
int KeywordsInFile::KeywordInLine(std::string keyword, int line_number){
    if(keywordCount.count(keyword)<=0){
        return 0;
    }
    if(keywordsInLineHolder.count(line_number)<=0){
        return 0;
    }
    return(keywordsInLineHolder.at(line_number).at(keyword));
}
int KeywordsInFile::TotalOccurrences(std::string keyword){
    if(keywordCount.count(keyword)<=0){
        return 0;
    }
    return(keywordCount.at(keyword));
}
std::ostream& operator<<(std::ostream &out, const KeywordsInFile& KeywordsInFileVar){
    for(auto x:KeywordsInFileVar.keywordCount){
        out<< x.first << " : "<<x.second<<" times"<<std::endl;
    }
    return out;


}