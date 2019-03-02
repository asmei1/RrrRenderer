#include <filesystem>
#include <fstream>
#include <algorithm>


#include "BMPImg.h"
#include "Helpers/FunctionHelper.h"


BMPImg::BMPImg(std::string fileName)
{
   load(fileName);
}
//Create 24 bit bmp image
BMPImg::BMPImg(uint32_t width, uint32_t height)
{
   this->infoHeader.width = width;
   this->infoHeader.height = height;
   this->infoHeader.planes = 1;
   this->infoHeader.headerSize = sizeof(BMPImg::bitmapInfoHeader);
   this->fileHeader.offset = sizeof(BMPImg::bitmapFileHeader_s) + sizeof(BMPImg::bitmapInfoHeader);
   this->infoHeader.bitCount = 24;
   this->infoHeader.compression = 0;
   this->rowStride = width * 3;
   for (size_t i = 0; i < height; ++i)
   {
      this->dataGrid.push_back(std::vector<uint8_t>(this->rowStride, 0));
   }

   uint32_t newStride = roundUp(this->rowStride, 4);
   this->fileHeader.size = this->fileHeader.offset + this->rowStride * height + this->infoHeader.height * (newStride - this->rowStride);

}

//Create 32 bit bmp with transparency/not transparency background
BMPImg::BMPImg(uint32_t width, uint32_t height, bool transparency)
{
   this->infoHeader.width = width;
   this->infoHeader.height = height;

   this->infoHeader.headerSize = sizeof(BMPImg::bitmapInfoHeader) + sizeof(BMPImg::bitmapColorHeader_s);
   this->fileHeader.offset = sizeof(BMPImg::bitmapFileHeader_s) + sizeof(BMPImg::bitmapInfoHeader) + sizeof(BMPImg::bitmapColorHeader_s);
   this->infoHeader.bitCount = 32;
   this->infoHeader.compression = 3;
   this->rowStride = width * 4;

   for (size_t i = 0; i < height; ++i)
   {
      std::vector<uint8_t> tempVec(this->rowStride, 255);
      if (transparency == true)
      {
         for (int i = 3; i < this->rowStride; i += 4)
         {
            tempVec[i] = 0;
         }
      }
      this->dataGrid.push_back(tempVec);
   }
   this->fileHeader.size = this->fileHeader.offset + this->rowStride * height;
}


BMPImg::~BMPImg()
{
}

void BMPImg::setName(std::string fileName)
{
   this->fileName = fileName;
}

void BMPImg::setData(const std::vector<std::vector<uint8_t>>& data)
{
   this->dataGrid = data;
}

int32_t BMPImg::getWidth() const
{
   return this->infoHeader.width;
}

int32_t BMPImg::getHeight() const
{
   return this->infoHeader.height;
}

bool BMPImg::load(std::string fileName)
{
   if (std::filesystem::path(fileName).extension() != ".bmp")
   {
      return false;
   }

   this->fileName = fileName;

   std::ifstream filestream(fileName, std::ios::binary);
   if (filestream.fail())
   {
      return false;
   }

   //get file header
   filestream.read((char*)&this->fileHeader, sizeof(BMPImg::bitmapFileHeader_s));
   if (this->fileHeader.type != 19788)
   {
      throw std::runtime_error("Error! Unrecognized file format.");
   }

   filestream.read((char*)&this->infoHeader, sizeof(BMPImg::bitmapInfoHeader));

   // The bitmapColorHeader is used only for transparent images
   if (this->infoHeader.bitCount == 32)
   {
      // Check if the file has bit mask color information
      if (this->infoHeader.headerSize >= (sizeof(BMPImg::bitmapInfoHeader) + sizeof(BMPImg::bitmapColorHeader_s)))
      {
         filestream.read((char*)&this->colorHeader, sizeof(BMPImg::bitmapColorHeader_s));

         checkColorMasks();
      }
      else
      {
         std::cerr << "The file \"" << fileName << "\" does not seem to contain bit mask information\n";
         throw std::runtime_error("Error! Unrecognized file format.");
      }
   }

   filestream.seekg(this->fileHeader.offset, filestream.beg);


   // Adjust the header fields for output.
   if (this->infoHeader.bitCount == 32)
   {
      this->infoHeader.headerSize = sizeof(BMPImg::bitmapInfoHeader) + sizeof(BMPImg::bitmapColorHeader_s);
      this->fileHeader.offset = sizeof(BMPImg::bitmapFileHeader_s) + sizeof(BMPImg::bitmapInfoHeader) + sizeof(BMPImg::bitmapColorHeader_s);
   }
   else
   {
      this->infoHeader.headerSize = sizeof(BMPImg::bitmapInfoHeader);
      this->fileHeader.offset = sizeof(BMPImg::bitmapFileHeader_s) + sizeof(BMPImg::bitmapInfoHeader);
   }

   this->fileHeader.size = this->fileHeader.offset;


   //this->dataGrid.resize(this->infoHeader.height);

   if (this->infoHeader.width % 4 == 0)
   {
      for (int i = 0; i < this->infoHeader.height; ++i)
      {
         std::vector<uint8_t> tempVec(this->infoHeader.width * this->infoHeader.bitCount / 8);
         filestream.read((char*)tempVec.data(), tempVec.size());
         this->fileHeader.size += static_cast<uint32_t>(tempVec.size());
         this->dataGrid.emplace_back(tempVec);
      }
   }
   else
   {
      this->rowStride = this->infoHeader.width * this->infoHeader.bitCount / 8;
      uint32_t newStride = roundUp(this->rowStride, 4);
      std::vector<uint8_t> paddingRow(newStride - this->rowStride);

      for (int y = 0; y < this->infoHeader.height; ++y)
      {
         std::vector<uint8_t> tempVec(this->rowStride);
         filestream.read((char*)tempVec.data(), this->rowStride);
         filestream.read((char*)paddingRow.data(), paddingRow.size());
         this->dataGrid.emplace_back(tempVec);

         this->fileHeader.size += static_cast<uint32_t>(tempVec.size());
      }
      this->fileHeader.size += this->infoHeader.height * static_cast<uint32_t>(paddingRow.size());

   }
   //close stream
   filestream.close();

   return true;
}

void BMPImg::checkColorMasks()
{
   // Check if the pixel data is stored as RrrColor::BGRA and if the color space type is sRGB
   BMPImg::bitmapColorHeader_s expected_color_header;

   if (expected_color_header.redMask != this->colorHeader.redMask ||
      expected_color_header.blueMask != this->colorHeader.blueMask ||
      expected_color_header.greenMask != this->colorHeader.greenMask ||
      expected_color_header.alphaMask != this->colorHeader.alphaMask)
   {
      throw std::runtime_error("Unexpected color mask format! The program expects the pixel data to be in the RrrColor::BGRA format");

   }
   if (expected_color_header.colorSpaceType != this->colorHeader.colorSpaceType)
   {
      throw std::runtime_error("Unexpected color space type! The program expects sRGB values");

   }
}

void BMPImg::set(uint32_t x, uint32_t y, const RrrColor::BGRA &color)
{
   short posX = x * this->infoHeader.bitCount / 8;
   this->dataGrid[y][posX + 0] = color.blue;
   this->dataGrid[y][posX + 1] = color.green;
   this->dataGrid[y][posX + 2] = color.red;
   if (this->infoHeader.bitCount == 32)
   {
      this->dataGrid[y][posX + 3] = color.alpha;
   }
}

RrrColor::BGRA BMPImg::get(uint32_t x, uint32_t y)
{
   RrrColor::BGRA color;
   short posX = x * this->infoHeader.bitCount / 8;
   color.blue = this->dataGrid[y][posX + 0];
   color.green = this->dataGrid[y][posX + 1];
   color.red = this->dataGrid[y][posX + 2];
   if (this->infoHeader.bitCount == 32)
   {
      color.alpha = this->dataGrid[y][posX + 3];
   }
   return (color);
}

void BMPImg::flipVertical()
{
   size_t width = getWidth();
   size_t height = this->dataGrid.size();
   for (int row = 0; row < static_cast<int>(height) / 2; ++row)
   {
      for (int col = 0; col < this->dataGrid[row].size(); ++col)
      {
         std::swap(this->dataGrid[row][col], this->dataGrid[height - row - 1][col]);
      }
   }
}

void BMPImg::flipHorizontal()
{
   size_t bytes = this->infoHeader.bitCount / 8;
   size_t height = this->dataGrid.size();

   for (int row = 0; row < static_cast<int>(height); ++row)
   {
      for (int col = 0; col < this->infoHeader.width / 2; ++col)
      {
         RrrColor::BGRA c1 = get(col, row);
         RrrColor::BGRA c2 = get(this->infoHeader.width - 1 - col, row);
         set(col, row, c2);
         set(this->infoHeader.width - 1 - col, row, c1);
      }
   }
}

bool BMPImg::save(std::string fileName)
{
   std::ofstream filestream;
   filestream.open(fileName == "" ? this->fileName : fileName, std::ios::binary);

   auto write = [this, &filestream]()
   {
      filestream.write((const char*)&this->fileHeader, sizeof(BMPImg::bitmapFileHeader_s));
      filestream.write((const char*)&this->infoHeader, sizeof(BMPImg::bitmapInfoHeader));
      if (this->infoHeader.bitCount == 32)
      {
         filestream.write((const char*)&this->colorHeader, sizeof(BMPImg::bitmapColorHeader_s));
      }
      for (int i = 0; i < this->dataGrid.size(); ++i)
      {
         auto & vec = this->dataGrid[i];
         filestream.write((char*)vec.data(), vec.size());
      }
   };

   if (filestream.is_open() == true)
   {
      if (this->infoHeader.bitCount == 32)
      {
         write();
      }
      else if (this->infoHeader.bitCount == 24)
      {
         if (this->infoHeader.width % 4 == 0)
         {
            write();
         }
         else
         {
            uint32_t newStride = roundUp(this->rowStride, 4);
            std::vector<uint8_t> paddingRow(newStride - this->rowStride);

            filestream.write((const char*)&this->fileHeader, sizeof(BMPImg::bitmapFileHeader_s));
            filestream.write((const char*)&this->infoHeader, sizeof(BMPImg::bitmapInfoHeader));

            for (int i = 0; i < this->dataGrid.size(); ++i)
            {
               auto & vec = this->dataGrid[i];
               filestream.write((char*)vec.data(), vec.size());
               filestream.write((const char*)paddingRow.data(), paddingRow.size());
            }
         }
      }
      else
      {
         throw std::runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
      }
   }
   else
   {
      throw std::runtime_error("Unable to open the output image file.");

   }

   filestream.close();

   return true;
}

void BMPImg::printAllDetails()
{
   printFileHeaderDetails();
   printInfoHeaderDetails();
}

std::vector<std::vector<uint8_t>> BMPImg::getData() const
{
   return this->dataGrid;
}

BMPImg::bitmapFileHeader_s BMPImg::getFileInfo() const
{
   return this->fileHeader;
}

BMPImg::bitmapInfoHeader BMPImg::getBMPInfo() const
{
   return this->infoHeader;
}



void BMPImg::printFileHeaderDetails()
{
   std::cout << "bfType          " << fileHeader.type << std::endl;
   std::cout << "bfSize          " << fileHeader.size << std::endl;
   std::cout << "bfReserved1     " << fileHeader.bfReserved1 << std::endl;
   std::cout << "bfReserved2     " << fileHeader.bfReserved2 << std::endl;
   std::cout << "bfOffBits       " << fileHeader.offset << std::endl;
}

void BMPImg::printInfoHeaderDetails()
{
   std::cout << "biSize          " << infoHeader.headerSize << std::endl;
   std::cout << "biWidth         " << infoHeader.width << std::endl;
   std::cout << "biHeight        " << infoHeader.height << std::endl;
   std::cout << "biPlanes        " << infoHeader.planes << std::endl;
   std::cout << "biBitCount      " << infoHeader.bitCount << std::endl;
   std::cout << "biCompression   " << infoHeader.compression << std::endl;
   std::cout << "biSizeImage     " << infoHeader.imgSize << std::endl;
   std::cout << "biXPelsPerMeter " << infoHeader.biXPelsPerMeter << std::endl;
   std::cout << "biYPelsPerMeter " << infoHeader.biYPelsPerMeter << std::endl;
   std::cout << "biClrUsed       " << infoHeader.biClrUsed << std::endl;
   std::cout << "biClrImportant  " << infoHeader.biClrImportant << std::endl;
}
