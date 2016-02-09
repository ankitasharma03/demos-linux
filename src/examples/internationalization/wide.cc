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

#include <firstinclude.h>
#include <stdio.h>	// for wprintf(3)
#include <wchar.h>	// for wprintf(3)
#include <locale.h>	// for setlocale(3)
#include <stdlib.h>	// for EXIT_SUCCESS

/*
 * This example explores wide strings in GCC.
 */
#define WS(s) L ## s

int main(int argc, char** argv, char** envp) {
	setlocale(LC_ALL, "");
	wprintf(L"size of char is %d\n", sizeof(char));
	wprintf(L"size of wchar_t is %d\n", sizeof(wchar_t));
	// const char* s1="hello";
	const wchar_t *s2=L"קרמ\n";
	// const wchar_t* s3=WS("מרק");
	int ret=fputws(s2, stdout);
	wprintf(L"return is %d\n", ret);
	// wprintf(L"here is a string\n");
	// printf("length of %s is %d\n",s1,strlen(s1));
	wprintf(L"here is a wide char for ya [%ls]\n", s2);
	return EXIT_SUCCESS;
}
