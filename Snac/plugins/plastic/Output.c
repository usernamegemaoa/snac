/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**
** Copyright (C), 2003,
**	Steve Quenette, 110 Victoria Street, Melbourne, Victoria, 3053, Australia.
**	Californian Institute of Technology, 1200 East California Boulevard, Pasadena, California, 91125, USA.
**	University of Texas, 1 University Station, Austin, Texas, 78712, USA.
**
** Authors:
**	Stevan M. Quenette, Senior Software Engineer, VPAC. (steve@vpac.org)
**	Stevan M. Quenette, Visitor in Geophysics, Caltech.
**	Luc Lavier, Research Scientist, The University of Texas. (luc@utig.ug.utexas.edu)
**	Luc Lavier, Research Scientist, Caltech.
**
** This program is free software; you can redistribute it and/or modify it
** under the terms of the GNU General Public License as published by the
** Free Software Foundation; either version 2, or (at your option) any
** later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** $Id: Output.c 2498 2005-01-07 03:57:00Z PatrickSunter $
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <mpi.h>
#include <StGermain/StGermain.h>
#include <StGermain/FD/FD.h>
#include "Snac/Snac.h"
#include "types.h"
#include "Output.h"
#include "Context.h"
#include "Element.h"
#include "Register.h"
#include <stdio.h>

void _SnacPlastic_DumpPlasticStrain( void* _context ) {
	Snac_Context*				context = (Snac_Context*) _context;
	SnacPlastic_Context*			contextExt = ExtensionManager_Get(
							context->extensionMgr,
							context,
							SnacPlastic_ContextHandle );


	if( context->timeStep ==0 || (context->timeStep-1) % context->dumpEvery == 0 ) {
		Element_LocalIndex			element_lI;

		#if DEBUG
			printf( "In %s()\n", __func__ );
		#endif

		for( element_lI = 0; element_lI < context->mesh->elementLocalCount; element_lI++ ) {
			Snac_Element* 				element = Snac_Element_At( context, element_lI );
			SnacPlastic_Element*			elementExt = ExtensionManager_Get(
											context->mesh->elementExtensionMgr,
											element,
											SnacPlastic_ElementHandle );
			float plasticStrain = elementExt->aps;
			/* Take average of tetra plastic strain for the element */
			fwrite( &plasticStrain, sizeof(float), 1, contextExt->plStrainOut );
		}
		fflush( contextExt->plStrainOut );
	}
}