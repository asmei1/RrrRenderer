#pragma once
#include "BMPImg.h"

BGRA_s HSVtoRGB(HSV_s);
HSV_s RGBtoHSV(BGRA_s);
uint8_t truncate(int val);
int roundUp(int numToRound, int multiple);

