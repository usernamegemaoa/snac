##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##
## Copyright (C), 2003, Victorian Partnership for Advanced Computing (VPAC) Ltd, 110 Victoria Street, Melbourne, 3053, Australia.
##
## Authors:
##	Stevan M. Quenette, Senior Software Engineer, VPAC. (steve@vpac.org)
##	Patrick D. Sunter, Software Engineer, VPAC. (pds@vpac.org)
##	Luke J. Hodkinson, Computational Engineer, VPAC. (lhodkins@vpac.org)
##	Siew-Ching Tan, Software Engineer, VPAC. (siew@vpac.org)
##	Alan H. Lo, Computational Engineer, VPAC. (alan@vpac.org)
##	Raquibul Hassan, Computational Engineer, VPAC. (raq@vpac.org)
##
##  This library is free software; you can redistribute it and/or
##  modify it under the terms of the GNU Lesser General Public
##  License as published by the Free Software Foundation; either
##  version 2.1 of the License, or (at your option) any later version.
##
##  This library is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
##  Lesser General Public License for more details.
##
##  You should have received a copy of the GNU Lesser General Public
##  License along with this library; if not, write to the Free Software
##  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
##
## $Id: Make.mm 3462 2006-02-19 06:53:24Z WalterLandry $
##
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
include Makefile.def
include Python/default.def

PROJECT = StGermain
PYTHON_PACKAGE = ${def_pyb_package}
PACKAGE = ${def_pyb}module

BLD_MODDIR = $(EXPORT_ROOT)/modules/$(PYTHON_PACKAGE)
PROJ_DLL = $(BLD_MODDIR)/$(PACKAGE).$(EXT_SO)
PROJ_TMPDIR = $(BLD_TMPDIR)/$(PROJECT)/$(PACKAGE)
PROJ_CLEAN += $(PROJ_DLL)

PROJ_SRCS = ${def_srcs}
PROJ_CC_FLAGS += -I$(BLD_INCDIR)/StGermain -I$(PYTHIA_INCDIR) `xml2-config --cflags`
PROJ_LIBRARIES = -L$(BLD_LIBDIR) -lStGermain `xml2-config --libs` $(MPI_LIBPATH) $(MPI_LIBS) -L$(PYTHIA_LIBDIR) -ljournal $(PYTHIA_DIR)/modules/mpi/mpimodule.so 
LCCFLAGS =
EXTERNAL_INCLUDES += $(PYTHIA_DIR)/include $(PYTHIA_INCDIR) $(EXCHANGER_INCDIR)

# hack to ensure dir is built by product_dirs
BLD_BINDIR = $(BLD_MODDIR)

all: DLL

DLL: product_dirs $(PROJ_OBJS)
	$(CC) -o $(PROJ_DLL) $(PROJ_OBJS) $(COMPILER_LCC_SOFLAGS) $(LCCFLAGS) $(PROJ_LIBRARIES) $(EXTERNAL_LIBPATH) $(EXTERNAL_LIBS)
