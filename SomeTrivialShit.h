#pragma once
#include<iostream>
#include<cmath>

int alphaToNum(char ch);
bool cmpstr(const char* , const char*);

void space(int count = 20);
void copy(char* dest, const char* src);

float distanceInPlane(int*&);
float slope(int*&);

void switchColor(const char*&);
void setUserDisplayColour(const char*&);

void skiplines(int k = 0);