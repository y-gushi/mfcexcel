#pragma once

#include <stdio.h>
#include<iostream>

class bitInOut {
public:
    unsigned char stocks[64] = { 0 };
    unsigned int bitoutvalue;
    unsigned short bitstartpos;//現在読み込んだ時の位置
    unsigned short bitendpos;//読み込んだ後の位置
    unsigned short stockValue;
    unsigned short bitpos;//読み込み位置の距離

    bitInOut();
    void BigendOut(int setValue);
    void LittleendOut(int setValueR);

    void LittleendIn(int bi, int n);
    void BigendIn(int bir, int nr);
};