# activer l'environnement conda test
# conda activate test
# conda env creat -f envCondaTest.yml


import serial
import serial.tools.list_ports



IOEPS_COM_PORT = "COM4"

print("*"*80)
print("Records boot sequence at serial {}".format(IOEPS_COM_PORT) )
print("*"*80)
ser=serial.Serial()
ser.baudrate=115200
ser.port='COM4'

ports = serial.tools.list_ports.comports()
print(ports)

for p in ports:
    print(p)
    print ("{}".format(p.name))
listP = [p.name for p in ports]
print("List des ports : {}".format(listP))

if IOEPS_COM_PORT in listP:
    print("Le port est dans la liste")
else:
    print("Le port n'est pas dans la liste")

# for port, desc, hwid in sorted(ports):
#         print("{}: {} [{}]".format(port, desc, hwid))
        
# print(list(serial.tools.list_ports.comports()))

print("Try to open serial")
try:
    ser.open()
except serial.serialutil.SerialException:
    print("Serial not open")

print("Serial is open ? {}".format(ser.is_open) )
ser.close()
