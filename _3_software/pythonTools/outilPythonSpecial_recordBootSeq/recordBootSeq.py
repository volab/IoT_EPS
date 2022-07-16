# cc0 J.soranzo
# 27/10/2021
# module recordBootSeq.py
# activer l'environnement conda test
# conda activate test
# conda env creat -f envCondaTest.yml


import serial
import serial.tools.list_ports
from time import sleep, strftime
import signal
import sys
from threading import Event

exit = Event()

""" def signal_handler(sig, frame):
    global file
    print('You pressed Ctrl+C!')
    file.close()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler) """

def quit(signo, _frame):
    print("Interrupted by %d, shutting down" % signo)
    exit.set()



for sig in ('TERM', 'INT'):
    signal.signal(getattr(signal, 'SIG'+sig), quit);


IOEPS_COM_PORT = "COM4"

print("*"*80)
print("Records boot sequence at serial {}".format(IOEPS_COM_PORT) )
print("*"*80)
ser=serial.Serial()
ser.baudrate=115200
ser.port=IOEPS_COM_PORT
listP = []

while (not( IOEPS_COM_PORT in listP )):
    ports = serial.tools.list_ports.comports()
    listP = [p.name for p in ports]
    print("wait")
    sleep(0.3)

# for p in ports:
#     print(p)
#     print ("{}".format(p.name))

# print("List des ports : {}".format(listP))

# if IOEPS_COM_PORT in listP:
#     print("Le port est dans la liste")
# else:
#     print("Le port n'est pas dans la liste")

# for port, desc, hwid in sorted(ports):
#         print("{}: {} [{}]".format(port, desc, hwid))
        
# print(list(serial.tools.list_ports.comports()))

print("Try to open serial")
while( not ser.is_open  ):
    try:
        ser.open()
        print("Serial is open and record")
    except serial.serialutil.SerialException:
        print("Serial not open")
        sys.exit(0)

filename= "bootSep_ioteps_" + strftime("%Y%m%d-%H%M%S") + ".txt"

file = open(filename, 'wb')

while not exit.is_set():
    if (ser.inWaiting() ):
        s=ser.readline()
        ligne=s
        #ligne=s.decode('cp037').replace('\r\n','')
        #print(ligne+"\r")
        file.write(ligne)
    else:
        exit.wait(0.1)

file.close()
print("end recording")

#exit with ctrl+c
