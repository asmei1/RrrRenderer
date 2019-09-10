#include "Settings.h"

void Settings::setWidth(uint32_t width) 
{
   this->width = width;
};

uint32_t Settings::getWidth() const 
{
   return this->width;
};

void Settings::setHeight(uint32_t height) 
{
   this->height = height;
};

uint32_t Settings::getHeight() const 
{
   return this->height;
};

void Settings::setFOV(float fov) 
{
   this->fov = fov;
};

float Settings::getFOV() const 
{
   return this->fov;
};

void Settings::setBias(float bias) 
{
   this->bias = bias;
};

float Settings::getBias() const 
{
   return this->bias;
};

float Settings::getRatio() const 
{
   return this->width / (float)this->height;
}

RrrColor::RGBA Settings::getBackgroundColor() const 
{
   return this->backgroundColor;
}

int Settings::getMaxDepth() const
{
   return this->maxDepth;
}

void Settings::setMaxDepth(int maxDepth)
{
   this->maxDepth = maxDepth;
}

void Settings::setBackgroundColor(const RrrColor::RGBA& color)
{
   this->backgroundColor = color;
}
