################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"/home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv64+ --include_path="/home/dkoh/workspace/USB_HostMsc_lcdkOMAPL138_c674xExampleProject" --include_path="/home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/drv/usb" --include_path="/home/dkoh/ti/pdk_omapl138_1_0_8/packages" --include_path="/home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/drv/usb/example/usb_host/msc" --include_path="/home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/drv/usb/src/usb_func/include" --include_path="/home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/drv/usb/example/common" --include_path="/home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/drv/usb/src/include" --include_path="/home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/drv/usb/example/shell" --include_path="/home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --define=USE_BIOS --define=TIRTOS --define=omapl138 --define=SOC_OMAPL138 --define=lcdkOMAPL138 --define=c6748 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-929350689:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-929350689-inproc

build-929350689-inproc: ../usb_c674x_omapl138.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"/home/dkoh/ti/xdctools_3_50_08_24_core/xs" --xdcpath="/home/dkoh/ti/bios_6_73_01_01/packages;/home/dkoh/ti/pdk_omapl138_1_0_8/packages;/home/dkoh/ti/edma3_lld_2_12_05_30C/packages;/home/dkoh/ti/ipc_3_50_03_05/packages;/home/dkoh/ti/ndk_3_40_01_01/packages;/home/dkoh/ti/uia_2_30_01_02/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p ti.platforms.evmOMAPL138 -r debug -b "/home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/build/omapl138/config_omapl138_c674x.bld" -c "/home/dkoh/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2" -DBOARD=lcdkOMAPL138 "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: /home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/build/omapl138/config_omapl138_c674x.bld
configPkg/linker.cmd: build-929350689 ../usb_c674x_omapl138.cfg /home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/build/omapl138/config_omapl138_c674x.bld
configPkg/compiler.opt: build-929350689 /home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/build/omapl138/config_omapl138_c674x.bld
configPkg/: build-929350689 /home/dkoh/ti/pdk_omapl138_1_0_8/packages/ti/build/omapl138/config_omapl138_c674x.bld


