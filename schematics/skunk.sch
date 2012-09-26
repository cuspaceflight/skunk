EESchema Schematic File Version 2  date 26/09/2012 21:43:37
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
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "26 sep 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Notes Line
	1750 5950 1750 3200
Wire Notes Line
	1750 5950 7500 5950
Wire Notes Line
	7500 5950 7500 3200
Wire Notes Line
	7500 3200 1750 3200
Wire Wire Line
	9100 1850 8700 1850
Wire Wire Line
	8700 1850 8700 4050
Wire Wire Line
	6900 4250 6500 4250
Wire Wire Line
	9100 1450 5000 1450
Wire Wire Line
	5000 1450 5000 2700
Wire Wire Line
	5000 2700 1300 2700
Wire Wire Line
	2250 4150 2500 4150
Connection ~ 1300 2700
Wire Wire Line
	1300 2850 1300 2450
Wire Wire Line
	1450 2600 1450 3000
Wire Wire Line
	1450 3000 750  3000
Wire Wire Line
	750  3000 750  4150
Wire Wire Line
	8700 4050 8150 4050
Wire Wire Line
	1250 3950 850  3950
Connection ~ 1650 2500
Wire Wire Line
	2050 1000 2050 1350
Wire Wire Line
	2050 1350 2250 1350
Wire Wire Line
	1300 1350 1100 1350
Wire Wire Line
	1100 1350 1100 1000
Wire Wire Line
	1700 1000 1700 1350
Wire Wire Line
	1700 1350 1500 1350
Wire Wire Line
	2450 1350 2650 1350
Wire Wire Line
	2650 1350 2650 1000
Wire Wire Line
	1500 2450 1500 2500
Wire Wire Line
	1500 2500 2250 2500
Wire Wire Line
	2250 2500 2250 2450
Connection ~ 1300 2600
Wire Wire Line
	750  4150 1250 4150
Wire Wire Line
	2450 2450 2450 2500
Wire Wire Line
	6900 3950 6750 3950
Wire Wire Line
	6750 3950 6750 4150
Wire Wire Line
	6750 4150 6900 4150
Connection ~ 1450 2600
Wire Wire Line
	850  3950 850  3100
Wire Wire Line
	850  3100 1650 3100
Wire Wire Line
	1650 3100 1650 2500
Wire Wire Line
	2500 3950 2250 3950
Wire Wire Line
	1300 2600 4900 2600
Wire Wire Line
	4900 2600 4900 1350
Wire Wire Line
	4900 1350 9100 1350
Wire Wire Line
	2450 2500 5100 2500
Wire Wire Line
	5100 2500 5100 1650
Wire Wire Line
	5100 1650 9100 1650
Wire Wire Line
	6500 4050 6900 4050
Wire Wire Line
	8150 4250 8800 4250
Wire Wire Line
	8800 4250 8800 1950
Wire Wire Line
	8800 1950 9100 1950
Text Label 6500 4050 0    60   ~ 0
RX
Text Label 2500 4150 2    60   ~ 0
0V
Text Label 2500 3950 2    60   ~ 0
+12V
Text Label 8400 1450 0    60   ~ 0
0V SENSE
Text Label 8850 1850 0    60   ~ 0
RX
Text Label 8400 1650 0    60   ~ 0
+24V
Text Label 8850 1950 0    60   ~ 0
TX
Text Label 8400 1350 0    60   ~ 0
0V
Text Label 950  4150 0    60   ~ 0
0V
Text Label 950  3950 0    60   ~ 0
+12V
$Comp
L DB9 J?
U 1 1 506362ED
P 9550 1550
F 0 "J?" H 9550 2100 70  0000 C CNN
F 1 "DB9_FLOWMETER" H 9550 1000 70  0000 C CNN
	1    9550 1550
	1    0    0    -1  
$EndComp
Text Label 6500 4250 0    60   ~ 0
TX
$Comp
L DB9 J?
U 1 1 50636112
P 7350 4050
F 0 "J?" H 7350 4600 70  0000 C CNN
F 1 "DB9_ARD_BOX" H 7100 3450 70  0000 C CNN
	1    7350 4050
	1    0    0    -1  
$EndComp
$Comp
L DB9 J?
U 1 1 506360FD
P 7700 4050
F 0 "J?" H 7700 4600 70  0000 C CNN
F 1 "DB9_ARD_BOX" H 7450 3450 70  0000 C CNN
	1    7700 4050
	-1   0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 50635EC9
P 1900 4050
F 0 "P?" V 1850 4050 40  0000 C CNN
F 1 "CONN_ARD_POWER" H 1750 4250 40  0000 C CNN
	1    1900 4050
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P?
U 1 1 50635E8C
P 1600 4050
F 0 "P?" V 1550 4050 40  0000 C CNN
F 1 "CONN_ARD_POWER" H 1450 4250 40  0000 C CNN
	1    1600 4050
	1    0    0    1   
$EndComp
Text Label 2800 2500 2    60   ~ 0
+24V
Text Label 1950 2500 2    60   ~ 0
+12V
$Comp
L GND #PWR?
U 1 1 50635463
P 1300 2850
F 0 "#PWR?" H 1300 2850 30  0001 C CNN
F 1 "GND" H 1300 2780 30  0001 C CNN
	1    1300 2850
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 506353B8
P 2350 2100
F 0 "P?" V 2300 2100 40  0000 C CNN
F 1 "CONN_BAT_2" V 2500 2100 40  0000 C CNN
	1    2350 2100
	0    -1   -1   0   
$EndComp
$Comp
L CONN_2 P?
U 1 1 5063538D
P 1400 2100
F 0 "P?" V 1350 2100 40  0000 C CNN
F 1 "CONN_BAT_1" V 1550 2100 40  0000 C CNN
	1    1400 2100
	0    -1   -1   0   
$EndComp
$Comp
L CONN_2 P?
U 1 1 506352F3
P 2350 1700
F 0 "P?" V 2300 1700 40  0000 C CNN
F 1 "CONN_BAT_2" V 2500 1700 40  0000 C CNN
	1    2350 1700
	0    -1   1    0   
$EndComp
$Comp
L CONN_2 P?
U 1 1 506352C8
P 1400 1700
F 0 "P?" V 1350 1700 40  0000 C CNN
F 1 "CONN_BAT_1" V 1550 1700 40  0000 C CNN
	1    1400 1700
	0    -1   1    0   
$EndComp
$Comp
L BATTERY BT?
U 1 1 5063529E
P 2350 1000
F 0 "BT?" H 2350 1200 50  0000 C CNN
F 1 "12V SLAB BAT2" H 2350 810 50  0000 C CNN
	1    2350 1000
	-1   0    0    -1  
$EndComp
$Comp
L BATTERY BT?
U 1 1 5063529A
P 1400 1000
F 0 "BT?" H 1400 1200 50  0000 C CNN
F 1 "12V SLAB BAT1" H 1400 810 50  0000 C CNN
	1    1400 1000
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
