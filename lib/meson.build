libsqsh_lzo_sources = [
    'lzo.c',
]
libsqsh_lzo_deps = [
    lzo,
    libsqsh_dep,
]

libsqsh_lzo = library(
    'sqsh-lzo',
    libsqsh_lzo_sources,
    install: not meson.is_subproject(),
    dependencies: libsqsh_lzo_deps,
    version: meson.project_version(),
)

