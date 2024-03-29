project(
    'libsqsh-lzo',
    ['c'],
    default_options: [
        'c_std=c11',
        'optimization=0',
        'werror=false',
        'warning_level=3',
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
