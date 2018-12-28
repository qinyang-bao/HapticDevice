EESchema Schematic File Version 4
EELAYER 26 0
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
L Connector:Conn_01x06_Male J2
U 1 1 5BC38CDF
P 3900 4000
F 0 "J2" H 4006 4378 50  0000 C CNN
F 1 "Conn_01x06_Male" H 4006 4287 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3900 4000 50  0001 C CNN
F 3 "~" H 3900 4000 50  0001 C CNN
	1    3900 4000
	1    0    0    -1  
$EndComp
Text Label 4500 3800 2    50   ~ 0
EN
Text Label 4500 3900 2    50   ~ 0
PWM
Text Label 4500 4000 2    50   ~ 0
LRA_ERM
Text Label 4500 4100 2    50   ~ 0
NC
Text Label 4500 4200 2    50   ~ 0
OUT-
Text Label 4500 4300 2    50   ~ 0
OUT+
Text Label 5400 3950 2    50   ~ 0
EN
Text Label 5400 4000 2    50   ~ 0
PWM
Text Label 5400 4050 2    50   ~ 0
LRA_ERM
Text Label 5400 4100 2    50   ~ 0
NC
Wire Wire Line
	5550 3950 5400 3950
Wire Wire Line
	5400 4000 5550 4000
Wire Wire Line
	5550 4050 5400 4050
Wire Wire Line
	5400 4100 5550 4100
Text Label 5950 3850 0    50   ~ 0
OUT+
Wire Wire Line
	5950 3850 5950 3950
$Comp
L Driver_Motor:drv2603 U1
U 1 1 5BC3895B
P 5750 4000
F 0 "U1" H 5789 4378 50  0000 C CNN
F 1 "drv2603" H 5789 4287 50  0000 C CNN
F 2 "DRV2603RUNR:QFN50P200X200X80-10N" H 5750 4000 50  0001 C CNN
F 3 "" H 5750 4000 50  0001 C CNN
	1    5750 4000
	1    0    0    -1  
$EndComp
Text Label 6200 4100 0    50   ~ 0
OUT-
Wire Wire Line
	6200 4100 5950 4100
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5BC3E102
P 7350 3650
F 0 "J1" V 7503 3463 50  0000 R CNN
F 1 "Conn_01x02_Male" V 7412 3463 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7350 3650 50  0001 C CNN
F 3 "~" H 7350 3650 50  0001 C CNN
	1    7350 3650
	0    -1   -1   0   
$EndComp
Text Label 5750 4300 2    50   ~ 0
GND
Wire Wire Line
	5750 4200 5750 4300
Wire Wire Line
	5750 3800 4850 3800
Wire Wire Line
	4850 3800 4850 4300
Wire Wire Line
	4850 4300 5750 4300
Wire Wire Line
	5950 4000 6600 4000
Wire Wire Line
	6600 4000 6600 4300
Wire Wire Line
	6600 4300 5750 4300
Connection ~ 5750 4300
Text Label 7350 3300 2    50   ~ 0
GND
Text Label 7450 3300 0    50   ~ 0
VDD
Text Label 6100 4050 2    50   ~ 0
VDD
Wire Wire Line
	6100 4050 5950 4050
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5BC41734
P 5750 4400
F 0 "#FLG0102" H 5750 4475 50  0001 C CNN
F 1 "PWR_FLAG" H 5750 4573 50  0000 C CNN
F 2 "" H 5750 4400 50  0001 C CNN
F 3 "~" H 5750 4400 50  0001 C CNN
	1    5750 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 4400 5750 4300
Text Label 5350 2600 2    50   ~ 0
EN_2
Text Label 5350 2650 2    50   ~ 0
PWM_2
Text Label 5350 2700 2    50   ~ 0
LRA_ERM_2
Text Label 5350 2750 2    50   ~ 0
NC_2
Wire Wire Line
	5500 2600 5350 2600
Wire Wire Line
	5350 2650 5500 2650
Wire Wire Line
	5500 2700 5350 2700
Wire Wire Line
	5350 2750 5500 2750
Text Label 5900 2500 0    50   ~ 0
OUT+_2
Wire Wire Line
	5900 2500 5900 2600
$Comp
L Driver_Motor:drv2603 U2
U 1 1 5BC41ABA
P 5700 2650
F 0 "U2" H 5739 3028 50  0000 C CNN
F 1 "drv2603" H 5739 2937 50  0000 C CNN
F 2 "DRV2603RUNR:QFN50P200X200X80-10N" H 5700 2650 50  0001 C CNN
F 3 "" H 5700 2650 50  0001 C CNN
	1    5700 2650
	1    0    0    -1  
$EndComp
Text Label 6150 2750 0    50   ~ 0
OUT-_2
Wire Wire Line
	6150 2750 5900 2750
Text Label 5700 2950 2    50   ~ 0
GND
Wire Wire Line
	5700 2850 5700 2950
Wire Wire Line
	5700 2450 4800 2450
Wire Wire Line
	4800 2450 4800 2950
Wire Wire Line
	4800 2950 5700 2950
Wire Wire Line
	5900 2650 6550 2650
Wire Wire Line
	6550 2650 6550 2950
Wire Wire Line
	6550 2950 5700 2950
Connection ~ 5700 2950
Text Label 6050 2700 2    50   ~ 0
VDD
Wire Wire Line
	6050 2700 5900 2700
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5BC41ACE
P 5700 3050
F 0 "#FLG0103" H 5700 3125 50  0001 C CNN
F 1 "PWR_FLAG" H 5700 3223 50  0000 C CNN
F 2 "" H 5700 3050 50  0001 C CNN
F 3 "~" H 5700 3050 50  0001 C CNN
	1    5700 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 3050 5700 2950
Wire Wire Line
	4100 3800 4500 3800
Wire Wire Line
	4100 3900 4500 3900
Wire Wire Line
	4100 4000 4500 4000
Wire Wire Line
	4100 4100 4500 4100
Wire Wire Line
	4100 4200 4500 4200
Wire Wire Line
	4100 4300 4500 4300
$Comp
L Connector:Conn_01x06_Male J3
U 1 1 5BC481F1
P 3800 2650
F 0 "J3" H 3906 3028 50  0000 C CNN
F 1 "Conn_01x06_Male" H 3906 2937 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3800 2650 50  0001 C CNN
F 3 "~" H 3800 2650 50  0001 C CNN
	1    3800 2650
	1    0    0    -1  
$EndComp
Text Label 4400 2450 2    50   ~ 0
EN_2
Text Label 4400 2550 2    50   ~ 0
PWM_2
Text Label 4400 2650 2    50   ~ 0
LRA_ERM_2
Text Label 4400 2750 2    50   ~ 0
NC_2
Text Label 4400 2850 2    50   ~ 0
OUT-_2
Text Label 4400 2950 2    50   ~ 0
OUT+_2
Wire Wire Line
	4000 2450 4400 2450
Wire Wire Line
	4000 2550 4400 2550
Wire Wire Line
	4000 2650 4400 2650
Wire Wire Line
	4000 2750 4400 2750
Wire Wire Line
	4000 2850 4400 2850
Wire Wire Line
	4000 2950 4400 2950
Wire Wire Line
	7350 3300 7350 3450
Wire Wire Line
	7450 3300 7450 3450
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5BC4BC7F
P 7450 3300
F 0 "#FLG0101" H 7450 3375 50  0001 C CNN
F 1 "PWR_FLAG" H 7450 3474 50  0000 C CNN
F 2 "" H 7450 3300 50  0001 C CNN
F 3 "~" H 7450 3300 50  0001 C CNN
	1    7450 3300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
