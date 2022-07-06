import socket
import sys


#def		main():
url=sys.argv[1]
print(socket.gethostbyname(url))
sys.exit(0)
#	return socket.gethostbyname(url)