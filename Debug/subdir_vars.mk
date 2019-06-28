################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../usb_c674x_omapl138.cfg 

C_SRCS += \
../fatfs_port_usbmsc.c \
../fs_shell_app_utils.c \
../host_msc_main.c \
../timer.c \
../usb_osal.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg/ 

C_DEPS += \
./fatfs_port_usbmsc.d \
./fs_shell_app_utils.d \
./host_msc_main.d \
./timer.d \
./usb_osal.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./fatfs_port_usbmsc.obj \
./fs_shell_app_utils.obj \
./host_msc_main.obj \
./timer.obj \
./usb_osal.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg/" 

OBJS__QUOTED += \
"fatfs_port_usbmsc.obj" \
"fs_shell_app_utils.obj" \
"host_msc_main.obj" \
"timer.obj" \
"usb_osal.obj" 

C_DEPS__QUOTED += \
"fatfs_port_usbmsc.d" \
"fs_shell_app_utils.d" \
"host_msc_main.d" \
"timer.d" \
"usb_osal.d" 

GEN_FILES__QUOTED += \
"configPkg/linker.cmd" \
"configPkg/compiler.opt" 

C_SRCS__QUOTED += \
"../fatfs_port_usbmsc.c" \
"../fs_shell_app_utils.c" \
"../host_msc_main.c" \
"../timer.c" \
"../usb_osal.c" 


