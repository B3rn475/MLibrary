#
# File:  Makefile (for library)
#
CC=g++
CFLAGS=-lm
LIB=MLibrary.a
LIBDEST=./

LIBSRC=	./MLibrary/MFAbs.cpp	\
	./MLibrary/MFAcos.cpp	\
	./MLibrary/MFAcotan.cpp	\
	./MLibrary/MFAdd.cpp	\
	./MLibrary/MFAsin.cpp	\
	./MLibrary/MFAtan.cpp	\
	./MLibrary/MFConst.cpp	\
	./MLibrary/MFCos.cpp	\
	./MLibrary/MFCosh.cpp	\
	./MLibrary/MFCoTan.cpp	\
	./MLibrary/MFCoTanh.cpp	\
	./MLibrary/MFDiv.cpp	\
	./MLibrary/MFExp.cpp	\
	./MLibrary/MFLn.cpp	\
	./MLibrary/MFLog10.cpp	\
	./MLibrary/MFLog.cpp	\
	./MLibrary/MFMul.cpp	\
	./MLibrary/MFOpp.cpp	\
	./MLibrary/MFPow.cpp	\
	./MLibrary/MFSign.cpp	\
	./MLibrary/MFSin.cpp	\
	./MLibrary/MFSinh.cpp	\
	./MLibrary/MFSqrt.cpp	\
	./MLibrary/MFSub.cpp	\
	./MLibrary/MFTan.cpp	\
	./MLibrary/MFTanh.cpp	\
	./MLibrary/MFVar.cpp	\
	./MLibrary/MInterpreter.cpp	\
	./MLibrary/MRelation.cpp	\
	./MLibrary/MSistem.cpp	\
	./MLibrary/MVariableList.cpp	\
	./MLibrary/MVariablesElement.cpp

LIBOBJ=$(LIBSRC:.cpp=.o)

install: $(LIB)
	@echo lib Makefile - installing $(LIB)
	@install -m 444 $(LIB) $(LIBDEST)

$(LIB): $(LIBOBJ)
	@echo lib Makefile - archiving $(LIB)
	@$(AR) -cvq $(LIB) $(LIBOBJ)

.cpp.o:
	@echo lib Makefile - compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@
