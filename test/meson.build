sqsh_lzo_test = 'lzo.c'

testlib_dep = subproject('cextras').get_variable('testlib_dep')
test = executable(
    'lzo_test',
    sqsh_lzo_test,
    install: false,
    dependencies: [libsqsh_lzo_dep, cextras_dep, testlib_dep],
    include_directories: libsqsh_include,
)
test('lzo.c', test)

mksquashfs = find_program('mksquashfs')
integration_test = files('integration.sh')
integration_image = custom_target(
    'image.squashfs',
    command: [mksquashfs, '@INPUT@', '@OUTPUT@', '-noappend', '-comp', 'lzo'],
    input: [integration_test],
    output: 'sqfs',
    install: false,
)
sqsh_ls = sqsh_tools_sub.get_variable('tools')['sqsh-ls']
integration_env = {
    'SQUASH_IMAGE': integration_image.full_path(),
    'SQSH_LS': sqsh_ls.full_path(),
}
integration_depends = [integration_image, sqsh_ls]
test(
    'integration',
    integration_test,
    env: integration_env + {
        'LIBSQSH_LZO': libsqsh_lzo.full_path(),
    },
    depends: integration_depends,
)
test(
    'integration_should_fail',
    integration_test,
    should_fail: true,
    env: integration_env,
    depends: integration_depends,
)
