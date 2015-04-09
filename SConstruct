import os, SCons.Script, sys

from scripts import formatted_output

env = Environment(ENV = {'PATH' : os.environ['PATH'],
                         'HOME' : os.environ['HOME'],
                         'TERM' : 'xterm'},
                  CXX='g++',
                  tools=['default'], toolpath=[''])


AddOption('--verbose',
          action='store_true',
          help='outputs full build commands',
          default=False)

AddOption('--release',
          action='store_true',
          help='no debug, optimized compile',
          default=False)

AddOption('--win64',
          action='store_true',
          help='cross-compiles for windows',
          default=False)

Help("""
Type: 'scons [OPTIONS]' -> compiles program

OPTIONS:
      '--verbose'       -> outputs full build commands
      '--release'       -> compiles with -O2, and without debugging info
      '--win64'         -> cross-compiles program for win64 platform.
""")


if not GetOption('verbose'):
    formatted_output.enableShortenedColoredOuput(env)

if GetOption('release'):
    env['CCFLAGS'].extend(['-O2', '-DNDEBUG'])
    build_type = 'release'
else:
    env['CCFLAGS'].extend(['-O0', '-g', '-gdwarf-2'])
    build_type = 'debug'

if GetOption('win64'):
    env.Tool('crossmingw', toolpath = ['./scripts/'])
    env['LINKFLAGS'].append('--static')
    os_target = 'win'
else:
    os_target = 'linux'

build_type_path = os_target + '/'+ build_type
env['base_vardir'] = '#build/' + build_type_path
env['base_exec_dir'] = '#/bin/' + build_type_path
env['base_lib_dir'] = '#/lib/' + build_type_path

vardir = env['base_vardir'] + '/src'

env['gccWarningFlags'] = [
   '-Wall', '-Wextra', '-Wcast-align', '-Wcast-qual',
   '-fpermissive',
   '-Wconversion', '-Wdisabled-optimization',
   '-Wfloat-equal', '-Wformat=2', '-Wimport', '-Winit-self',
   '-Winline', '-Winvalid-pch', '-Wlong-long',
   '-Wmissing-format-attribute', '-Wmissing-include-dirs',
   '-Wmissing-noreturn', '-Wpacked', '-Wpointer-arith',
   '-Wredundant-decls', '-Wshadow', '-Wstack-protector',
   '-Wstrict-aliasing=2', '-Wunreachable-code',
   '-Wunsafe-loop-optimizations', '-Wunused',
   '-Wvariadic-macros', '-Wwrite-strings', '-pedantic',
   '-pedantic-errors', '-Woverloaded-virtual',
   '-Wswitch-enum'
]

Export('env')
env.VariantDir(vardir, 'src')
SConscript(vardir + '/SConscript')
