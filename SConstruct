# SConstruct file for the Azalea Libc port of musl.
#
# I've chosen to use this because I'm more familiar with it than regular Makefiles, and I want to be able to move
# quickly. Once the project is more mature perhaps I will fall back on the old Makefile.

import os
import azalea_config.config as config

def main_build_script():
  global dependencies
  libc_env = build_default_env()
  libc_env['CXXFLAGS'] = '-mno-red-zone -nostdlib -nostdinc -nodefaultlibs -mcmodel=large -ffreestanding -fno-exceptions -std=gnu++14 -U _LINUX -U __linux__ -D __AZALEA__ -D KL_TRACE_BY_SERIAL_PORT -Wno-bitwise-op-parentheses -Wno-shift-op-parentheses'
  libc_env['CFLAGS'] = '-mno-red-zone -nostdlib -nostdinc -nodefaultlibs -mcmodel=large -ffreestanding -fno-exceptions -U _LINUX -U __linux__ -D __AZALEA__ -D KL_TRACE_BY_SERIAL_PORT -Wno-bitwise-op-parentheses -Wno-shift-op-parentheses'
  libc_env['LINKFLAGS'] = "-T build_support/kernel_stage.ld --start-group"
  libc_env['LINK'] = 'ld -Map output/kernel_map.map'
  libc_env.AppendENVPath('CPATH', '#/include')
  libc_env.AppendENVPath('CPATH', '#/output')
  libc_env.AppendENVPath('CPATH', '#/arch/x86_64')
  libc_env.AppendENVPath('CPATH', '#/arch/generic')
  libc_env.AppendENVPath('CPATH', '#/src/internal')
  libc_env.AppendENVPath('CPATH', os.path.join(config.azalea_dev_folder, "include"))

  lib_obj = libc_env.SConscript("#SConscript", 'libc_env', variant_dir='output', duplicate=0)
  libc_env.Install(config.install_folder, lib_obj)
  libc_env.Alias('install', config.install_folder)

  headers = libc_env.File(Glob("include/*.h"))
  include_folder = os.path.join(config.install_folder, "include")
  libc_env.Install(include_folder, headers)
  libc_env.Alias('install', include_folder)

  bits_headers = [libc_env.File("output/bits/alltypes.h"), libc_env.Glob("arch/x86_64/bits/*.h")]
  bits_folder = os.path.join(include_folder, "bits")
  libc_env.Install(bits_folder, bits_headers)
  libc_env.Alias('install', bits_headers)

def build_default_env():
  global at_header_preproc
  env = Environment()
  env['CC'] = 'clang'
  env['CXX'] = 'clang++'
  env['CPPPATH'] = '#'
  env['LINK'] = 'g++'
  env['AS'] = 'nasm'
  env['ASFLAGS'] = '-f elf64'
  env['RANLIBCOM'] = ''
  env['ASCOMSTR'] =   "Assembling:   $TARGET"
  env['CCCOMSTR'] =   "Compiling:    $TARGET"
  env['CXXCOMSTR'] =  "Compiling:    $TARGET"
  env['LINKCOMSTR'] = "Linking:      $TARGET"
  env['ARCOMSTR'] =   "(pre-linking) $TARGET"
  env['LIBS'] = [ ]
  env.Append(BUILDERS = {'AlltypesHeaderBuilder' : at_header_preproc})

  return env

def syscall_header_action(target, source, env):
  if len(source) != len(target):
    raise SCons.Errors.StopError(SCons.Warnings.Warning, "Syscall builder input and output lengths must be the same")
    return None

  for x in range(len(source)):
    copy_cmd = "cp %s %s" % (source[x], target[x])
    sed_cmd = "sed -n -e s/__NR_/SYS_/p < %s >> %s" % (source[x], target[x])

    os.system(copy_cmd)
    os.system(sed_cmd)

at_header_preproc = Builder(
  action = Action('sed -f tools/mkalltypes.sed $SOURCES > $TARGET'),
  suffix = '.h',
  src_suffix = '.h.in'
)

main_build_script()