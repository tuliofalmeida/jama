import socket
import threading
import time
import numpy as np
import csv
from threading import Lock
"""
DONE BY: Tulio F. Almeida and André Dantas

MIT License

Copyright (c) 2021 Tulio F. Almeida

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""
#_________________________________________________________________________
# Variables to be edited
data_name = 'Data_1.txt' # File name
on_time = 120 # Acquisition time
frequency = 75 # Acquisition frequency (must be the same as ESP)
ip1 = '192.168.137.100' # edit the IP of device 1
ip2 = '192.168.137.101' # edit the IP of device 2
gate = 4000 # If you change the gate here, you must change on ESP32 too.
#_________________________________________________________________________

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
    clientTCP(ip1,gate,0) 

def worker2(message):
    clientTCP(ip2,gate,1) 

t1 = threading.Thread(target=worker1,args=("Thread being executed",));t1.start()
t2 = threading.Thread(target=worker2,args=("Thread being executed ",));t2.start()

time.sleep(on_time+60)

with open(("Data"+data_name), "w") as output:
    output.write(str(data))

with open(("DataTime"+data_name), "w") as output:
    output.write(str(data_time))