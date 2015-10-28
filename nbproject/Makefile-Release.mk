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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/GameBoard.o \
	${OBJECTDIR}/Card.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/libraries/DeckBuilder.o \
	${OBJECTDIR}/Holding.o \
	${OBJECTDIR}/StrongHold.o \
	${OBJECTDIR}/BlackCard.o \
	${OBJECTDIR}/Personality.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/Item.o \
	${OBJECTDIR}/GreenCard.o \
	${OBJECTDIR}/libraries/L5R_Library.o \
	${OBJECTDIR}/libraries/TypeConverter.o \
	${OBJECTDIR}/Follower.o \
	${OBJECTDIR}/libraries/PlayerComm.o \
	${OBJECTDIR}/Province.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/l5r

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/l5r: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/l5r ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/GameBoard.o: GameBoard.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GameBoard.o GameBoard.cpp

${OBJECTDIR}/Card.o: Card.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Card.o Card.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/libraries/DeckBuilder.o: libraries/DeckBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}/libraries
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libraries/DeckBuilder.o libraries/DeckBuilder.cpp

${OBJECTDIR}/Holding.o: Holding.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Holding.o Holding.cpp

${OBJECTDIR}/StrongHold.o: StrongHold.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/StrongHold.o StrongHold.cpp

${OBJECTDIR}/BlackCard.o: BlackCard.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BlackCard.o BlackCard.cpp

${OBJECTDIR}/Personality.o: Personality.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Personality.o Personality.cpp

${OBJECTDIR}/Player.o: Player.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/Item.o: Item.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Item.o Item.cpp

${OBJECTDIR}/GreenCard.o: GreenCard.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GreenCard.o GreenCard.cpp

${OBJECTDIR}/libraries/L5R_Library.o: libraries/L5R_Library.cpp 
	${MKDIR} -p ${OBJECTDIR}/libraries
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libraries/L5R_Library.o libraries/L5R_Library.cpp

${OBJECTDIR}/libraries/TypeConverter.o: libraries/TypeConverter.cpp 
	${MKDIR} -p ${OBJECTDIR}/libraries
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libraries/TypeConverter.o libraries/TypeConverter.cpp

${OBJECTDIR}/Follower.o: Follower.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Follower.o Follower.cpp

${OBJECTDIR}/libraries/PlayerComm.o: libraries/PlayerComm.cpp 
	${MKDIR} -p ${OBJECTDIR}/libraries
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libraries/PlayerComm.o libraries/PlayerComm.cpp

${OBJECTDIR}/Province.o: Province.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Province.o Province.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/l5r

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
