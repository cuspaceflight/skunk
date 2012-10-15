EESchema Schematic File Version 2  date Mon 15 Oct 2012 14:43:06 BST
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:skunk-cache
EELAYER 27 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "SKUNK WIRING HARNESS AND SCHEMATIC"
Date "15 oct 2012"
Rev ""
Comp "CAMBRIDGE UNIVERSITY SPACE FLIGHT - dwt27"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2600 2850 0    60   ~ 0
0V_SENSE
Text Label 2600 2750 0    60   ~ 0
0V
Text Label 9550 1250 0    60   ~ 0
+16V
Text Label 13100 8600 0    60   ~ 0
0V
Text Label 11250 9000 0    60   ~ 0
LCD_DATA
Text Label 11250 9100 0    60   ~ 0
3V3
Text Label 10150 8250 0    60   ~ 0
+5V
Text Label 10900 8850 0    60   ~ 0
0V
$Comp
L SPST SW?
U 1 1 50638E78
P 10500 10350
F 0 "SW?" H 10500 10450 70  0000 C CNN
F 1 "KEYSW" H 10500 10250 70  0000 C CNN
	1    10500 10350
	1    0    0    -1  
$EndComp
Text Label 14600 10050 0    60   ~ 0
R4
Text Label 14600 9800 0    60   ~ 0
R3
Text Label 14600 9550 0    60   ~ 0
R2
Text Label 14600 9300 0    60   ~ 0
R1
Text Label 14800 9200 0    60   ~ 0
C1
Text Label 15150 9100 0    60   ~ 0
C2
Text Label 15500 9000 0    60   ~ 0
C3
$Comp
L SW_PUSH_SMALL SW?
U 1 1 5063882A
P 14800 9400
F 0 "SW?" H 14950 9510 30  0000 C CNN
F 1 "1" H 14800 9321 30  0000 C CNN
	1    14800 9400
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 5063886A
P 15500 10150
F 0 "SW?" H 15650 10260 30  0000 C CNN
F 1 "#" H 15500 10071 30  0000 C CNN
	1    15500 10150
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 50638866
P 15150 10150
F 0 "SW?" H 15300 10260 30  0000 C CNN
F 1 "0" H 15150 10071 30  0000 C CNN
	1    15150 10150
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 50638863
P 14800 10150
F 0 "SW?" H 14950 10260 30  0000 C CNN
F 1 "*" H 14800 10071 30  0000 C CNN
	1    14800 10150
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 50638860
P 15500 9900
F 0 "SW?" H 15650 10010 30  0000 C CNN
F 1 "9" H 15500 9821 30  0000 C CNN
	1    15500 9900
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 5063885C
P 15150 9900
F 0 "SW?" H 15300 10010 30  0000 C CNN
F 1 "8" H 15150 9821 30  0000 C CNN
	1    15150 9900
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 5063885A
P 14800 9900
F 0 "SW?" H 14950 10010 30  0000 C CNN
F 1 "7" H 14800 9821 30  0000 C CNN
	1    14800 9900
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 50638853
P 15500 9650
F 0 "SW?" H 15650 9760 30  0000 C CNN
F 1 "6" H 15500 9571 30  0000 C CNN
	1    15500 9650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 50638851
P 15150 9650
F 0 "SW?" H 15300 9760 30  0000 C CNN
F 1 "5" H 15150 9571 30  0000 C CNN
	1    15150 9650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 5063884D
P 14800 9650
F 0 "SW?" H 14950 9760 30  0000 C CNN
F 1 "4" H 14800 9571 30  0000 C CNN
	1    14800 9650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 5063884B
P 15500 9400
F 0 "SW?" H 15650 9510 30  0000 C CNN
F 1 "3" H 15500 9321 30  0000 C CNN
	1    15500 9400
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 50638847
P 15150 9400
F 0 "SW?" H 15300 9510 30  0000 C CNN
F 1 "2" H 15150 9321 30  0000 C CNN
	1    15150 9400
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K?
U 1 1 50637AB3
P 12600 9000
F 0 "K?" V 12550 9000 50  0000 C CNN
F 1 "LCD" H 12600 8800 40  0000 C CNN
	1    12600 9000
	1    0    0    -1  
$EndComp
$Comp
L SPEAKER SP?
U 1 1 50637AA3
P 13700 8500
F 0 "SP?" H 13600 8750 70  0000 C CNN
F 1 "SPEAKER" H 13600 8250 70  0000 C CNN
	1    13700 8500
	1    0    0    -1  
$EndComp
$Comp
L POT RV?
U 1 1 50637A55
P 10850 8500
F 0 "RV?" H 10850 8400 50  0000 C CNN
F 1 "POT" H 10850 8500 50  0000 C CNN
	1    10850 8500
	0    -1   -1   0   
$EndComp
$Comp
L DB25 J?
U 1 1 50636BD9
P 9200 9450
F 0 "J?" H 9250 10800 70  0000 C CNN
F 1 "DB25_PERIPHS" H 8950 8100 70  0000 C CNN
	1    9200 9450
	-1   0    0    -1  
$EndComp
$Comp
L DB25 J?
U 1 1 50636AAF
P 7200 9450
F 0 "J?" H 7250 10800 70  0000 C CNN
F 1 "DB25_PERIPHS" H 7000 8100 70  0000 C CNN
	1    7200 9450
	1    0    0    -1  
$EndComp
$Comp
L CONN_14 P?
U 1 1 50636A9D
P 5450 7850
F 0 "P?" V 5420 7850 60  0000 C CNN
F 1 "CONN_ARD_PERIPHS" V 5530 7850 60  0000 C CNN
	1    5450 7850
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 K?
U 1 1 50636A67
P 7600 1800
F 0 "K?" V 7550 1800 50  0000 C CNN
F 1 "CONN_ARD_RS232" H 7400 1500 40  0000 C CNN
	1    7600 1800
	-1   0    0    -1  
$EndComp
Text Label 8050 1800 0    60   ~ 0
RX
Text Label 9550 1050 0    60   ~ 0
0V_SENSE
Text Label 10000 1450 0    60   ~ 0
RX
Text Label 10000 1550 0    60   ~ 0
TX
Text Label 9550 950  0    60   ~ 0
0V
Text Label 2100 3400 0    60   ~ 0
0V
Text Label 2100 3200 0    60   ~ 0
+12V
$Comp
L DB9 J?
U 1 1 506362ED
P 15500 1150
F 0 "J?" H 15500 1700 70  0000 C CNN
F 1 "DB9_FLOWMETER" H 15500 600 70  0000 C CNN
	1    15500 1150
	1    0    0    -1  
$EndComp
Text Label 8050 2000 0    60   ~ 0
TX
$Comp
L DB9 J?
U 1 1 50636112
P 8900 1800
F 0 "J?" H 8900 2350 70  0000 C CNN
F 1 "DB9_ARD_BOX" H 8650 1200 70  0000 C CNN
	1    8900 1800
	1    0    0    -1  
$EndComp
$Comp
L DB9 J?
U 1 1 506360FD
P 9250 1800
F 0 "J?" H 9250 2350 70  0000 C CNN
F 1 "DB9_ARD_BOX" H 9000 1200 70  0000 C CNN
	1    9250 1800
	-1   0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 50635E8C
P 2750 3300
F 0 "P?" V 2700 3300 40  0000 C CNN
F 1 "CONN_ARD_POWER" H 2550 3500 40  0000 C CNN
	1    2750 3300
	1    0    0    1   
$EndComp
Text Label 2800 2500 2    60   ~ 0
+16V
Text Label 1950 2250 2    60   ~ 0
+12V
$Comp
L GND #PWR?
U 1 1 50635463
P 800 2600
F 0 "#PWR?" H 800 2600 30  0001 C CNN
F 1 "GND" H 800 2530 30  0001 C CNN
	1    800  2600
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 5063538D
P 900 1900
F 0 "P?" V 850 1900 40  0000 C CNN
F 1 "CONN_BAT_1" V 1050 1900 40  0000 C CNN
	1    900  1900
	0    -1   -1   0   
$EndComp
$Comp
L CONN_2 P?
U 1 1 506352C8
P 900 1500
F 0 "P?" V 850 1500 40  0000 C CNN
F 1 "CONN_BAT_1" V 1050 1500 40  0000 C CNN
	1    900  1500
	0    -1   1    0   
$EndComp
$Comp
L BATTERY BT?
U 1 1 5063529A
P 900 800
F 0 "BT?" H 900 1000 50  0000 C CNN
F 1 "BAT1" H 900 610 50  0000 C CNN
	1    900  800 
	-1   0    0    -1  
$EndComp
Text Notes 2000 1800 0    60   ~ 0
BOOST SWITCHER\nMODULE
Text Label 2050 2050 0    60   ~ 0
Vin
Text Label 2250 2050 0    60   ~ 0
GND
Text Label 2500 2050 0    60   ~ 0
Vout
$Comp
L DB25 J?
U 1 1 506EE73C
P 8750 9450
F 0 "J?" H 8800 10800 70  0000 C CNN
F 1 "DB25_PERIPHS" H 8650 8100 70  0000 C CNN
	1    8750 9450
	1    0    0    -1  
$EndComp
$Comp
L DB25 J?
U 1 1 506EE74B
P 7650 9450
F 0 "J?" H 7700 10800 70  0000 C CNN
F 1 "DB25_PERIPHS" H 7450 8100 70  0000 C CNN
	1    7650 9450
	-1   0    0    -1  
$EndComp
$Comp
L FUSE F?
U 1 1 506F0508
P 1350 2250
F 0 "F?" H 1450 2300 40  0000 C CNN
F 1 "FUSE 2A" H 1300 2100 40  0000 C CNN
	1    1350 2250
	1    0    0    -1  
$EndComp
$Comp
L FUSE F?
U 1 1 506F151A
P 3800 750
F 0 "F?" H 3900 800 40  0000 C CNN
F 1 "FUSE 1A" H 3750 600 40  0000 C CNN
	1    3800 750 
	1    0    0    -1  
$EndComp
Text Label 3250 750  0    60   ~ 0
+16V
Text Label 3300 1700 0    60   ~ 0
0V
$Comp
L C C?
U 1 1 506F1B91
P 4150 1150
F 0 "C?" H 4200 1250 50  0000 L CNN
F 1 "100nF" H 4200 1050 50  0000 L CNN
	1    4150 1150
	1    0    0    -1  
$EndComp
$Comp
L ZENER D?
U 1 1 506F1D24
P 4600 950
F 0 "D?" H 4600 1050 50  0000 C CNN
F 1 "20V" H 4600 850 40  0000 C CNN
	1    4600 950 
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 506F1D33
P 4600 1450
F 0 "R?" V 4680 1450 50  0000 C CNN
F 1 "1k" V 4600 1450 50  0000 C CNN
	1    4600 1450
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 506F22D9
P 4900 1450
F 0 "C?" H 4950 1550 50  0000 L CNN
F 1 "47nF" H 4950 1350 50  0000 L CNN
	1    4900 1450
	1    0    0    -1  
$EndComp
$Comp
L THYRISTOR T?
U 1 1 506F2A69
P 5300 1100
F 0 "T?" H 5200 1200 40  0000 C CNN
F 1 "THYRISTOR" H 5300 1000 40  0000 C CNN
	1    5300 1100
	0    -1   1    0   
$EndComp
Text Notes 1150 1750 0    60   ~ 0
POWER INPUT\n
Text Notes 3700 1850 0    60   ~ 0
OVERVOLTAGE CROWBAR
$Comp
L DIODE D?
U 1 1 506F2E41
P 1650 2450
F 0 "D?" H 1650 2550 40  0000 C CNN
F 1 "DIODE" H 1650 2350 40  0000 C CNN
	1    1650 2450
	0    -1   -1   0   
$EndComp
Text Notes 1350 2650 0    60   ~ 0
IDIOT\nDIODE
Text Notes 14700 1900 0    60   ~ 0
FLOWMETER CONNECTION
Text Notes 7450 7950 0    60   ~ 0
PERIPHERAL CONNECTION CABLE
Text Notes 11150 7900 0    60   ~ 0
PERIPHERALS
Wire Wire Line
	9500 1250 15050 1250
Connection ~ 9500 1250
Wire Wire Line
	9500 1250 9500 1150
Wire Wire Line
	9500 1150 9200 1150
Wire Wire Line
	9200 1150 9200 750 
Wire Wire Line
	9300 1050 15050 1050
Wire Wire Line
	9400 950  15050 950 
Wire Wire Line
	5600 8200 5600 9750
Wire Wire Line
	5400 8200 5400 9650
Wire Wire Line
	4800 8200 4800 10350
Wire Wire Line
	5100 8200 5100 8850
Wire Wire Line
	4900 8200 4900 8250
Wire Wire Line
	5800 8200 5800 9150
Wire Wire Line
	6100 8350 6750 8350
Wire Wire Line
	6100 8350 6100 8200
Wire Wire Line
	2050 2050 2050 3200
Wire Wire Line
	2050 3200 2400 3200
Wire Wire Line
	13700 9200 14900 9200
Wire Wire Line
	13700 9200 13700 10100
Wire Wire Line
	13700 10100 9800 10100
Wire Wire Line
	9800 10100 9800 8350
Wire Wire Line
	9800 8350 9650 8350
Wire Wire Line
	15400 9550 13350 9550
Wire Wire Line
	13350 9550 13350 9450
Wire Wire Line
	10250 9250 12600 9250
Wire Wire Line
	10250 9250 10250 8950
Wire Wire Line
	10250 8950 9650 8950
Wire Wire Line
	15400 10050 14100 10050
Wire Wire Line
	14100 10050 14100 9950
Wire Wire Line
	14100 9950 9650 9950
Wire Wire Line
	12900 9000 15600 9000
Wire Wire Line
	12900 9000 12900 9550
Wire Wire Line
	12900 9550 9650 9550
Wire Wire Line
	11050 8600 13400 8600
Wire Wire Line
	10950 9850 9650 9850
Connection ~ 10850 8850
Wire Wire Line
	9650 8250 10850 8250
Wire Wire Line
	10700 8500 10250 8500
Wire Wire Line
	10250 8500 10250 8450
Wire Wire Line
	10250 8450 9650 8450
Wire Wire Line
	15250 10250 15250 9100
Connection ~ 15600 9500
Connection ~ 15600 10000
Connection ~ 15250 9500
Connection ~ 15250 10000
Connection ~ 14900 9500
Wire Wire Line
	14900 9200 14900 10250
Connection ~ 14900 9750
Connection ~ 14700 10050
Connection ~ 14700 9550
Connection ~ 15050 10050
Connection ~ 15050 9800
Connection ~ 15050 9550
Connection ~ 15050 9300
Wire Wire Line
	9700 2000 9950 2000
Wire Wire Line
	9950 2000 9950 1550
Wire Wire Line
	5600 9750 6750 9750
Wire Wire Line
	5500 9550 6750 9550
Wire Wire Line
	5900 8950 6750 8950
Wire Wire Line
	6000 8750 6750 8750
Wire Wire Line
	5000 8450 6750 8450
Wire Wire Line
	4900 8250 6750 8250
Wire Wire Line
	4800 10350 6750 10350
Wire Wire Line
	8450 2000 8000 2000
Wire Wire Line
	8000 2000 8000 1900
Wire Wire Line
	8000 1900 7950 1900
Wire Wire Line
	7950 1800 8450 1800
Wire Wire Line
	9950 1550 15050 1550
Wire Wire Line
	8450 1900 8300 1900
Wire Wire Line
	8300 1900 8300 1700
Wire Wire Line
	8300 1700 8450 1700
Wire Wire Line
	1000 1150 1200 1150
Wire Wire Line
	1200 1150 1200 800 
Wire Wire Line
	600  800  600  1150
Wire Wire Line
	600  1150 800  1150
Wire Wire Line
	9850 1450 15050 1450
Wire Wire Line
	5700 9950 6750 9950
Wire Wire Line
	5200 8650 6750 8650
Wire Wire Line
	5100 8850 6750 8850
Wire Wire Line
	5800 9150 6750 9150
Wire Wire Line
	5400 9650 6750 9650
Wire Wire Line
	5300 9850 6750 9850
Wire Wire Line
	9850 1450 9850 1800
Wire Wire Line
	9850 1800 9700 1800
Connection ~ 14700 9800
Connection ~ 14700 9300
Connection ~ 14900 10000
Connection ~ 15250 9750
Connection ~ 15600 9750
Wire Wire Line
	15600 9000 15600 10250
Wire Wire Line
	10850 8850 10850 8750
Wire Wire Line
	9650 9650 10850 9650
Wire Wire Line
	9650 8650 9900 8650
Wire Wire Line
	9900 8650 9900 8050
Wire Wire Line
	9900 8050 13050 8050
Wire Wire Line
	13050 8050 13050 8400
Wire Wire Line
	9650 9750 13000 9750
Wire Wire Line
	13000 9750 13000 9300
Wire Wire Line
	13000 9300 15400 9300
Wire Wire Line
	9650 9150 10000 9150
Wire Wire Line
	10000 9150 10000 9350
Wire Wire Line
	10000 9350 12800 9350
Wire Wire Line
	9650 8750 10650 8750
Wire Wire Line
	10650 8750 10650 9450
Wire Wire Line
	10650 9450 13350 9450
Wire Wire Line
	12600 9250 12600 9650
Wire Wire Line
	12600 9650 13200 9650
Wire Wire Line
	13200 9650 13200 9800
Wire Wire Line
	13200 9800 15400 9800
Wire Wire Line
	6000 8750 6000 8200
Wire Wire Line
	5900 8950 5900 8200
Wire Wire Line
	5000 8450 5000 8200
Wire Wire Line
	5200 8650 5200 8200
Wire Wire Line
	5300 9850 5300 8200
Wire Wire Line
	5500 9550 5500 8200
Wire Wire Line
	5700 9950 5700 8200
Wire Wire Line
	3100 550  3100 2750
Wire Wire Line
	3100 550  9400 550 
Wire Wire Line
	9400 550  9400 950 
Connection ~ 9400 950 
Wire Wire Line
	3200 650  3200 2850
Wire Wire Line
	3200 650  9300 650 
Wire Wire Line
	9300 650  9300 1050
Connection ~ 9300 1050
Wire Wire Line
	3000 750  3000 2500
Wire Notes Line
	1950 1650 1950 2050
Wire Notes Line
	1950 2050 2800 2050
Wire Notes Line
	1950 1650 2800 1650
Wire Wire Line
	2500 2050 2500 2500
Wire Wire Line
	2500 2500 3000 2500
Wire Notes Line
	2800 1650 2800 2050
Wire Wire Line
	8100 8250 8300 8250
Wire Wire Line
	8300 8350 8100 8350
Wire Wire Line
	8100 8450 8300 8450
Wire Wire Line
	8300 8550 8100 8550
Wire Wire Line
	8100 8650 8300 8650
Wire Wire Line
	8300 8750 8100 8750
Wire Wire Line
	8100 8850 8300 8850
Wire Wire Line
	8300 8950 8100 8950
Wire Wire Line
	8100 9050 8300 9050
Wire Wire Line
	8300 9150 8100 9150
Wire Wire Line
	8100 9250 8300 9250
Wire Wire Line
	8300 9350 8100 9350
Wire Wire Line
	8100 9450 8300 9450
Wire Wire Line
	8300 9550 8100 9550
Wire Wire Line
	8100 9650 8300 9650
Wire Wire Line
	8300 9750 8100 9750
Wire Wire Line
	8100 9850 8300 9850
Wire Wire Line
	8300 9950 8100 9950
Wire Wire Line
	8100 10050 8300 10050
Wire Wire Line
	8300 10150 8100 10150
Wire Wire Line
	8100 10250 8300 10250
Wire Wire Line
	8300 10350 8100 10350
Wire Wire Line
	8100 10450 8300 10450
Wire Wire Line
	8300 10550 8100 10550
Wire Wire Line
	8100 10650 8300 10650
Wire Wire Line
	800  2250 800  2600
Connection ~ 800  2500
Connection ~ 2050 2250
Wire Wire Line
	1000 2250 1100 2250
Wire Wire Line
	800  2400 1100 2400
Wire Wire Line
	1100 2400 1100 2750
Connection ~ 800  2400
Wire Wire Line
	800  2450 1050 2450
Wire Wire Line
	1050 2450 1050 2850
Connection ~ 800  2450
Wire Wire Line
	800  2500 1000 2500
Wire Wire Line
	1000 2500 1000 3400
Wire Wire Line
	1000 3400 2400 3400
Wire Wire Line
	3000 750  3550 750 
Wire Wire Line
	9200 750  4050 750 
Wire Wire Line
	4150 1350 4150 1700
Wire Wire Line
	4150 750  4150 950 
Wire Wire Line
	3100 1700 5300 1700
Connection ~ 3100 1700
Connection ~ 4150 1700
Wire Wire Line
	4600 1150 4600 1200
Connection ~ 4150 750 
Wire Wire Line
	4900 1700 4900 1650
Connection ~ 4600 1700
Wire Wire Line
	4600 1200 5150 1200
Wire Wire Line
	4900 1200 4900 1250
Connection ~ 4900 1200
Wire Wire Line
	5300 750  5300 900 
Connection ~ 4600 750 
Wire Wire Line
	5300 1700 5300 1300
Connection ~ 4900 1700
Wire Wire Line
	1050 2850 3200 2850
Wire Wire Line
	1100 2750 3100 2750
Wire Wire Line
	1650 2650 1650 2750
Connection ~ 1650 2750
Wire Wire Line
	1600 2250 2050 2250
Connection ~ 1650 2250
Connection ~ 5300 750 
Text Label 6100 4300 0    60   ~ 0
GND
Text Label 6100 4400 0    60   ~ 0
Vin
Text Label 6100 4500 0    60   ~ 0
+5V
Text Label 6100 4600 0    60   ~ 0
53
Text Label 6100 4700 0    60   ~ 0
9
Text Label 6100 4800 0    60   ~ 0
7
Text Label 6100 4900 0    60   ~ 0
A0
Text Label 6200 5000 0    60   ~ 0
A1
Text Label 7300 4300 0    60   ~ 0
5
Text Label 7300 4400 0    60   ~ 0
37
Text Label 7300 4500 0    60   ~ 0
36
Text Label 7300 4600 0    60   ~ 0
35
Text Label 7300 4700 0    60   ~ 0
34
Text Label 7300 4800 0    60   ~ 0
33
Text Label 7300 4900 0    60   ~ 0
32
Text Label 7300 5000 0    60   ~ 0
31
Wire Wire Line
	4250 4300 6350 4300
Wire Wire Line
	4350 4400 6350 4400
Wire Wire Line
	4850 4600 6350 4600
Wire Wire Line
	5350 4800 6350 4800
Wire Wire Line
	5450 4900 6350 4900
Wire Wire Line
	7250 4400 8150 4400
Wire Wire Line
	7250 4500 8100 4500
Wire Wire Line
	7250 4600 8050 4600
Wire Wire Line
	7250 4700 8000 4700
Wire Wire Line
	7250 4800 8400 4800
Wire Wire Line
	7250 4900 8600 4900
Wire Wire Line
	7250 5000 8800 5000
Text Label 5550 4600 0    60   ~ 0
UART1 RX
Text Label 5550 4700 0    60   ~ 0
UART1 TX
Text Label 5550 4800 0    60   ~ 0
LCD_DATA
Text Label 5550 4900 0    60   ~ 0
FLOWPOT
Text Label 6000 5100 3    60   ~ 0
BATT_IN
Text Label 7500 4300 0    60   ~ 0
KEYSW_IN
Text Label 7500 4400 0    60   ~ 0
R1
Text Label 7500 4500 0    60   ~ 0
R2
Text Label 7500 4600 0    60   ~ 0
R3
Text Label 7500 4700 0    60   ~ 0
R4
Text Label 7500 4800 0    60   ~ 0
C1
Text Label 7500 4900 0    60   ~ 0
C2
Text Label 7500 5000 0    60   ~ 0
C3
Wire Wire Line
	8400 4800 8400 4650
$Comp
L R R?
U 1 1 506F6F28
P 8400 4400
F 0 "R?" V 8480 4400 50  0000 C CNN
F 1 "10k" V 8400 4400 50  0000 C CNN
	1    8400 4400
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 506F6F37
P 8600 4400
F 0 "R?" V 8680 4400 50  0000 C CNN
F 1 "10k" V 8600 4400 50  0000 C CNN
	1    8600 4400
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 506F6F46
P 8800 4400
F 0 "R?" V 8880 4400 50  0000 C CNN
F 1 "10k" V 8800 4400 50  0000 C CNN
	1    8800 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 4900 8600 4650
Wire Wire Line
	8800 5000 8800 4650
Text Label 13100 8400 0    60   ~ 0
SPK
Wire Wire Line
	13050 8400 13400 8400
Text Label 10250 8500 0    60   ~ 0
FLOWPOT
Text Label 9700 10350 0    60   ~ 0
KEYSW
Wire Wire Line
	4850 4600 4850 2350
Wire Wire Line
	4850 2350 6400 2350
Wire Wire Line
	6400 2350 6400 1800
Wire Wire Line
	6400 1800 7200 1800
Wire Wire Line
	4750 4700 4750 2250
Wire Wire Line
	4750 2250 6300 2250
Wire Wire Line
	6300 2250 6300 1700
Wire Wire Line
	6300 1700 7200 1700
Wire Wire Line
	4750 4700 6350 4700
$Comp
L CONN_2 P?
U 1 1 506F9349
P 3050 3300
F 0 "P?" V 3000 3300 40  0000 C CNN
F 1 "CONN_2" V 3100 3300 40  0000 C CNN
	1    3050 3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3400 3400 4250 3400
Wire Wire Line
	4250 3400 4250 4300
Wire Wire Line
	3400 3200 4350 3200
Wire Wire Line
	4350 3200 4350 4400
Text Label 6300 8250 0    60   ~ 0
+5V
Text Label 6300 8350 0    60   ~ 0
C1
Text Label 6300 8450 0    60   ~ 0
FLOWPOT
Text Label 6300 8650 0    60   ~ 0
SPK
Text Label 6300 8750 0    60   ~ 0
R2
Text Label 6300 8850 0    60   ~ 0
0V
Text Label 6300 8950 0    60   ~ 0
R3
Text Label 6300 9150 0    60   ~ 0
C2
Text Label 6300 9550 0    60   ~ 0
C3
Text Label 6300 9650 0    60   ~ 0
LCD_DATA
Text Label 6300 9750 0    60   ~ 0
R1
Text Label 6300 9850 0    60   ~ 0
3V3
Text Label 6300 9950 0    60   ~ 0
R4
Text Label 6300 10350 0    60   ~ 0
KEYSW
$Comp
L CONN_8 P?
U 1 1 506FB0F8
P 6700 4650
F 0 "P?" V 6650 4650 60  0000 C CNN
F 1 "ARDUINO CONNS" V 6750 4650 60  0000 C CNN
	1    6700 4650
	1    0    0    -1  
$EndComp
$Comp
L CONN_9 P?
U 1 1 506FB107
P 6900 4700
F 0 "P?" V 6850 4700 60  0000 C CNN
F 1 "ARDUINO CONNS" V 6950 4700 60  0000 C CNN
	1    6900 4700
	-1   0    0    -1  
$EndComp
Text Label 7300 5100 0    60   ~ 0
30
Text Label 7500 5100 0    60   ~ 0
SPK
Wire Wire Line
	5450 4900 5450 6300
Wire Wire Line
	5150 4400 5150 5050
Connection ~ 5150 4400
Wire Wire Line
	6000 4150 9050 4150
Connection ~ 8600 4150
Connection ~ 8400 4150
Wire Wire Line
	7250 5100 7700 5100
Wire Wire Line
	7700 5100 7700 6500
Wire Wire Line
	7800 5000 7800 6600
Connection ~ 7800 5000
Wire Wire Line
	7850 4900 7850 6900
Connection ~ 7850 4900
Wire Wire Line
	7900 4800 7900 6750
Connection ~ 7900 4800
Wire Wire Line
	8000 4700 8000 6700
Wire Wire Line
	8050 4600 8050 6800
Wire Wire Line
	8150 4400 8150 6650
Wire Wire Line
	7250 4300 8250 4300
Wire Wire Line
	8250 4300 8250 5950
Wire Wire Line
	3050 4500 6350 4500
Wire Wire Line
	6000 4500 6000 4150
Wire Wire Line
	5350 4800 5350 6400
$Comp
L CONN_14 P?
U 1 1 506FE3B5
P 5450 7450
F 0 "P?" V 5420 7450 60  0000 C CNN
F 1 "CONN_ARD_PERIPHS" V 5530 7450 60  0000 C CNN
	1    5450 7450
	0    -1   1    0   
$EndComp
Wire Wire Line
	4800 5950 4800 7100
Wire Wire Line
	5250 4500 5250 6100
Wire Wire Line
	5250 6100 4900 6100
Wire Wire Line
	4900 6100 4900 7100
Connection ~ 6000 4500
Wire Wire Line
	5000 7100 5000 6300
Wire Wire Line
	5000 6300 5450 6300
Wire Wire Line
	5400 7100 5400 6400
Wire Wire Line
	5400 6400 5350 6400
Wire Wire Line
	5050 4300 5050 5200
Connection ~ 5050 4300
Wire Wire Line
	7700 6500 5200 6500
Wire Wire Line
	5200 6500 5200 7100
$Comp
L 7805 U?
U 1 1 506FEDD2
P 3550 5600
F 0 "U?" H 3700 5404 60  0000 C CNN
F 1 "7803" H 3550 5800 60  0000 C CNN
	1    3550 5600
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 506FEDF0
P 3050 5750
F 0 "C?" H 3100 5850 50  0000 L CNN
F 1 "C" H 3100 5650 50  0000 L CNN
	1    3050 5750
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 506FEDFF
P 4050 5750
F 0 "C?" H 4100 5850 50  0000 L CNN
F 1 "C" H 4100 5650 50  0000 L CNN
	1    4050 5750
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 506FEE0E
P 4350 5750
F 0 "C?" H 4400 5850 50  0000 L CNN
F 1 "CP1" H 4400 5650 50  0000 L CNN
	1    4350 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 5950 4350 5950
Connection ~ 4050 5950
Wire Wire Line
	3050 5550 3150 5550
Wire Wire Line
	3950 5550 4650 5550
Connection ~ 4050 5550
Wire Wire Line
	3050 5550 3050 4500
Connection ~ 5250 4500
Wire Wire Line
	5300 7100 5300 6600
Wire Wire Line
	5300 6600 4650 6600
Wire Wire Line
	4650 6600 4650 5550
Connection ~ 4350 5550
Wire Wire Line
	7800 6600 5500 6600
Wire Wire Line
	5500 6600 5500 7100
Wire Wire Line
	5600 7100 5600 6650
Wire Wire Line
	5600 6650 8150 6650
Wire Wire Line
	5700 7100 5700 6700
Wire Wire Line
	5700 6700 8000 6700
Wire Wire Line
	5800 7100 5800 6750
Wire Wire Line
	5800 6750 7900 6750
Wire Wire Line
	5900 7100 5900 6800
Wire Wire Line
	5900 6800 8050 6800
Wire Wire Line
	6000 7100 6000 6850
Wire Wire Line
	6000 6850 8100 6850
Wire Wire Line
	8100 6850 8100 4500
Wire Wire Line
	6100 7100 6100 6900
Wire Wire Line
	6100 6900 7850 6900
Wire Wire Line
	8250 5950 4800 5950
$Comp
L R R?
U 1 1 5070099C
P 8500 5950
F 0 "R?" V 8580 5950 50  0000 C CNN
F 1 "10k" V 8500 5950 50  0000 C CNN
	1    8500 5950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9050 4150 9050 5950
Wire Wire Line
	9050 5950 8750 5950
Connection ~ 8800 4150
Text Label 6750 4150 0    60   ~ 0
+5V
Text Label 8850 5950 0    60   ~ 0
+5V
Wire Wire Line
	3550 5850 3550 5950
Connection ~ 3550 5950
$Comp
L R R?
U 1 1 507C15C2
P 11950 9000
F 0 "R?" V 12030 9000 50  0000 C CNN
F 1 "100k" V 11950 9000 50  0000 C CNN
	1    11950 9000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9650 10350 10000 10350
Wire Wire Line
	11000 10350 11000 8850
Connection ~ 11000 8850
Wire Wire Line
	11050 8850 11050 8600
Connection ~ 11050 8850
Wire Wire Line
	15250 9100 12800 9100
Wire Wire Line
	12800 9100 12800 9350
Wire Wire Line
	10950 9850 10950 9100
Wire Wire Line
	10950 9100 12250 9100
Wire Wire Line
	12200 9000 12250 9000
Wire Wire Line
	10850 9650 10850 9000
Wire Wire Line
	10850 9000 11700 9000
Wire Wire Line
	9650 8850 12200 8850
Wire Wire Line
	12200 8850 12200 8900
Wire Wire Line
	12200 8900 12250 8900
Text Notes 11400 8850 0    60   ~ 0
CLAMP RESISTOR
$Comp
L R R?
U 1 1 507C11BB
P 5750 5050
F 0 "R?" V 5830 5050 50  0000 C CNN
F 1 "3k3" V 5750 5050 50  0000 C CNN
	1    5750 5050
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 507C11CA
P 6000 5650
F 0 "R?" V 6080 5650 50  0000 C CNN
F 1 "1k5" V 6000 5650 50  0000 C CNN
	1    6000 5650
	-1   0    0    1   
$EndComp
Connection ~ 5100 5900
Wire Wire Line
	5100 5900 6000 5900
Connection ~ 6000 5050
Text Notes 6050 5300 0    60   ~ 0
BATT SCALING\n15V -> 4.7V
Wire Wire Line
	6000 5400 6000 5050
Wire Wire Line
	6000 5050 6100 5050
Wire Wire Line
	6100 5050 6100 5000
Wire Wire Line
	6100 5000 6350 5000
Wire Wire Line
	5150 5050 5500 5050
Wire Wire Line
	5050 5200 5100 5200
Wire Wire Line
	5100 5200 5100 7100
$EndSCHEMATC
