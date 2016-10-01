#!/usr/bin/env python
import kma
import max7219.led as led
import time
from time import strftime
from max7219.font import proportional, SINCLAIR_FONT, TINY_FONT, CP437_FONT
from random import randrange

lat = 37.38
lon = 126.55
wcode = 0

data=kma.getWeather(lat,lon)
for item in data:
	day=int(item[1])
	hour=int(item[0])
	if day == 0 :
		wcode = kma.getWeatherCode(item[7])
		break

currentTime = strftime("%H", time.localtime())
timeh= (int(currentTime[0])*10)+(int(currentTime[1]))

device = led.matrix(cascaded=1)
brightMax = 0
try:
	while True:
		
		if timeh >= 7 and timeh <= 22:
			brightMax=10
		else:
			brightMax=3  
			
		if wcode == 1 :
			device.brightness(brightMax)
			device.letter(0, ord('0'))
			time.sleep(1)
			for _ in range(3):
				for intensity in xrange(brightMax):
					device.brightness(intensity)
					time.sleep(0.7)
			device.brightness(brightMax)
			device.letter(0, ord('1'))
			time.sleep(1)
			for _ in range(3):
				for intensity in xrange(brightMax):
					device.brightness(intensity)
					time.sleep(0.7)
		elif wcode == 2 :
			device.letter(0, ord('4'))
			device.brightness(brightMax)
			time.sleep(1)
			for _ in range(3):
				for column in range(8):
					device.rotate_right(redraw=True)
					time.sleep(1)
		elif wcode == 3 :
			device.letter(0, ord('5'))
			device.brightness(brightMax)
			time.sleep(1)
			for _ in range(3):
				for column in range(8) :
					device.rotate_right(redraw=True)
					time.sleep(1)
		elif wcode == 4 :
			device.letter(0, ord('6'))
			device.brightness(brightMax)
			time.sleep(1)
			for _ in range(3):
				for row in range(8):
    					device.rotate_right(redraw=True)
					time.sleep(1)
		elif wcode == 5 :
			device.brightness(brightMax)
			device.letter(0, ord('A'))
			time.sleep(0.8)
			device.letter(0, ord('B'))
			time.sleep(0.8)
			device.letter(0, ord('C'))
			time.sleep(0.8)
			device.letter(0, ord('D'))
			time.sleep(0.8)
			device.letter(0, ord('E'))
			time.sleep(0.8)
			device.letter(0, ord('F'))
			time.sleep(0.8)
			device.letter(0, ord('G'))
			time.sleep(0.8)
			device.letter(0, ord('H'))
			time.sleep(0.8)
		elif wcode == 6 :
			device.brightness(brightMax)
			device.letter(0, ord('I'))
			time.sleep(0.8)
			device.letter(0, ord('J'))
			time.sleep(0.8)
			device.letter(0, ord('K'))
			time.sleep(0.8)
			device.letter(0, ord('L'))
			time.sleep(0.8)
			device.letter(0, ord('M'))
			time.sleep(0.8)
			device.letter(0, ord('N'))
			time.sleep(0.8)
			device.letter(0, ord('O'))
			time.sleep(0.8)
			device.letter(0, ord('P'))
			time.sleep(0.8)

		elif wcode == 7 :
			device.brightness(brightMax) 
			device.letter(0, ord('Q'))
			time.sleep(0.8)
			device.letter(0, ord('R'))
			time.sleep(0.8)
			device.letter(0, ord('S'))
			time.sleep(0.8)
			device.letter(0, ord('T'))
			time.sleep(0.8)

except KeyboardInterrupt:
	device.clear()



