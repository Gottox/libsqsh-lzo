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

#include <cextras/collection.h>
#include <sqsh_error.h>
#include <sqsh_extract_private.h>

#include <lzo/lzo1x.h>

SQSH_STATIC_ASSERT(
		sizeof(sqsh__extractor_context_t) >= sizeof(struct CxBuffer));

static int
sqshlzo_impl_init(void *context, uint8_t *target, size_t target_size) {
	(void)target;
	(void)target_size;
	int rv = cx_buffer_init(context);
	if (rv < 0) {
		goto out;
	}
	rv = cx_buffer_add_capacity(context, NULL, target_size);
	if (rv < 0) {
		goto out;
	}
out:
	return rv;
}

static int
sqshlzo_impl_write(
		void *context, const uint8_t *compressed,
		const size_t compressed_size) {
	return cx_buffer_append(context, compressed, compressed_size);
}

static int
sqshlzo_impl_finish(void *context, uint8_t *target, size_t *target_size) {
	int rv = 0;
	char wrkmem[LZO1X_1_MEM_COMPRESS] = {0};
	const uint8_t *data = cx_buffer_data(context);
	size_t data_size = cx_buffer_size(context);

	int lzo_ret = rv =
			lzo1x_decompress_safe(data, data_size, target, target_size, wrkmem);
	if (lzo_ret < 0) {
		rv = -SQSH_ERROR_COMPRESSION_DECOMPRESS;
		goto out;
	}

out:
	cx_buffer_cleanup(context);
	return rv;
}

static const struct SqshExtractorImpl impl_lzo = {
		.init = sqshlzo_impl_init,
		.write = sqshlzo_impl_write,
		.finish = sqshlzo_impl_finish,
};

const struct SqshExtractorImpl *const sqsh__impl_lzo = &impl_lzo;
