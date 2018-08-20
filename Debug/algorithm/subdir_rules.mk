################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
algorithm/Algorithm.obj: ../algorithm/Algorithm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="E:/LowVoltControl/LVControl1015/libs/FPUfastRTS/V100/include" --include_path="E:/LowVoltControl/LVControl1015/libs/IQmath/v15c/include" --include_path="E:/LowVoltControl/LVControl1015/DSP2833x_common/include" --include_path="E:/LowVoltControl/LVControl1015/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="algorithm/Algorithm.d" --obj_directory="algorithm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

algorithm/VVVF.obj: ../algorithm/VVVF.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="E:/LowVoltControl/LVControl1015/libs/FPUfastRTS/V100/include" --include_path="E:/LowVoltControl/LVControl1015/libs/IQmath/v15c/include" --include_path="E:/LowVoltControl/LVControl1015/DSP2833x_common/include" --include_path="E:/LowVoltControl/LVControl1015/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="algorithm/VVVF.d" --obj_directory="algorithm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


