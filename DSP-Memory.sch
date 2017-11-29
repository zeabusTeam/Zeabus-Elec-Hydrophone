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
Sheet 3 8
Title "DSP Boot Flash and Reset Logic"
Date "17 August 2017"
Rev "1.0.0"
Comp "Zeabus, Kasetsart University"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ADSP-21489BSWZ-4B U1
U 1 1 59928C8D
P 5400 2600
F 0 "U1" H 4700 4300 45  0000 L BNN
F 1 "ADSP-21489BSWZ-4B" H 4700 1000 45  0000 L BNN
F 2 "Zeabus:ADSP-21489-177" H 5430 2750 20  0001 C CNN
F 3 "" H 5400 2600 60  0001 C CNN
	1    5400 2600
	1    0    0    -1  
$EndComp
$Comp
L S29GL032N U3
U 1 1 5993D1E1
P 8350 1400
F 0 "U3" H 8650 1500 60  0000 C CNN
F 1 "S29GL032N" H 8850 -1200 60  0000 C CNN
F 2 "Housings_SSOP:TSOP-I-48_12x18.4mm_Pitch0.5mm" H 8350 1400 60  0001 C CNN
F 3 "" H 8350 1400 60  0001 C CNN
	1    8350 1400
	1    0    0    -1  
$EndComp
NoConn ~ 6300 3400
NoConn ~ 6300 3500
NoConn ~ 6300 3600
NoConn ~ 6300 3700
NoConn ~ 6300 3800
NoConn ~ 6300 3900
NoConn ~ 6300 4000
NoConn ~ 6300 3200
NoConn ~ 6300 2800
NoConn ~ 6300 2600
NoConn ~ 6300 2500
NoConn ~ 6300 2400
NoConn ~ 6300 2300
NoConn ~ 6300 2200
NoConn ~ 6300 2100
NoConn ~ 6300 2000
NoConn ~ 6300 1900
Wire Wire Line
	4500 1100 4250 1100
Wire Wire Line
	4500 1200 4250 1200
Wire Wire Line
	4500 1300 4250 1300
Wire Wire Line
	4500 1400 4250 1400
Wire Wire Line
	4500 1500 4250 1500
Wire Wire Line
	4500 1600 4250 1600
Wire Wire Line
	4500 1700 4250 1700
Wire Wire Line
	4500 1800 4250 1800
Wire Wire Line
	4500 1900 4250 1900
Wire Wire Line
	4500 2000 4250 2000
Wire Wire Line
	4500 2100 4250 2100
Wire Wire Line
	4500 2200 4250 2200
Wire Wire Line
	4500 2300 4250 2300
Wire Wire Line
	4500 2400 4250 2400
Wire Wire Line
	4500 2500 4250 2500
Wire Wire Line
	4500 2600 4250 2600
Wire Wire Line
	4500 2700 4250 2700
Wire Wire Line
	4500 2800 4250 2800
Wire Wire Line
	4500 2900 4250 2900
Wire Wire Line
	4500 3000 4250 3000
Wire Wire Line
	4500 3100 4250 3100
Wire Wire Line
	4500 3200 4250 3200
Wire Wire Line
	6300 1100 6550 1100
Wire Wire Line
	6300 1200 6550 1200
Wire Wire Line
	6300 1300 6550 1300
Wire Wire Line
	6300 1400 6550 1400
Wire Wire Line
	6300 1500 6550 1500
Wire Wire Line
	6300 1600 6550 1600
Wire Wire Line
	6300 1700 6550 1700
Wire Wire Line
	6300 1800 6550 1800
Wire Wire Line
	6300 2900 6550 2900
Wire Wire Line
	6300 3000 6550 3000
Wire Wire Line
	6300 3100 6550 3100
NoConn ~ 9400 2800
NoConn ~ 9400 2700
NoConn ~ 9400 2600
NoConn ~ 9400 2500
NoConn ~ 9400 2400
NoConn ~ 9400 2300
NoConn ~ 9400 2200
Text Label 4250 1100 0    60   ~ 0
A0_Z
Text Label 4250 1200 0    60   ~ 0
A1_Z
Text Label 4250 1300 0    60   ~ 0
A2_Z
Text Label 4250 1400 0    60   ~ 0
A3_Z
Text Label 4250 1500 0    60   ~ 0
A4_Z
Text Label 4250 1600 0    60   ~ 0
A5_Z
Text Label 4250 1700 0    60   ~ 0
A6_Z
Text Label 4250 1800 0    60   ~ 0
A7_Z
Text Label 4250 1900 0    60   ~ 0
A8_Z
Text Label 4250 2000 0    60   ~ 0
A9_Z
Text Label 4250 2100 0    60   ~ 0
A10_Z
Text Label 4250 2200 0    60   ~ 0
A11_Z
Text Label 4250 2300 0    60   ~ 0
A12_Z
Text Label 4250 2400 0    60   ~ 0
A13_Z
Text Label 4250 2500 0    60   ~ 0
A14_Z
Text Label 4250 2600 0    60   ~ 0
A15_Z
Text Label 4250 2700 0    60   ~ 0
A16_Z
Text Label 4250 2800 0    60   ~ 0
A17_Z
Text Label 4250 2900 0    60   ~ 0
A18_Z
Text Label 4250 3000 0    60   ~ 0
A19_Z
Text Label 4250 3100 0    60   ~ 0
A20_Z
Text Label 4250 3200 0    60   ~ 0
A21_Z
Text Label 6300 1100 0    60   ~ 0
D0_Z
Text Label 6300 1200 0    60   ~ 0
D1_Z
Text Label 6300 1300 0    60   ~ 0
D2_Z
Text Label 6300 1400 0    60   ~ 0
D3_Z
Text Label 6300 1500 0    60   ~ 0
D4_Z
Text Label 6300 1600 0    60   ~ 0
D5_Z
Text Label 6300 1700 0    60   ~ 0
D6_Z
Text Label 6300 1800 0    60   ~ 0
D7_Z
Text Label 6300 2900 0    60   ~ 0
~MS1
Text Label 6300 3000 0    60   ~ 0
~AMI_RD
Text Label 6300 3100 0    60   ~ 0
~AMI_WR
Wire Wire Line
	8350 1400 8050 1400
Wire Wire Line
	8350 1500 8050 1500
Wire Wire Line
	8350 1600 8050 1600
Wire Wire Line
	8350 1700 8050 1700
Wire Wire Line
	8350 1800 8050 1800
Wire Wire Line
	8350 1900 8050 1900
Wire Wire Line
	8350 2000 8050 2000
Wire Wire Line
	8350 2100 8050 2100
Wire Wire Line
	8350 2200 8050 2200
Wire Wire Line
	8350 2300 8050 2300
Wire Wire Line
	8350 2400 8050 2400
Wire Wire Line
	8350 2500 8050 2500
Wire Wire Line
	8350 2600 8050 2600
Wire Wire Line
	8350 2700 8050 2700
Wire Wire Line
	8350 2800 8050 2800
Wire Wire Line
	8350 2900 8050 2900
Wire Wire Line
	8350 3000 8050 3000
Wire Wire Line
	8350 3100 8050 3100
Wire Wire Line
	8350 3200 8050 3200
Wire Wire Line
	8350 3300 8050 3300
Wire Wire Line
	8350 3400 8050 3400
Wire Wire Line
	6900 3600 8350 3600
Wire Wire Line
	8350 3700 8050 3700
Wire Wire Line
	8350 3800 8050 3800
Wire Wire Line
	7150 3900 8350 3900
Wire Wire Line
	9400 1600 9700 1600
Wire Wire Line
	9400 1700 9700 1700
Wire Wire Line
	9400 1800 9700 1800
Wire Wire Line
	9400 1900 9700 1900
Wire Wire Line
	9400 2000 9700 2000
Wire Wire Line
	9400 2100 9700 2100
Wire Wire Line
	9400 2900 9700 2900
Wire Wire Line
	9400 1400 9700 1400
Wire Wire Line
	9400 1500 9700 1500
Text Label 8050 1400 0    60   ~ 0
A1
Text Label 8050 1500 0    60   ~ 0
A2
Text Label 8050 1600 0    60   ~ 0
A3
Text Label 8050 1700 0    60   ~ 0
A4
Text Label 8050 1800 0    60   ~ 0
A5
Text Label 8050 1900 0    60   ~ 0
A6
Text Label 8050 2000 0    60   ~ 0
A7
Text Label 8050 2100 0    60   ~ 0
A8
Text Label 8050 2200 0    60   ~ 0
A9
Text Label 8050 2300 0    60   ~ 0
A10
Text Label 8050 2400 0    60   ~ 0
A11
Text Label 8050 2500 0    60   ~ 0
A12
Text Label 8050 2600 0    60   ~ 0
A13
Text Label 8050 2700 0    60   ~ 0
A14
Text Label 8050 2800 0    60   ~ 0
A15
Text Label 8050 2900 0    60   ~ 0
A16
Text Label 8050 3000 0    60   ~ 0
A17
Text Label 8050 3100 0    60   ~ 0
A18
Text Label 8050 3200 0    60   ~ 0
A19
Text Label 8050 3300 0    60   ~ 0
A20
Text Label 8050 3400 0    60   ~ 0
A21
Text Label 9450 1400 0    60   ~ 0
D0
Text Label 9450 1500 0    60   ~ 0
D1
Text Label 9450 1600 0    60   ~ 0
D2
Text Label 9450 1700 0    60   ~ 0
D3
Text Label 9450 1800 0    60   ~ 0
D4
Text Label 9450 1900 0    60   ~ 0
D5
Text Label 9450 2000 0    60   ~ 0
D6
Text Label 9450 2100 0    60   ~ 0
D7
Text Label 9450 2900 0    60   ~ 0
A0
Text Label 8050 3700 0    60   ~ 0
~RD
Text Label 8050 3800 0    60   ~ 0
~WR
$Comp
L R R14
U 1 1 59940626
P 7600 3350
F 0 "R14" V 7680 3350 50  0000 C CNN
F 1 "10k" V 7600 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 7530 3350 50  0001 C CNN
F 3 "" H 7600 3350 50  0001 C CNN
	1    7600 3350
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 59940656
P 7400 3350
F 0 "R13" V 7480 3350 50  0000 C CNN
F 1 "10k" V 7400 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 7330 3350 50  0001 C CNN
F 3 "" H 7400 3350 50  0001 C CNN
	1    7400 3350
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 5994067B
P 9950 3850
F 0 "R15" V 10030 3850 50  0000 C CNN
F 1 "10k" V 9950 3850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 9880 3850 50  0001 C CNN
F 3 "" H 9950 3850 50  0001 C CNN
	1    9950 3850
	1    0    0    -1  
$EndComp
$Comp
L C_Small C45
U 1 1 5994072B
P 7400 4050
F 0 "C45" H 7410 4120 50  0000 L CNN
F 1 "0.01uF" H 7410 3970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7400 4050 50  0001 C CNN
F 3 "" H 7400 4050 50  0001 C CNN
	1    7400 4050
	1    0    0    -1  
$EndComp
$Comp
L Jumper JP1
U 1 1 59940772
P 7150 4200
F 0 "JP1" H 7150 4350 50  0000 C CNN
F 1 "Write Protect" H 7150 4120 50  0000 C CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7150 4200 50  0001 C CNN
F 3 "" H 7150 4200 50  0001 C CNN
	1    7150 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	7600 3600 7600 3500
Connection ~ 7600 3600
Wire Wire Line
	7400 3500 7400 3950
Connection ~ 7400 3900
Wire Wire Line
	7400 4500 7400 4150
Wire Wire Line
	7150 4500 7400 4500
Wire Wire Line
	7400 3200 7600 3200
Wire Wire Line
	9400 3700 9950 3700
$Comp
L +3.3V #PWR032
U 1 1 59940B9E
P 7500 3200
F 0 "#PWR032" H 7500 3050 50  0001 C CNN
F 1 "+3.3V" H 7500 3340 50  0000 C CNN
F 2 "" H 7500 3200 50  0001 C CNN
F 3 "" H 7500 3200 50  0001 C CNN
	1    7500 3200
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR033
U 1 1 59940BC7
P 7300 4500
F 0 "#PWR033" H 7300 4250 50  0001 C CNN
F 1 "GNDD" H 7300 4350 50  0000 C CNN
F 2 "" H 7300 4500 50  0001 C CNN
F 3 "" H 7300 4500 50  0001 C CNN
	1    7300 4500
	1    0    0    -1  
$EndComp
Connection ~ 7500 3200
Connection ~ 7300 4500
Wire Wire Line
	9400 3800 9400 4050
Wire Wire Line
	9400 4050 10250 4050
Wire Wire Line
	9950 4050 9950 4000
Connection ~ 9400 3900
$Comp
L C_Small C46
U 1 1 59940CA2
P 10250 3700
F 0 "C46" H 10260 3770 50  0000 L CNN
F 1 "0.01uF" H 10260 3620 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10250 3700 50  0001 C CNN
F 3 "" H 10250 3700 50  0001 C CNN
	1    10250 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 4050 10250 3800
Connection ~ 9950 4050
Wire Wire Line
	10250 3600 10250 3400
Wire Wire Line
	10250 3400 9400 3400
$Comp
L +3.3V #PWR034
U 1 1 59940DC4
P 10250 3400
F 0 "#PWR034" H 10250 3250 50  0001 C CNN
F 1 "+3.3V" H 10250 3540 50  0000 C CNN
F 2 "" H 10250 3400 50  0001 C CNN
F 3 "" H 10250 3400 50  0001 C CNN
	1    10250 3400
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR035
U 1 1 59940DE7
P 9950 4050
F 0 "#PWR035" H 9950 3800 50  0001 C CNN
F 1 "GNDD" H 9950 3900 50  0000 C CNN
F 2 "" H 9950 4050 50  0001 C CNN
F 3 "" H 9950 4050 50  0001 C CNN
	1    9950 4050
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P J22
U 1 1 59940E9F
P 10000 3000
F 0 "J22" H 10000 3270 50  0000 C CNN
F 1 "TEST_1P" H 10000 3200 50  0000 C CNN
F 2 "Zeabus:1Pin-TP" H 10200 3000 50  0001 C CNN
F 3 "" H 10200 3000 50  0001 C CNN
	1    10000 3000
	1    0    0    -1  
$EndComp
Text Label 6900 3600 0    60   ~ 0
~Flash_CS
Wire Wire Line
	9400 3100 10000 3100
Wire Wire Line
	10000 3100 10000 3000
Text Label 9450 3200 0    60   ~ 0
~RESET
Wire Wire Line
	9400 3200 9700 3200
$Comp
L R_Pack04 RN6
U 1 1 599411FA
P 6650 5250
F 0 "RN6" V 6350 5250 50  0000 C CNN
F 1 "EXBN8V-22" V 6850 5250 50  0000 C CNN
F 2 "Zeabus:CRA06S" V 6925 5250 50  0001 C CNN
F 3 "" H 6650 5250 50  0001 C CNN
	1    6650 5250
	0    1    1    0   
$EndComp
$Comp
L R_Pack04 RN7
U 1 1 5994154F
P 6650 5850
F 0 "RN7" V 6350 5850 50  0000 C CNN
F 1 "EXBN8V-22" V 6850 5850 50  0000 C CNN
F 2 "Zeabus:CRA06S" V 6925 5850 50  0001 C CNN
F 3 "" H 6650 5850 50  0001 C CNN
	1    6650 5850
	0    1    1    0   
$EndComp
$Comp
L R_Pack04 RN8
U 1 1 5994158F
P 7600 5250
F 0 "RN8" V 7300 5250 50  0000 C CNN
F 1 "EXBN8V-22" V 7800 5250 50  0000 C CNN
F 2 "Zeabus:CRA06S" V 7875 5250 50  0001 C CNN
F 3 "" H 7600 5250 50  0001 C CNN
	1    7600 5250
	0    1    1    0   
$EndComp
$Comp
L R_Pack04 RN11
U 1 1 599415CD
P 8550 5850
F 0 "RN11" V 8250 5850 50  0000 C CNN
F 1 "EXBN8V-22" V 8750 5850 50  0000 C CNN
F 2 "Zeabus:CRA06S" V 8825 5850 50  0001 C CNN
F 3 "" H 8550 5850 50  0001 C CNN
	1    8550 5850
	0    1    1    0   
$EndComp
$Comp
L R_Pack04 RN12
U 1 1 5994160F
P 9500 5250
F 0 "RN12" V 9200 5250 50  0000 C CNN
F 1 "EXBN8V-22" V 9700 5250 50  0000 C CNN
F 2 "Zeabus:CRA06S" V 9775 5250 50  0001 C CNN
F 3 "" H 9500 5250 50  0001 C CNN
	1    9500 5250
	0    1    1    0   
$EndComp
$Comp
L R_Pack04 RN9
U 1 1 59941656
P 7600 5850
F 0 "RN9" V 7300 5850 50  0000 C CNN
F 1 "EXBN8V-22" V 7800 5850 50  0000 C CNN
F 2 "Zeabus:CRA06S" V 7875 5850 50  0001 C CNN
F 3 "" H 7600 5850 50  0001 C CNN
	1    7600 5850
	0    1    1    0   
$EndComp
$Comp
L R_Pack04 RN10
U 1 1 599416B2
P 8550 5250
F 0 "RN10" V 8250 5250 50  0000 C CNN
F 1 "EXBN8V-22" V 8750 5250 50  0000 C CNN
F 2 "Zeabus:CRA06S" V 8825 5250 50  0001 C CNN
F 3 "" H 8550 5250 50  0001 C CNN
	1    8550 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	6850 5050 7100 5050
Wire Wire Line
	6850 5150 7100 5150
Wire Wire Line
	6850 5250 7100 5250
Wire Wire Line
	6850 5350 7100 5350
Wire Wire Line
	6850 5650 7100 5650
Wire Wire Line
	6850 5750 7100 5750
Wire Wire Line
	6850 5850 7100 5850
Wire Wire Line
	6850 5950 7100 5950
Wire Wire Line
	7800 5050 8050 5050
Wire Wire Line
	7800 5150 8050 5150
Wire Wire Line
	7800 5250 8050 5250
Wire Wire Line
	7800 5350 8050 5350
Wire Wire Line
	6450 5050 6250 5050
Wire Wire Line
	6450 5150 6250 5150
Wire Wire Line
	6450 5250 6250 5250
Wire Wire Line
	6450 5350 6250 5350
Wire Wire Line
	6450 5650 6250 5650
Wire Wire Line
	6450 5750 6250 5750
Wire Wire Line
	6450 5850 6250 5850
Wire Wire Line
	6450 5950 6250 5950
Wire Wire Line
	7400 5050 7200 5050
Wire Wire Line
	7400 5150 7200 5150
Wire Wire Line
	7400 5250 7200 5250
Wire Wire Line
	7400 5350 7200 5350
Text Label 6850 5050 0    60   ~ 0
A0_Z
Text Label 6850 5150 0    60   ~ 0
A1_Z
Text Label 6850 5250 0    60   ~ 0
A2_Z
Text Label 6850 5350 0    60   ~ 0
A3_Z
Text Label 6850 5650 0    60   ~ 0
A4_Z
Text Label 6850 5750 0    60   ~ 0
A5_Z
Text Label 6850 5850 0    60   ~ 0
A6_Z
Text Label 6850 5950 0    60   ~ 0
A7_Z
Text Label 7800 5050 0    60   ~ 0
A8_Z
Text Label 7800 5150 0    60   ~ 0
A9_Z
Text Label 7800 5250 0    60   ~ 0
A10_Z
Text Label 7800 5350 0    60   ~ 0
A11_Z
Text Label 6250 5050 0    60   ~ 0
A0
Text Label 6250 5150 0    60   ~ 0
A1
Text Label 6250 5250 0    60   ~ 0
A2
Text Label 6250 5350 0    60   ~ 0
A3
Text Label 6250 5650 0    60   ~ 0
A4
Text Label 6250 5750 0    60   ~ 0
A5
Text Label 6250 5850 0    60   ~ 0
A6
Text Label 6250 5950 0    60   ~ 0
A7
Text Label 7200 5050 0    60   ~ 0
A8
Text Label 7200 5150 0    60   ~ 0
A9
Text Label 7200 5250 0    60   ~ 0
A10
Text Label 7200 5350 0    60   ~ 0
A11
Wire Wire Line
	7400 5650 7200 5650
Wire Wire Line
	7400 5750 7200 5750
Wire Wire Line
	7400 5850 7200 5850
Wire Wire Line
	7400 5950 7200 5950
Wire Wire Line
	7800 5650 8050 5650
Wire Wire Line
	7800 5750 8050 5750
Wire Wire Line
	7800 5850 8050 5850
Wire Wire Line
	7800 5950 8050 5950
Wire Wire Line
	8350 5050 8150 5050
Wire Wire Line
	8350 5150 8150 5150
Wire Wire Line
	8350 5250 8150 5250
Wire Wire Line
	8350 5350 8150 5350
Wire Wire Line
	8750 5050 9000 5050
Wire Wire Line
	8750 5150 9000 5150
Wire Wire Line
	8750 5250 9000 5250
Wire Wire Line
	8750 5350 9000 5350
Text Label 7800 5650 0    60   ~ 0
A12_Z
Text Label 7800 5750 0    60   ~ 0
A17_Z
Text Label 7800 5850 0    60   ~ 0
A13_Z
Text Label 7800 5950 0    60   ~ 0
A18_Z
Text Label 7200 5650 0    60   ~ 0
A12
Text Label 7200 5750 0    60   ~ 0
A17
Text Label 7200 5850 0    60   ~ 0
A13
Text Label 7200 5950 0    60   ~ 0
A18
Text Label 8750 5050 0    60   ~ 0
A23_Z
Text Label 8750 5150 0    60   ~ 0
A22_Z
Text Label 8750 5250 0    60   ~ 0
A21_Z
Text Label 8750 5350 0    60   ~ 0
A20_Z
Text Label 8150 5050 0    60   ~ 0
A23
Text Label 8150 5150 0    60   ~ 0
A22
Text Label 8150 5250 0    60   ~ 0
A21
Text Label 8150 5350 0    60   ~ 0
A20
Wire Wire Line
	4500 3300 4250 3300
Wire Wire Line
	4500 3400 4250 3400
Text Label 4250 3300 0    60   ~ 0
A22_Z
Text Label 4250 3400 0    60   ~ 0
A23_Z
Wire Wire Line
	8750 5650 9000 5650
Wire Wire Line
	8750 5750 9000 5750
Wire Wire Line
	8750 5850 9000 5850
Wire Wire Line
	8750 5950 9000 5950
Wire Wire Line
	8350 5650 8150 5650
Wire Wire Line
	8350 5750 8150 5750
Wire Wire Line
	8350 5850 8150 5850
Wire Wire Line
	8350 5950 8150 5950
Text Label 8750 5650 0    60   ~ 0
A19_Z
Text Label 8750 5750 0    60   ~ 0
A16_Z
Text Label 8750 5850 0    60   ~ 0
A15_Z
Text Label 8750 5950 0    60   ~ 0
A14_Z
Text Label 8150 5650 0    60   ~ 0
A19
Text Label 8150 5750 0    60   ~ 0
A16
Text Label 8150 5850 0    60   ~ 0
A15
Text Label 8150 5950 0    60   ~ 0
A14
$Comp
L R_Pack04 RN13
U 1 1 59947A2E
P 9500 5850
F 0 "RN13" V 9200 5850 50  0000 C CNN
F 1 "EXBN8V-22" V 9700 5850 50  0000 C CNN
F 2 "Zeabus:CRA06S" V 9775 5850 50  0001 C CNN
F 3 "" H 9500 5850 50  0001 C CNN
	1    9500 5850
	0    1    1    0   
$EndComp
Wire Wire Line
	9700 5050 9950 5050
Wire Wire Line
	9700 5150 9950 5150
Wire Wire Line
	9700 5250 9950 5250
Wire Wire Line
	9700 5350 9950 5350
Wire Wire Line
	9700 5650 9950 5650
Wire Wire Line
	9700 5750 9950 5750
Wire Wire Line
	9700 5850 9950 5850
Wire Wire Line
	9700 5950 9950 5950
Wire Wire Line
	9300 5950 9100 5950
Wire Wire Line
	9300 5850 9100 5850
Wire Wire Line
	9300 5750 9100 5750
Wire Wire Line
	9300 5650 9100 5650
Wire Wire Line
	9300 5350 9100 5350
Wire Wire Line
	9300 5250 9100 5250
Wire Wire Line
	9300 5150 9100 5150
Wire Wire Line
	9300 5050 9100 5050
Text Label 9700 5050 0    60   ~ 0
D0_Z
Text Label 9700 5150 0    60   ~ 0
D1_Z
Text Label 9700 5250 0    60   ~ 0
D2_Z
Text Label 9700 5350 0    60   ~ 0
D3_Z
Text Label 9700 5650 0    60   ~ 0
D4_Z
Text Label 9700 5750 0    60   ~ 0
D5_Z
Text Label 9700 5850 0    60   ~ 0
D6_Z
Text Label 9700 5950 0    60   ~ 0
D7_Z
Text Label 9100 5950 0    60   ~ 0
D7
Text Label 9100 5850 0    60   ~ 0
D6
Text Label 9100 5750 0    60   ~ 0
D5
Text Label 9100 5650 0    60   ~ 0
D4
Text Label 9100 5350 0    60   ~ 0
D3
Text Label 9100 5250 0    60   ~ 0
D2
Text Label 9100 5150 0    60   ~ 0
D1
Text Label 9100 5050 0    60   ~ 0
D0
$Comp
L R R10
U 1 1 5994A11D
P 10550 5350
F 0 "R10" V 10630 5350 50  0000 C CNN
F 1 "22" V 10550 5350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10480 5350 50  0001 C CNN
F 3 "" H 10550 5350 50  0001 C CNN
	1    10550 5350
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 5994A267
P 10550 5550
F 0 "R11" V 10630 5550 50  0000 C CNN
F 1 "22" V 10550 5550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10480 5550 50  0001 C CNN
F 3 "" H 10550 5550 50  0001 C CNN
	1    10550 5550
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 5994A2B4
P 10550 5750
F 0 "R12" V 10630 5750 50  0000 C CNN
F 1 "22" V 10550 5750 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 10480 5750 50  0001 C CNN
F 3 "" H 10550 5750 50  0001 C CNN
	1    10550 5750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10400 5350 10150 5350
Wire Wire Line
	10100 5550 10400 5550
Wire Wire Line
	10100 5750 10400 5750
Wire Wire Line
	10700 5350 10950 5350
Wire Wire Line
	10700 5550 10950 5550
Wire Wire Line
	10700 5750 10950 5750
Text Label 10150 5350 0    60   ~ 0
~MS1
Text Label 10100 5550 0    60   ~ 0
~AMI_RD
Text Label 10100 5750 0    60   ~ 0
~AMI_WR
Text Label 10700 5350 0    60   ~ 0
~Flash_CS
Text Label 10750 5550 0    60   ~ 0
~RD
Text Label 10750 5750 0    60   ~ 0
~WR
$Comp
L Resonator Y1
U 1 1 5994CC01
P 3600 3750
F 0 "Y1" V 3250 3650 50  0000 C CNN
F 1 "CSTCC2M00G53-R0" V 3350 3700 50  0000 C CNN
F 2 "Crystals:Resonator_7.2x3mm" H 3575 3750 50  0001 C CNN
F 3 "" H 3575 3750 50  0001 C CNN
	1    3600 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 3600 4500 3600
Wire Wire Line
	4500 3700 3950 3700
Wire Wire Line
	3950 3700 3750 3900
Wire Wire Line
	3750 3900 3600 3900
$Comp
L GNDD #PWR036
U 1 1 5994D5CC
P 3250 3800
F 0 "#PWR036" H 3250 3550 50  0001 C CNN
F 1 "GNDD" H 3250 3650 50  0000 C CNN
F 2 "" H 3250 3800 50  0001 C CNN
F 3 "" H 3250 3800 50  0001 C CNN
	1    3250 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3800 3250 3750
Wire Wire Line
	3250 3750 3400 3750
$Comp
L ADM708SARZ U6
U 1 1 5995340C
P 1300 6350
F 0 "U6" H 1650 6600 45  0000 L BNN
F 1 "ADM708SARZ" H 1600 5350 45  0000 L BNN
F 2 "Zeabus:ADM708_R_8" H 1330 6500 20  0001 C CNN
F 3 "" H 1300 6350 60  0001 C CNN
	1    1300 6350
	1    0    0    -1  
$EndComp
$Comp
L 74LVC1G08 U4
U 1 1 59954102
P 2300 5100
F 0 "U4" H 2300 5150 50  0000 C CNN
F 1 "74LVC1G08" H 2300 5050 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-353" H 2300 5100 50  0001 C CNN
F 3 "" H 2300 5100 50  0001 C CNN
	1    2300 5100
	1    0    0    -1  
$EndComp
$Comp
L 74LVC1G08 U5
U 1 1 59954174
P 3600 5000
F 0 "U5" H 3600 5050 50  0000 C CNN
F 1 "74LVC1G08" H 3600 4950 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-353" H 3600 5000 50  0001 C CNN
F 3 "" H 3600 5000 50  0001 C CNN
	1    3600 5000
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 5995426D
P 1400 4450
F 0 "R16" V 1480 4450 50  0000 C CNN
F 1 "10k" V 1400 4450 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1330 4450 50  0001 C CNN
F 3 "" H 1400 4450 50  0001 C CNN
	1    1400 4450
	1    0    0    -1  
$EndComp
$Comp
L R R17
U 1 1 59954303
P 1600 4450
F 0 "R17" V 1680 4450 50  0000 C CNN
F 1 "10k" V 1600 4450 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1530 4450 50  0001 C CNN
F 3 "" H 1600 4450 50  0001 C CNN
	1    1600 4450
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 5995436A
P 3000 4450
F 0 "R18" V 3080 4450 50  0000 C CNN
F 1 "10k" V 3000 4450 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2930 4450 50  0001 C CNN
F 3 "" H 3000 4450 50  0001 C CNN
	1    3000 4450
	1    0    0    -1  
$EndComp
$Comp
L R R19
U 1 1 599543E2
P 4600 6300
F 0 "R19" V 4680 6300 50  0000 C CNN
F 1 "330" V 4600 6300 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4530 6300 50  0001 C CNN
F 3 "" H 4600 6300 50  0001 C CNN
	1    4600 6300
	1    0    0    -1  
$EndComp
$Comp
L LED_Small D1
U 1 1 59954ABA
P 4600 6050
F 0 "D1" H 4550 6175 50  0000 L CNN
F 1 "Yellow" V 4600 5750 50  0000 L CNN
F 2 "LEDs:LED_0603" V 4600 6050 50  0001 C CNN
F 3 "" V 4600 6050 50  0001 C CNN
	1    4600 6050
	0    -1   -1   0   
$EndComp
$Comp
L SW_Push_Dual SW2
U 1 1 59954B50
P 1200 5550
F 0 "SW2" H 1250 5650 50  0000 L CNN
F 1 "PB" H 1200 5280 50  0000 C CNN
F 2 "Zeabus:Button-EVQ" H 1200 5750 50  0001 C CNN
F 3 "" H 1200 5750 50  0001 C CNN
	1    1200 5550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 5100 3000 5100
Wire Wire Line
	1400 4300 1400 4250
Wire Wire Line
	1400 4250 3450 4250
Wire Wire Line
	3450 4250 3450 4700
Wire Wire Line
	3000 4300 3000 4250
Connection ~ 3000 4250
Wire Wire Line
	1600 4300 1600 4250
Connection ~ 1600 4250
Wire Wire Line
	2150 4800 2150 4250
Connection ~ 2150 4250
Wire Wire Line
	3000 4900 3000 4600
Wire Wire Line
	850  5000 1700 5000
Wire Wire Line
	1600 5000 1600 4600
Wire Wire Line
	1700 5200 1400 5200
Wire Wire Line
	1400 4600 1400 5350
Connection ~ 1400 5200
Wire Wire Line
	1200 5750 1200 5850
Wire Wire Line
	850  5850 3450 5850
Wire Wire Line
	3450 5850 3450 5300
Wire Wire Line
	2150 5400 2150 5850
Connection ~ 2150 5850
Wire Wire Line
	1400 5750 1400 5850
Connection ~ 1400 5850
Wire Wire Line
	1400 5350 1200 5350
Wire Wire Line
	1300 6450 1100 6450
Wire Wire Line
	1100 6450 1100 6000
Wire Wire Line
	1100 6000 4200 6000
Wire Wire Line
	4200 6000 4200 5000
Wire Wire Line
	4500 3800 4300 3800
Wire Wire Line
	4300 3800 4300 4650
Wire Wire Line
	4300 4650 3000 4650
Connection ~ 3000 4650
$Comp
L GNDD #PWR037
U 1 1 59955DE7
P 3800 5650
F 0 "#PWR037" H 3800 5400 50  0001 C CNN
F 1 "GNDD" H 3800 5500 50  0000 C CNN
F 2 "" H 3800 5650 50  0001 C CNN
F 3 "" H 3800 5650 50  0001 C CNN
	1    3800 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5650 3450 5650
Connection ~ 3450 5650
$Comp
L +3.3V #PWR038
U 1 1 59956004
P 2150 4250
F 0 "#PWR038" H 2150 4100 50  0001 C CNN
F 1 "+3.3V" H 2150 4390 50  0000 C CNN
F 2 "" H 2150 4250 50  0001 C CNN
F 3 "" H 2150 4250 50  0001 C CNN
	1    2150 4250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR039
U 1 1 59956069
P 1000 6950
F 0 "#PWR039" H 1000 6800 50  0001 C CNN
F 1 "+3.3V" H 1000 7090 50  0000 C CNN
F 2 "" H 1000 6950 50  0001 C CNN
F 3 "" H 1000 6950 50  0001 C CNN
	1    1000 6950
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR040
U 1 1 59956182
P 3700 6950
F 0 "#PWR040" H 3700 6700 50  0001 C CNN
F 1 "GNDD" H 3700 6800 50  0000 C CNN
F 2 "" H 3700 6950 50  0001 C CNN
F 3 "" H 3700 6950 50  0001 C CNN
	1    3700 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 6350 1200 6350
Wire Wire Line
	1200 6350 1200 7100
Wire Wire Line
	1000 6950 1300 6950
Connection ~ 1200 6950
$Comp
L +3.3V #PWR041
U 1 1 59956548
P 4600 5950
F 0 "#PWR041" H 4600 5800 50  0001 C CNN
F 1 "+3.3V" H 4600 6090 50  0000 C CNN
F 2 "" H 4600 5950 50  0001 C CNN
F 3 "" H 4600 5950 50  0001 C CNN
	1    4600 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 6550 4900 6550
Wire Wire Line
	4600 6450 4600 6550
Connection ~ 4600 6550
Text Label 3800 6550 0    60   ~ 0
~RESET
$Comp
L Jumper JP2
U 1 1 59956EB4
P 850 5500
F 0 "JP2" H 850 5650 50  0000 C CNN
F 1 "External Reset" H 850 5420 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 850 5500 50  0001 C CNN
F 3 "" H 850 5500 50  0001 C CNN
	1    850  5500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	850  5850 850  5800
Connection ~ 1200 5850
Wire Wire Line
	850  5200 850  5000
Connection ~ 1600 5000
Wire Notes Line
	500  4000 4450 4000
Wire Notes Line
	4450 4000 5500 5200
Wire Notes Line
	5500 5200 5500 7800
Text Notes 2150 7600 0    60   ~ 12
Reset Logic
Text GLabel 4900 6550 2    60   Output ~ 12
~RESET
$Comp
L C_Small C47
U 1 1 5995A997
P 1200 7200
F 0 "C47" H 1210 7270 50  0000 L CNN
F 1 "0.01uF" H 1210 7120 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1200 7200 50  0001 C CNN
F 3 "" H 1200 7200 50  0001 C CNN
	1    1200 7200
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR042
U 1 1 5995AC03
P 1200 7300
F 0 "#PWR042" H 1200 7050 50  0001 C CNN
F 1 "GNDD" H 1200 7150 50  0000 C CNN
F 2 "" H 1200 7300 50  0001 C CNN
F 3 "" H 1200 7300 50  0001 C CNN
	1    1200 7300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
