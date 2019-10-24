/*
 * Copyright (C) 2019 Serafin Leschke
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335  USA
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>

#define RNG_DEV "/dev/hwrng"
#define RANDOM_DEV "/dev/random"
#define CHUNKSIZE 32
#define FEEDSIZE 32
#define NR_OF_CHUNKS ((FEEDSIZE + CHUNKSIZE - 1) / CHUNKSIZE)

extern int random_add_entropy(void *buf, size_t size);
extern void init_kernel_rng(const char* randomdev);

int main(int argc, char *argv[])
{
	char buf[CHUNKSIZE];
	int in_fd;
	ssize_t count;
	ssize_t ret;

	in_fd = open(RNG_DEV, O_RDONLY);
	if (in_fd < 0) {
		exit(EXIT_FAILURE);
	}

	init_kernel_rng(RANDOM_DEV);

	for (int i = 0; i < NR_OF_CHUNKS; i++) {
		count = 0;
		do {
			ret = read(in_fd, buf + count, CHUNKSIZE - count);
			if (ret < 0) {
				exit(EXIT_FAILURE);
			}
			count += ret;
		} while (count < CHUNKSIZE);
		random_add_entropy(buf, CHUNKSIZE);
	}

	close(in_fd);
	exit(EXIT_SUCCESS);
}
