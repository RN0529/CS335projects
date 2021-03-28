#ifndef SQUARE_MATRIX_
#define SQUARE_MATRIX_
#include <iostream>
#include<stdexcept>
template <class T>
class SquareMatrix
{

    public:
        SquareMatrix():sizeOfArray(0),arr(nullptr){ 
            //constructor
        } 

        //big 5
        ~SquareMatrix(){  
            //destructor
            for(int i = 0; i<sizeOfArray; i++){  
                delete[]  arr[i];
            }
            delete[] arr;
            
            arr = nullptr;
            sizeOfArray=0;
            
        }

        SquareMatrix(const SquareMatrix &trg):arr(nullptr),sizeOfArray(0){
            //copy constructor
            //mking arr = new array with resie and then setting all values to the trg values
            
            resize(trg.sizeOfArray);
            
            for(int i = 0; i<sizeOfArray;i++){
                for(int j=0;j<sizeOfArray;j++){
                    arr[i][j] = trg.arr[i][j];
                }
            }

        } 
        SquareMatrix( SquareMatrix &&trg):sizeOfArray(trg.sizeOfArray),arr(trg.arr){
             //move constryctor
             //setting arr = trg arr and then setting trg to null
            trg.arr = nullptr;
            trg.sizeOfArray = 0;
        }

        SquareMatrix & operator=(const SquareMatrix &trg){
            // copy assignment 
            //if array is itself return itself, if it is not a nullptr then delete old data 
            //then make a new dynmaically allocated matrix with resize and then set the values accordingly
            if(this ==  &trg){
                return *this;
            }
            if(arr!=nullptr){
                for(int i = 0; i<sizeOfArray; i++){  
                    delete[]  arr[i];
                }
                delete[] arr;
                arr = nullptr;  
            }
            resize(trg.sizeOfArray);
            for(int i = 0; i<sizeOfArray;i++){
                for(int j=0;j<sizeOfArray;j++){
                    arr[i][j] = trg.arr[i][j];
                }
            }
            return *this;
        } 




        SquareMatrix & operator=( SquareMatrix &&trg){
            // move assignment
            //if it is itslef just return itself
            //delete old data
            //setting arr = trg arr and then setting trg to null
            if(this ==  &trg){
                return *this;
            }

            for(int i = 0; i<sizeOfArray; i++){  
                delete[]  arr[i];
            }
            delete[] arr;

            arr = trg.arr;
            sizeOfArray =  trg.sizeOfArray;
            trg.arr = nullptr;
            trg.sizeOfArray = 0;

            return *this;
        } 

        void resize(int newSize){
            //if array is null pointer than make a new dynamically allocated 2d array and set size variable to the inputed newsize
            //else delete old array and then doing the step above
            if(arr == nullptr){
                arr = new T*[newSize];
                for(int i = 0; i<newSize;i++){
                    arr[i] = new T[newSize];
                }
                sizeOfArray = newSize;
                return;

            }else{

                for(int i = 0; i<sizeOfArray; i++){  
                    delete[]  arr[i];
                }
                delete[] arr;

                arr = new T*[newSize];
                sizeOfArray = newSize;
                for(int i = 0; i<newSize ;i++){
                    arr[i] = new T[newSize];
                }

            }
            return;

        }


        bool operator==(const SquareMatrix &trg)const{
            //if every value of the matrix are the same return true 
            //if there was an inconsistancy found return false
            if(sizeOfArray!= trg.sizeOfArray){
                return false;
            }

            for(int i=0; i<sizeOfArray;i++){
                for(int j =0; j<sizeOfArray; j++){
                   if(arr[i][j]!=trg.arr[i][j]){
                       return false;
                   }
                }
            }
            return true;
        }

        SquareMatrix operator+(const SquareMatrix&  trg)const{
            //make new matrix c and then resize that to the inputed matrix size
            //then add the values of the corrosponding indexes and put them into the new matrix
            SquareMatrix<T> c;
            c.resize(trg.sizeOfArray);
            for(int i=0; i<trg.sizeOfArray;i++){
                for(int j =0; j<trg.sizeOfArray; j++){
                    c.at(i,j) = arr[i][j]+trg.arr[i][j];
                }
            }
            return c;
            
        }

        T& at(int row, int col){
            //if the input row/col is bigger than the size-1 then throw bounds else return that variable
            if(row > sizeOfArray-1 || col > sizeOfArray-1 || row<0 || col<0){
                throw std::out_of_range ("out of range!!!");
            }
            else{
                return(arr[row][col]);
            }
            
        }


        int size()const{ 
            //return the size of the matrix
            return sizeOfArray;
        }



    private:
        //private members
        int sizeOfArray;
        T** arr;



}; // end SquareMAtrix
#endif
