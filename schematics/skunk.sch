EESchema Schematic File Version 2  date 26/09/2012 21:02:12
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
$Comp
L CONN_2 P?
U 1 1 50635EC9
P 1900 4050
F 0 "P?" V 1850 4050 40  0000 C CNN
F 1 "CONN_ARD_POWER" H 1750 4250 40  0000 C CNN
	1    1900 4050
	-1   0    0    1   
$EndComp
Connection ~ 1650 2650
Wire Wire Line
	1250 3950 850  3950
Wire Wire Line
	850  3950 850  2900
Wire Wire Line
	1650 2900 850  2900
Wire Wire Line
	1650 2500 1650 2900
Wire Wire Line
	2700 2650 2450 2650
Wire Wire Line
	1650 2650 1900 2650
Connection ~ 1650 2500
Wire Wire Line
	1300 2450 1300 2650
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
Wire Wire Line
	2450 2650 2450 2450
Wire Wire Line
	1300 2600 1450 2600
Connection ~ 1300 2600
Wire Wire Line
	1450 2600 1450 2800
Wire Wire Line
	1450 2800 750  2800
Wire Wire Line
	750  2800 750  4150
Wire Wire Line
	750  4150 1250 4150
$Comp
L CONN_2 P?
U 1 1 50635E8C
P 1600 4050
F 0 "P?" V 1550 4050 40  0000 C CNN
F 1 "CONN_ARD_POWER" H 1450 4250 40  0000 C CNN
	1    1600 4050
	1    0    0    1   
$EndComp
Text Label 2700 2650 2    60   ~ 0
+24V
Text Label 1900 2650 2    60   ~ 0
+12V
$Comp
L GND #PWR?
U 1 1 50635463
P 1300 2650
F 0 "#PWR?" H 1300 2650 30  0001 C CNN
F 1 "GND" H 1300 2580 30  0001 C CNN
	1    1300 2650
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
