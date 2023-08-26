sqsh_lzo_test = 'lzo.c'

testlib_dep = subproject('cextras').get_variable('testlib_dep')
test = executable(
    'lzo_test',
    sqsh_lzo_test,
    install: false,
    dependencies: [ libsqsh_lzo_dep, cextras_dep, testlib_dep ],
    include_directories: libsqsh_include,
)
test('lzo.c', test)

