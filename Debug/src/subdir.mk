################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/error_mandatos.c \
../src/libreria.c \
../src/minishellPropia.c \
../src/my_libreria.c 

OBJS += \
./src/error_mandatos.o \
./src/libreria.o \
./src/minishellPropia.o \
./src/my_libreria.o 

C_DEPS += \
./src/error_mandatos.d \
./src/libreria.d \
./src/minishellPropia.d \
./src/my_libreria.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


