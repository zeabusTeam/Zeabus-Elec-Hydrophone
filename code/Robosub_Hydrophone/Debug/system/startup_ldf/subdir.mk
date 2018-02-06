################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/startup_ldf/app_heaptab.c 

S_SRCS += \
../system/startup_ldf/app_IVT.s \
../system/startup_ldf/app_startup.s 

LDF_SRCS += \
../system/startup_ldf/app.ldf 

SRC_OBJS += \
./system/startup_ldf/app_IVT.doj \
./system/startup_ldf/app_heaptab.doj \
./system/startup_ldf/app_startup.doj 

C_DEPS += \
./system/startup_ldf/app_heaptab.d 

S_DEPS += \
./system/startup_ldf/app_IVT.d \
./system/startup_ldf/app_startup.d 


# Each subdirectory must supply rules for building sources it contributes
system/startup_ldf/app_IVT.doj: ../system/startup_ldf/app_IVT.s
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC Assembler'
	easm21k.exe -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -si-revision any -g -D_DEBUG -DCORE0 -DDEBUG -i"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -i"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\src" -swc -gnu-style-dependencies -MM -Mo "system/startup_ldf/app_IVT.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/startup_ldf/app_heaptab.doj: ../system/startup_ldf/app_heaptab.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -flags-compiler --no_wrap_diagnostics -si-revision any -g -D_DEBUG -DCORE0 -I"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -D__PROCESSOR_SPEED__=400000000 -double-size-32 -swc -gnu-style-dependencies -MD -Mo "system/startup_ldf/app_heaptab.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/startup_ldf/app_startup.doj: ../system/startup_ldf/app_startup.s
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC Assembler'
	easm21k.exe -file-attr ProjectName="Robosub_Hydrophone_update" -proc ADSP-21489 -si-revision any -g -D_DEBUG -DCORE0 -DDEBUG -i"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\system" -i"C:\Users\User\Desktop\Zeabus\Robosub_Hydrophone_update\src" -swc -gnu-style-dependencies -MM -Mo "system/startup_ldf/app_startup.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


