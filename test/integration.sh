#!/bin/sh
set -xe

LD_PRELOAD=$LIBSQSH_LZO "$SQSH_LS" "$SQUASH_IMAGE"
