################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ABS_Threshold.c \
../src/Robosub_Hydrophone.c \
../src/UART.c \
../src/helper.c \
../src/hw_accel.c \
../src/init.c \
../src/led.c \
../src/processing.c 

ASM_SRCS += \
../src/sport1_isr_process_samples.asm 

SRC_OBJS += \
./src/ABS_Threshold.doj \
./src/Robosub_Hydrophone.doj \
./src/UART.doj \
./src/helper.doj \
./src/hw_accel.doj \
./src/init.doj \
./src/led.doj \
./src/processing.doj \
./src/sport1_isr_process_samples.doj 

C_DEPS += \
./src/ABS_Threshold.d \
./src/Robosub_Hydrophone.d \
./src/UART.d \
./src/helper.d \
./src/hw_accel.d \
./src/init.d \
./src/led.d \
./src/processing.d 

ASM_DEPS += \
./src/sport1_isr_process_samples.d 


# Each subdirectory must supply rules for building sources it contributes
src/ABS_Threshold.doj: ../src/ABS_Threshold.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "src/ABS_Threshold.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Robosub_Hydrophone.doj: ../src/Robosub_Hydrophone.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "src/Robosub_Hydrophone.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/UART.doj: ../src/UART.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "src/UART.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/helper.doj: ../src/helper.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "src/helper.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/hw_accel.doj: ../src/hw_accel.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "src/hw_accel.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/init.doj: ../src/init.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "src/init.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/led.doj: ../src/led.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "src/led.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/processing.doj: ../src/processing.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "src/processing.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sport1_isr_process_samples.doj: ../src/sport1_isr_process_samples.asm
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC Assembler'
	easm21k.exe -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -si-revision any -g -D_DEBUG -DCORE0 -DDEBUG -i"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -i"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\src" -swc -gnu-style-dependencies -MM -Mo "src/sport1_isr_process_samples.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


