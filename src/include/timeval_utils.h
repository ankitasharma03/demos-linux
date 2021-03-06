/*
 * This file is part of the linuxapi package.
 * Copyright (C) 2011-2016 Mark Veltzer <mark.veltzer@gmail.com>
 *
 * linuxapi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * linuxapi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with linuxapi. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __timeval_utils_h
#define __timeval_utils_h

/*
 * This file is here to help you deal with the Linux 'struct timeval'
 * It seems that there are no such utility functions in the standard
 * C library
 */

/* THIS IS A C FILE, NO C++ here */

#include <firstinclude.h>
#include <time.h>	// for struct timeval

/*
 * An easy function to return how many micros have passed between
 * two timeval structures.
 */
static inline double micro_diff(struct timeval* t1, struct timeval* t2) {
	unsigned long long u1, u2;
	u1=((unsigned long long)t1->tv_sec*1000000)+t1->tv_usec;
	u2=((unsigned long long)t2->tv_sec*1000000)+t2->tv_usec;
	double diff=u2-u1;
	return diff;
}

#endif	/* !__timeval_utils_h */
