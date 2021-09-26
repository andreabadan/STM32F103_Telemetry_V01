@echo off
echo Writing Application using STM32_Programmer_CLI.exe 
echo (on standard path C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin)
C:

cd C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin
STM32_Programmer_CLI.exe -c port=COM4 -e 0 19 -w %~dp0\Bootloader_STM32F103C8T6\Debug\Bootloader_STM32F103C8T6.bin 0x08000000

@pause