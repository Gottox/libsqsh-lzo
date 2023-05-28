libsqsh_lzo_sources = [
    'lzo.c',
]
libsqsh_lzo_deps = [
    lzo,
    libsqsh_dep,
]

default_library = get_option('default_library')
libsqsh_lzo = library(
    'sqsh-lzo',
    libsqsh_lzo_sources,
    install: not meson.is_subproject(),
    dependencies: libsqsh_lzo_deps,
    version: meson.project_version(),
    soversion: meson.project_version().split('.')[0],
    include_directories: [
        libsqsh_lzo_include,
    ],
)

