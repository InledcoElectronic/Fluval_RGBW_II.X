#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Program_Bootloader_Application.mk)" "nbproject/Makefile-local-Program_Bootloader_Application.mk"
include nbproject/Makefile-local-Program_Bootloader_Application.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Program_Bootloader_Application
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/eusart.c src/comman.c src/ble.c src/rtc.c src/led.c src/eeprom.c src/pwm.c src/tmr.c src/pin.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/eusart.p1 ${OBJECTDIR}/src/comman.p1 ${OBJECTDIR}/src/ble.p1 ${OBJECTDIR}/src/rtc.p1 ${OBJECTDIR}/src/led.p1 ${OBJECTDIR}/src/eeprom.p1 ${OBJECTDIR}/src/pwm.p1 ${OBJECTDIR}/src/tmr.p1 ${OBJECTDIR}/src/pin.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.p1.d ${OBJECTDIR}/src/eusart.p1.d ${OBJECTDIR}/src/comman.p1.d ${OBJECTDIR}/src/ble.p1.d ${OBJECTDIR}/src/rtc.p1.d ${OBJECTDIR}/src/led.p1.d ${OBJECTDIR}/src/eeprom.p1.d ${OBJECTDIR}/src/pwm.p1.d ${OBJECTDIR}/src/tmr.p1.d ${OBJECTDIR}/src/pin.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/eusart.p1 ${OBJECTDIR}/src/comman.p1 ${OBJECTDIR}/src/ble.p1 ${OBJECTDIR}/src/rtc.p1 ${OBJECTDIR}/src/led.p1 ${OBJECTDIR}/src/eeprom.p1 ${OBJECTDIR}/src/pwm.p1 ${OBJECTDIR}/src/tmr.p1 ${OBJECTDIR}/src/pin.p1

# Source Files
SOURCEFILES=src/main.c src/eusart.c src/comman.c src/ble.c src/rtc.c src/led.c src/eeprom.c src/pwm.c src/tmr.c src/pin.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Program_Bootloader_Application.mk dist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F18345
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/main.p1  src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/eusart.p1: src/eusart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eusart.p1.d 
	@${RM} ${OBJECTDIR}/src/eusart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/eusart.p1  src/eusart.c 
	@-${MV} ${OBJECTDIR}/src/eusart.d ${OBJECTDIR}/src/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/comman.p1: src/comman.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/comman.p1.d 
	@${RM} ${OBJECTDIR}/src/comman.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/comman.p1  src/comman.c 
	@-${MV} ${OBJECTDIR}/src/comman.d ${OBJECTDIR}/src/comman.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/comman.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ble.p1: src/ble.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ble.p1.d 
	@${RM} ${OBJECTDIR}/src/ble.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ble.p1  src/ble.c 
	@-${MV} ${OBJECTDIR}/src/ble.d ${OBJECTDIR}/src/ble.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ble.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/rtc.p1: src/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtc.p1.d 
	@${RM} ${OBJECTDIR}/src/rtc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/rtc.p1  src/rtc.c 
	@-${MV} ${OBJECTDIR}/src/rtc.d ${OBJECTDIR}/src/rtc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/rtc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/led.p1: src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/led.p1.d 
	@${RM} ${OBJECTDIR}/src/led.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/led.p1  src/led.c 
	@-${MV} ${OBJECTDIR}/src/led.d ${OBJECTDIR}/src/led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/eeprom.p1: src/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/src/eeprom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/eeprom.p1  src/eeprom.c 
	@-${MV} ${OBJECTDIR}/src/eeprom.d ${OBJECTDIR}/src/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pwm.p1: src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/pwm.p1.d 
	@${RM} ${OBJECTDIR}/src/pwm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pwm.p1  src/pwm.c 
	@-${MV} ${OBJECTDIR}/src/pwm.d ${OBJECTDIR}/src/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/tmr.p1: src/tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tmr.p1.d 
	@${RM} ${OBJECTDIR}/src/tmr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/tmr.p1  src/tmr.c 
	@-${MV} ${OBJECTDIR}/src/tmr.d ${OBJECTDIR}/src/tmr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/tmr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pin.p1: src/pin.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/pin.p1.d 
	@${RM} ${OBJECTDIR}/src/pin.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pin.p1  src/pin.c 
	@-${MV} ${OBJECTDIR}/src/pin.d ${OBJECTDIR}/src/pin.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pin.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/main.p1  src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/eusart.p1: src/eusart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eusart.p1.d 
	@${RM} ${OBJECTDIR}/src/eusart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/eusart.p1  src/eusart.c 
	@-${MV} ${OBJECTDIR}/src/eusart.d ${OBJECTDIR}/src/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/comman.p1: src/comman.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/comman.p1.d 
	@${RM} ${OBJECTDIR}/src/comman.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/comman.p1  src/comman.c 
	@-${MV} ${OBJECTDIR}/src/comman.d ${OBJECTDIR}/src/comman.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/comman.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ble.p1: src/ble.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ble.p1.d 
	@${RM} ${OBJECTDIR}/src/ble.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ble.p1  src/ble.c 
	@-${MV} ${OBJECTDIR}/src/ble.d ${OBJECTDIR}/src/ble.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ble.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/rtc.p1: src/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtc.p1.d 
	@${RM} ${OBJECTDIR}/src/rtc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/rtc.p1  src/rtc.c 
	@-${MV} ${OBJECTDIR}/src/rtc.d ${OBJECTDIR}/src/rtc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/rtc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/led.p1: src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/led.p1.d 
	@${RM} ${OBJECTDIR}/src/led.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/led.p1  src/led.c 
	@-${MV} ${OBJECTDIR}/src/led.d ${OBJECTDIR}/src/led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/eeprom.p1: src/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/src/eeprom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/eeprom.p1  src/eeprom.c 
	@-${MV} ${OBJECTDIR}/src/eeprom.d ${OBJECTDIR}/src/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pwm.p1: src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/pwm.p1.d 
	@${RM} ${OBJECTDIR}/src/pwm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pwm.p1  src/pwm.c 
	@-${MV} ${OBJECTDIR}/src/pwm.d ${OBJECTDIR}/src/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/tmr.p1: src/tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tmr.p1.d 
	@${RM} ${OBJECTDIR}/src/tmr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/tmr.p1  src/tmr.c 
	@-${MV} ${OBJECTDIR}/src/tmr.d ${OBJECTDIR}/src/tmr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/tmr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pin.p1: src/pin.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/pin.p1.d 
	@${RM} ${OBJECTDIR}/src/pin.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pin.p1  src/pin.c 
	@-${MV} ${OBJECTDIR}/src/pin.d ${OBJECTDIR}/src/pin.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pin.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../BleBootloader.X/dist/default/production/BleBootloader.X.production.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.map  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_Program_Bootloader_Application=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	@echo "Creating unified hex file"
	@"D:/Program Files/Microchip/MPLABX/v4.15/mplab_ide/platform/../mplab_ide/modules/../../bin/hexmate" --edf="D:/Program Files/Microchip/MPLABX/v4.15/mplab_ide/platform/../mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/Fluval_RGBW_II.X.${IMAGE_TYPE}.hex ../BleBootloader.X/dist/default/production/BleBootloader.X.production.hex -odist/${CND_CONF}/production/Fluval_RGBW_II.X.production.unified.hex

endif


# Subprojects
.build-subprojects:
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
	cd /D ../BleBootloader.X && ${MAKE}  -f Makefile CONF=default TYPE_IMAGE=DEBUG_RUN
else
	cd /D ../BleBootloader.X && ${MAKE}  -f Makefile CONF=default
endif


# Subprojects
.clean-subprojects:
	cd /D ../BleBootloader.X && rm -rf "build/default" "dist/default"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Program_Bootloader_Application
	${RM} -r dist/Program_Bootloader_Application

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
