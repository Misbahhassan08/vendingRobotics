import time
import pigpio
import rotary_encoder
import wavePWM


res = 10 # resolution of getting encoder values
speed = 0.1
freq = 8000 # 20KHz
d = 0
debug = 1
_pwm = 18 # sv pin connected to gpio 13 - ok
_dir = 12 # F/R - ok
_BRK = 19 # BRK - ok
_EN = 26  # EN - ok

_Encoder1 = 27 # HU connected gpio 27 - ok 
_Encoder2 = 22 # HV connected to gpio 22 - ok
_Encoder3 = 23 # HW connected to gpio 23 - ok

#COM connected to GND of PI - ok


if __name__ == "__main__":
   
   def callback():
      global pos
      #print("pos={}".format(pos))
   pos = 0
   pi = pigpio.pi()
   pi.set_mode(_pwm, pigpio.OUTPUT)
   pi.set_mode(_dir, pigpio.OUTPUT)
   pi.set_mode(_BRK, pigpio.OUTPUT)
   pi.set_mode(_EN, pigpio.OUTPUT)

   pi.write(_EN, 0)
   pi.write(_BRK, 1)
   #decoder = rotary_encoder.decoder(pi,res, _Encoder1 , _Encoder2 ,_Encoder3,callback )
   pwm = wavePWM.PWM(pi, 100)
   pwm.set_frequency(freq)
   if d:
      pi.write(_dir, 1)
   else:
      pi.write(_dir, 0)
   try:
      pwm.set_frequency(freq)
      pwm.set_pulse_length_in_fraction(_pwm,speed)
      pwm.update()
      while 1:
         #pos = decoder.pos
         if debug:
            #print(decoder.pos)
            pass
   except KeyboardInterrupt:
       pwm.set_frequency(0)
       pwm.set_pulse_length_in_fraction(_pwm, 0.0)
       pwm.update()
       #decoder.cancel()
       pi.stop()
       pass        # Go to next line
   

   
