################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2

GEN_OPTS__FLAG := --cmd_file="configPkg/compiler.opt"
GEN_CMDS__FLAG := -l"configPkg/linker.cmd"

ORDERED_OBJS += \
"./fatfs_port_usbmsc.obj" \
"./fs_shell_app_utils.obj" \
"./host_msc_main.obj" \
"./timer.obj" \
"./usb_osal.obj" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

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
USB_HostMsc_lcdkOMAPL138_c674xExampleProject.out \

EXE_OUTPUTS__QUOTED += \
"USB_HostMsc_lcdkOMAPL138_c674xExampleProject.out" \

BIN_OUTPUTS += \
USB_HostMsc_lcdkOMAPL138_c674xExampleProject.hex \

BIN_OUTPUTS__QUOTED += \
"USB_HostMsc_lcdkOMAPL138_c674xExampleProject.hex" \


# All Target
all: $(OBJS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "USB_HostMsc_lcdkOMAPL138_c674xExampleProject.out"

# Tool invocations
USB_HostMsc_lcdkOMAPL138_c674xExampleProject.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C6000 Linker'
	"/home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv64+ --define=USE_BIOS --define=TIRTOS --define=omapl138 --define=SOC_OMAPL138 --define=lcdkOMAPL138 --define=c6748 -g --diag_warning=225 --diag_wrap=off --display_error_number -z -m"USB_HostMsc_lcdkOMAPL138_c674xExampleProject.map" --heap_size=0x800 --stack_size=0x800 -i"/home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/lib" -i"/home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="USB_HostMsc_lcdkOMAPL138_c674xExampleProject_linkInfo.xml" --rom_model -o "USB_HostMsc_lcdkOMAPL138_c674xExampleProject.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

USB_HostMsc_lcdkOMAPL138_c674xExampleProject.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C6000 Hex Utility'
	"/home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/hex6x"  -o "USB_HostMsc_lcdkOMAPL138_c674xExampleProject.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "fatfs_port_usbmsc.obj" "fs_shell_app_utils.obj" "host_msc_main.obj" "timer.obj" "usb_osal.obj" 
	-$(RM) "fatfs_port_usbmsc.d" "fs_shell_app_utils.d" "host_msc_main.d" "timer.d" "usb_osal.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-/home/dkoh/ti/pdk_omapl138_1_0_8/packages/pdkAppImageCreate.sh /home/dkoh/ti/pdk_omapl138_1_0_8/packages /home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2 /home/dkoh/workspace/USB_HostMsc_lcdkOMAPL138_c674xExampleProject/Debug USB_HostMsc_lcdkOMAPL138_c674xExampleProject OMAPL138 dsp
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

