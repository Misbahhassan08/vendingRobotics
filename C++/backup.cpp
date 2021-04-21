#include <iostream>

#include <pigpio.h>

#include "rotary_encoder.hpp"

void re_decoder::_pulseA(int gpio, int level, uint32_t tick)
{
   if (gpio != lastGpio) /* debounce */
   {
      lastGpio = gpio;

      if ((gpio == mygpioA) && (level == 1))
      {
         
         if(levC) { posi += -1; (mycallback)(posi);}
        else if(levB) { posi += 1; (mycallback)(posi);}
        levA = 1; levB = 0; levC = 0;
      }
      
      
   }
}
void re_decoder::_pulseB(int gpio, int level, uint32_t tick)
{
   if (gpio != lastGpio) /* debounce */
   {
      lastGpio = gpio;

      if ((gpio == mygpioB) && (level == 1))
      {
         if(levA) { posi += -1; (mycallback)(posi);}
        else if(levC) { posi += 1; (mycallback)(posi);}
        levA = 0; levB = 1; levC = 0;
      }
      
      
   }
}
void re_decoder::_pulseC(int gpio, int level, uint32_t tick)
{
   if (gpio != lastGpio) /* debounce */
   {
      lastGpio = gpio;

      if ((gpio == mygpioC) && (level == 1))
      {
         if(levB) { posi += -1; (mycallback)(posi);}
        else if(levA) { posi += 1; (mycallback)(posi);}
        levA = 0; levB = 0; levC = 1;
      }
      
      
   }
}
void re_decoder::_pulseExA(int gpio, int level, uint32_t tick, void *user)
{
   /*
      Need a static callback to link with C.
   */

   re_decoder *mySelf = (re_decoder *) user;

   mySelf->_pulseA(gpio, level, tick); /* Call the instance callback. */
}
void re_decoder::_pulseExB(int gpio, int level, uint32_t tick, void *user)
{
   /*
      Need a static callback to link with C.
   */

   re_decoder *mySelf = (re_decoder *) user;

   mySelf->_pulseB(gpio, level, tick); /* Call the instance callback. */
}
void re_decoder::_pulseExC(int gpio, int level, uint32_t tick, void *user)
{
   /*
      Need a static callback to link with C.
   */

   re_decoder *mySelf = (re_decoder *) user;

   mySelf->_pulseC(gpio, level, tick); /* Call the instance callback. */
}
re_decoder::re_decoder(int gpioA, int gpioB, int gpioC, re_decoderCB_t callback)
{
   mygpioA = gpioA;
   mygpioB = gpioB;
   mygpioC = gpioC;

   mycallback = callback;

   levA=1;
   levB=0;
   levC=0;

   lastGpio = -1;
   posi = 0;

   gpioSetMode(gpioA, PI_INPUT);
   gpioSetMode(gpioB, PI_INPUT);
   gpioSetMode(gpioC, PI_INPUT);
   /* pull up is needed as encoder common is grounded */

   gpioSetPullUpDown(gpioA, PI_PUD_UP);
   gpioSetPullUpDown(gpioB, PI_PUD_UP);
   gpioSetPullUpDown(gpioC, PI_PUD_UP);
   /* monitor encoder level changes */

   gpioSetAlertFuncEx(gpioA, _pulseExA, this);
   gpioSetAlertFuncEx(gpioB, _pulseExB, this);
   gpioSetAlertFuncEx(gpioC, _pulseExC, this);
}

void re_decoder::re_cancel(void)
{
   gpioSetAlertFuncEx(mygpioA, 0, this);
   gpioSetAlertFuncEx(mygpioB, 0, this);
   gpioSetAlertFuncEx(mygpioC, 0, this);
}

