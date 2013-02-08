/*
	This file is part of the linuxapi project.
	Copyright (C) 2011-2013 Mark Veltzer <mark.veltzer@gmail.com>

	The linuxapi package is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	The linuxapi package is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with the GNU C Library; if not, write to the Free
	Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
	02111-1307 USA.
*/

#include <firstinclude.h>
#include <strings.h> // for bzero(3)
#include <alloca.h> // for alloca(3)
#include <stdio.h> // for printf(3)
#include <stdlib.h> // for EXIT_SUCCESS

/*
* This example investigates what happens if you call alloca(3) twice...
*
* Results:
* - you can call alloca more than once.
* - as a result you CANNOT free memory obtained by alloca(3).
* - alloca rounds stuff up by 8 bytes or some such.
*/

int main(int argc,char** argv,char** envp) {
	for(int i=0;i<10;i++) {
		char* p=(char*)alloca(10);
		bzero(p,10);
		printf("p1 is %p\n",p);
	}
	return EXIT_SUCCESS;
}
