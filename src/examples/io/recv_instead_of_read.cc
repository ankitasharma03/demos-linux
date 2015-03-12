/*
 * This file is part of the linuxapi package.
 * Copyright (C) 2011-2015 Mark Veltzer <mark.veltzer@gmail.com>
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

#include <firstinclude.h>
#include <sys/types.h>	// for recv(2), open(2)
#include <sys/socket.h>	// for recv(2)
#include <stdio.h>	// for printf(3)
#include <stdlib.h>	// for EXIT_SUCCESS
#include <sys/stat.h>	// for open(2)
#include <fcntl.h>	// for open(2)
#include <err_utils.h>	// for CHECK_NOT_M1()

/*
 * This example shows that recv(2) cannot be used instead of read for regular
 * disk based IO. The error returned is ENOTSOCK.
 */

int main(int argc, char** argv, char** envp) {
	const char* file="/etc/passwd";
	int fd=CHECK_NOT_M1(open(file, O_RDONLY));
	char buf[256];
	CHECK_NOT_M1(recv(fd, buf, sizeof(buf), 0));
	CHECK_NOT_M1(close(fd));
	return EXIT_SUCCESS;
}
