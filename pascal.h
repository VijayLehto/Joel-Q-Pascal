#ifndef PASCAL_H
#define PASCAL_H

#include <vector>

class PascalRow{
    public:

    PascalRow(const long long int base, const int row, int rowDown) : m_base{base}, m_rowNum(row), m_rowDown(rowDown){
        m_rowVals.resize(m_rowNum,1);
    }

    void iterate();

    std::vector<int>& getValues(){
        return m_rowVals;
    }

    long long int getBase(){
        return m_base;
    }

    int getLen(){
        return m_rowVals.size();
    }

    int getRowDown(){
        return m_rowDown;
    }

    private:
    
    const long long int m_base;
    int m_rowNum;
    int m_rowDown;
    //bool m_rowParity;
    std::vector<int> m_rowVals;
};

#endif