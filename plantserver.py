import sys
import SimpleHTTPServer
import socket
import os
import time

class Server(object):
    def __init__(self, host, port):
        self.host = host
        self.port = port
        #self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    def close_connection(self):
        self.sock.shutdown(socket.SHUT_RDWR)
        sys.exit(0)

    def poll_sensors(self, ips):
        all_data = []
        for addr in ips:
            self.sock = socket.create_connection((addr, 8080))
            data = self.sock.recv(4096)
            time.sleep(2)
            all_data.append((addr, data))
            self.sock.close()

        return all_data


if __name__ == "__main__":
    port = 8080
    host = ''

    svr = Server(host, port)

    ips = ["192.168.1.101"]
    while True:
        c = raw_input("Poll? ")
        if 'n' in c:
            sys.exit(0)
        else:
           # svr.start_connection()
            data = svr.poll_sensors(ips)
            print(data)
            #svr.close_connection()



