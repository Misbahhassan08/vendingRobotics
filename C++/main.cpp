#include <iostream>

#include <pigpio.h>

#include "rotary_encoder.hpp"

/*

REQUIRES

A rotary encoder contacts A and B connected to separate gpios and
the common contact connected to Pi ground.

TO BUILD

g++ -o main main.cpp rotary_encoder.cpp -lpigpio -lrt

TO RUN

sudo ./main

*/
int res = 10;
int pos = 0;
int side = 1;
#define speed 100
#define freq  8000 
#define d  1
#define debug  1
#define _pwm  18 
#define _dir  12
#define _BRK  19
#define _EN 26  
#define _Encoder1 27
#define _Encoder2 22
#define _Encoder3 23

void callback(int way)
{
   pos = way;
   std::cout << "pos=" << pos << std::endl;
}


int main(int argc, char *argv[])
{
   gpioInitialise();
   if (gpioInitialise() < 0) std::cout << "ERROR\n";
   else std::cout << "DONE\n";
   gpioSetMode(_dir, PI_OUTPUT);
   gpioSetMode(_EN, PI_OUTPUT);
   gpioSetMode(_BRK, PI_OUTPUT);
   gpioSetMode(_pwm, PI_OUTPUT);
   //if(d) gpioWrite(_dir, 1);
   //else gpioWrite(_dir, 0);
   gpioWrite(_EN, 0);
   gpioWrite(_BRK, 1);
   
   re_decoder dec(_Encoder1, _Encoder2, _Encoder3, callback);
   
   
   gpioWrite(_BRK, 0); // brakes on
   gpioPWM(_pwm, speed);
   while(true)
   {
	   if (side)
	   {   
		   gpioWrite(_dir, 1);
		   gpioWrite(_BRK, 1); // brakes off
		   if(pos == 100)
			{
				gpioWrite(_BRK, 0); //brakes on
				side = 0;
				time_sleep(1);
				} 
		   }
		else
		{
		   gpioWrite(_dir, 0);
		   gpioWrite(_BRK, 1); // brakes off
		   if(pos == 0)
			{
				gpioWrite(_BRK, 0); //brakes on
				side = 1;
				time_sleep(1);
				}	
			}
		}
	
   gpioWrite(_BRK, 0);
   gpioPWM(_pwm, 0);
   //time_sleep(30);

   dec.re_cancel();

   gpioTerminate();
}

