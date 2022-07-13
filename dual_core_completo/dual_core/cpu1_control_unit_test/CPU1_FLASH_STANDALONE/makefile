################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./F2837xD_Adc.obj" \
"./F2837xD_CodeStartBranch.obj" \
"./F2837xD_CpuTimers.obj" \
"./F2837xD_DefaultISR.obj" \
"./F2837xD_EPwm.obj" \
"./F2837xD_GlobalVariableDefs.obj" \
"./F2837xD_Gpio.obj" \
"./F2837xD_Ipc.obj" \
"./F2837xD_Ipc_Driver_Util.obj" \
"./F2837xD_PieCtrl.obj" \
"./F2837xD_PieVect.obj" \
"./F2837xD_SysCtrl.obj" \
"./F2837xD_usDelay.obj" \
"./GPIO_management.obj" \
"./LoRa.obj" \
"./SPI_LoRa.obj" \
"./Telemetry.obj" \
"./can.obj" \
"./cmdline.obj" \
"./display.obj" \
"./ff.obj" \
"./interrupt.obj" \
"./main.obj" \
"./mmc_F2837x.obj" \
"./sd_card.obj" \
"./sysctl.obj" \
"./systick.obj" \
"./uart.obj" \
"./ustdlib.obj" \
"../2837xD_FLASH_lnk_cpu1.cmd" \
$(GEN_CMDS__FLAG) \
-lrts2800_fpu32.lib \
-lF2837xD_Headers_nonBIOS_cpu1.cmd \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
cpu1_control_unit_test.out \

EXE_OUTPUTS__QUOTED += \
"cpu1_control_unit_test.out" \

BIN_OUTPUTS += \
cpu1_control_unit_test.hex \

BIN_OUTPUTS__QUOTED += \
"cpu1_control_unit_test.hex" \


# All Target
all: cpu1_control_unit_test.out

# Tool invocations
cpu1_control_unit_test.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --advice:performance=all --define=_STANDALONE --define=LOGGING --define=NO_LORA_DEBUG --define=NO_LORA --define=CPU1 --define=_LAUNCHXL_F28379D --define=_FLASH -g --diag_warning=225 --display_error_number --abi=coffabi -z -m"cpu1_control_unit_test.map" --heap_size=0x400 --stack_size=0x3F8 --warn_sections -i"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/lib" -i"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" -i"C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/cmd" --reread_libs --display_error_number --xml_link_info="cpu1_control_unit_test_linkInfo.xml" --rom_model -o "cpu1_control_unit_test.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

cpu1_control_unit_test.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/hex2000" --diag_wrap=off -o "cpu1_control_unit_test.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "F2837xD_Adc.obj" "F2837xD_CodeStartBranch.obj" "F2837xD_CpuTimers.obj" "F2837xD_DefaultISR.obj" "F2837xD_EPwm.obj" "F2837xD_GlobalVariableDefs.obj" "F2837xD_Gpio.obj" "F2837xD_Ipc.obj" "F2837xD_Ipc_Driver_Util.obj" "F2837xD_PieCtrl.obj" "F2837xD_PieVect.obj" "F2837xD_SysCtrl.obj" "F2837xD_usDelay.obj" "GPIO_management.obj" "LoRa.obj" "SPI_LoRa.obj" "Telemetry.obj" "can.obj" "cmdline.obj" "display.obj" "ff.obj" "interrupt.obj" "main.obj" "mmc_F2837x.obj" "sd_card.obj" "sysctl.obj" "systick.obj" "uart.obj" "ustdlib.obj" 
	-$(RM) "F2837xD_Adc.d" "F2837xD_CpuTimers.d" "F2837xD_DefaultISR.d" "F2837xD_EPwm.d" "F2837xD_GlobalVariableDefs.d" "F2837xD_Gpio.d" "F2837xD_Ipc.d" "F2837xD_Ipc_Driver_Util.d" "F2837xD_PieCtrl.d" "F2837xD_PieVect.d" "F2837xD_SysCtrl.d" "GPIO_management.d" "LoRa.d" "SPI_LoRa.d" "Telemetry.d" "can.d" "cmdline.d" "display.d" "ff.d" "interrupt.d" "main.d" "mmc_F2837x.d" "sd_card.d" "sysctl.d" "systick.d" "uart.d" "ustdlib.d" 
	-$(RM) "F2837xD_CodeStartBranch.d" "F2837xD_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

