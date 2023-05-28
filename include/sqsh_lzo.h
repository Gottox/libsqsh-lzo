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
 * @file         sqsh_lzo.h
 */

#ifndef SQSH_LZO_H
#define SQSH_LZO_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief configures libsqsh to support lzo compression
 * @return 0 on success, less than 0 on error
 */
int sqsh_lzo_support(void);

#ifdef __cplusplus
}
#endif
#endif // SQSH_LZO_H
