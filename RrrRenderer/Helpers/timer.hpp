#pragma once

#include <chrono>


class Timer {

public:
   void StartMeasureTime() inline
   {
      this->start = std::chrono::high_resolution_clock::now();
   }

   void StoptMeasureTime() inline
   {
      this->stop = std::chrono::high_resolution_clock::now();
   }

   unsigned long GetTimeInMiliSec() inline
   {
      return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
   }

   double GetTimeInSec() inline
   {
      return GetTimeInMiliSec() / 1000.f;
   }

private:
   std::chrono::high_resolution_clock::time_point start;
   std::chrono::high_resolution_clock::time_point stop;
};


