################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../2837xD_FLASH_lnk_cpu1.cmd 

ASM_SRCS += \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_CodeStartBranch.asm \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_usDelay.asm 

C_SRCS += \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_Adc.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_CpuTimers.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_DefaultISR.c \
../F2837xD_EPwm.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/headers/source/F2837xD_GlobalVariableDefs.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_Gpio.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_Ipc.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_Ipc_Driver_Util.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_PieCtrl.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_PieVect.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_SysCtrl.c \
../GPIO_management.c \
../LoRa.c \
../SPI_LoRa.c \
../Telemetry.c \
C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/deprecated/driverlib/can.c \
../cmdline.c \
../display.c \
../ff.c \
C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/interrupt.c \
../main.c \
../mmc_F2837x.c \
../sd_card.c \
C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/sysctl.c \
C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/systick.c \
../uart.c \
C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/utils/ustdlib.c 

C_DEPS += \
./F2837xD_Adc.d \
./F2837xD_CpuTimers.d \
./F2837xD_DefaultISR.d \
./F2837xD_EPwm.d \
./F2837xD_GlobalVariableDefs.d \
./F2837xD_Gpio.d \
./F2837xD_Ipc.d \
./F2837xD_Ipc_Driver_Util.d \
./F2837xD_PieCtrl.d \
./F2837xD_PieVect.d \
./F2837xD_SysCtrl.d \
./GPIO_management.d \
./LoRa.d \
./SPI_LoRa.d \
./Telemetry.d \
./can.d \
./cmdline.d \
./display.d \
./ff.d \
./interrupt.d \
./main.d \
./mmc_F2837x.d \
./sd_card.d \
./sysctl.d \
./systick.d \
./uart.d \
./ustdlib.d 

OBJS += \
./F2837xD_Adc.obj \
./F2837xD_CodeStartBranch.obj \
./F2837xD_CpuTimers.obj \
./F2837xD_DefaultISR.obj \
./F2837xD_EPwm.obj \
./F2837xD_GlobalVariableDefs.obj \
./F2837xD_Gpio.obj \
./F2837xD_Ipc.obj \
./F2837xD_Ipc_Driver_Util.obj \
./F2837xD_PieCtrl.obj \
./F2837xD_PieVect.obj \
./F2837xD_SysCtrl.obj \
./F2837xD_usDelay.obj \
./GPIO_management.obj \
./LoRa.obj \
./SPI_LoRa.obj \
./Telemetry.obj \
./can.obj \
./cmdline.obj \
./display.obj \
./ff.obj \
./interrupt.obj \
./main.obj \
./mmc_F2837x.obj \
./sd_card.obj \
./sysctl.obj \
./systick.obj \
./uart.obj \
./ustdlib.obj 

ASM_DEPS += \
./F2837xD_CodeStartBranch.d \
./F2837xD_usDelay.d 

OBJS__QUOTED += \
"F2837xD_Adc.obj" \
"F2837xD_CodeStartBranch.obj" \
"F2837xD_CpuTimers.obj" \
"F2837xD_DefaultISR.obj" \
"F2837xD_EPwm.obj" \
"F2837xD_GlobalVariableDefs.obj" \
"F2837xD_Gpio.obj" \
"F2837xD_Ipc.obj" \
"F2837xD_Ipc_Driver_Util.obj" \
"F2837xD_PieCtrl.obj" \
"F2837xD_PieVect.obj" \
"F2837xD_SysCtrl.obj" \
"F2837xD_usDelay.obj" \
"GPIO_management.obj" \
"LoRa.obj" \
"SPI_LoRa.obj" \
"Telemetry.obj" \
"can.obj" \
"cmdline.obj" \
"display.obj" \
"ff.obj" \
"interrupt.obj" \
"main.obj" \
"mmc_F2837x.obj" \
"sd_card.obj" \
"sysctl.obj" \
"systick.obj" \
"uart.obj" \
"ustdlib.obj" 

C_DEPS__QUOTED += \
"F2837xD_Adc.d" \
"F2837xD_CpuTimers.d" \
"F2837xD_DefaultISR.d" \
"F2837xD_EPwm.d" \
"F2837xD_GlobalVariableDefs.d" \
"F2837xD_Gpio.d" \
"F2837xD_Ipc.d" \
"F2837xD_Ipc_Driver_Util.d" \
"F2837xD_PieCtrl.d" \
"F2837xD_PieVect.d" \
"F2837xD_SysCtrl.d" \
"GPIO_management.d" \
"LoRa.d" \
"SPI_LoRa.d" \
"Telemetry.d" \
"can.d" \
"cmdline.d" \
"display.d" \
"ff.d" \
"interrupt.d" \
"main.d" \
"mmc_F2837x.d" \
"sd_card.d" \
"sysctl.d" \
"systick.d" \
"uart.d" \
"ustdlib.d" 

ASM_DEPS__QUOTED += \
"F2837xD_CodeStartBranch.d" \
"F2837xD_usDelay.d" 

C_SRCS__QUOTED += \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_Adc.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_CpuTimers.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_DefaultISR.c" \
"../F2837xD_EPwm.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/headers/source/F2837xD_GlobalVariableDefs.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_Gpio.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_Ipc.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_Ipc_Driver_Util.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_PieCtrl.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_PieVect.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_SysCtrl.c" \
"../GPIO_management.c" \
"../LoRa.c" \
"../SPI_LoRa.c" \
"../Telemetry.c" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/deprecated/driverlib/can.c" \
"../cmdline.c" \
"../display.c" \
"../ff.c" \
"C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/interrupt.c" \
"../main.c" \
"../mmc_F2837x.c" \
"../sd_card.c" \
"C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/sysctl.c" \
"C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/systick.c" \
"../uart.c" \
"C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/utils/ustdlib.c" 

ASM_SRCS__QUOTED += \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_CodeStartBranch.asm" \
"C:/ti/c2000/C2000Ware_3_03_00_00/device_support/f2837xd/common/source/F2837xD_usDelay.asm" 


