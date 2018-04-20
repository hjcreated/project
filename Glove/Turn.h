#ifndef Turn_h
#define Turn_h
#if (ARDUINO >=1000)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Turnlib{
  public:
   //Constructor
   Turnlib();

   //Method
   int readAngle();
   void Setup();
   static void dmpDataReady();
   static void fifoReset();
   static int Turnlib::readLeft();
   static int Turnlib::readUp() ;
   private:
  
  
  
  };
#endif
