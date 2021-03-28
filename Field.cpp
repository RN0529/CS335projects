#include "Field.h"
#include <vector>
#include <iostream>
Field::Field(const std::vector<std::vector<int>>  & trg ){
    // if array is empty do nothing
    if (trg.empty()|| trg[0].empty()){
        return;
    }
    //loop though input vector and push back each vector row
    for(int i=0;i<trg.size();i++){
        values.push_back(trg[i]);
    }

    //resizing cost array to be same dimensions as first array
    costsArray.resize(values.size());
    for(int i=0;i<values.size();i++){
        costsArray[i].resize(values[i].size());
    }


    //setting the values of cost array, doing the first row and col seprately and then filling the rest of the array using a simple formula
    //the current value of array+the top and botttom costs subtracting the previous diangonal to negate any duplicates in the calulation
    costsArray[0][0]=values[0][0];

    for(int i =1; i<values.size();i++){
        costsArray[i][0] =  values[i][0]+costsArray[i-1][0];
    }
    for(int j =1; j<values[0].size();j++){
        costsArray[0][j] =  values[0][j]+costsArray[0][j-1];
    }

    for(int i=1;i<costsArray.size();i++){
        for(int j=1;j<costsArray[i].size();j++){
          costsArray[i][j] = costsArray[i-1][j] + costsArray[i][j-1] - costsArray[i-1][j-1] + values[i][j];
        }
    }
}
Field::Field(std::vector<std::vector<int>>  && trg ){
    if (trg.empty()|| trg[0].empty()){
        return;
    }
    //same process as above but only calculate costs array because the values will take the trg array
    values = std::move(trg);

    //resizing cost array to be same dimensions as first array
    costsArray.resize(values.size());
    for(int i=0;i<values.size();i++){
        costsArray[i].resize(values[i].size());
    }

    //setting the values of cost array, doing the first row and col seprately and then filling the rest of the array using a simple formula
    //the current value of array+the top and botttom costs subtracting the previous diangonal to negate any duplicates in the calulation
    costsArray[0][0]=values[0][0];

    for(int i =1; i<values.size();i++){
        costsArray[i][0] =  values[i][0]+costsArray[i-1][0];
    }
    for(int j =1; j<values[0].size();j++){
        costsArray[0][j] =  values[0][j]+costsArray[0][j-1];
    }

    for(int i=1;i<costsArray.size();i++){
        for(int j=1;j<costsArray[i].size();j++){
          costsArray[i][j] = costsArray[i-1][j] + costsArray[i][j-1] - costsArray[i-1][j-1] + values[i][j];
        }
    }

}

int Field::Weight( int x1, int y1, int x2, int y2 ) const{
    //O(1)
    //in this function the x values are on the cols and y values are the rows, normally i would be rows and j would be cols but in this function we must swap the two
    if (values.empty()|| values[0].empty()){
        return 0;
    }
    if((x1<0 || x1>values[0].size()-1) || (y1<0 || y1>values.size()-1) || (x2<0 || x2>values[0].size()-1) || (y2 <0 || y2 > values.size()-1)){
         throw std::out_of_range("INVALID INDEX");
    }
    
    int lowX,lowY,highX,highY;
    
    //ints keeping track of the bottom right of the square made(the highest sum of this is the highest x and the highest y values)
    //the low x and low y keep track of the borders of the square, if those values != 0 than we must subtract the value of 1 less than the border.
    lowX = std::min(x1,x2);
    lowY = std::min(y1,y2);
    highX = std::max(x1,x2);
    highY = std::max(y1,y2);
    int sum = costsArray[highY][highX];

    //if the bottom right != 0 than subtract the value to the left of the bottom right
    if(lowX!=0){
        sum -= costsArray[highY][lowX-1];
    }
    //if the top right is != 0 than we subtract the value to the top of the top right
    //the != stops us from going out of bounds and in addition gets rid of the duplicate values from taking the bottom right as the sum
    if(lowY!=0){
        sum -= costsArray[lowY-1][highX];
    }
    //if we subtracted both the left and top of the square we must add the previous diagonal because this prevents the subtraction of the same costs twice
    if(lowX!=0 && lowY!=0){
        sum += costsArray[lowY-1][lowX-1];
    }
    //return the sum
    return(sum);

} 

int Field::PathCost() const{
    //O(N) N is num items in array
    //if row/cols == 0 return 0 meaning empty array
    if (values.empty() || values[0].empty()){
        return 0;
    }
    //if the rows or cols ==1 than that means theres only one possible path so return that path cost
    if(values.size()==1){
        return(costsArray[0][values[0].size()-1]);
    }
    if(values[0].size()==1){
        return(costsArray[values.size()-1][0]);
    }
    //Dynmamic programing vector to hold sum values
    std::vector<std::vector<int>> sums;
    //resize sum to be equal to values
    sums.resize(values.size());

    for(int i=0;i<values.size();i++){
        sums[i].resize(values[i].size());
    }


    //setting the first row and col of the sums array manually
    sums[0][0]=values[0][0];
    for(int i =1; i<values.size();i++){
        sums[i][0] =  sums[i-1][0]+values[i][0];
    }
    for(int j =1; j<values[0].size();j++){
        sums[0][j] =  sums[0][j-1]+values[0][j];
    }

    //take the minimum value of either the sum of the path on top of the index or the sum of the path to the left of the index
    for(int i=1;i<values.size();i++){
        for(int j=1;j<values[i].size();j++){
            sums[i][j] = std::min(sums[i-1][j],sums[i][j-1]) + values[i][j];
        }
    }

    return sums[values.size()-1][values[0].size()-1];
} 