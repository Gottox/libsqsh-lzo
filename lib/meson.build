libsqsh_lzo_deps = [
    lzo,
    cextras_dep,
]

libsqsh_lzo = shared_library(
    'sqsh-lzo',
    'lzo.c',
    install: not meson.is_subproject(),
    dependencies: libsqsh_lzo_deps,
    version: meson.project_version(),
    include_directories: libsqsh_include,
)

