import time
from time import strftime

def main():
	try:
		currentTimeLine = strftime("%H", time.localtime())
		print currentTimeLine

		ct=(int(currentTimeLine[0])*10)+(int(currentTimeLine[1]))
		#a=int(currentTimeLine[0]
		print ct
		print currentTimeLine[0]
		print currentTimeLine[1]
	finally:
		print 'end'
if __name__ == '__main__':
	main()
