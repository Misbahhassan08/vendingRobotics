#!/usr/bin/env python

import pigpio

class decoder:

   """Class to decode mechanical rotary encoder pulses."""

   def __init__(self, pi,res, gpioA, gpioB, gpioC, callback):
      self.pi = pi
      self.res = res
      self.gpioA = gpioA
      self.gpioB = gpioB
      self.gpioC = gpioC
      self.callback = callback

      self.levA = 0
      self.levB = 0
      self.levC = 0

      self.lastGpio = None
      self.count = 0

      self.pi.set_mode(gpioA, pigpio.INPUT)
      self.pi.set_mode(gpioB, pigpio.INPUT)
      self.pi.set_mode(gpioC, pigpio.INPUT)

      self.pi.set_pull_up_down(gpioA, pigpio.PUD_UP)
      self.pi.set_pull_up_down(gpioB, pigpio.PUD_UP)
      self.pi.set_pull_up_down(gpioC, pigpio.PUD_UP)

      self.cbA = self.pi.callback(gpioA, pigpio.EITHER_EDGE, self._pulseA)
      self.cbB = self.pi.callback(gpioB, pigpio.EITHER_EDGE, self._pulseB)
      self.cbC = self.pi.callback(gpioC, pigpio.EITHER_EDGE, self._pulseC)
 
   def _pulseA(self, gpio, level, tick):
      if self.lastGpio == gpio: # debouce detected
         pass
      else:
         if self.gpioA == self.gpioB:
            if self.count < self.res:
               pass
            else:
               self.callback(1)
               self.count = 0
            pass
         else:
            if self.count < self.res:
               pass
            else:
               self.callback(-1)
               self.count = 0
         self.lastGpio = gpio
         self.count = self.count + 1
         
         
            
   def _pulseB(self, gpio, level, tick):
      if self.lastGpio == gpio: # debouce detected
         pass
      else:
         if self.gpioB == self.gpioC:
            if self.count < self.res:
               pass
            else:
               self.callback(1)
               self.count = 0
            pass
         else:
            if self.count < self.res:
               pass
            else:
               self.callback(-1)
               self.count = 0
         self.lastGpio = gpio
         self.count = self.count + 1

   def _pulseC(self, gpio, level, tick):
      if self.lastGpio == gpio: # debouce detected
         pass
      else:
         if self.gpioC == self.gpioA:
            if self.count < self.res:
               pass
            else:
               self.callback(1)
               self.count = 0
            pass
         else:
            if self.count < self.res:
               pass
            else:
               self.callback(-1)
               self.count = 0
         self.lastGpio = gpio
         self.count = self.count + 1


   def cancel(self):

      """
      Cancel the rotary encoder decoder.
      """

      self.cbA.cancel()
      self.cbB.cancel()
      self.cbC.cancel()



