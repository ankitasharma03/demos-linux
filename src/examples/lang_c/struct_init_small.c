/*
	This file is part of the linuxapi project.
	Copyright (C) 2011, 2012 Mark Veltzer <mark.veltzer@gmail.com>

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

#include<firstinclude.h>
#include<stdio.h> // for printf(3)
#include<stdlib.h> // for EXIT_SUCCESS

/*
* This example explores some weird gcc optimization regarding structures.
* As you can see from this, if your struct is small (8 bytes or less) then
* gcc will initialize it for you (=0). If not, then you will get junk.
*
* The weird this is, if you access the same field twice gcc will 0 it for you
* (see the last part of this example).
*/

struct smallstruct {
	int a;
	int b;
};

struct largestruct {
	int a;
	int b;
	int c;
};

int main(int argc,char** argv,char** envp) {
	struct smallstruct vsmall;
	printf("vsmall.a is %d\n",vsmall.a);
	printf("vsmall.b is %d\n",vsmall.b);
	struct largestruct vlarge;
	printf("vlarge.a is %d\n",vlarge.a);
	printf("vlarge.b is %d\n",vlarge.b);
	printf("vlarge.c is %d\n",vlarge.c);
	struct largestruct vlarge2;
	printf("vlarge2.a is %d\n",vlarge2.a);
	printf("vlarge2.b is %d\n",vlarge2.b);
	printf("vlarge2.c is %d\n",vlarge2.b);
	return EXIT_SUCCESS;
}