#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include <stdint.h>

typedef void (*re_decoderCB_t)(int);

class re_decoder
{
   int mygpioA, mygpioB, mygpioC, levA, levB, levC, lastGpio, posi;

   re_decoderCB_t mycallback;

   void _pulseA(int gpio, int level, uint32_t tick);
   void _pulseB(int gpio, int level, uint32_t tick);
   void _pulseC(int gpio, int level, uint32_t tick);

   /* Need a static callback to link with C. */
   static void _pulseExA(int gpio, int level, uint32_t tick, void *user);
   static void _pulseExB(int gpio, int level, uint32_t tick, void *user);
   static void _pulseExC(int gpio, int level, uint32_t tick, void *user);

   public:

   re_decoder(int gpioA, int gpioB, int gpioC, re_decoderCB_t callback);
   /*
      This function establishes a rotary encoder on gpioA and gpioB.

      When the encoder is turned the callback function is called.
   */

   void re_cancel(void);
   /*
      This function releases the resources used by the decoder.
   */
};

#endif
