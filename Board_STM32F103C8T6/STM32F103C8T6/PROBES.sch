EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 1900 4000 0    50   Input ~ 0
COIL_RPM
Wire Wire Line
	1900 4000 1950 4000
Wire Wire Line
	1950 4000 1950 4050
Wire Wire Line
	1950 4000 2000 4000
Connection ~ 1950 4000
$Comp
L Device:R_Small R703
U 1 1 608E6B2B
P 2450 4000
F 0 "R703" V 2254 4000 50  0000 C CNN
F 1 "4k7" V 2345 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" H 2450 4000 50  0001 C CNN
F 3 "~" H 2450 4000 50  0001 C CNN
F 4 "C52443" H 2450 4000 50  0001 C CNN "LCSC Part #"
	1    2450 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R704
U 1 1 608E7676
P 2600 4150
F 0 "R704" H 2659 4196 50  0000 L CNN
F 1 "10K" H 2659 4105 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" H 2600 4150 50  0001 C CNN
F 3 "~" H 2600 4150 50  0001 C CNN
F 4 "C25672" H 2600 4150 50  0001 C CNN "LCSC Part #"
	1    2600 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C702
U 1 1 608E84B8
P 2950 4150
F 0 "C702" H 3042 4196 50  0000 L CNN
F 1 "220n" H 3042 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric_Pad1.33x2.70mm_HandSolder" H 2950 4150 50  0001 C CNN
F 3 "~" H 2950 4150 50  0001 C CNN
F 4 "C396814" H 2950 4150 50  0001 C CNN "LCSC Part #"
	1    2950 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener_Small D704
U 1 1 608EB557
P 3400 4150
F 0 "D704" V 3354 4220 50  0000 L CNN
F 1 "5v1" V 3445 4220 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 3400 4150 50  0001 C CNN
F 3 "~" V 3400 4150 50  0001 C CNN
F 4 "C78479" H 3400 4150 50  0001 C CNN "LCSC Part #"
	1    3400 4150
	0    1    1    0   
$EndComp
$Comp
L Device:D_Small D702
U 1 1 608ED048
P 2100 4000
F 0 "D702" H 2100 3793 50  0000 C CNN
F 1 "1N4007F" H 2100 3884 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" V 2100 4000 50  0001 C CNN
F 3 "~" V 2100 4000 50  0001 C CNN
F 4 "C110856" H 2100 4000 50  0001 C CNN "LCSC Part #"
	1    2100 4000
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Small D701
U 1 1 608EE357
P 1950 4150
F 0 "D701" V 1904 4220 50  0000 L CNN
F 1 "1N4007F" V 1995 4220 50  0000 L CNN
F 2 "Diode_SMD:D_SMA" V 1950 4150 50  0001 C CNN
F 3 "~" V 1950 4150 50  0001 C CNN
F 4 "C110856" H 1950 4150 50  0001 C CNN "LCSC Part #"
	1    1950 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 4000 2600 4000
Wire Wire Line
	2600 4050 2600 4000
Connection ~ 2600 4000
Wire Wire Line
	2600 4000 2950 4000
Wire Wire Line
	2950 4050 2950 4000
Connection ~ 2950 4000
Wire Wire Line
	2950 4000 3000 4000
Wire Wire Line
	2200 4000 2350 4000
$Comp
L Device:D_Small D703
U 1 1 608F07CE
P 3100 4000
F 0 "D703" H 3100 3793 50  0000 C CNN
F 1 "1N4148WS" H 3100 3884 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323F" V 3100 4000 50  0001 C CNN
F 3 "~" V 3100 4000 50  0001 C CNN
F 4 "C2128" H 3100 4000 50  0001 C CNN "LCSC Part #"
	1    3100 4000
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 4000 3400 4000
Wire Wire Line
	3400 4000 3400 4050
$Comp
L Device:R_Small R705
U 1 1 608F1257
P 3750 4000
F 0 "R705" V 3554 4000 50  0000 C CNN
F 1 "100" V 3645 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" H 3750 4000 50  0001 C CNN
F 3 "~" H 3750 4000 50  0001 C CNN
F 4 "C56239" H 3750 4000 50  0001 C CNN "LCSC Part #"
	1    3750 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 4000 3650 4000
Connection ~ 3400 4000
$Comp
L Isolator:TLP627 U701
U 1 1 608F2776
P 4450 4150
F 0 "U701" H 4450 4475 50  0000 C CNN
F 1 "TLP627" H 4450 4384 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 4150 3950 50  0001 L CIN
F 3 "https://toshiba.semicon-storage.com/info/docget.jsp?did=16914&prodName=TLP627" H 4450 4150 50  0001 L CNN
F 4 "C79290" H 4450 4150 50  0001 C CNN "LCSC Part #"
	1    4450 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 4000 3950 4000
Wire Wire Line
	3950 4000 3950 4050
Wire Wire Line
	3950 4050 4050 4050
Wire Wire Line
	1950 4250 2600 4250
Connection ~ 2600 4250
Wire Wire Line
	2600 4250 2950 4250
Connection ~ 2950 4250
Wire Wire Line
	2950 4250 3400 4250
Connection ~ 3400 4250
Wire Wire Line
	3400 4250 4050 4250
$Comp
L power:GND #PWR0706
U 1 1 608F606B
P 4900 4300
F 0 "#PWR0706" H 4900 4050 50  0001 C CNN
F 1 "GND" H 4905 4127 50  0000 C CNN
F 2 "" H 4900 4300 50  0001 C CNN
F 3 "" H 4900 4300 50  0001 C CNN
	1    4900 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0705
U 1 1 608F6E9B
P 4900 3800
F 0 "#PWR0705" H 4900 3650 50  0001 C CNN
F 1 "+3.3V" H 4915 3973 50  0000 C CNN
F 2 "" H 4900 3800 50  0001 C CNN
F 3 "" H 4900 3800 50  0001 C CNN
	1    4900 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4250 4900 4250
Wire Wire Line
	4900 4250 4900 4300
$Comp
L Device:R_Small R706
U 1 1 608F79CA
P 4900 3900
F 0 "R706" H 4959 3946 50  0000 L CNN
F 1 "10K" H 4959 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" H 4900 3900 50  0001 C CNN
F 3 "~" H 4900 3900 50  0001 C CNN
F 4 "C17902" H 4900 3900 50  0001 C CNN "LCSC Part #"
	1    4900 3900
	1    0    0    -1  
$EndComp
Text GLabel 4950 4050 2    50   Input ~ 0
RPM_SENSOR
Wire Wire Line
	4850 4050 4900 4050
Wire Wire Line
	4900 4000 4900 4050
Connection ~ 4900 4050
Wire Wire Line
	4900 4050 4950 4050
$Comp
L power:GND1 #PWR0702
U 1 1 608FAF86
P 1950 4250
F 0 "#PWR0702" H 1950 4000 50  0001 C CNN
F 1 "GND1" H 1955 4077 50  0000 C CNN
F 2 "" H 1950 4250 50  0001 C CNN
F 3 "" H 1950 4250 50  0001 C CNN
	1    1950 4250
	1    0    0    -1  
$EndComp
Connection ~ 1950 4250
$Comp
L Device:C_Small C?
U 1 1 608683D4
P 2050 5350
AR Path="/608B029C/608683D4" Ref="C?"  Part="1" 
AR Path="/608D8494/608683D4" Ref="C703"  Part="1" 
F 0 "C703" H 2142 5396 50  0000 L CNN
F 1 "10u" H 2142 5305 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 2050 5350 50  0001 C CNN
F 3 "~" H 2050 5350 50  0001 C CNN
F 4 "C13585" H 2050 5350 50  0001 C CNN "LCSC Part #"
	1    2050 5350
	1    0    0    -1  
$EndComp
Text GLabel 1550 5550 3    50   Input ~ 0
TRACK_SENSOR
$Comp
L power:+3.3V #PWR0701
U 1 1 60869BC2
P 1550 5200
F 0 "#PWR0701" H 1550 5050 50  0001 C CNN
F 1 "+3.3V" H 1565 5373 50  0000 C CNN
F 2 "" H 1550 5200 50  0001 C CNN
F 3 "" H 1550 5200 50  0001 C CNN
	1    1550 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R701
U 1 1 60869BC8
P 1550 5350
F 0 "R701" H 1609 5396 50  0000 L CNN
F 1 "10K" H 1609 5305 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" H 1550 5350 50  0001 C CNN
F 3 "~" H 1550 5350 50  0001 C CNN
F 4 "C17902" H 1550 5350 50  0001 C CNN "LCSC Part #"
	1    1550 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 5550 1550 5450
$Comp
L power:GND #PWR0703
U 1 1 6086B1EA
P 2050 5500
F 0 "#PWR0703" H 2050 5250 50  0001 C CNN
F 1 "GND" H 2055 5327 50  0000 C CNN
F 2 "" H 2050 5500 50  0001 C CNN
F 3 "" H 2050 5500 50  0001 C CNN
	1    2050 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 5200 2050 5200
Wire Wire Line
	1550 5200 1550 5250
Connection ~ 1550 5200
Wire Wire Line
	2050 5200 2050 5250
Wire Wire Line
	2050 5500 2050 5450
Wire Wire Line
	2100 2800 2100 2700
Wire Wire Line
	1950 2800 2100 2800
$Comp
L Device:R_Small R702
U 1 1 608D8DBB
P 2100 2600
F 0 "R702" H 2159 2646 50  0000 L CNN
F 1 "10K" H 2159 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" H 2100 2600 50  0001 C CNN
F 3 "~" H 2100 2600 50  0001 C CNN
F 4 "C17902" H 2100 2600 50  0001 C CNN "LCSC Part #"
	1    2100 2600
	1    0    0    -1  
$EndComp
Text GLabel 1950 2800 0    50   Input ~ 0
H2O_NTC+
$Comp
L power:+3.3V #PWR0704
U 1 1 608D87B1
P 2100 2350
F 0 "#PWR0704" H 2100 2200 50  0001 C CNN
F 1 "+3.3V" H 2115 2523 50  0000 C CNN
F 2 "" H 2100 2350 50  0001 C CNN
F 3 "" H 2100 2350 50  0001 C CNN
	1    2100 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C701
U 1 1 61DBD2BE
P 2550 2600
F 0 "C701" H 2642 2646 50  0000 L CNN
F 1 "10u" H 2642 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 2550 2600 50  0001 C CNN
F 3 "~" H 2550 2600 50  0001 C CNN
F 4 "C13585" H 2550 2600 50  0001 C CNN "LCSC Part #"
	1    2550 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 61DBD90C
P 2550 2800
F 0 "#PWR0101" H 2550 2550 50  0001 C CNN
F 1 "GND" H 2555 2627 50  0000 C CNN
F 2 "" H 2550 2800 50  0001 C CNN
F 3 "" H 2550 2800 50  0001 C CNN
	1    2550 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2800 2550 2700
Wire Wire Line
	2100 2500 2100 2450
Wire Wire Line
	2550 2500 2550 2450
Wire Wire Line
	2550 2450 2100 2450
Connection ~ 2100 2450
Wire Wire Line
	2100 2450 2100 2350
$EndSCHEMATC
