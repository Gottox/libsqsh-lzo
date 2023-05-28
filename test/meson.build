sqsh_lzo_test = 'lzo.c'

test = executable(
    'lzo_test',
    sqsh_lzo_test,
    install: false,
    dependencies: [ libsqsh_lzo_dep, libsqsh_dep ],
)
test('lzo.c', test)

