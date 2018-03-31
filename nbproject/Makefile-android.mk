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
CND_CONF=android
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/application.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/sound.o \
	${OBJECTDIR}/src/tile.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk irrlicht-android-base

irrlicht-android-base: ${OBJECTFILES}
	${LINK.cc} -o irrlicht-android-base ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/application.o: src/application.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_ANDROID_ -D_IRR_ANDROID_PLATFORM_ -I../../../libraries/irrlicht-ogl-es/include -I/home/daddy/Android/Sdk/ndk-bundle/sources/android/native_app_glue -I/home/daddy/Android/Sdk/ndk-bundle/sources/android -I/home/daddy/Android/Sdk/ndk-bundle/platforms/android-12/arch-x86/usr/include -I../../../libraries/cricket-1.6.5/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/application.o src/application.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_ANDROID_ -D_IRR_ANDROID_PLATFORM_ -I../../../libraries/irrlicht-ogl-es/include -I/home/daddy/Android/Sdk/ndk-bundle/sources/android/native_app_glue -I/home/daddy/Android/Sdk/ndk-bundle/sources/android -I/home/daddy/Android/Sdk/ndk-bundle/platforms/android-12/arch-x86/usr/include -I../../../libraries/cricket-1.6.5/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/sound.o: src/sound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_ANDROID_ -D_IRR_ANDROID_PLATFORM_ -I../../../libraries/irrlicht-ogl-es/include -I/home/daddy/Android/Sdk/ndk-bundle/sources/android/native_app_glue -I/home/daddy/Android/Sdk/ndk-bundle/sources/android -I/home/daddy/Android/Sdk/ndk-bundle/platforms/android-12/arch-x86/usr/include -I../../../libraries/cricket-1.6.5/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sound.o src/sound.cpp

${OBJECTDIR}/src/tile.o: src/tile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_ANDROID_ -D_IRR_ANDROID_PLATFORM_ -I../../../libraries/irrlicht-ogl-es/include -I/home/daddy/Android/Sdk/ndk-bundle/sources/android/native_app_glue -I/home/daddy/Android/Sdk/ndk-bundle/sources/android -I/home/daddy/Android/Sdk/ndk-bundle/platforms/android-12/arch-x86/usr/include -I../../../libraries/cricket-1.6.5/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tile.o src/tile.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} irrlicht-android-base

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
