project(
    'libsqsh-lzo',
    ['c'],
    default_options: [
        'c_std=c11',
        'optimization=0',
        'werror=false',
        'warning_level=3',
        'sqsh-tools:curl=disabled',
        'sqsh-tools:doc=false',
        'sqsh-tools:examples=false',
        'sqsh-tools:fuse=disabled',
        'sqsh-tools:fuse-old=disabled',
        'sqsh-tools:fuzzer=false',
        'sqsh-tools:lz4=disabled',
        'sqsh-tools:lzma=disabled',
        'sqsh-tools:posix=enabled',
        'sqsh-tools:test=false',
        'sqsh-tools:threads=disabled',
        'sqsh-tools:tools=true',
        'sqsh-tools:zlib=disabled',
        'sqsh-tools:zstd=disabled',
    ],
    version: '0.0.0',
    meson_version: '>=0.57',
    license: [
        'GPL-2.0-only',
    ],
)

sqsh_tools_sub = subproject('sqsh-tools')
libsqsh_include = [
    sqsh_tools_sub.get_variable('libsqsh_include'),
    sqsh_tools_sub.get_variable('libsqsh_private_include'),
    sqsh_tools_sub.get_variable('libsqsh_common_include'),
]
cextras_dep = subproject('cextras').get_variable('cextras_dep')
lzo = dependency('lzo2')

subdir('lib')

libsqsh_lzo_dep = declare_dependency(
    link_with: libsqsh_lzo,
)

if get_option('test') != 'false'
    subdir('test')
endif

pkg_mod = import('pkgconfig')
pkg_mod.generate(
    libsqsh_lzo,
    name: 'libsqsh-lzo',
    filebase: 'libsqsh',
    description: 'A library to access squashfs archives [lzo extension]',
    subdirs: 'sqsh',
    libraries: libsqsh_lzo,
    version: meson.project_version(),
)
