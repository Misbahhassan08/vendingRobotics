#!/usr/bin/env python

import pigpio
import time

class decoder:

   """Class to decode mechanical rotary encoder pulses."""

   def __init__(self, pi,res, gpioA, gpioB, gpioC, callback):
      self.pi = pi
      self.res = res
      self.gpioA = gpioA
      self.gpioB = gpioB
      self.gpioC = gpioC
      self.callback = callback
      self.CW = 1
      self.CCW = -1
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

      self.cbA = self.pi.callback(gpioA, pigpio.EITHER_EDGE, self._pulse)
      self.cbB = self.pi.callback(gpioB, pigpio.EITHER_EDGE, self._pulse)
      self.cbC = self.pi.callback(gpioC, pigpio.EITHER_EDGE, self._pulse)
 
   def _pulse(self, gpio, level, tick):
      if self.lastGpio == gpio: # debouce detected
         pass
      else:
         if gpio == self.gpioA:
            print('A, {} : {} , {}, {}'.format(level, self.pi.read(self.gpioA),
                                          self.pi.read(self.gpioB),
                                          self.pi.read(self.gpioC)))
         elif gpio == self.gpioB:
            print('B, {} : {} , {}, {}'.format(level, self.pi.read(self.gpioA),
                                          self.pi.read(self.gpioB),
                                          self.pi.read(self.gpioC)))
         elif gpio == self.gpioC:
            print('C, {} : {} , {}, {}'.format(level, self.pi.read(self.gpioA),
                                          self.pi.read(self.gpioB),
                                          self.pi.read(self.gpioC)))
         self.lastGpio = gpio
         time.sleep(0.01)
         
         
         
            



   def cancel(self):

      """
      Cancel the rotary encoder decoder.
      """

      self.cbA.cancel()
      self.cbB.cancel()
      self.cbC.cancel()



