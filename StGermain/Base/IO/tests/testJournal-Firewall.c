/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**
** Copyright (C), 2003, Victorian Partnership for Advanced Computing (VPAC) Ltd, 110 Victoria Street, Melbourne, 3053, Australia.
**
** Authors:
**	Stevan M. Quenette, Senior Software Engineer, VPAC. (steve@vpac.org)
**	Patrick D. Sunter, Software Engineer, VPAC. (pds@vpac.org)
**	Luke J. Hodkinson, Computational Engineer, VPAC. (lhodkins@vpac.org)
**	Siew-Ching Tan, Software Engineer, VPAC. (siew@vpac.org)
**	Alan H. Lo, Computational Engineer, VPAC. (alan@vpac.org)
**	Raquibul Hassan, Computational Engineer, VPAC. (raq@vpac.org)
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Lesser General Public
**  License as published by the Free Software Foundation; either
**  version 2.1 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License along with this library; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**
** Role:
**	Tests the journal functionality
**
** $Id: testJournal-Firewall.c 3462 2006-02-19 06:53:24Z WalterLandry $
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "Base/Foundation/Foundation.h"
#include "Base/IO/IO.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <mpi.h>



int main( int argc, char* argv[] ) {
	MPI_Comm CommWorld;
	int rank;
	int numProcessors;
	int procToWatch;
	
	/* Initialise MPI, get world info */
	MPI_Init( &argc, &argv );
	MPI_Comm_dup( MPI_COMM_WORLD, &CommWorld );
	MPI_Comm_size( CommWorld, &numProcessors );
	MPI_Comm_rank( CommWorld, &rank );
	
	BaseFoundation_Init( &argc, &argv );
	BaseIO_Init( &argc, &argv );
	
	if( argc >= 2 ) {
		procToWatch = atoi( argv[1] );
	}
	else {
		procToWatch = 0;
	}
	if( rank == procToWatch )
	{
		Stream* myInfo;

		myInfo = Journal_Register( Info_Type, "MyInfo" );
		
		printf( "TEST: Firewall 1\n" );
		Journal_Firewall( 1, myInfo, "Firewall\n" );
		
		printf( "TEST: Firewall 0\n" );
/* Disable a fail for now as this causes make check to pickup an error even though its intentional. */
#ifdef STARS_ALIGN
		Journal_Firewall( 1 == 0, myInfo, "Firewall\n" );
#endif
	}

	BaseIO_Finalise();
	BaseFoundation_Finalise();

	/* Close off MPI */
	MPI_Finalize();
	
	return EXIT_SUCCESS;
}


