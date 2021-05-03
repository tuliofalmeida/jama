import socket
import threading
import time
import numpy as np
import csv
from threading import Lock

#-------------------------------------------------
#Variables to be edited
data_name = 'Data_1.txt'
on_time = 120
frequency = 75
ip1 = '192.168.137.100' #edit the IP of device 1
ip2 = '192.168.137.101' #edit the IP of device 2
port = 4000
#-------------------------------------------------

data = [[],[],[],[],[],[],[],[]]
dataTemp = [[],[],[],[],[],[],[],[]]
data_time = [[],[],[],[],[],[],[],[]]
data_lock = Lock()
current_milli_time = lambda: int(round(time.time() * 1000))

def clientTCP(HOST,PORT,indEsp):
    tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    dest = (HOST, PORT)
    tcp.connect(dest)
    print ('To quit CTRL+X\n' + HOST)
    time.sleep(10)
    print("Started sending ",indEsp)
    tcp.send (bytes('1?' + str(on_time) + ',' + str(frequency), 'utf-8'))
    tempo[indEsp].append(current_milli_time()) 
    tempoInicio = current_milli_time()
    while True:
        dataTemp[indEsp] = tcp.recv(64000)
        data[indEsp].append(dataTemp[indEsp])
        if ((current_milli_time()-tempoInicio)/1000 > on_time):
            print("Sending is finished")

    tcp.close()

def worker1(message):
    clientTCP(ip1,port,0) 

def worker2(message):
    clientTCP(ip2,port,1) 

t1 = threading.Thread(target=worker1,args=("Thread being executed",));t1.start()
t2 = threading.Thread(target=worker2,args=("Thread being executed ",));t2.start()

time.sleep(on_time+60)

with open(("Data"+data_name), "w") as output:
    output.write(str(data))

with open(("DataTime"+data_name), "w") as output:
    output.write(str(data_time))