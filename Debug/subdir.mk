################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ModelFitter.cpp \
../MultiRansac.cpp \
../Ransac.cpp \
../test.cpp 

OBJS += \
./ModelFitter.o \
./MultiRansac.o \
./Ransac.o \
./test.o 

CPP_DEPS += \
./ModelFitter.d \
./MultiRansac.d \
./Ransac.d \
./test.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


