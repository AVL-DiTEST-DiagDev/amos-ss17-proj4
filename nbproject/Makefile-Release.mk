#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/broadcast_receiver.o \
	${OBJECTDIR}/src/ecu_lua_script.o \
	${OBJECTDIR}/src/ecu_timer.o \
	${OBJECTDIR}/src/electronic_control_unit.o \
	${OBJECTDIR}/src/isotp_receiver.o \
	${OBJECTDIR}/src/isotp_sender.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/session_controller.o \
	${OBJECTDIR}/src/uds_receiver.o \
	${OBJECTDIR}/src/utilities.o \
	${OBJECTDIR}/src/j1939_simulator.o


# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/ecu_lua_script_test.o \
	${TESTDIR}/tests/ecu_lua_script_test_runner.o \
	${TESTDIR}/tests/electronic_control_unit_test.o \
	${TESTDIR}/tests/electronic_control_unit_test_runner.o \
	${TESTDIR}/tests/isotp_sender_test.o \
	${TESTDIR}/tests/isotp_sender_test_runner.o \
	${TESTDIR}/tests/uds_receiver_test.o \
	${TESTDIR}/tests/uds_receiver_test_runner.o \
	${TESTDIR}/tests/utils_test.o \
	${TESTDIR}/tests/utils_test_runner.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pthread
CXXFLAGS=-pthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs lua-5.2`  `pkg-config --libs libsocketcan` -lstdc++fs 

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amos-ss17-proj4

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amos-ss17-proj4: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amos-ss17-proj4 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/broadcast_receiver.o: src/broadcast_receiver.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/broadcast_receiver.o src/broadcast_receiver.cpp

${OBJECTDIR}/src/ecu_lua_script.o: src/ecu_lua_script.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ecu_lua_script.o src/ecu_lua_script.cpp

${OBJECTDIR}/src/ecu_timer.o: src/ecu_timer.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ecu_timer.o src/ecu_timer.cpp

${OBJECTDIR}/src/electronic_control_unit.o: src/electronic_control_unit.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/electronic_control_unit.o src/electronic_control_unit.cpp

${OBJECTDIR}/src/isotp_receiver.o: src/isotp_receiver.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/isotp_receiver.o src/isotp_receiver.cpp

${OBJECTDIR}/src/isotp_sender.o: src/isotp_sender.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/isotp_sender.o src/isotp_sender.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/session_controller.o: src/session_controller.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/session_controller.o src/session_controller.cpp

${OBJECTDIR}/src/uds_receiver.o: src/uds_receiver.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/uds_receiver.o src/uds_receiver.cpp

${OBJECTDIR}/src/utilities.o: src/utilities.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utilities.o src/utilities.cpp

${OBJECTDIR}/src/j1939_simulator.o: src/j1939_simulator.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/j1939_simulator.o src/j1939_simulator.cpp


# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/ecu_lua_script_test.o ${TESTDIR}/tests/ecu_lua_script_test_runner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/electronic_control_unit_test.o ${TESTDIR}/tests/electronic_control_unit_test_runner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/isotp_sender_test.o ${TESTDIR}/tests/isotp_sender_test_runner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/uds_receiver_test.o ${TESTDIR}/tests/uds_receiver_test_runner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/utils_test.o ${TESTDIR}/tests/utils_test_runner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   


${TESTDIR}/tests/ecu_lua_script_test.o: tests/ecu_lua_script_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ecu_lua_script_test.o tests/ecu_lua_script_test.cpp


${TESTDIR}/tests/ecu_lua_script_test_runner.o: tests/ecu_lua_script_test_runner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ecu_lua_script_test_runner.o tests/ecu_lua_script_test_runner.cpp


${TESTDIR}/tests/electronic_control_unit_test.o: tests/electronic_control_unit_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/electronic_control_unit_test.o tests/electronic_control_unit_test.cpp


${TESTDIR}/tests/electronic_control_unit_test_runner.o: tests/electronic_control_unit_test_runner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/electronic_control_unit_test_runner.o tests/electronic_control_unit_test_runner.cpp


${TESTDIR}/tests/isotp_sender_test.o: tests/isotp_sender_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/isotp_sender_test.o tests/isotp_sender_test.cpp


${TESTDIR}/tests/isotp_sender_test_runner.o: tests/isotp_sender_test_runner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/isotp_sender_test_runner.o tests/isotp_sender_test_runner.cpp


${TESTDIR}/tests/uds_receiver_test.o: tests/uds_receiver_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/uds_receiver_test.o tests/uds_receiver_test.cpp


${TESTDIR}/tests/uds_receiver_test_runner.o: tests/uds_receiver_test_runner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/uds_receiver_test_runner.o tests/uds_receiver_test_runner.cpp


${TESTDIR}/tests/utils_test.o: tests/utils_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/utils_test.o tests/utils_test.cpp


${TESTDIR}/tests/utils_test_runner.o: tests/utils_test_runner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include -Isrc `pkg-config --cflags lua-5.2` -std=c++17 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/utils_test_runner.o tests/utils_test_runner.cpp


${OBJECTDIR}/src/broadcast_receiver_nomain.o: ${OBJECTDIR}/src/broadcast_receiver.o src/broadcast_receiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/broadcast_receiver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/broadcast_receiver_nomain.o src/broadcast_receiver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/broadcast_receiver.o ${OBJECTDIR}/src/broadcast_receiver_nomain.o;\
	fi

${OBJECTDIR}/src/ecu_lua_script_nomain.o: ${OBJECTDIR}/src/ecu_lua_script.o src/ecu_lua_script.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ecu_lua_script.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ecu_lua_script_nomain.o src/ecu_lua_script.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ecu_lua_script.o ${OBJECTDIR}/src/ecu_lua_script_nomain.o;\
	fi

${OBJECTDIR}/src/ecu_timer_nomain.o: ${OBJECTDIR}/src/ecu_timer.o src/ecu_timer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ecu_timer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ecu_timer_nomain.o src/ecu_timer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ecu_timer.o ${OBJECTDIR}/src/ecu_timer_nomain.o;\
	fi

${OBJECTDIR}/src/electronic_control_unit_nomain.o: ${OBJECTDIR}/src/electronic_control_unit.o src/electronic_control_unit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/electronic_control_unit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/electronic_control_unit_nomain.o src/electronic_control_unit.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/electronic_control_unit.o ${OBJECTDIR}/src/electronic_control_unit_nomain.o;\
	fi

${OBJECTDIR}/src/isotp_receiver_nomain.o: ${OBJECTDIR}/src/isotp_receiver.o src/isotp_receiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/isotp_receiver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/isotp_receiver_nomain.o src/isotp_receiver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/isotp_receiver.o ${OBJECTDIR}/src/isotp_receiver_nomain.o;\
	fi

${OBJECTDIR}/src/isotp_sender_nomain.o: ${OBJECTDIR}/src/isotp_sender.o src/isotp_sender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/isotp_sender.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/isotp_sender_nomain.o src/isotp_sender.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/isotp_sender.o ${OBJECTDIR}/src/isotp_sender_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

${OBJECTDIR}/src/session_controller_nomain.o: ${OBJECTDIR}/src/session_controller.o src/session_controller.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/session_controller.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/session_controller_nomain.o src/session_controller.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/session_controller.o ${OBJECTDIR}/src/session_controller_nomain.o;\
	fi

${OBJECTDIR}/src/uds_receiver_nomain.o: ${OBJECTDIR}/src/uds_receiver.o src/uds_receiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/uds_receiver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/uds_receiver_nomain.o src/uds_receiver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/uds_receiver.o ${OBJECTDIR}/src/uds_receiver_nomain.o;\
	fi

${OBJECTDIR}/src/utilities_nomain.o: ${OBJECTDIR}/src/utilities.o src/utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/utilities.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utilities_nomain.o src/utilities.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/utilities.o ${OBJECTDIR}/src/utilities_nomain.o;\
	fi

${OBJECTDIR}/src/j1939_simulator_nomain.o: ${OBJECTDIR}/src/j1939_simulator.o src/j1939_simulator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/j1939_simulator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I/usr/include/lua5.2 -ISelene/include `pkg-config --cflags lua-5.2` -std=c++17  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/j1939_simulator_nomain.o src/j1939_simulator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/j1939_simulator.o ${OBJECTDIR}/src/j1939_simulator_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
