#include <iostream>
#include "pascal.h"
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <cmath>
#include <stdexcept>
#include <chrono>
//#include <thread>

void printRow(PascalRow& primeTriangle);

std::unordered_map<int,std::unordered_set<int>> squaresModP(PascalRow& primeTriangle);

std::vector<std::array<long long int,3>> pythagTripleModP(int index1,int index2, std::vector<PascalRow>& primeTriangles, std::vector<std::unordered_map<int,std::unordered_set<int>>>& primeSquares);
std::array<long long int,3> pythagTriple(int rowDown,int index1, int index2, int index3);
long long int squarePascal(int rowDown, int indexAcross);
void mainCycle(std::vector<PascalRow>& trianges);

int main() {
    
    std::cout << "Hellooo. Thanks Fatal you're a real one =)" << "\n";

    std::vector<long long int> primes = { 28493 , 24799, 29501  };

    std::vector<PascalRow> triangles;

    for(int p : primes){
        PascalRow primeTriangle(p,1,0);
        triangles.push_back(primeTriangle);
        
    }

    //const auto processor_count = std::thread::hardware_concurrency();
    
    auto start = std::chrono::system_clock::now();
    for(int cycle = 0; cycle < 100000; ++cycle){
        //std::vector<std::thread> threads = {};

        for(int i = 0; i < 1; ++i){
            for(PascalRow& row: triangles){
                row.iterate();
            }
            mainCycle(triangles);
            //threads.push_back(std::thread(mainCycle,triangles));
        }
        
         
        if(cycle % 100 == 0){
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

            std::cout << cycle << " " << duration.count() << std::endl;
            start = std::chrono::system_clock::now();

        } 

    }
    

   /*
   for(int cycle = 0; cycle < 100000; ++cycle){

        std::vector<std::unordered_map<int,std::unordered_set<int>>> primeSquares = {};

        for(PascalRow& row: triangles){
            row.iterate();
            primeSquares.push_back(squaresModP(row));
            //printRow(row);
        }

        if(cycle == 61){
            std::vector<std::array<long long int,3>> triples = pythagTripleModP(26,27,triangles,primeSquares);
            std::cout << "too late";

            if(!triples.empty()){
                    std::cout<< triples[0][0] << " " << triples[0][1] << " " << triples[0][2] << "\n";

                    return 0;
            }
        }
   }
   */
    return 0;
}

void mainCycle(std::vector<PascalRow>& triangles){

    std::vector<std::unordered_map<int,std::unordered_set<int>>> primeSquares = {};

    for(PascalRow& row: triangles){

        primeSquares.push_back(squaresModP(row));

    }
    

    
    for(int i = 0; i < triangles[0].getLen();++i){
        for(int j = i; j < triangles[0].getLen();++j){
            std::vector<std::array<long long int,3>> triples = pythagTripleModP(i,j,triangles,primeSquares);

            if(!triples.empty()){
                std::cout<< triples[0][0] << " " << triples[0][1] << " " << triples[0][2] << "\n";
                std::cout << i << " " << j << " " << triangles[0].getRowDown() << "\n";
                //return 0;
            }
        }
    }
    /*
    if(cycle % 100 == 0){
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        std::cout << cycle << " " << duration.count() << std::endl;
        start = std::chrono::system_clock::now();

    } */
}

void printRow(PascalRow& primeTriangle){
    std::vector<int>& values = primeTriangle.getValues();

    for(int i: values){
        std::cout << i << " ";
    }
    std::cout << "\n";
}

std::unordered_map<int,std::unordered_set<int>> squaresModP(PascalRow& primeTriangle){
    std::unordered_map<int,std::unordered_set<int>> squares;

    long long int base = primeTriangle.getBase();
    int length = primeTriangle.getLen();
    std::vector<int>& values = primeTriangle.getValues();

    for(int i = 0; i < length; ++i){

        squares[(values[i] * values[i]) % base].insert(i);
    }

    return squares;
}

long long int squarePascal(int rowDown, int indexAcross){

    long long int value = 1;

    for(long long int i = 0; i < indexAcross; ++i){
        value *= (rowDown-i);
        value /= i+1;
    }

    if(value < 0){
        std::cout << rowDown << " " << indexAcross;
        throw std::invalid_argument( "aaaaah" );
    }
    return value;
}

std::array<long long int,3> pythagTriple(int rowDown,int index1, int index2, int index3){
    /*
    long long int aSquare = squarePascal(rowDown,index1);
    long long int bSquare = squarePascal(rowDown,index2);
    long long int cSquare = squarePascal(rowDown,index3);

    if (aSquare + bSquare == cSquare){
        return {aSquare,bSquare,cSquare};
    }
    return {0,0,0};
    */
    return {index1,index2,index3};
}

std::vector<std::array<long long int,3>> pythagTripleModP(int index1,int index2, std::vector<PascalRow>& primeTriangles, std::vector<std::unordered_map<int,std::unordered_set<int>>>& primeSquares){

    int base = primeTriangles[0].getBase();
    int aSquare = (primeTriangles[0].getValues()[index1]*primeTriangles[0].getValues()[index1]) % base;
    int bSquare = (primeTriangles[0].getValues()[index2]*primeTriangles[0].getValues()[index2]) % base;
    
    int lhsSum = (aSquare + bSquare) % base;
    //std::cout << aSquare << " " << bSquare << " " << lhsSum << " " << primeTriangles[0].getValues()[28];
    

    std::unordered_set<int> possibleC = primeSquares[0][lhsSum];

    if(possibleC.size() == 0){
        return {};
    }
    else{
        for(int i = 1; i < primeTriangles.size(); ++i){
            //std::cout << i << "\n";
            base = primeTriangles[i].getBase();
            aSquare = ((primeTriangles[i].getValues()[index1])*(primeTriangles[i].getValues()[index1])) % base;
            bSquare = ((primeTriangles[i].getValues()[index2])*(primeTriangles[i].getValues()[index2])) % base;

            int lhsSum = (aSquare + bSquare) % base;
            
            std::unordered_set<int> otherC = primeSquares[i][lhsSum];

            std::unordered_set<int> newC;

            for(int rowIndex: possibleC){
                if(otherC.count(rowIndex) > 0){
                    newC.insert(rowIndex);
                }
            }
            if(newC.size() == 0){
                return {};
            }
            possibleC = newC;
            
        }
    }
    std::array<long long int,3> nullValue = {0,0,0};
    std::vector<std::array<long long int,3>> triplesAll = {};
    for(int cVals: possibleC){
        std::array<long long int,3> value = pythagTriple(primeTriangles[0].getRowDown(),index1,index2,cVals);
        
        if (value != nullValue){
            triplesAll.push_back(value);
        }
    }
    return triplesAll;
}