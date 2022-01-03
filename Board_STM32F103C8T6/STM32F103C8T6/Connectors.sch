EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 8
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
L Connector_Generic:Conn_02x05_Odd_Even J405
U 1 1 608B1F9A
P 2750 1350
F 0 "J405" H 2900 1650 50  0000 C CNN
F 1 "SWD" H 2800 1050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x05_P2.54mm_Vertical" H 2750 1350 50  0001 C CNN
F 3 "~" H 2750 1350 50  0001 C CNN
	1    2750 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0401
U 1 1 608B35ED
P 2500 1100
F 0 "#PWR0401" H 2500 950 50  0001 C CNN
F 1 "+3.3V" H 2515 1273 50  0000 C CNN
F 2 "" H 2500 1100 50  0001 C CNN
F 3 "" H 2500 1100 50  0001 C CNN
	1    2500 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1100 2500 1150
Wire Wire Line
	2500 1150 2550 1150
$Comp
L power:GND #PWR0402
U 1 1 608B3D25
P 2500 1600
F 0 "#PWR0402" H 2500 1350 50  0001 C CNN
F 1 "GND" H 2505 1427 50  0000 C CNN
F 2 "" H 2500 1600 50  0001 C CNN
F 3 "" H 2500 1600 50  0001 C CNN
	1    2500 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1250 2500 1250
Wire Wire Line
	2500 1550 2550 1550
Wire Wire Line
	2500 1250 2500 1350
Wire Wire Line
	2550 1350 2500 1350
Connection ~ 2500 1350
Wire Wire Line
	2500 1350 2500 1550
NoConn ~ 2550 1450
Text GLabel 3050 1150 2    50   Input ~ 0
SWDIO
Text GLabel 3050 1250 2    50   Input ~ 0
SWCLK
Text GLabel 3050 1350 2    50   Input ~ 0
SWO
NoConn ~ 3050 1450
Text GLabel 3050 1550 2    50   Input ~ 0
NRST
Wire Wire Line
	2500 1550 2500 1600
Connection ~ 2500 1550
$Comp
L Connector_Generic:Conn_01x02 J402
U 1 1 60846C8C
P 2550 5350
F 0 "J402" H 2700 5250 50  0000 C CNN
F 1 "I2C" H 2700 5350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2550 5350 50  0001 C CNN
F 3 "~" H 2550 5350 50  0001 C CNN
	1    2550 5350
	-1   0    0    1   
$EndComp
Text GLabel 2750 5250 2    50   Input ~ 0
I2C1_SCL
Text GLabel 2750 5350 2    50   Input ~ 0
12C1_SDA
$Comp
L Connector_Generic:Conn_01x02 J406
U 1 1 608920A2
P 4050 5350
F 0 "J406" H 4200 5250 50  0000 C CNN
F 1 "USART1" H 4250 5350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4050 5350 50  0001 C CNN
F 3 "~" H 4050 5350 50  0001 C CNN
	1    4050 5350
	-1   0    0    1   
$EndComp
Text GLabel 4250 5350 2    50   Input ~ 0
USART1_RX
Text GLabel 4250 5250 2    50   Input ~ 0
USART1_TX
Text GLabel 5750 5250 2    50   Input ~ 0
BLUETOOTH_RESET
Text GLabel 5750 5350 2    50   Input ~ 0
USART2_TX
Text GLabel 5750 5450 2    50   Input ~ 0
USART2_RX
$Comp
L Connector_Generic:Conn_01x03 J408
U 1 1 608D50B8
P 5550 5350
F 0 "J408" H 5700 5300 50  0000 C CNN
F 1 "BLUETOOTH" H 5850 5400 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5550 5350 50  0001 C CNN
F 3 "~" H 5550 5350 50  0001 C CNN
	1    5550 5350
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0408
U 1 1 6085CF38
P 4300 6600
F 0 "#PWR0408" H 4300 6450 50  0001 C CNN
F 1 "+3.3V" H 4315 6773 50  0000 C CNN
F 2 "" H 4300 6600 50  0001 C CNN
F 3 "" H 4300 6600 50  0001 C CNN
	1    4300 6600
	1    0    0    -1  
$EndComp
Text GLabel 4250 6750 2    50   Input ~ 0
TRACK_SENSOR
Wire Wire Line
	4250 6650 4300 6650
Wire Wire Line
	4300 6650 4300 6600
Wire Wire Line
	4250 6850 4300 6850
Wire Wire Line
	4300 6850 4300 6900
$Comp
L Connector:Screw_Terminal_01x03 J407
U 1 1 60875364
P 4050 6750
F 0 "J407" H 4200 6700 50  0000 C CNN
F 1 "CIRCUIT_SENSOR" H 4450 6800 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_PT-1,5-3-5.0-H_1x03_P5.00mm_Horizontal" H 4050 6750 50  0001 C CNN
F 3 "https://standexelectronics.com/resources/technical-library/brochures-catalogs/product-solutions-hall-effect-sensor-series/" H 4050 6750 50  0001 C CNN
F 4 "" H 4050 6750 50  0001 C CNN "Field4"
F 5 "MH21-10S-300W" H 4050 6750 50  0001 C CNN "Name"
	1    4050 6750
	-1   0    0    1   
$EndComp
Text GLabel 2750 6650 2    50   Input ~ 0
H2O_NTC+
Text GLabel 5750 6650 2    50   Input ~ 0
COIL_RPM
$Comp
L Connector:Screw_Terminal_01x02 J409
U 1 1 608B8921
P 5550 6750
F 0 "J409" H 5700 6650 50  0000 C CNN
F 1 "RPM" H 5750 6750 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_PT-1,5-2-3.5-H_1x02_P3.50mm_Horizontal" H 5550 6750 50  0001 C CNN
F 3 "~" H 5550 6750 50  0001 C CNN
	1    5550 6750
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 6750 5800 6750
Wire Wire Line
	5800 6750 5800 6800
$Comp
L power:GND #PWR?
U 1 1 60939A4F
P 2800 6800
AR Path="/608D8494/60939A4F" Ref="#PWR?"  Part="1" 
AR Path="/608B029C/60939A4F" Ref="#PWR0406"  Part="1" 
F 0 "#PWR0406" H 2800 6550 50  0001 C CNN
F 1 "GND" H 2805 6627 50  0000 C CNN
F 2 "" H 2800 6800 50  0001 C CNN
F 3 "" H 2800 6800 50  0001 C CNN
	1    2800 6800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J403
U 1 1 6087809D
P 2550 6750
F 0 "J403" H 2700 6650 50  0000 C CNN
F 1 "H2O" H 2700 6750 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_PT-1,5-2-3.5-H_1x02_P3.50mm_Horizontal" H 2550 6750 50  0001 C CNN
F 3 "~" H 2550 6750 50  0001 C CNN
	1    2550 6750
	-1   0    0    1   
$EndComp
Wire Wire Line
	2750 6750 2800 6750
Wire Wire Line
	2800 6750 2800 6800
$Comp
L Connector_Generic:Conn_01x02 J410
U 1 1 60A183B9
P 6500 6800
F 0 "J410" H 6650 6700 50  0000 C CNN
F 1 "POWER" H 6700 6800 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6500 6800 50  0001 C CNN
F 3 "~" H 6500 6800 50  0001 C CNN
	1    6500 6800
	-1   0    0    1   
$EndComp
$Comp
L power:GND1 #PWR?
U 1 1 608BB24C
P 5800 6800
AR Path="/608D8494/608BB24C" Ref="#PWR?"  Part="1" 
AR Path="/608B029C/608BB24C" Ref="#PWR0414"  Part="1" 
F 0 "#PWR0414" H 5800 6550 50  0001 C CNN
F 1 "GND1" H 5805 6627 50  0000 C CNN
F 2 "" H 5800 6800 50  0001 C CNN
F 3 "" H 5800 6800 50  0001 C CNN
	1    5800 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0409
U 1 1 6085C426
P 4300 6900
F 0 "#PWR0409" H 4300 6650 50  0001 C CNN
F 1 "GND" H 4305 6727 50  0000 C CNN
F 2 "" H 4300 6900 50  0001 C CNN
F 3 "" H 4300 6900 50  0001 C CNN
	1    4300 6900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0416
U 1 1 60A18DC4
P 6700 6800
F 0 "#PWR0416" H 6700 6550 50  0001 C CNN
F 1 "GND" H 6705 6627 50  0000 C CNN
F 2 "" H 6700 6800 50  0001 C CNN
F 3 "" H 6700 6800 50  0001 C CNN
	1    6700 6800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0415
U 1 1 60A1924A
P 6700 6700
F 0 "#PWR0415" H 6700 6550 50  0001 C CNN
F 1 "+3.3V" H 6715 6873 50  0000 C CNN
F 2 "" H 6700 6700 50  0001 C CNN
F 3 "" H 6700 6700 50  0001 C CNN
	1    6700 6700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C401
U 1 1 608EDDAA
P 7300 3050
F 0 "C401" H 7350 3100 50  0000 L CNN
F 1 "100n" H 7350 3000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 7300 3050 50  0001 C CNN
F 3 "~" H 7300 3050 50  0001 C CNN
F 4 "C1525" H 7300 3050 50  0001 C CNN "LCSC Part #"
	1    7300 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0411
U 1 1 60872E86
P 5700 3500
F 0 "#PWR0411" H 5700 3250 50  0001 C CNN
F 1 "GND" H 5705 3327 50  0000 C CNN
F 2 "" H 5700 3500 50  0001 C CNN
F 3 "" H 5700 3500 50  0001 C CNN
	1    5700 3500
	1    0    0    -1  
$EndComp
Text GLabel 6100 3050 2    50   Input ~ 0
USB_CONN_D+
Text GLabel 5300 3050 0    50   Input ~ 0
USB_CONN_D-
Text GLabel 4450 2850 0    50   Input ~ 0
USB_D-
Text GLabel 6850 2850 2    50   Input ~ 0
USB_D+
Wire Wire Line
	2800 4250 2800 4300
Wire Wire Line
	2750 4250 2800 4250
$Comp
L power:GND #PWR0405
U 1 1 60846037
P 2800 4300
F 0 "#PWR0405" H 2800 4050 50  0001 C CNN
F 1 "GND" H 2805 4127 50  0000 C CNN
F 2 "" H 2800 4300 50  0001 C CNN
F 3 "" H 2800 4300 50  0001 C CNN
	1    2800 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4150 2800 4100
Wire Wire Line
	2750 4150 2800 4150
$Comp
L power:+BATT #PWR?
U 1 1 60844527
P 2800 4100
AR Path="/607F2DBC/60844527" Ref="#PWR?"  Part="1" 
AR Path="/608B029C/60844527" Ref="#PWR0404"  Part="1" 
F 0 "#PWR0404" H 2800 3950 50  0001 C CNN
F 1 "+BATT" H 2815 4273 50  0000 C CNN
F 2 "" H 2800 4100 50  0001 C CNN
F 3 "" H 2800 4100 50  0001 C CNN
	1    2800 4100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J401
U 1 1 60842371
P 2550 4250
F 0 "J401" H 2700 4150 50  0000 C CNN
F 1 "BATTERY" H 2800 4250 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_PT-1,5-2-3.5-H_1x02_P3.50mm_Horizontal" H 2550 4250 50  0001 C CNN
F 3 "~" H 2550 4250 50  0001 C CNN
	1    2550 4250
	-1   0    0    1   
$EndComp
Text GLabel 3000 2950 2    50   Input ~ 0
USB_CONN_D-
Text GLabel 3000 2850 2    50   Input ~ 0
USB_CONN_D+
NoConn ~ 3000 3050
Wire Wire Line
	3000 2650 3050 2650
$Comp
L power:+5V #PWR0407
U 1 1 60843733
P 3050 2600
F 0 "#PWR0407" H 3050 2450 50  0001 C CNN
F 1 "+5V" H 3065 2773 50  0000 C CNN
F 2 "" H 3050 2600 50  0001 C CNN
F 3 "" H 3050 2600 50  0001 C CNN
	1    3050 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2650 3050 2600
NoConn ~ 2600 3250
$Comp
L power:GND #PWR0403
U 1 1 60843210
P 2700 3250
F 0 "#PWR0403" H 2700 3000 50  0001 C CNN
F 1 "GND" H 2705 3077 50  0000 C CNN
F 2 "" H 2700 3250 50  0001 C CNN
F 3 "" H 2700 3250 50  0001 C CNN
	1    2700 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J404
U 1 1 6084131D
P 2700 2850
F 0 "J404" H 2850 3200 50  0000 C CNN
F 1 "USB_B_Micro" H 3000 2500 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Wuerth_629105150521" H 2850 2800 50  0001 C CNN
F 3 "~" H 2850 2800 50  0001 C CNN
F 4 "C40943" H 2700 2850 50  0001 C CNN "LCSC Part #"
	1    2700 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 61D1BB27
P 5700 2400
F 0 "#PWR0102" H 5700 2250 50  0001 C CNN
F 1 "+3.3V" H 5715 2573 50  0000 C CNN
F 2 "" H 5700 2400 50  0001 C CNN
F 3 "" H 5700 2400 50  0001 C CNN
	1    5700 2400
	1    0    0    -1  
$EndComp
$Comp
L Power_Protection:USBLC6-2SC6 U401
U 1 1 6086FC62
P 5700 2950
F 0 "U401" H 5950 3300 50  0000 C CNN
F 1 "USBLC6-2SC6" H 6000 2600 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 5700 2450 50  0001 C CNN
F 3 "https://www.st.com/resource/en/datasheet/usblc6-2.pdf" H 5900 3300 50  0001 C CNN
F 4 "C558442" H 5700 2950 50  0001 C CNN "LCSC Part #"
	1    5700 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R402
U 1 1 61D28325
P 6200 2850
F 0 "R402" V 6004 2850 50  0000 C CNN
F 1 "22" V 6095 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 6200 2850 50  0001 C CNN
F 3 "~" H 6200 2850 50  0001 C CNN
F 4 "C25092" H 6200 2850 50  0001 C CNN "LCSC Part #"
	1    6200 2850
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R401
U 1 1 61D2919D
P 5200 2850
F 0 "R401" V 5004 2850 50  0000 C CNN
F 1 "22" V 5095 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 5200 2850 50  0001 C CNN
F 3 "~" H 5200 2850 50  0001 C CNN
F 4 "C25092" H 5200 2850 50  0001 C CNN "LCSC Part #"
	1    5200 2850
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C403
U 1 1 61D2E57B
P 6800 3050
F 0 "C403" H 6850 3100 50  0000 L CNN
F 1 "47p" H 6850 3000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 6800 3050 50  0001 C CNN
F 3 "~" H 6800 3050 50  0001 C CNN
F 4 "C1567" H 6800 3050 50  0001 C CNN "LCSC Part #"
	1    6800 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2850 6800 2850
Wire Wire Line
	6800 2950 6800 2850
Wire Wire Line
	7300 2450 7300 2950
$Comp
L Device:C_Small C402
U 1 1 61D3175C
P 4500 3050
F 0 "C402" H 4550 3100 50  0000 L CNN
F 1 "47p" H 4550 3000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 4500 3050 50  0001 C CNN
F 3 "~" H 4500 3050 50  0001 C CNN
F 4 "C1567" H 4500 3050 50  0001 C CNN "LCSC Part #"
	1    4500 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2950 4500 2850
Wire Wire Line
	4500 2850 5100 2850
Wire Wire Line
	4500 3150 4500 3400
Wire Wire Line
	4500 3400 5700 3400
Wire Wire Line
	5700 3400 5700 3500
Wire Wire Line
	5700 3400 5700 3350
Connection ~ 5700 3400
Wire Wire Line
	5700 3400 6800 3400
Wire Wire Line
	6800 3400 6800 3150
Wire Wire Line
	7300 3400 7300 3150
Wire Wire Line
	4450 2850 4500 2850
Connection ~ 4500 2850
Wire Wire Line
	5700 2400 5700 2450
Wire Wire Line
	5700 2450 7300 2450
Connection ~ 5700 2450
Wire Wire Line
	5700 2450 5700 2550
Wire Wire Line
	7300 3400 6800 3400
Connection ~ 6800 3400
Wire Wire Line
	6850 2850 6800 2850
Connection ~ 6800 2850
$EndSCHEMATC
