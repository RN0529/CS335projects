#include "AudioProcessor.h"
std::vector<short> AudioProcessor::Compress(const std::vector<short> & audio, short threshold, float rate){
    //If threshold is negative or rate is less than 1.0, throw the std::invalid_argument exception
    //loop though the audio file
    //if neg num set the is neg bool and convert, if its under the threshold then great else 
    //num =((num-threshold)/rate) + treshold
    //if num is negative than make bool is neg true and then do calculation as a pos number and then turn it back
    //The compression result should be rounded to the closest short. If both upper and lower shorts are equally far, chose the one with the larger absolute value.

    if(threshold<0 || rate<1.0){
        throw std::invalid_argument("threshold < 0 or rate <1.0");
    }
    std::vector<short> returnVect;
    returnVect.reserve(audio.size());
    if(audio.size()==0){
        return returnVect;
    }

    short numToBeAdded=0;
    bool isNegative=false;
    for(int i=0;i<audio.size();i++){
        isNegative=false;
        numToBeAdded=audio[i];
        
        if(audio[i]<0){
            isNegative=true;
            numToBeAdded=-audio[i];
        }


        if(numToBeAdded<=threshold){
            if(isNegative){
                numToBeAdded=-numToBeAdded;
            }
            returnVect.push_back(numToBeAdded);
        }else{
            numToBeAdded = round(((numToBeAdded-threshold)/rate) + threshold);
            if(isNegative){
                numToBeAdded=-numToBeAdded;
            }
            returnVect.push_back(numToBeAdded);
        }

    }
    return returnVect;
}

std::vector<short> AudioProcessor::CutOutSilence(const std::vector<short> & audio, short level, int silenceLength){
    //cut out a portion of the aido where all nums are in the range -level,level
    // if level <0 or silence length is < 1 throw std::invalid exception
    std::vector<short> returnVect;
    if(level<0 || silenceLength<1){
        throw std::invalid_argument("level < 0 or silence length <1");
    }
    if(audio.size()<silenceLength){
        returnVect=audio;
        return returnVect;
    }
    
    std::vector<short> tempVect;
    bool continueToDel=false;
    for(int i=0;i<audio.size();i++){
        tempVect.push_back(audio[i]);
        if(audio[i]>level || audio[i]< -level){
            for(auto x:tempVect){
                returnVect.push_back(x);
            }
            continueToDel=false;
            tempVect.clear();
        }
        if(tempVect.size()==silenceLength||continueToDel){
            tempVect.clear();
            continueToDel=true;
            
        }
    }
    for(int x:tempVect){
       returnVect.push_back(x);
    }
    return returnVect;
}

std::vector<short> AudioProcessor::StretchTwice(const std::vector<short> & audio){
    std::vector<short> returnVect;
    if(audio.size()==0){
        return returnVect;
    }
    returnVect.push_back(audio[0]);
    if(audio.size()==1){
        return returnVect;
    }
    float avgToBeAdded;
    bool isNeg;
    for(int i =1;i<audio.size();i++){
        avgToBeAdded=audio[i]+audio[i-1];
        if(audio[i]+audio[i-1]<0){
            isNeg=true;
            avgToBeAdded=-avgToBeAdded;
        }else{
            isNeg=false;
        }
        avgToBeAdded = avgToBeAdded/2;
        if(isNeg){
            returnVect.push_back(-round(avgToBeAdded));
        }
        else{
            returnVect.push_back(round(avgToBeAdded));
        }
        returnVect.push_back(audio[i]);
    }
    return returnVect;
}

std::vector<short> AudioProcessor::Normalize(const std::vector<short> & audio, short normalizeTarget){
    //if normalizetargeto < 1 return invalid argument
    //loop through input to find the absolute value closest to normalize target
    std::vector<short> returnVect;
    if(normalizeTarget < 1){
        throw std::invalid_argument("normalizeTarget < 1");
    }
    if(audio.size()==0){
        return returnVect;
    }
    short valueOfLargest=audio[0];
    float ratio=0;
    for(int i=0; i<audio.size();i++){
        if(abs(audio[i]) > abs(valueOfLargest)){
            valueOfLargest=audio[i];
        }
    }
    if(valueOfLargest==0){
        ratio=0;
        returnVect=audio;
        return returnVect;
         
    }else{
        ratio = (normalizeTarget/valueOfLargest);
    }
    ratio = abs((float)normalizeTarget/valueOfLargest);
    for(int i=0;i<audio.size();i++){
        returnVect.push_back(round(ratio*audio[i]));
    }
    return returnVect;
}