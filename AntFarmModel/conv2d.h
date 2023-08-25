//
//  conv2d.h
//  PerceptionTraversalModel
//
//  Created by Caleb Price on 8/24/23.
//

#ifndef CONV2D_H
#define CONV2D_H

#include <stdio.h>
#include <iostream>

class conv2d
{
public:
    conv2d (char* center, int rows, int cols, int row_orig, int col_orig);
    conv2d (const conv2d* cpyObj);
    ~conv2d ();
    const int getCurrentRow();
    const int getCurrentCol();
    void printPerceptionMap();
    bool setNavRight();
    bool setNavLeft();
    bool setNavUp();
    bool setNavDown();
    bool setNavLeftUp();
    bool setNavLeftDown();
    bool setNavRightUp();
    bool setNavRightDown();
    void setDropValue(const char inVal);
    void resetOrigin();
    const char centerValue();
    const char leftUpValue();
    const char leftDownValue();
    const char rightUpValue();
    const char rightDownValue();
    const char leftValue();
    const char rightValue();
    const char upValue();
    const char downValue();
protected:
    char* centerPtr();
    char* leftUpPtr();
    char* leftDownPtr();
    char* rightUpPtr();
    char* rightDownPtr();
    char* leftPtr();
    char* rightPtr();
    char* upPtr();
    char* downPtr();
    void navigateTo(const int rowOffset, const int colOffset);
private:
    bool getIsInRange(const int row, const int col);

    char* ptr;
    int rowLen, colLen, rowOrig, colOrig, rowCurr, colCurr;
};

#endif /* conv2d_h */
