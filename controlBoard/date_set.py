import boardControlLib as b
import sys
import datetime
import calendar

board = b.BoardControlLib("COM11")

print
print "Current board time:", datetime.datetime.utcfromtimestamp(board.get_rtc_time())
print
print "Current computer time:", datetime.datetime.now()
print
print "Update board to computer time? (y/n)",

line = sys.stdin.readline()

if line.strip() == "y":
	print "Setting board time..."
	board.set_rtc_time(calendar.timegm(datetime.datetime.now().timetuple()))
	print "Done!"
else:
	print "Aborting..."