from socket import *
import random
import sys


# Create a UDP socket
# Notice the use of SOCK_DGRAM for UDP packets
serverSocket = socket(AF_INET, SOCK_DGRAM)
# Assign IP address and port number to socket
serverSocket.bind(("", 12000))
print ("ready to recive: ")
messageR = "PONG"
while True:
	# Generate random number in the range of 0 to 10
	rand = random.randint(0, 10)
	# Receive the client packet along with the address it is coming from
	message, address = serverSocket.recvfrom(1024)
	print (message)
	# If rand is less is than 3, we consider the packet lost and do not respond
	if rand < 3:
		print ("lost packet sim")
		continue
	elif rand > 3:
		serverSocket.sendto(messageR.encode(), address)
	# Otherwise, the server responds
