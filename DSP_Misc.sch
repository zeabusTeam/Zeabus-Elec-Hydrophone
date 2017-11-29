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
Sheet 4 8
Title "Misc. I/O and USB with Main-Power Source"
Date "18 August 2017"
Rev "1.0.0"
Comp "Zeabus, Kasetsart University"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SW_Push_Dual SW3
U 1 1 59959E33
P 1550 1500
F 0 "SW3" H 1600 1600 50  0000 L CNN
F 1 "PB" H 1550 1230 50  0000 C CNN
F 2 "Zeabus:Button-EVQ" H 1550 1700 50  0001 C CNN
F 3 "" H 1550 1700 50  0001 C CNN
	1    1550 1500
	1    0    0    -1  
$EndComp
$Comp
L C_Small C48
U 1 1 59959EC3
P 3000 1100
F 0 "C48" H 3010 1170 50  0000 L CNN
F 1 "0.01uF" H 3010 1020 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3000 1100 50  0001 C CNN
F 3 "" H 3000 1100 50  0001 C CNN
	1    3000 1100
	0    -1   -1   0   
$EndComp
$Comp
L R R21
U 1 1 59959EFE
P 2450 1250
F 0 "R21" V 2530 1250 50  0000 C CNN
F 1 "10k" V 2450 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2380 1250 50  0001 C CNN
F 3 "" H 2450 1250 50  0001 C CNN
	1    2450 1250
	1    0    0    -1  
$EndComp
$Comp
L 74LVC14 U7
U 1 1 5995AFBD
P 2950 1500
F 0 "U7" H 3100 1600 50  0000 C CNN
F 1 "74LVC14" H 3150 1400 50  0000 C CNN
F 2 "Housings_SSOP:SSOP-14_5.3x6.2mm_Pitch0.65mm" H 2950 1500 50  0001 C CNN
F 3 "" H 2950 1500 50  0001 C CNN
	1    2950 1500
	1    0    0    -1  
$EndComp
$Comp
L 74LVC14 U7
U 2 1 5995AFFA
P 2950 2650
F 0 "U7" H 3100 2750 50  0000 C CNN
F 1 "74LVC14" H 3150 2550 50  0000 C CNN
F 2 "Housings_SSOP:SSOP-14_5.3x6.2mm_Pitch0.65mm" H 2950 2650 50  0001 C CNN
F 3 "" H 2950 2650 50  0001 C CNN
	2    2950 2650
	1    0    0    -1  
$EndComp
$Comp
L 74LVC14 U7
U 3 1 5995B04E
P 2950 3850
F 0 "U7" H 3100 3950 50  0000 C CNN
F 1 "74LVC14" H 3150 3750 50  0000 C CNN
F 2 "Housings_SSOP:SSOP-14_5.3x6.2mm_Pitch0.65mm" H 2950 3850 50  0001 C CNN
F 3 "" H 2950 3850 50  0001 C CNN
	3    2950 3850
	1    0    0    -1  
$EndComp
$Comp
L 74LVC14 U7
U 4 1 5995B0A8
P 2950 5050
F 0 "U7" H 3100 5150 50  0000 C CNN
F 1 "74LVC14" H 3150 4950 50  0000 C CNN
F 2 "Housings_SSOP:SSOP-14_5.3x6.2mm_Pitch0.65mm" H 2950 5050 50  0001 C CNN
F 3 "" H 2950 5050 50  0001 C CNN
	4    2950 5050
	1    0    0    -1  
$EndComp
$Comp
L 74LVC14 U7
U 5 1 5995B0E9
P 2250 6000
F 0 "U7" H 2400 6100 50  0000 C CNN
F 1 "74LVC14" H 2450 5900 50  0000 C CNN
F 2 "Housings_SSOP:SSOP-14_5.3x6.2mm_Pitch0.65mm" H 2250 6000 50  0001 C CNN
F 3 "" H 2250 6000 50  0001 C CNN
	5    2250 6000
	1    0    0    -1  
$EndComp
$Comp
L 74LVC14 U7
U 6 1 5995B13E
P 2250 6400
F 0 "U7" H 2400 6500 50  0000 C CNN
F 1 "74LVC14" H 2450 6300 50  0000 C CNN
F 2 "Housings_SSOP:SSOP-14_5.3x6.2mm_Pitch0.65mm" H 2250 6400 50  0001 C CNN
F 3 "" H 2250 6400 50  0001 C CNN
	6    2250 6400
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 5995B1F3
P 2000 1500
F 0 "R20" V 2080 1500 50  0000 C CNN
F 1 "100" V 2000 1500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1930 1500 50  0001 C CNN
F 3 "" H 2000 1500 50  0001 C CNN
	1    2000 1500
	0    1    1    0   
$EndComp
$Comp
L C_Small C49
U 1 1 5995B2B5
P 2450 1750
F 0 "C49" H 2460 1820 50  0000 L CNN
F 1 "1uF" H 2460 1670 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2450 1750 50  0001 C CNN
F 3 "" H 2450 1750 50  0001 C CNN
	1    2450 1750
	1    0    0    -1  
$EndComp
$Comp
L R R29
U 1 1 5995B301
P 8000 2100
F 0 "R29" V 8080 2100 50  0000 C CNN
F 1 "330" V 8000 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 7930 2100 50  0001 C CNN
F 3 "" H 8000 2100 50  0001 C CNN
	1    8000 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 1400 2450 1650
Wire Wire Line
	1750 1700 1750 1500
Wire Wire Line
	1750 1500 1850 1500
Wire Wire Line
	1350 1500 1350 1900
Wire Wire Line
	2150 1500 2500 1500
Connection ~ 2450 1500
Wire Wire Line
	1350 1900 2450 1900
Wire Wire Line
	2450 1900 2450 1850
Connection ~ 1350 1700
$Comp
L GNDD #PWR043
U 1 1 5995B4AC
P 1350 1900
F 0 "#PWR043" H 1350 1650 50  0001 C CNN
F 1 "GNDD" H 1350 1750 50  0000 C CNN
F 2 "" H 1350 1900 50  0001 C CNN
F 3 "" H 1350 1900 50  0001 C CNN
	1    1350 1900
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR044
U 1 1 5995B4E4
P 2450 1100
F 0 "#PWR044" H 2450 950 50  0001 C CNN
F 1 "+3.3V" H 2450 1240 50  0000 C CNN
F 2 "" H 2450 1100 50  0001 C CNN
F 3 "" H 2450 1100 50  0001 C CNN
	1    2450 1100
	1    0    0    -1  
$EndComp
$Comp
L SW_Push_Dual SW4
U 1 1 5995B80C
P 1550 2650
F 0 "SW4" H 1600 2750 50  0000 L CNN
F 1 "PB" H 1550 2380 50  0000 C CNN
F 2 "Zeabus:Button-EVQ" H 1550 2850 50  0001 C CNN
F 3 "" H 1550 2850 50  0001 C CNN
	1    1550 2650
	1    0    0    -1  
$EndComp
$Comp
L R R23
U 1 1 5995B812
P 2450 2400
F 0 "R23" V 2530 2400 50  0000 C CNN
F 1 "10k" V 2450 2400 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2380 2400 50  0001 C CNN
F 3 "" H 2450 2400 50  0001 C CNN
	1    2450 2400
	1    0    0    -1  
$EndComp
$Comp
L R R22
U 1 1 5995B818
P 2000 2650
F 0 "R22" V 2080 2650 50  0000 C CNN
F 1 "100" V 2000 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1930 2650 50  0001 C CNN
F 3 "" H 2000 2650 50  0001 C CNN
	1    2000 2650
	0    1    1    0   
$EndComp
$Comp
L C_Small C50
U 1 1 5995B81E
P 2450 2900
F 0 "C50" H 2460 2970 50  0000 L CNN
F 1 "1uF" H 2460 2820 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2450 2900 50  0001 C CNN
F 3 "" H 2450 2900 50  0001 C CNN
	1    2450 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2550 2450 2800
Wire Wire Line
	1750 2850 1750 2650
Wire Wire Line
	1750 2650 1850 2650
Wire Wire Line
	1350 2650 1350 3050
Wire Wire Line
	2150 2650 2500 2650
Connection ~ 2450 2650
Wire Wire Line
	1350 3050 2450 3050
Wire Wire Line
	2450 3050 2450 3000
Connection ~ 1350 2850
$Comp
L GNDD #PWR045
U 1 1 5995B82D
P 1350 3050
F 0 "#PWR045" H 1350 2800 50  0001 C CNN
F 1 "GNDD" H 1350 2900 50  0000 C CNN
F 2 "" H 1350 3050 50  0001 C CNN
F 3 "" H 1350 3050 50  0001 C CNN
	1    1350 3050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR046
U 1 1 5995B833
P 2450 2250
F 0 "#PWR046" H 2450 2100 50  0001 C CNN
F 1 "+3.3V" H 2450 2390 50  0000 C CNN
F 2 "" H 2450 2250 50  0001 C CNN
F 3 "" H 2450 2250 50  0001 C CNN
	1    2450 2250
	1    0    0    -1  
$EndComp
$Comp
L SW_Push_Dual SW5
U 1 1 5995B989
P 1550 3850
F 0 "SW5" H 1600 3950 50  0000 L CNN
F 1 "PB" H 1550 3580 50  0000 C CNN
F 2 "Zeabus:Button-EVQ" H 1550 4050 50  0001 C CNN
F 3 "" H 1550 4050 50  0001 C CNN
	1    1550 3850
	1    0    0    -1  
$EndComp
$Comp
L R R25
U 1 1 5995B98F
P 2450 3600
F 0 "R25" V 2530 3600 50  0000 C CNN
F 1 "10k" V 2450 3600 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2380 3600 50  0001 C CNN
F 3 "" H 2450 3600 50  0001 C CNN
	1    2450 3600
	1    0    0    -1  
$EndComp
$Comp
L R R24
U 1 1 5995B995
P 2000 3850
F 0 "R24" V 2080 3850 50  0000 C CNN
F 1 "100" V 2000 3850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1930 3850 50  0001 C CNN
F 3 "" H 2000 3850 50  0001 C CNN
	1    2000 3850
	0    1    1    0   
$EndComp
$Comp
L C_Small C51
U 1 1 5995B99B
P 2450 4100
F 0 "C51" H 2460 4170 50  0000 L CNN
F 1 "1uF" H 2460 4020 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2450 4100 50  0001 C CNN
F 3 "" H 2450 4100 50  0001 C CNN
	1    2450 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3750 2450 4000
Wire Wire Line
	1750 4050 1750 3850
Wire Wire Line
	1750 3850 1850 3850
Wire Wire Line
	1350 3850 1350 4250
Wire Wire Line
	2150 3850 2500 3850
Connection ~ 2450 3850
Wire Wire Line
	1350 4250 2450 4250
Wire Wire Line
	2450 4250 2450 4200
Connection ~ 1350 4050
$Comp
L GNDD #PWR047
U 1 1 5995B9AA
P 1350 4250
F 0 "#PWR047" H 1350 4000 50  0001 C CNN
F 1 "GNDD" H 1350 4100 50  0000 C CNN
F 2 "" H 1350 4250 50  0001 C CNN
F 3 "" H 1350 4250 50  0001 C CNN
	1    1350 4250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR048
U 1 1 5995B9B0
P 2450 3450
F 0 "#PWR048" H 2450 3300 50  0001 C CNN
F 1 "+3.3V" H 2450 3590 50  0000 C CNN
F 2 "" H 2450 3450 50  0001 C CNN
F 3 "" H 2450 3450 50  0001 C CNN
	1    2450 3450
	1    0    0    -1  
$EndComp
$Comp
L SW_Push_Dual SW6
U 1 1 5995BA6A
P 1550 5050
F 0 "SW6" H 1600 5150 50  0000 L CNN
F 1 "PB" H 1550 4780 50  0000 C CNN
F 2 "Zeabus:Button-EVQ" H 1550 5250 50  0001 C CNN
F 3 "" H 1550 5250 50  0001 C CNN
	1    1550 5050
	1    0    0    -1  
$EndComp
$Comp
L R R27
U 1 1 5995BA70
P 2450 4800
F 0 "R27" V 2530 4800 50  0000 C CNN
F 1 "10k" V 2450 4800 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2380 4800 50  0001 C CNN
F 3 "" H 2450 4800 50  0001 C CNN
	1    2450 4800
	1    0    0    -1  
$EndComp
$Comp
L R R26
U 1 1 5995BA76
P 2000 5050
F 0 "R26" V 2080 5050 50  0000 C CNN
F 1 "100" V 2000 5050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1930 5050 50  0001 C CNN
F 3 "" H 2000 5050 50  0001 C CNN
	1    2000 5050
	0    1    1    0   
$EndComp
$Comp
L C_Small C52
U 1 1 5995BA7C
P 2450 5300
F 0 "C52" H 2460 5370 50  0000 L CNN
F 1 "1uF" H 2460 5220 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2450 5300 50  0001 C CNN
F 3 "" H 2450 5300 50  0001 C CNN
	1    2450 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 4950 2450 5200
Wire Wire Line
	1750 5250 1750 5050
Wire Wire Line
	1750 5050 1850 5050
Wire Wire Line
	1350 5050 1350 5450
Wire Wire Line
	2150 5050 2500 5050
Connection ~ 2450 5050
Wire Wire Line
	1350 5450 2450 5450
Wire Wire Line
	2450 5450 2450 5400
Connection ~ 1350 5250
$Comp
L GNDD #PWR049
U 1 1 5995BA8B
P 1350 5450
F 0 "#PWR049" H 1350 5200 50  0001 C CNN
F 1 "GNDD" H 1350 5300 50  0000 C CNN
F 2 "" H 1350 5450 50  0001 C CNN
F 3 "" H 1350 5450 50  0001 C CNN
	1    1350 5450
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR050
U 1 1 5995BA91
P 2450 4650
F 0 "#PWR050" H 2450 4500 50  0001 C CNN
F 1 "+3.3V" H 2450 4790 50  0000 C CNN
F 2 "" H 2450 4650 50  0001 C CNN
F 3 "" H 2450 4650 50  0001 C CNN
	1    2450 4650
	1    0    0    -1  
$EndComp
$Comp
L 74AC11244 U8
U 1 1 5995624A
P 6950 1650
F 0 "U8" H 6550 2475 45  0000 L BNN
F 1 "74AC11244" H 6550 650 45  0000 L BNN
F 2 "Housings_SSOP:TSSOP-24_4.4x7.8mm_Pitch0.65mm" H 6900 1600 20  0001 C CNN
F 3 "" H 6950 1850 60  0001 C CNN
	1    6950 1650
	1    0    0    -1  
$EndComp
Text HLabel 3400 1500 2    60   Output ~ 0
PB1
Text HLabel 3400 2650 2    60   Output ~ 0
PB2
Text HLabel 3400 3850 2    60   Output ~ 0
PB3
Text HLabel 3400 5050 2    60   Output ~ 0
PB4
$Comp
L +3.3V #PWR051
U 1 1 59959415
P 2900 950
F 0 "#PWR051" H 2900 800 50  0001 C CNN
F 1 "+3.3V" H 2900 1090 50  0000 C CNN
F 2 "" H 2900 950 50  0001 C CNN
F 3 "" H 2900 950 50  0001 C CNN
	1    2900 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 950  2900 1250
Connection ~ 2900 1100
$Comp
L GNDD #PWR052
U 1 1 5995957F
P 3100 1100
F 0 "#PWR052" H 3100 850 50  0001 C CNN
F 1 "GNDD" H 3100 950 50  0000 C CNN
F 2 "" H 3100 1100 50  0001 C CNN
F 3 "" H 3100 1100 50  0001 C CNN
	1    3100 1100
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR053
U 1 1 599595D5
P 2900 1750
F 0 "#PWR053" H 2900 1500 50  0001 C CNN
F 1 "GNDD" H 2900 1600 50  0000 C CNN
F 2 "" H 2900 1750 50  0001 C CNN
F 3 "" H 2900 1750 50  0001 C CNN
	1    2900 1750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR054
U 1 1 59959C22
P 6350 950
F 0 "#PWR054" H 6350 800 50  0001 C CNN
F 1 "+3.3V" H 6350 1090 50  0000 C CNN
F 2 "" H 6350 950 50  0001 C CNN
F 3 "" H 6350 950 50  0001 C CNN
	1    6350 950 
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR055
U 1 1 59959C78
P 6350 2550
F 0 "#PWR055" H 6350 2300 50  0001 C CNN
F 1 "GNDD" H 6350 2400 50  0000 C CNN
F 2 "" H 6350 2550 50  0001 C CNN
F 3 "" H 6350 2550 50  0001 C CNN
	1    6350 2550
	1    0    0    -1  
$EndComp
$Comp
L C_Small C53
U 1 1 59959E77
P 7450 2350
F 0 "C53" H 7460 2420 50  0000 L CNN
F 1 "0.01uF" H 7460 2270 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7450 2350 50  0001 C CNN
F 3 "" H 7450 2350 50  0001 C CNN
	1    7450 2350
	1    0    0    -1  
$EndComp
$Comp
L LED_Small D2
U 1 1 5995A128
P 8000 1750
F 0 "D2" H 7950 1875 50  0000 L CNN
F 1 "Yellow" H 7850 1650 50  0000 L CNN
F 2 "LEDs:LED_0603" V 8000 1750 50  0001 C CNN
F 3 "" V 8000 1750 50  0001 C CNN
	1    8000 1750
	0    -1   -1   0   
$EndComp
$Comp
L LED_Small D3
U 1 1 5995A1AC
P 8350 1750
F 0 "D3" H 8300 1875 50  0000 L CNN
F 1 "Red" H 8250 1650 50  0000 L CNN
F 2 "LEDs:LED_0603" V 8350 1750 50  0001 C CNN
F 3 "" V 8350 1750 50  0001 C CNN
	1    8350 1750
	0    -1   -1   0   
$EndComp
$Comp
L LED_Small D4
U 1 1 5995A215
P 8700 1750
F 0 "D4" H 8650 1875 50  0000 L CNN
F 1 "Blue" H 8600 1650 50  0000 L CNN
F 2 "LEDs:LED_0603" V 8700 1750 50  0001 C CNN
F 3 "" V 8700 1750 50  0001 C CNN
	1    8700 1750
	0    -1   -1   0   
$EndComp
$Comp
L LED_Small D5
U 1 1 5995A280
P 9050 1750
F 0 "D5" H 9000 1875 50  0000 L CNN
F 1 "Green" H 8950 1650 50  0000 L CNN
F 2 "LEDs:LED_0603" V 9050 1750 50  0001 C CNN
F 3 "" V 9050 1750 50  0001 C CNN
	1    9050 1750
	0    -1   -1   0   
$EndComp
$Comp
L LED_Small D6
U 1 1 5995A2F3
P 9400 1750
F 0 "D6" H 9350 1875 50  0000 L CNN
F 1 "Yellow" H 9250 1650 50  0000 L CNN
F 2 "LEDs:LED_0603" V 9400 1750 50  0001 C CNN
F 3 "" V 9400 1750 50  0001 C CNN
	1    9400 1750
	0    -1   -1   0   
$EndComp
$Comp
L R R30
U 1 1 5995A49D
P 8350 2100
F 0 "R30" V 8430 2100 50  0000 C CNN
F 1 "330" V 8350 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 8280 2100 50  0001 C CNN
F 3 "" H 8350 2100 50  0001 C CNN
	1    8350 2100
	-1   0    0    1   
$EndComp
$Comp
L R R31
U 1 1 5995A510
P 8700 2100
F 0 "R31" V 8780 2100 50  0000 C CNN
F 1 "330" V 8700 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 8630 2100 50  0001 C CNN
F 3 "" H 8700 2100 50  0001 C CNN
	1    8700 2100
	-1   0    0    1   
$EndComp
$Comp
L R R32
U 1 1 5995A588
P 9050 2100
F 0 "R32" V 9130 2100 50  0000 C CNN
F 1 "330" V 9050 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 8980 2100 50  0001 C CNN
F 3 "" H 9050 2100 50  0001 C CNN
	1    9050 2100
	-1   0    0    1   
$EndComp
$Comp
L GNDD #PWR056
U 1 1 5995A602
P 9050 2350
F 0 "#PWR056" H 9050 2100 50  0001 C CNN
F 1 "GNDD" H 9050 2200 50  0000 C CNN
F 2 "" H 9050 2350 50  0001 C CNN
F 3 "" H 9050 2350 50  0001 C CNN
	1    9050 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1650 9400 950 
Wire Wire Line
	9400 950  7450 950 
Wire Wire Line
	7450 1050 9050 1050
Wire Wire Line
	9050 1050 9050 1650
Wire Wire Line
	8700 1650 8700 1150
Wire Wire Line
	8700 1150 7450 1150
Wire Wire Line
	7450 1250 8350 1250
Wire Wire Line
	8350 1250 8350 1650
Wire Wire Line
	8000 1650 8000 1350
Wire Wire Line
	8000 1350 7450 1350
Wire Wire Line
	8000 1850 8000 1950
Wire Wire Line
	8350 1850 8350 1950
Wire Wire Line
	8700 1850 8700 1950
Wire Wire Line
	9050 1850 9050 1950
Wire Wire Line
	9400 1850 9400 1950
Wire Wire Line
	9400 1950 9050 1950
Wire Wire Line
	8000 2250 9050 2250
Connection ~ 8350 2250
Connection ~ 8700 2250
Wire Wire Line
	9050 2250 9050 2350
$Comp
L +3.3V #PWR057
U 1 1 5995B10B
P 7450 1950
F 0 "#PWR057" H 7450 1800 50  0001 C CNN
F 1 "+3.3V" H 7450 2090 50  0000 C CNN
F 2 "" H 7450 1950 50  0001 C CNN
F 3 "" H 7450 1950 50  0001 C CNN
	1    7450 1950
	1    0    0    -1  
$EndComp
NoConn ~ 7450 1450
NoConn ~ 7450 1550
NoConn ~ 7450 1650
Wire Wire Line
	7450 1950 7450 2250
Connection ~ 7450 2050
Connection ~ 7450 2150
$Comp
L GNDD #PWR058
U 1 1 5995B30A
P 7450 2450
F 0 "#PWR058" H 7450 2200 50  0001 C CNN
F 1 "GNDD" H 7450 2300 50  0000 C CNN
F 2 "" H 7450 2450 50  0001 C CNN
F 3 "" H 7450 2450 50  0001 C CNN
	1    7450 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1450 6350 2550
Connection ~ 6350 1550
Connection ~ 6350 1650
Connection ~ 6350 1850
Connection ~ 6350 1950
Connection ~ 6350 2150
Connection ~ 6350 2250
Connection ~ 6350 2350
Connection ~ 6350 2450
Text HLabel 6200 1050 0    60   Input ~ 0
LED1
Text HLabel 6200 1150 0    60   Input ~ 0
LED2
Text HLabel 6200 1250 0    60   Input ~ 0
LED3
Text HLabel 6200 1350 0    60   Input ~ 0
LED4
Wire Wire Line
	6350 1050 6200 1050
Wire Wire Line
	6200 1150 6350 1150
Wire Wire Line
	6350 1250 6200 1250
Wire Wire Line
	6200 1350 6350 1350
$Comp
L R R28
U 1 1 5995C4CB
P 1550 6000
F 0 "R28" V 1630 6000 50  0000 C CNN
F 1 "10k" V 1550 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1480 6000 50  0001 C CNN
F 3 "" H 1550 6000 50  0001 C CNN
	1    1550 6000
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR059
U 1 1 5995C575
P 1400 6000
F 0 "#PWR059" H 1400 5850 50  0001 C CNN
F 1 "+3.3V" H 1400 6140 50  0000 C CNN
F 2 "" H 1400 6000 50  0001 C CNN
F 3 "" H 1400 6000 50  0001 C CNN
	1    1400 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6400 1800 6000
Wire Wire Line
	1800 6000 1700 6000
NoConn ~ 2700 6000
NoConn ~ 2700 6400
$Comp
L FT232RQ U10
U 1 1 5995A7F9
P 8550 5050
F 0 "U10" H 7900 5950 50  0000 L CNN
F 1 "FT232RQ" H 8950 5950 50  0000 L CNN
F 2 "Housings_DFN_QFN:QFN-32-1EP_5x5mm_Pitch0.5mm" H 8550 5050 50  0001 C CNN
F 3 "" H 8550 5050 50  0001 C CNN
	1    8550 5050
	1    0    0    -1  
$EndComp
$Comp
L NCP361SNT1G U9
U 1 1 5995A7A4
P 6600 3800
F 0 "U9" H 6150 4150 45  0000 L BNN
F 1 "NCP361SNT1G" H 6350 3100 45  0000 L BNN
F 2 "Zeabus:TSOP-5" H 6630 3950 20  0001 C CNN
F 3 "" H 6600 3800 60  0001 C CNN
	1    6600 3800
	1    0    0    -1  
$EndComp
$Comp
L USB_OTG J2
U 1 1 5995B100
P 4750 4650
F 0 "J2" H 4550 5100 50  0000 L CNN
F 1 "USB_OTG" H 4550 5000 50  0000 L CNN
F 2 "Connectors:USB_Mini-B" H 4900 4600 50  0001 C CNN
F 3 "" H 4900 4600 50  0001 C CNN
	1    4750 4650
	1    0    0    -1  
$EndComp
$Comp
L C_Small C55
U 1 1 5995B3CB
P 5500 3800
F 0 "C55" H 5510 3870 50  0000 L CNN
F 1 "0.01uF" H 5510 3720 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5500 3800 50  0001 C CNN
F 3 "" H 5500 3800 50  0001 C CNN
	1    5500 3800
	1    0    0    -1  
$EndComp
$Comp
L C_Small C54
U 1 1 5995B468
P 5250 3800
F 0 "C54" H 5260 3870 50  0000 L CNN
F 1 "1uF" H 5260 3720 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5250 3800 50  0001 C CNN
F 3 "" H 5250 3800 50  0001 C CNN
	1    5250 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4650 7750 4650
Wire Wire Line
	5050 4750 7750 4750
Wire Wire Line
	5100 3700 5900 3700
Connection ~ 5500 3700
Wire Wire Line
	5050 4450 5100 4450
Wire Wire Line
	5100 4450 5100 3700
Connection ~ 5250 3700
Wire Wire Line
	7300 3700 9250 3700
Wire Wire Line
	8650 3700 8650 4050
Wire Wire Line
	5250 3900 5900 3900
Connection ~ 5500 3900
Wire Wire Line
	5900 4200 5250 4200
Wire Wire Line
	5250 4200 5250 3900
$Comp
L GNDD #PWR060
U 1 1 5995BCD8
P 5500 4200
F 0 "#PWR060" H 5500 3950 50  0001 C CNN
F 1 "GNDD" H 5500 4050 50  0000 C CNN
F 2 "" H 5500 4200 50  0001 C CNN
F 3 "" H 5500 4200 50  0001 C CNN
	1    5500 4200
	1    0    0    -1  
$EndComp
Text Label 5400 4650 0    60   ~ 0
D+
Text Label 5400 4750 0    60   ~ 0
D-
$Comp
L TEST_1P J18
U 1 1 5995BE4F
P 5900 4000
F 0 "J18" H 5900 4270 50  0000 C CNN
F 1 "TEST_1P" V 5800 4050 50  0000 C CNN
F 2 "Zeabus:1Pin-TP" H 6100 4000 50  0001 C CNN
F 3 "" H 6100 4000 50  0001 C CNN
	1    5900 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4750 5100 4650 5100
Wire Wire Line
	4650 5100 4650 5050
Wire Wire Line
	4750 5050 4750 5100
Connection ~ 4750 5100
$Comp
L GNDD #PWR061
U 1 1 5995C30E
P 4750 5100
F 0 "#PWR061" H 4750 4850 50  0001 C CNN
F 1 "GNDD" H 4750 4950 50  0000 C CNN
F 2 "" H 4750 5100 50  0001 C CNN
F 3 "" H 4750 5100 50  0001 C CNN
	1    4750 5100
	1    0    0    -1  
$EndComp
Text GLabel 7500 5050 0    60   Input ~ 0
~RESET
Wire Wire Line
	7750 5050 7500 5050
$Comp
L TEST_1P J3
U 1 1 5995C49A
P 7750 5750
F 0 "J3" H 7750 6020 50  0000 C CNN
F 1 "TEST_1P" H 7750 5950 50  0000 C CNN
F 2 "Zeabus:1Pin-TP" H 7950 5750 50  0001 C CNN
F 3 "" H 7950 5750 50  0001 C CNN
	1    7750 5750
	0    -1   -1   0   
$EndComp
NoConn ~ 7750 5250
NoConn ~ 7750 5450
$Comp
L C_Small C57
U 1 1 5995C5B9
P 7450 4350
F 0 "C57" H 7460 4420 50  0000 L CNN
F 1 "0.1uF" H 7460 4270 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7450 4350 50  0001 C CNN
F 3 "" H 7450 4350 50  0001 C CNN
	1    7450 4350
	0    -1   -1   0   
$EndComp
$Comp
L GNDD #PWR062
U 1 1 5995C67D
P 7350 4350
F 0 "#PWR062" H 7350 4100 50  0001 C CNN
F 1 "GNDD" H 7350 4200 50  0000 C CNN
F 2 "" H 7350 4350 50  0001 C CNN
F 3 "" H 7350 4350 50  0001 C CNN
	1    7350 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 6050 8750 6050
Connection ~ 8650 6050
$Comp
L GNDD #PWR063
U 1 1 5995CA03
P 8650 6050
F 0 "#PWR063" H 8650 5800 50  0001 C CNN
F 1 "GNDD" H 8650 5900 50  0000 C CNN
F 2 "" H 8650 6050 50  0001 C CNN
F 3 "" H 8650 6050 50  0001 C CNN
	1    8650 6050
	1    0    0    -1  
$EndComp
Connection ~ 8550 6050
Wire Notes Line
	3900 500  3900 7800
Wire Notes Line
	3900 3200 11200 3200
NoConn ~ 5050 4850
$Comp
L C_Small C56
U 1 1 5996465A
P 7400 3800
F 0 "C56" H 7410 3870 50  0000 L CNN
F 1 "1uF" H 7410 3720 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7400 3800 50  0001 C CNN
F 3 "" H 7400 3800 50  0001 C CNN
	1    7400 3800
	1    0    0    -1  
$EndComp
Connection ~ 7400 3700
$Comp
L R R33
U 1 1 5996510F
P 9750 5200
F 0 "R33" V 9830 5200 50  0000 C CNN
F 1 "330" V 9750 5200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 9680 5200 50  0001 C CNN
F 3 "" H 9750 5200 50  0001 C CNN
	1    9750 5200
	-1   0    0    1   
$EndComp
$Comp
L LED_Small D7
U 1 1 59965115
P 9750 4850
F 0 "D7" H 9700 4975 50  0000 L CNN
F 1 "Blue" H 9650 4750 50  0000 L CNN
F 2 "LEDs:LED_0603" V 9750 4850 50  0001 C CNN
F 3 "" V 9750 4850 50  0001 C CNN
	1    9750 4850
	0    -1   -1   0   
$EndComp
$Comp
L LED_Small D8
U 1 1 5996511B
P 10100 4850
F 0 "D8" H 10050 4975 50  0000 L CNN
F 1 "Red" H 10000 4750 50  0000 L CNN
F 2 "LEDs:LED_0603" V 10100 4850 50  0001 C CNN
F 3 "" V 10100 4850 50  0001 C CNN
	1    10100 4850
	0    -1   -1   0   
$EndComp
$Comp
L LED_Small D9
U 1 1 59965121
P 10450 4850
F 0 "D9" H 10400 4975 50  0000 L CNN
F 1 "Green" H 10350 4750 50  0000 L CNN
F 2 "LEDs:LED_0603" V 10450 4850 50  0001 C CNN
F 3 "" V 10450 4850 50  0001 C CNN
	1    10450 4850
	0    -1   -1   0   
$EndComp
$Comp
L R R34
U 1 1 59965127
P 10100 5200
F 0 "R34" V 10180 5200 50  0000 C CNN
F 1 "330" V 10100 5200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10030 5200 50  0001 C CNN
F 3 "" H 10100 5200 50  0001 C CNN
	1    10100 5200
	-1   0    0    1   
$EndComp
$Comp
L R R35
U 1 1 5996512D
P 10450 5200
F 0 "R35" V 10530 5200 50  0000 C CNN
F 1 "330" V 10450 5200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10380 5200 50  0001 C CNN
F 3 "" H 10450 5200 50  0001 C CNN
	1    10450 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	9750 4950 9750 5050
Wire Wire Line
	10100 4950 10100 5050
Wire Wire Line
	10450 4950 10450 5050
NoConn ~ 9350 5750
NoConn ~ 9350 5050
NoConn ~ 9350 4950
NoConn ~ 9350 4850
NoConn ~ 9350 4750
NoConn ~ 9350 4650
NoConn ~ 9350 4550
Text Notes 9600 6350 0    60   ~ 0
CBUS0 = ~TxLED\nCBUS1 = ~RxLED\nCBUS2 = ~PWREN\nCBUS3 = ~SLEEP\nCBUS4 = Any output function
Wire Wire Line
	9350 5350 9750 5350
Wire Wire Line
	9350 5450 10100 5450
Wire Wire Line
	10100 5450 10100 5350
Wire Wire Line
	9350 5550 10450 5550
Wire Wire Line
	10450 5550 10450 5350
Wire Wire Line
	9750 4750 10450 4750
Connection ~ 10100 4750
$Comp
L TEST_1P J4
U 1 1 59967A04
P 9350 5650
F 0 "J4" H 9350 5920 50  0000 C CNN
F 1 "TEST_1P" V 9450 5900 50  0000 C CNN
F 2 "Zeabus:1Pin-TP" H 9550 5650 50  0001 C CNN
F 3 "" H 9550 5650 50  0001 C CNN
	1    9350 5650
	0    1    1    0   
$EndComp
Text HLabel 9750 4350 2    60   Input ~ 0
UART_TX
Text HLabel 9750 4450 2    60   Output ~ 0
UART_RX
Wire Wire Line
	9350 4350 9750 4350
Wire Wire Line
	9750 4450 9350 4450
Text Notes 2200 7100 2    60   ~ 12
Push buttons
Text Notes 7400 3050 2    60   ~ 12
Status LEDs
Text Notes 6350 6100 2    60   ~ 12
USB and Power input
Wire Wire Line
	7550 4350 7750 4350
Wire Wire Line
	7650 4350 7650 4050
Wire Wire Line
	7650 4050 8450 4050
Connection ~ 7650 4350
Text HLabel 9250 3700 2    60   Output ~ 0
V_USB
Connection ~ 8650 3700
$Comp
L GND #PWR064
U 1 1 599BCCAE
P 7400 3900
F 0 "#PWR064" H 7400 3650 50  0001 C CNN
F 1 "GND" H 7400 3750 50  0000 C CNN
F 2 "" H 7400 3900 50  0001 C CNN
F 3 "" H 7400 3900 50  0001 C CNN
	1    7400 3900
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR065
U 1 1 599C061F
P 10100 4750
F 0 "#PWR065" H 10100 4600 50  0001 C CNN
F 1 "+3.3V" H 10100 4890 50  0000 C CNN
F 2 "" H 10100 4750 50  0001 C CNN
F 3 "" H 10100 4750 50  0001 C CNN
	1    10100 4750
	1    0    0    -1  
$EndComp
Connection ~ 5500 4200
$EndSCHEMATC
