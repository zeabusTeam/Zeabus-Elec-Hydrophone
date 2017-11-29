EESchema Schematic File Version 2
LIBS:Zeabus-Elec-Hydrophone-rescue
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
LIBS:zeabus
LIBS:ftdi
LIBS:Zeabus-Elec-Hydrophone-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 8
Title "Analog-Digital Codec"
Date "18 August 2017"
Rev "1.0.0"
Comp "Zeabus, Kasetsart University"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AD1939WBSTZ U11
U 1 1 59966752
P 4800 1600
F 0 "U11" H 6114 1959 45  0000 L BNN
F 1 "AD1939WBSTZ" H 6077 1859 45  0000 L BNN
F 2 "Housings_QFP:LQFP-64_10x10mm_Pitch0.5mm" H 4830 1750 20  0001 C CNN
F 3 "" H 4800 1600 60  0001 C CNN
	1    4800 1600
	1    0    0    -1  
$EndComp
$Comp
L FOX924B U13
U 1 1 59966784
P 8950 3200
F 0 "U13" H 8500 3850 45  0000 L BNN
F 1 "FOX924B - 12.288MHz" H 7900 3100 45  0000 L BNN
F 2 "Zeabus:Oscillator-TCXO" H 8980 3350 20  0001 C CNN
F 3 "" H 8950 3200 60  0001 C CNN
	1    8950 3200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7800 3100 9050 3100
NoConn ~ 7800 3400
NoConn ~ 7800 3700
NoConn ~ 7800 1600
NoConn ~ 7800 1700
NoConn ~ 7800 1800
NoConn ~ 7800 1900
NoConn ~ 7800 4000
NoConn ~ 7800 4100
NoConn ~ 7800 4200
NoConn ~ 7800 4300
NoConn ~ 7800 4400
NoConn ~ 7800 4500
NoConn ~ 7800 4600
NoConn ~ 7800 4700
NoConn ~ 7800 4800
NoConn ~ 7800 4900
NoConn ~ 7800 5000
NoConn ~ 7800 5100
NoConn ~ 7800 5200
NoConn ~ 7800 5300
NoConn ~ 7800 5400
NoConn ~ 7800 5500
NoConn ~ 4800 3900
NoConn ~ 4800 4000
NoConn ~ 4800 4100
NoConn ~ 4800 4200
NoConn ~ 10150 2700
$Comp
L GNDD #PWR066
U 1 1 59966FCA
P 10150 3100
F 0 "#PWR066" H 10150 2850 50  0001 C CNN
F 1 "GNDD" H 10150 2950 50  0000 C CNN
F 2 "" H 10150 3100 50  0001 C CNN
F 3 "" H 10150 3100 50  0001 C CNN
	1    10150 3100
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR067
U 1 1 5996700C
P 8150 2600
F 0 "#PWR067" H 8150 2350 50  0001 C CNN
F 1 "GNDA" H 8150 2450 50  0000 C CNN
F 2 "" H 8150 2600 50  0001 C CNN
F 3 "" H 8150 2600 50  0001 C CNN
	1    8150 2600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR068
U 1 1 59967026
P 9050 2700
F 0 "#PWR068" H 9050 2550 50  0001 C CNN
F 1 "+3.3V" H 9050 2840 50  0000 C CNN
F 2 "" H 9050 2700 50  0001 C CNN
F 3 "" H 9050 2700 50  0001 C CNN
	1    9050 2700
	1    0    0    -1  
$EndComp
$Comp
L +3.3VA #PWR069
U 1 1 59967068
P 4800 1400
F 0 "#PWR069" H 4800 1250 50  0001 C CNN
F 1 "+3.3VA" H 4800 1540 50  0000 C CNN
F 2 "" H 4800 1400 50  0001 C CNN
F 3 "" H 4800 1400 50  0001 C CNN
	1    4800 1400
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P J5
U 1 1 599670B8
P 8500 3000
F 0 "J5" H 8500 3270 50  0000 C CNN
F 1 "TEST_1P" H 8500 3200 50  0000 C CNN
F 2 "Zeabus:1Pin-TP" H 8700 3000 50  0001 C CNN
F 3 "" H 8700 3000 50  0001 C CNN
	1    8500 3000
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR070
U 1 1 599671EA
P 8150 2200
F 0 "#PWR070" H 8150 1950 50  0001 C CNN
F 1 "GNDD" H 8150 2050 50  0000 C CNN
F 2 "" H 8150 2200 50  0001 C CNN
F 3 "" H 8150 2200 50  0001 C CNN
	1    8150 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 2300 7800 2200
Wire Wire Line
	7800 2200 8150 2200
Wire Wire Line
	7800 2400 7800 2800
Connection ~ 7800 2500
Connection ~ 7800 2600
Connection ~ 7800 2700
Wire Wire Line
	7800 2600 8150 2600
Wire Wire Line
	7800 3000 8500 3000
Text HLabel 8200 3300 2    60   Input ~ 0
SPI_CLK
Text HLabel 8200 3500 2    60   Input ~ 0
ABCLK
Text HLabel 8200 3800 2    60   Input ~ 0
ALRCLK
Wire Wire Line
	7800 3300 8200 3300
Wire Wire Line
	8200 3500 7800 3500
Wire Wire Line
	7800 3800 8200 3800
$Comp
L +3.3V #PWR071
U 1 1 59967361
P 4500 2100
F 0 "#PWR071" H 4500 1950 50  0001 C CNN
F 1 "+3.3V" H 4500 2240 50  0000 C CNN
F 2 "" H 4500 2100 50  0001 C CNN
F 3 "" H 4500 2100 50  0001 C CNN
	1    4500 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1400 4800 1900
Connection ~ 4800 1800
Connection ~ 4800 1700
Connection ~ 4800 1600
Wire Wire Line
	4800 2000 4800 2100
Wire Wire Line
	4800 2100 4500 2100
Text HLabel 4500 2300 0    60   Input ~ 0
ADC1LN
Text HLabel 4500 2400 0    60   Input ~ 0
ADC1LP
Text HLabel 4500 2500 0    60   Input ~ 0
ADC1RN
Text HLabel 4500 2600 0    60   Input ~ 0
ADC1RP
Text HLabel 4500 2700 0    60   Input ~ 0
ADC2LN
Text HLabel 4500 2800 0    60   Input ~ 0
ADC2LP
Text HLabel 4500 2900 0    60   Input ~ 0
ADC2RN
Text HLabel 4500 3000 0    60   Input ~ 0
ADC2RP
Wire Wire Line
	4800 2300 4500 2300
Wire Wire Line
	4500 2400 4800 2400
Wire Wire Line
	4800 2500 4500 2500
Wire Wire Line
	4500 2600 4800 2600
Wire Wire Line
	4800 2700 4500 2700
Wire Wire Line
	4500 2800 4800 2800
Wire Wire Line
	4800 2900 4500 2900
Wire Wire Line
	4500 3000 4800 3000
$Comp
L GNDD #PWR072
U 1 1 59967561
P 4500 3300
F 0 "#PWR072" H 4500 3050 50  0001 C CNN
F 1 "GNDD" H 4500 3150 50  0000 C CNN
F 2 "" H 4500 3300 50  0001 C CNN
F 3 "" H 4500 3300 50  0001 C CNN
	1    4500 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3200 4800 3400
Connection ~ 4800 3300
Wire Wire Line
	4500 3300 4800 3300
Text HLabel 4500 4400 0    60   Input ~ 0
SPI_MOSI
Text HLabel 4500 4500 0    60   Output ~ 0
SPI_MISO
Text HLabel 4500 3600 0    60   Output ~ 0
ASDATA1
Text HLabel 4500 3700 0    60   Output ~ 0
ASDATA2
Wire Wire Line
	4500 3600 4800 3600
Wire Wire Line
	4800 3700 4500 3700
Wire Wire Line
	4500 4400 4800 4400
Wire Wire Line
	4800 4500 4500 4500
Text HLabel 2050 5600 0    60   Input ~ 0
~AD1939_CS
Text HLabel 2250 3900 0    60   Input ~ 0
~AD1939_SOFT_RESET
$Comp
L 74LVC1G08 U12
U 1 1 59968180
P 3050 4000
F 0 "U12" H 3050 4050 50  0000 C CNN
F 1 "74LVC1G08" H 3050 3950 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-353" H 3050 4000 50  0001 C CNN
F 3 "" H 3050 4000 50  0001 C CNN
	1    3050 4000
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR073
U 1 1 599681C6
P 2900 4300
F 0 "#PWR073" H 2900 4050 50  0001 C CNN
F 1 "GNDD" H 2900 4150 50  0000 C CNN
F 2 "" H 2900 4300 50  0001 C CNN
F 3 "" H 2900 4300 50  0001 C CNN
	1    2900 4300
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR074
U 1 1 599681FD
P 2900 3700
F 0 "#PWR074" H 2900 3550 50  0001 C CNN
F 1 "+3.3V" H 2900 3840 50  0000 C CNN
F 2 "" H 2900 3700 50  0001 C CNN
F 3 "" H 2900 3700 50  0001 C CNN
	1    2900 3700
	1    0    0    -1  
$EndComp
Text GLabel 2250 4100 0    60   Input ~ 0
~RESET
Wire Wire Line
	2450 4100 2250 4100
Wire Wire Line
	2250 3900 2450 3900
Wire Wire Line
	3650 4000 3650 4700
Wire Wire Line
	3650 4700 4800 4700
$Comp
L C_Small C58
U 1 1 599686D6
P 2750 5200
F 0 "C58" H 2760 5270 50  0000 L CNN
F 1 "0.1uF" H 2760 5120 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2750 5200 50  0001 C CNN
F 3 "" H 2750 5200 50  0001 C CNN
	1    2750 5200
	1    0    0    -1  
$EndComp
$Comp
L C_Small C59
U 1 1 5996870E
P 3050 5200
F 0 "C59" H 3060 5270 50  0000 L CNN
F 1 "47uF" H 3060 5120 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3050 5200 50  0001 C CNN
F 3 "" H 3050 5200 50  0001 C CNN
	1    3050 5200
	1    0    0    -1  
$EndComp
$Comp
L C_Small C60
U 1 1 59968731
P 3450 5200
F 0 "C60" H 3460 5270 50  0000 L CNN
F 1 "0.1uF" H 3460 5120 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3450 5200 50  0001 C CNN
F 3 "" H 3450 5200 50  0001 C CNN
	1    3450 5200
	1    0    0    -1  
$EndComp
$Comp
L C_Small C61
U 1 1 59968759
P 3700 5200
F 0 "C61" H 3710 5270 50  0000 L CNN
F 1 "10uF" H 3710 5120 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3700 5200 50  0001 C CNN
F 3 "" H 3700 5200 50  0001 C CNN
	1    3700 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4900 2750 4900
Wire Wire Line
	2750 4900 2750 5100
Wire Wire Line
	3050 5100 3050 4900
Connection ~ 3050 4900
Wire Wire Line
	3450 5100 4800 5100
Connection ~ 3700 5100
Wire Wire Line
	3700 5300 3700 5350
Wire Wire Line
	3700 5350 2750 5350
Wire Wire Line
	2750 5350 2750 5300
Wire Wire Line
	3050 5300 3050 5350
Connection ~ 3050 5350
Wire Wire Line
	3450 5300 3450 5350
Connection ~ 3450 5350
$Comp
L R R36
U 1 1 59968A1B
P 2350 3600
F 0 "R36" V 2430 3600 50  0000 C CNN
F 1 "10k" V 2350 3600 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2280 3600 50  0001 C CNN
F 3 "" H 2350 3600 50  0001 C CNN
	1    2350 3600
	1    0    0    -1  
$EndComp
$Comp
L R R37
U 1 1 59968ACC
P 2450 5250
F 0 "R37" V 2530 5250 50  0000 C CNN
F 1 "10k" V 2450 5250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2380 5250 50  0001 C CNN
F 3 "" H 2450 5250 50  0001 C CNN
	1    2450 5250
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR075
U 1 1 59968BAE
P 3050 5350
F 0 "#PWR075" H 3050 5100 50  0001 C CNN
F 1 "GNDD" H 3050 5200 50  0000 C CNN
F 2 "" H 3050 5350 50  0001 C CNN
F 3 "" H 3050 5350 50  0001 C CNN
	1    3050 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 5600 4000 5600
Wire Wire Line
	4000 5600 4000 5300
Wire Wire Line
	4000 5300 4800 5300
Wire Wire Line
	2450 5400 2450 5600
Connection ~ 2450 5600
Wire Wire Line
	2350 3750 2350 3900
Connection ~ 2350 3900
$Comp
L +3.3V #PWR076
U 1 1 59968D2B
P 2350 3450
F 0 "#PWR076" H 2350 3300 50  0001 C CNN
F 1 "+3.3V" H 2350 3590 50  0000 C CNN
F 2 "" H 2350 3450 50  0001 C CNN
F 3 "" H 2350 3450 50  0001 C CNN
	1    2350 3450
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR077
U 1 1 59968D54
P 2450 5100
F 0 "#PWR077" H 2450 4950 50  0001 C CNN
F 1 "+3.3V" H 2450 5240 50  0000 C CNN
F 2 "" H 2450 5100 50  0001 C CNN
F 3 "" H 2450 5100 50  0001 C CNN
	1    2450 5100
	1    0    0    -1  
$EndComp
$Comp
L C_Small C62
U 1 1 59968DEB
P 4150 6050
F 0 "C62" H 4160 6120 50  0000 L CNN
F 1 "390pF" H 4160 5970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4150 6050 50  0001 C CNN
F 3 "" H 4150 6050 50  0001 C CNN
	1    4150 6050
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C63
U 1 1 59968E52
P 4400 6350
F 0 "C63" H 4410 6420 50  0000 L CNN
F 1 "5600pF" H 4410 6270 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4400 6350 50  0001 C CNN
F 3 "" H 4400 6350 50  0001 C CNN
	1    4400 6350
	0    -1   -1   0   
$EndComp
$Comp
L R R38
U 1 1 59968E97
P 3950 6350
F 0 "R38" V 4030 6350 50  0000 C CNN
F 1 "560" V 3950 6350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 3880 6350 50  0001 C CNN
F 3 "" H 3950 6350 50  0001 C CNN
	1    3950 6350
	0    1    1    0   
$EndComp
Wire Wire Line
	4300 6350 4100 6350
Wire Wire Line
	3800 6350 3800 6050
Wire Wire Line
	3800 6050 4050 6050
Wire Wire Line
	4250 6050 4800 6050
Wire Wire Line
	4800 5500 4800 6350
Wire Wire Line
	4800 6350 4500 6350
Connection ~ 4800 6050
$Comp
L +3.3VA #PWR078
U 1 1 599691FE
P 3800 6050
F 0 "#PWR078" H 3800 5900 50  0001 C CNN
F 1 "+3.3VA" H 3800 6190 50  0000 C CNN
F 2 "" H 3800 6050 50  0001 C CNN
F 3 "" H 3800 6050 50  0001 C CNN
	1    3800 6050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
