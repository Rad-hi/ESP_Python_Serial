#! /usr/bin/env python3

import serial
import time


MAX_BUFF_LEN = 255
SETUP 		 = False
port 		 = None

prev = time.time()
while(not SETUP):
	try:
		# 					 Serial port(windows-->COM), baud rate, timeout msg
		port = serial.Serial("/dev/ttyUSB0", 115200, timeout=1)

	except: # Bad way of writing excepts (always know your errors)
		if(time.time() - prev > 2): # Don't spam with msg
			print("No serial detected, please plug your uController")
			prev = time.time()

	if(port is not None): # We're connected
		SETUP = True


# read one char (default)
def read_ser(num_char = 1):
	string = port.read(num_char)
	return string.decode()

# Write whole strings
def write_ser(cmd):
	cmd = cmd + '\n'
	port.write(cmd.encode())

# Super loop
while(1):
	string = read_ser(MAX_BUFF_LEN)
	if(len(string)):
		print(string)

	cmd = input() # Blocking, there're solutions for this ;)
	if(cmd):
		write_ser(cmd)
