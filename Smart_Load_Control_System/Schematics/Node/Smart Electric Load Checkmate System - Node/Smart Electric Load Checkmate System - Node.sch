EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector:Conn_01x04_Male J1
U 1 1 645EE41F
P 7100 3000
F 0 "J1" H 7072 2974 50  0000 R CNN
F 1 "Conn_01x04_Male" H 7072 2883 50  0000 R CNN
F 2 "" H 7100 3000 50  0001 C CNN
F 3 "~" H 7100 3000 50  0001 C CNN
	1    7100 3000
	-1   0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 U1
U 1 1 645EFB5A
P 3900 3700
F 0 "U1" H 3900 3942 50  0000 C CNN
F 1 "LM7805" H 3900 3851 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3900 3925 50  0001 C CIN
F 3 "https://www.onsemi.cn/PowerSolutions/document/MC7800-D.PDF" H 3900 3650 50  0001 C CNN
	1    3900 3700
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 U2
U 1 1 645F05C0
P 3900 4500
F 0 "U2" H 3900 4742 50  0000 C CNN
F 1 "LM2596" H 3900 4651 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3900 4725 50  0001 C CIN
F 3 "https://www.onsemi.cn/PowerSolutions/document/MC7800-D.PDF" H 3900 4450 50  0001 C CNN
	1    3900 4500
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 645ED5D7
P 5100 3750
F 0 "A1" H 4800 2800 50  0000 C CNN
F 1 "Arduino_Nano" H 4800 2750 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5100 3750 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 5100 3750 50  0001 C CNN
	1    5100 3750
	-1   0    0    -1  
$EndComp
$Comp
L RF:NRF24L01_Breakout U3
U 1 1 645EF3DF
P 7000 4050
F 0 "U3" H 7380 4096 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 7380 4005 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 7150 4650 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 7000 3950 50  0001 C CNN
	1    7000 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4150 6300 4150
Wire Wire Line
	6300 4150 6300 4050
Wire Wire Line
	6300 4050 6500 4050
Wire Wire Line
	6500 4250 6250 4250
Wire Wire Line
	6250 4250 6250 4050
Wire Wire Line
	6250 4050 5600 4050
Wire Wire Line
	6500 3750 6200 3750
Wire Wire Line
	6200 3750 6200 4250
Wire Wire Line
	6200 4250 5600 4250
Wire Wire Line
	6500 3850 6150 3850
Wire Wire Line
	6150 3850 6150 4350
Wire Wire Line
	6150 4350 5600 4350
Wire Wire Line
	6500 3950 6100 3950
Wire Wire Line
	6100 3950 6100 4450
Wire Wire Line
	6100 4450 5600 4450
Wire Wire Line
	6900 3200 6350 3200
Wire Wire Line
	6350 3200 6350 4650
Wire Wire Line
	6350 4650 7000 4650
Wire Wire Line
	6900 3100 6000 3100
Wire Wire Line
	6000 3100 6000 3550
Wire Wire Line
	6000 3550 5600 3550
Wire Wire Line
	6900 3000 5850 3000
Wire Wire Line
	5850 3000 5850 3650
Wire Wire Line
	5850 3650 5600 3650
$Comp
L Relay:G5V-1 K1
U 1 1 645FDEF4
P 7450 5300
F 0 "K1" H 7880 5346 50  0000 L CNN
F 1 "Relay" H 7880 5255 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Omron_G5V-1" H 8580 5270 50  0001 C CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g5v_1.pdf" H 7450 5300 50  0001 C CNN
	1    7450 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery BT1
U 1 1 64603B14
P 3350 4200
F 0 "BT1" H 3100 4250 50  0000 L CNN
F 1 "7.4V" H 3100 4150 50  0000 L CNN
F 2 "" V 3350 4260 50  0001 C CNN
F 3 "~" V 3350 4260 50  0001 C CNN
	1    3350 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4000 3350 3700
Wire Wire Line
	3350 3700 3500 3700
Wire Wire Line
	3350 4400 3350 4900
Wire Wire Line
	3350 4900 3900 4900
Wire Wire Line
	3900 4900 3900 4800
Wire Wire Line
	3600 4500 3500 4500
Wire Wire Line
	3500 4500 3500 3700
Connection ~ 3500 3700
Wire Wire Line
	3500 3700 3600 3700
Text GLabel 4200 4500 2    50   Input Italic 10
3.3V
Text GLabel 4250 3700 2    50   Input Italic 10
5V
Wire Wire Line
	4250 3700 4200 3700
Wire Wire Line
	3500 3700 3500 2550
Wire Wire Line
	3500 2550 5200 2550
Wire Wire Line
	5200 2550 5200 2750
$Comp
L power:GND #PWR02
U 1 1 64607300
P 3900 4900
F 0 "#PWR02" H 3900 4650 50  0001 C CNN
F 1 "GND" H 3905 4727 50  0000 C CNN
F 2 "" H 3900 4900 50  0001 C CNN
F 3 "" H 3900 4900 50  0001 C CNN
	1    3900 4900
	1    0    0    -1  
$EndComp
Connection ~ 3900 4900
$Comp
L power:GND #PWR01
U 1 1 646081E6
P 3900 4000
F 0 "#PWR01" H 3900 3750 50  0001 C CNN
F 1 "GND" H 3905 3827 50  0000 C CNN
F 2 "" H 3900 4000 50  0001 C CNN
F 3 "" H 3900 4000 50  0001 C CNN
	1    3900 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 646085E0
P 5000 4850
F 0 "#PWR03" H 5000 4600 50  0001 C CNN
F 1 "GND" H 5005 4677 50  0000 C CNN
F 2 "" H 5000 4850 50  0001 C CNN
F 3 "" H 5000 4850 50  0001 C CNN
	1    5000 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 4850 5000 4750
Wire Wire Line
	5000 4750 5100 4750
Connection ~ 5000 4750
$Comp
L power:GND #PWR04
U 1 1 64609CAD
P 7000 4650
F 0 "#PWR04" H 7000 4400 50  0001 C CNN
F 1 "GND" H 7005 4477 50  0000 C CNN
F 2 "" H 7000 4650 50  0001 C CNN
F 3 "" H 7000 4650 50  0001 C CNN
	1    7000 4650
	1    0    0    -1  
$EndComp
Connection ~ 7000 4650
Text GLabel 7050 3450 2    50   Input Italic 10
3.3V
Wire Wire Line
	7050 3450 7000 3450
Text GLabel 6900 2900 0    50   Input Italic 10
5V
NoConn ~ 4600 3150
NoConn ~ 4600 3250
NoConn ~ 4600 3550
NoConn ~ 4600 3750
NoConn ~ 4600 3850
NoConn ~ 4600 3950
NoConn ~ 4600 4050
NoConn ~ 4600 4150
NoConn ~ 4600 4250
NoConn ~ 4600 4350
NoConn ~ 4600 4450
NoConn ~ 5600 3950
NoConn ~ 5600 3750
NoConn ~ 5600 3450
NoConn ~ 5600 3350
NoConn ~ 5600 3250
NoConn ~ 5600 3150
NoConn ~ 5000 2750
NoConn ~ 4900 2750
$Comp
L Device:R R1
U 1 1 64614949
P 6100 5400
F 0 "R1" V 5893 5400 50  0000 C CNN
F 1 "1K" V 5984 5400 50  0000 C CNN
F 2 "" V 6030 5400 50  0001 C CNN
F 3 "~" H 6100 5400 50  0001 C CNN
	1    6100 5400
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:TIP41 Q1
U 1 1 646153FF
P 6450 5400
F 0 "Q1" H 6641 5446 50  0000 L CNN
F 1 "TIP41" H 6641 5355 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6700 5325 50  0001 L CIN
F 3 "https://www.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=tip41.PDF" H 6450 5400 50  0001 L CNN
	1    6450 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3850 5800 3850
Wire Wire Line
	5800 3850 5800 5400
Wire Wire Line
	5800 5400 5950 5400
$Comp
L Diode:1N4001 D1
U 1 1 6461974C
P 6550 5050
F 0 "D1" V 6504 5130 50  0000 L CNN
F 1 "1N4001" V 6595 5130 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 6550 4875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 6550 5050 50  0001 C CNN
	1    6550 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 4900 7250 4900
Wire Wire Line
	7250 4900 7250 5000
Wire Wire Line
	6550 5200 6950 5200
Wire Wire Line
	6950 5200 6950 5600
Wire Wire Line
	6950 5600 7250 5600
Connection ~ 6550 5200
$Comp
L power:GND #PWR05
U 1 1 6461BFAF
P 6550 5700
F 0 "#PWR05" H 6550 5450 50  0001 C CNN
F 1 "GND" H 6555 5527 50  0000 C CNN
F 2 "" H 6550 5700 50  0001 C CNN
F 3 "" H 6550 5700 50  0001 C CNN
	1    6550 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5600 6550 5700
Text Label 7650 5700 0    50   ~ 0
AC_Mains
Text Label 7550 4900 0    50   ~ 0
AC_Mains_Output
Wire Wire Line
	7550 4900 7550 5000
Wire Wire Line
	7650 5600 7650 5700
Text GLabel 6500 4900 0    50   Input Italic 10
5V
Wire Wire Line
	6500 4900 6550 4900
Connection ~ 6550 4900
Text Notes 3300 2050 0    118  Italic 24
Smart Electric Load Checkmate System - Node\n
NoConn ~ 6500 4350
NoConn ~ 7750 5000
$EndSCHEMATC
