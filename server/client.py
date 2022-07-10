import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

message = "teste".encode('ascii')

s.sendto(message, ('localhost', 8080))

s.close()