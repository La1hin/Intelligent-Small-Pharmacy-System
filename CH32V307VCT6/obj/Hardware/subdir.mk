################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/Interrupt_Init.c \
../Hardware/Motor.c \
../Hardware/PCA9685_Init.c \
../Hardware/PCA9685_USE.c \
../Hardware/Usart.c 

OBJS += \
./Hardware/Interrupt_Init.o \
./Hardware/Motor.o \
./Hardware/PCA9685_Init.o \
./Hardware/PCA9685_USE.o \
./Hardware/Usart.o 

C_DEPS += \
./Hardware/Interrupt_Init.d \
./Hardware/Motor.d \
./Hardware/PCA9685_Init.d \
./Hardware/PCA9685_USE.d \
./Hardware/Usart.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"C:\Users\PC\Desktop\Mrs_practice\CH32V307VCT6\Debug" -I"C:\Users\PC\Desktop\Mrs_practice\CH32V307VCT6\Hardware" -I"C:\Users\PC\Desktop\Mrs_practice\CH32V307VCT6\Core" -I"C:\Users\PC\Desktop\Mrs_practice\CH32V307VCT6\User" -I"C:\Users\PC\Desktop\Mrs_practice\CH32V307VCT6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

