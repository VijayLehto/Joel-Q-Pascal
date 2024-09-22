
#include "pascal.h"
#include <vector>

void PascalRow::iterate(){

    int oldRowNum = m_rowNum;
    m_rowDown += 1;
    m_rowNum = (m_rowDown/2) + 1;



    int bufferVal = 1;

    for( int i = 1; i < oldRowNum; ++i){

        int value = bufferVal + m_rowVals[i];
        bufferVal = m_rowVals[i];

        if (value >= m_base){
            m_rowVals[i] = value - m_base;
        }
        else{
            m_rowVals[i] = value;
        }
    }

    if (m_rowDown % 2 == 0){
        int value = 2*bufferVal;
         if (value >= m_base){
            m_rowVals.push_back(value-m_base);
        }
        else{
            m_rowVals.push_back(value);
        }

    }


}