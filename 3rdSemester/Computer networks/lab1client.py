import socket
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
msg = "1 2 3 4 5 6"
s.sendto(str.encode(msg),("172.30.112.43",1239))
msg, addr = s.recvfrom(127)                 
print(msg.decode()) 
 
 