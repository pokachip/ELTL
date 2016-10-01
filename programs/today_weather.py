import kma
import time

lat = 55
lon = 123
wcode = 0

data=kma.getWeather(lat,lon)
for item in data:
	day = int(item[1])
	hour = int(item[0])
	if day == 0 and hour >=12:
		wcode = kma.getWeatherCode(item[2])
		break

print item[0],item[1],wcode

