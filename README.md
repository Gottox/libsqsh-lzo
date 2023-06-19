libsqsh-lzo
===========

This is an extension for [libsqsh](https://github.com/Gottox/libsqsh) that adds
support for the [LZO](http://www.oberhumer.com/opensource/lzo/) compression.

## Usage:

libsqsh-lzo overwrites the `sqsh__impl_lzo` symbol (that is marked as `weak`
within libsqsh). This allows to add support for LZO compression to existing binaries
without the need to recompile them, but also to link against libsqsh-lzo directly.

### injecting into existing binaries:

To inject libsqsh-lzo into an existing binary you need to set the `LD_PRELOAD`
environment variable to the path of the libsqsh-lzo.so library. For example:

```
LD_PRELOAD=/usr/local/lib/libsqsh-lzo.so sqsh-ls /path/to/archive.squashfs
```

If the archive uses LZO compression, you should be able to extract the archive.

### linking against libsqsh-lzo:

To link against libsqsh-lzo you need to link against libsqsh and liblzo2. For 
example:

```
cd libsqsh
cc tools/ls.c tools/common.c -lsqsh-lzo -lsqsh -llzo2 -Lbuild/lib -L../libsqsh-lzo/build/lib -o sqsh-ls
```

## Building:

libsqsh-lzo uses [meson](https://mesonbuild.com/) as build system. To build it
you need to have meson and ninja installed. Then run:

```
meson build 
ninja -C build
```

## License:

libsqsh-lzo is licensed under the GPLv2. See the LICENSE file for more details.

Keep in mind, that libsqsh itself is BSD licensed. The implications of this are
kept as a exercise for the reader.
