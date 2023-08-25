//
//  conv2d.cpp
//  PerceptionTraversalModel
//
//  Created by Caleb Price on 8/24/23.
//


#include "conv2d.h"


conv2d::conv2d (char* center, int rows, int cols, int row_orig, int col_orig)
{
    ptr = center;
    rowLen = rows;
    colLen = cols;
    rowOrig = row_orig;
    colOrig = col_orig;
    rowCurr = 0;
    colCurr = 0;
    navigateTo(row_orig, col_orig);
}

conv2d::conv2d (const conv2d* cpyObj)
{
    this->ptr = cpyObj->ptr;
    this->rowLen = cpyObj->rowLen;
    this->colLen = cpyObj->colLen;
    this->rowOrig = cpyObj->rowOrig;
    this->colOrig = cpyObj->colOrig;
    this->rowCurr = cpyObj->rowCurr;
    this->colCurr = cpyObj->colCurr;
}

conv2d::~conv2d ()
{
    // de-reference ptr
    ptr = nullptr;
}

const int conv2d::getCurrentRow()
{
    
    return this->rowCurr;
}

const int conv2d::getCurrentCol()
{
    
    return this->colCurr;
}

void conv2d::printPerceptionMap()
{
    std::cout << this->leftUpValue() << this->upValue() << this->rightUpValue();
    std::cout << std::endl;
    std::cout << this->leftValue() << '*' << this->rightValue();
    std::cout << std::endl;
    std::cout << this->leftDownValue() << this->downValue() << this->rightDownValue();
    std::cout << std::endl;
}

bool conv2d::setNavRight()
{
    char* tmpPtr = rightPtr();
    if (tmpPtr != nullptr)
    {
        ptr = tmpPtr;
        
        return true;
    }
    tmpPtr = nullptr;
    
    return false;
}

bool conv2d::setNavLeft()
{
    char* tmpPtr = leftPtr();
    if (tmpPtr != nullptr)
    {
        ptr = tmpPtr;
        
        return true;
    }
    tmpPtr = nullptr;
    
    return false;
}

bool conv2d::setNavUp()
{
    char* tmpPtr = upPtr();
    if (tmpPtr != nullptr)
    {
        ptr = tmpPtr;
        
        return true;
    }
    tmpPtr = nullptr;
    
    return false;
}

bool conv2d::setNavDown()
{
    char* tmpPtr = downPtr();
    if (tmpPtr != nullptr)
    {
        ptr = tmpPtr;
        
        return true;
    }
    tmpPtr = nullptr;
    
    return false;
}

bool conv2d::setNavLeftUp()
{
    char* tmpPtr = leftUpPtr();
    if (tmpPtr != nullptr)
    {
        ptr = tmpPtr;
        
        return true;
    }
    tmpPtr = nullptr;
    
    return false;
}
bool conv2d::setNavLeftDown()
{
    char* tmpPtr = leftDownPtr();
    if (tmpPtr != nullptr)
    {
        ptr = tmpPtr;
        
        return true;
    }
    tmpPtr = nullptr;
    
    return false;
}

bool conv2d::setNavRightUp()
{
    char* tmpPtr = rightUpPtr();
    if (tmpPtr != nullptr)
    {
        ptr = tmpPtr;
        
        return true;
    }
    tmpPtr = nullptr;
    
    return false;
}

bool conv2d::setNavRightDown()
{
    char* tmpPtr = rightDownPtr();
    if (tmpPtr != nullptr)
    {
        ptr = tmpPtr;
        
        return true;
    }
    tmpPtr = nullptr;
    
    return false;
}

void conv2d::setDropValue(const char inVal)
{
    if (getIsInRange(this->rowCurr, this->colCurr))
    {
        *this->ptr = inVal;
    }
}

void conv2d::resetOrigin()
{
    if (this->ptr != nullptr)
    {
        navigateTo(this->rowOrig-this->rowCurr, this->colOrig-this->colCurr);
    }
}

const char conv2d::centerValue()
{
    return *centerPtr();
}

const char conv2d::leftUpValue()
{
    char* tmpPtr = leftUpPtr();
    if (tmpPtr != nullptr)
    {
        
        return *tmpPtr;
    }
    
    return 0;
}

const char conv2d::leftDownValue()
{
    char* tmpPtr = leftDownPtr();
    if (tmpPtr != nullptr)
    {
        
        return *tmpPtr;
    }
    
    return 0;
}

const char conv2d::rightUpValue()
{
    char* tmpPtr = rightUpPtr();
    if (tmpPtr != nullptr)
    {
        
        return *tmpPtr;
    }
    
    return 0;
}

const char conv2d::rightDownValue()
{
    char* tmpPtr = rightDownPtr();
    if (tmpPtr != nullptr)
    {
        
        return *tmpPtr;
    }
    
    return 0;
}

const char conv2d::leftValue()
{
    char* tmpPtr = leftPtr();
    if (tmpPtr != nullptr)
    {
        
        return *tmpPtr;
    }
    
    return 0;
}

const char conv2d::rightValue()
{
    char* tmpPtr = rightPtr();
    if (tmpPtr != nullptr)
    {
        
        return *tmpPtr;
    }
    
    return 0;
    
}

const char conv2d::upValue()
{
    char* tmpPtr = upPtr();
    if (tmpPtr != nullptr)
    {
        
        return *tmpPtr;
    }
    
    return 0;
}

const char conv2d::downValue()
{
    char* tmpPtr = downPtr();
    if (tmpPtr != nullptr)
    {
        
        return *tmpPtr;
    }
    
    return 0;
}

char* conv2d::centerPtr()
{
    return ptr;
}

char* conv2d::leftUpPtr()
{
    if (getIsInRange(rowCurr-1, colCurr-1))
    {
        colCurr--;
        rowCurr--;
        
        return (ptr - sizeof(char) - (this->rowLen * sizeof(char)));
    }
    
    return nullptr;
}

char* conv2d::leftDownPtr()
{
    if (getIsInRange(rowCurr+1, colCurr-1))
    {
        colCurr--;
        rowCurr++;
        
        return (ptr - sizeof(char) + (this->rowLen * sizeof(char)));
    }
    
    return nullptr;
}

char* conv2d::rightUpPtr()
{
    if (getIsInRange(rowCurr-1, colCurr+1))
    {
        colCurr++;
        rowCurr--;
        
        return (ptr + sizeof(char) - (this->rowLen * sizeof(char)));
    }
    
    return nullptr;
}

char* conv2d::rightDownPtr()
{
    if (getIsInRange(rowCurr+1, colCurr+1))
    {
        colCurr++;
        rowCurr++;
        
        return (ptr + sizeof(char) + (this->rowLen * sizeof(char)));
    }
    
    return nullptr;
}

char* conv2d::leftPtr()
{
    if (getIsInRange(rowCurr, colCurr-1))
    {
        colCurr--;
        
        return (ptr - sizeof(char));
    }
    
    return nullptr;
}

char* conv2d::rightPtr()
{
    if (getIsInRange(rowCurr, colCurr+1))
    {
        colCurr++;
        
        return ((ptr) + sizeof(char));
    }
    
    return nullptr;
    
}

char* conv2d::upPtr()
{
    if (getIsInRange(rowCurr-1, colCurr))
    {
        rowCurr--;
        
        return (ptr - (this->rowLen * sizeof(char)));
    }
    
    return nullptr;
}

char* conv2d::downPtr()
{
    if (getIsInRange(rowCurr+1, colCurr))
    {
        rowCurr++;
        
        return (ptr + (this->rowLen * sizeof(char)));
    }
    
    return nullptr;
}

void conv2d::navigateTo(const int rowOffset, const int colOffset)
{
    const int absRowOffset = std::abs(rowOffset);
    const int absColOffset = std::abs(colOffset);
    if (colOffset < 0)
    {
        for (int i = 0; i < absColOffset; ++i)
            this->setNavLeft();
    }
    else
    {
        for (int i = 0; i < absColOffset; ++i)
            this->setNavRight();
    }
    if (rowOffset < 0)
    {
        for (int i = 0; i < absRowOffset; ++i)
            this->setNavUp();
    }
    else
    {
        for (int i = 0; i < absRowOffset; ++i)
            this->setNavDown();
    }
}

bool conv2d::getIsInRange(const int row, const int col)
{
    
    return (row >= 0 &&
            col >= 0 &&
            row < rowLen &&
            col < colLen);
}
