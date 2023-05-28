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

#libsqsh_dep = dependency('libsqsh', version: '>=0.5.0')
libsqsh_dep = subproject('libsqsh').get_variable('libsqsh_dep')
lzo = dependency('lzo2')

subdir('include')

subdir('lib')

if get_option('default_library') == 'both'
    libsqsh_lzo = libsqsh_lzo.get_static_lib()
endif

libsqsh_lzo_dep = declare_dependency(
    link_with: libsqsh_lzo,
    include_directories: libsqsh_lzo_include,
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
