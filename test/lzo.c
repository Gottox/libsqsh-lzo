/*
 * Copyright (C) 2023 Enno Boland
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/**
 * @author      : Enno Boland (mail@eboland.de)
 * @file        : lzo.c
 */

#include <assert.h>
#include <sqsh_extract_private.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	uint8_t input[] = {0x15, 0x61, 0x62, 0x63, 0x64, 0x11, 0x00, 0x00};

	int rv;
	uint8_t output[16];
	size_t output_size = sizeof(output);
	sqsh__extractor_context_t context = {0};
	const struct SqshExtractorImpl *impl = sqsh__impl_lzo;

	rv = impl->init(context, output, output_size);
	assert(rv >= 0);
	rv = impl->extract(context, input, sizeof(input));
	assert(rv >= 0);
	rv = impl->finish(context, output, &output_size);
	assert(rv >= 0);

	assert(output_size == 4);

	assert(memcmp(output, "abcd", 4) == 0);

	return 0;
}
