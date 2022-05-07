################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F2837xD_Adc.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_Adc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_CodeStartBranch.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_CpuTimers.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_CpuTimers.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_DefaultISR.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_DefaultISR.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_GlobalVariableDefs.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/source/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_Gpio.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_Gpio.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_Ipc.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_Ipc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_Ipc_Driver_Util.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_Ipc_Driver_Util.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_PieCtrl.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_PieCtrl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_PieVect.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_PieVect.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_SysCtrl.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_SysCtrl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_usDelay.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/source/F2837xD_usDelay.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

can.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/can.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

interrupt.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/interrupt.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sysctl.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/sysctl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

systick.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/driverlib/systick.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ustdlib.obj: C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated/utils/ustdlib.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/utilities/third_party/f2837xd" --include_path="C:/ti/ff14b/source" --include_path="C:/Users/utente/Documents/RaceUp/Codice/ti_dual_core/dual_core_completo/ff14b/source" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/deprecated" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --advice:performance=all --define=CPU1 --define=LORA_DEBUG --define=_LAUNCHXL_F28379D --define=_FLASH -g --printf_support=full --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


