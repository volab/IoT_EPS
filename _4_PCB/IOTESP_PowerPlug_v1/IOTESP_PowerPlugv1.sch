EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L wemos_mini:WeMos_mini U1
U 1 1 5CAC789D
P 5600 3600
F 0 "U1" H 5600 4237 60  0000 C CNN
F 1 "WeMos_mini" H 5600 4131 60  0000 C CNN
F 2 "IOTESP_PowerPlug_v1:D1_mini_board" H 6150 2900 60  0001 C CNN
F 3 "" H 6150 2900 60  0000 C CNN
	1    5600 3600
	1    0    0    -1  
$EndComp
$Comp
L arduino_nano:Arduino_Nano A1
U 1 1 5CAC83BE
P 8700 2850
F 0 "A1" H 8725 4187 60  0000 C CNN
F 1 "Arduino_Nano" H 8725 4081 60  0000 C CNN
F 2 "IOTESP_PowerPlug_v1:arduino_nano" H 8700 2850 60  0001 C CNN
F 3 "" H 8700 2850 60  0000 C CNN
	1    8700 2850
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q1
U 1 1 5CAC9B58
P 4400 2100
F 0 "Q1" H 4606 2146 50  0000 L CNN
F 1 "2N7000" H 4606 2055 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 4600 2025 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 4400 2100 50  0001 L CNN
	1    4400 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 5CACEF40
P 6250 1700
F 0 "J?" H 6358 1981 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6358 1890 50  0000 C CNN
F 2 "" H 6250 1700 50  0001 C CNN
F 3 "~" H 6250 1700 50  0001 C CNN
	1    6250 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5CAD33B1
P 5250 1450
F 0 "D?" H 5243 1666 50  0000 C CNN
F 1 "LED" H 5243 1575 50  0000 C CNN
F 2 "" H 5250 1450 50  0001 C CNN
F 3 "~" H 5250 1450 50  0001 C CNN
	1    5250 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5CAD3F84
P 5550 1950
F 0 "R?" H 5620 1996 50  0000 L CNN
F 1 "R" H 5620 1905 50  0000 L CNN
F 2 "" V 5480 1950 50  0001 C CNN
F 3 "~" H 5550 1950 50  0001 C CNN
	1    5550 1950
	1    0    0    -1  
$EndComp
$EndSCHEMATC
