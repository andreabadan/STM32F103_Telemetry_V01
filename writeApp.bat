@echo off
echo Writing Application using STM32_Programmer_CLI.exe 
echo(on standard path C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin)

C:
cd C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin
STM32_Programmer_CLI.exe -c port=COM4 -e 20 -w %~dp0\BadiApp_STM32F103C8T6\Debug\BadiApp_STM32F103C8T6.bin 0x08005000

@pause