libsqsh-lzo
===========

This is an extension for [libsqsh](https://github.com/Gottox/libsqsh) that adds
support for the [LZO](http://www.oberhumer.com/opensource/lzo/) compression.

## Usage:

To enable the LZO support, you have to call `sqsh_lzo_support()` before you
start using libsqsh:

```c 
#include <sqsh.h>
#include <sqsh-lzo.h>

int main(int argc, char **argv) {
	sqsh_lzo_support();

	/* ... */
}
```
