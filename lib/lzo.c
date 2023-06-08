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
 * @author       Enno Boland (mail@eboland.de)
 * @file         lzo.c
 */

#define _GNU_SOURCE

#include <sqsh_error.h>
#include <sqsh_extract_private.h>

#include <lzo/lzo1x.h>

struct SqshLzoContext {
	/**
	 * @privatesection
	 */
	struct SqshBuffer buffer;
	const uint8_t *compressed;
	size_t compressed_size;
};

SQSH_STATIC_ASSERT(
		sizeof(sqsh__extractor_context_t) >= sizeof(struct SqshLzoContext));

int
sqsh__impl_lzo_init(void *context, uint8_t *target, size_t target_size) {
	(void)target;
	(void)target_size;
	int rv = 0;
	struct SqshLzoContext *buffering = context;

	rv = sqsh__buffer_init(&buffering->buffer);
	if (rv < 0) {
		goto out;
	}
	buffering->compressed = NULL;
	buffering->compressed_size = 0;

out:
	return rv;
}

int
sqsh__impl_lzo_extract(
		void *context, const uint8_t *compressed,
		const size_t compressed_size) {
	int rv = 0;
	struct SqshLzoContext *buffering = context;
	if (buffering->compressed == NULL &&
		sqsh__buffer_size(&buffering->buffer) == 0) {
		buffering->compressed = compressed;
		buffering->compressed_size = compressed_size;
		return 0;
	} else if (sqsh__buffer_size(&buffering->buffer) == 0) {
		rv = sqsh__buffer_append(
				&buffering->buffer, buffering->compressed,
				buffering->compressed_size);
		if (rv < 0) {
			return rv;
		}
	}

	rv = sqsh__buffer_append(&buffering->buffer, compressed, compressed_size);
	if (rv < 0) {
		return rv;
	}
	buffering->compressed = sqsh__buffer_data(&buffering->buffer);
	buffering->compressed_size = sqsh__buffer_size(&buffering->buffer);

	return rv;
}

static int
sqsh__impl_lzo_finish(void *context, uint8_t *target, size_t *target_size) {
	int rv;
	struct SqshLzoContext *buffering = context;
	char wrkmem[LZO1X_1_MEM_COMPRESS] = {0};
	const uint8_t *compressed = buffering->compressed;
	const size_t compressed_size = buffering->compressed_size;
	rv = lzo1x_decompress_safe(
			compressed, compressed_size, target, target_size, wrkmem);
	if (rv != LZO_E_OK) {
		return -SQSH_ERROR_COMPRESSION_DECOMPRESS;
	} else {
		return 0;
	}
}

const struct SqshExtractorImpl impl_lzo = {
		.init = sqsh__impl_lzo_init,
		.extract = sqsh__impl_lzo_extract,
		.finish = sqsh__impl_lzo_finish,
};

const struct SqshExtractorImpl *const sqsh__impl_lzo = &impl_lzo;
