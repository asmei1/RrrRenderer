#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Colors.h"

class BMPImg
{
   friend class Geometry;

#pragma pack(push, 1) //its for tighly pack structure
   struct bitmapFileHeader_s
   {
      uint16_t  type = 0x4d42;              //must be equal to "BM" (or 19788). It declare that this is bmp file
      uint32_t  size;                      //size of .bmp file
      uint16_t  bfReserved1 = 0;           //must be equal 0
      uint16_t  bfReserved2 = 0;           //must be equal 0
      uint32_t  offset;                    //specifies the offset from the beginning of the file to the bitmap data.
   };
#pragma pack(pop)

#pragma pack(push, 1) 
   struct bitmapInfoHeader
   {
      uint32_t headerSize;             //Size of_header_st, standard value = 40
      int32_t  width;                  //width of image, in pixel
      int32_t  height;                 //height of image, in pixel
      uint16_t planes = 0;             //specifies the number of planes of the target device
      uint16_t bitCount;               //Number of bits per pixel Typical values are 1, 4, 8, 16, 24 and 32.
      uint32_t compression;            //Type of compression
      uint32_t imgSize;                //specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.
      int32_t  biXPelsPerMeter = 0;    //specifies the the horizontal pixels per meter on the designated targer device, usually set to zero.
      int32_t  biYPelsPerMeter = 0;    //specifies the the vertical pixels per meter on the designated targer device, usually set to zero.
      uint32_t biClrUsed = 0;          //specifies the number of colors used in the bitmap, if set to zero the number of colors is calculated using the biBitCount member.
      uint32_t biClrImportant = 0;     //specifies the number of color that are 'important' for the bitmap, if set to zero, all colors are important.
   };
#pragma pack(pop)

#pragma pack(push, 1) 
   struct bitmapColorHeader_s
   {
      uint32_t redMask = 0x00ff0000;       // Bit mask for the red channel
      uint32_t greenMask = 0x0000ff00;       // Bit mask for the green channel
      uint32_t blueMask = 0x000000ff;       // Bit mask for the blue channel
      uint32_t alphaMask = 0xff000000;       // Bit mask for the alpha channel
      uint32_t colorSpaceType = 0x73524742;       // Default "sRGB" (0x73524742)
      uint32_t unused[16]{ 0 };                     // Unused data for sRGB color space

   };
#pragma pack(pop)
public:
   BMPImg(std::string fileName);
   BMPImg(uint32_t width, uint32_t height, RrrColor::RGBA color, bool extended);
   ~BMPImg();


   void printFileHeaderDetails();
   void printInfoHeaderDetails();
   void printAllDetails();

   std::vector<std::vector<uint8_t>> getData() const;
   bitmapFileHeader_s getFileInfo() const;
   bitmapInfoHeader getBMPInfo() const;

   int32_t getWidth() const;
   int32_t getHeight() const;
   uint32_t getSize() const;

   void setName(std::string fileName);
   void setData(const std::vector<std::vector<uint8_t>>& data);

   bool save(std::string fileName = "");
   bool load(std::string fileName);

   void checkColorMasks();

   void set(uint32_t x, uint32_t y, const RrrColor::RGBA &color);
   RrrColor::RGBA get(uint32_t x, uint32_t y);

   void flipVertical();
   void flipHorizontal();



   static void testColors();

private: 
   std::vector<std::vector<uint8_t>> dataGrid;

   bitmapFileHeader_s fileHeader;
   bitmapInfoHeader infoHeader;
   bitmapColorHeader_s colorHeader;


   uint32_t rowStride = 0;
   std::string fileName;
};
