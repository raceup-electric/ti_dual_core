################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
device/driverlib/%.obj: ../device/driverlib/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/Desktop/raceup/tmpws/Cpu2_test" --include_path="D:/Desktop/raceup/tmpws/Cpu2_test/device" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/driverlib/f2837xd/driverlib" --advice:performance=all --define=CPU2 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="device/driverlib/$(basename $(<F)).d_raw" --obj_directory="device/driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


