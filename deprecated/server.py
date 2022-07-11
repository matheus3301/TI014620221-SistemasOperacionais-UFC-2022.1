import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.bind(('localhost', 7777))

while (True):
    message, address = s.recvfrom(1024)
    print(message.decode('ascii'))
