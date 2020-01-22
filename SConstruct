# SConstruct file for the Azalea Libc port of musl.
#
# I've chosen to use this because I'm more familiar with it than regular Makefiles, and I want to be able to move
# quickly. Once the project is more mature perhaps I will fall back on the old Makefile.

import os

def main_build_script(vars):
  global dependencies
  libc_env = build_default_env()
  libc_env['CXXFLAGS'] = '-nostdlib -nostdinc -nodefaultlibs -mcmodel=large -ffreestanding -fno-exceptions -std=c++17 -U _LINUX -U __linux__ -D __AZALEA__ -D KL_TRACE_BY_SERIAL_PORT -Wno-bitwise-op-parentheses -Wno-shift-op-parentheses'
  libc_env['CFLAGS'] = '-nostdlib -nostdinc -nodefaultlibs -mcmodel=large -ffreestanding -fno-exceptions -U _LINUX -U __linux__ -D __AZALEA__ -D KL_TRACE_BY_SERIAL_PORT -Wno-bitwise-op-parentheses -Wno-shift-op-parentheses'
  libc_env['LINKFLAGS'] = "-T build_support/kernel_stage.ld --start-group"
  libc_env['LINK'] = 'ld -Map output/kernel_map.map'
  libc_env.AppendENVPath('CPATH', '#/include')
  libc_env.AppendENVPath('CPATH', '#/output')
  libc_env.AppendENVPath('CPATH', '#/arch/x86_64')
  libc_env.AppendENVPath('CPATH', '#/arch/generic')
  libc_env.AppendENVPath('CPATH', '#/src/internal')
  libc_env.AppendENVPath('CPATH', os.path.join(vars['sys_image_root'], "apps", "developer", "kernel", "include"))

  lib_core_objects = libc_env.SConscript("#SConscript-core", 'libc_env', variant_dir='output', duplicate=0)
  lib_user_objects = libc_env.SConscript("#SConscript-user", 'libc_env', variant_dir='output', duplicate=0)
  lib_kernel_objects = libc_env.SConscript("#SConscript-kernel", 'libc_env', variant_dir='output', duplicate=0)
  lib_all_objects = lib_core_objects + lib_user_objects
  lib_complete = StaticLibrary("output/azalea_libc/azalea_libc", lib_all_objects)
  lib_kernel_objects = lib_core_objects + lib_kernel_objects
  lib_kernel = StaticLibrary("output/azalea_libc/azalea_libc_kernel", lib_kernel_objects)
  lib_folder = os.path.join(vars['sys_image_root'], "apps", "developer", "libc")
  lib_obj_folder = os.path.join(lib_folder, "lib")
  lib_include_folder = os.path.join(lib_folder, "include")
  libc_env.Install(lib_obj_folder, lib_complete)
  libc_env.Install(lib_obj_folder, lib_kernel)
  libc_env.Alias('install', lib_obj_folder)

  linux_shim_objects = libc_env.SConscript("#SConscript-linux_shim", 'libc_env', variant_dir='output', duplicate=0)
  linux_shim_lib = StaticLibrary("output/azalea_libc/azalea_linux_shim", linux_shim_objects)
  libc_env.Install(lib_obj_folder, linux_shim_lib)

  headers = libc_env.File(Glob("include/*.h"))
  libc_env.Install(lib_include_folder, headers)
  libc_env.Alias('install', lib_include_folder)

  bits_headers = [
    libc_env.File("output/bits/alltypes.h"),
    libc_env.Glob("arch/x86_64/bits/*.h"),
    libc_env.File("arch/generic/bits/errno.h"),
    libc_env.File("arch/generic/bits/poll.h"),
    libc_env.File("arch/generic/bits/resource.h"),
    libc_env.File("arch/generic/bits/termios.h"),
    ]
  bits_folder = os.path.join(lib_include_folder, "bits")
  libc_env.Install(bits_folder, bits_headers)
  libc_env.Alias('install', bits_headers)

  sys_headers = [
    libc_env.File("include/sys/file.h"),
    libc_env.File("include/sys/param.h"),
    libc_env.File("include/sys/poll.h"),
    libc_env.File("include/sys/resource.h"),
    libc_env.File("include/sys/time.h"),
    libc_env.File("include/sys/types.h"),
    libc_env.File("include/sys/select.h"),
    libc_env.File("include/sys/stat.h"),
    libc_env.File("include/sys/sysmacros.h"),

    ]
  sys_folder = os.path.join(lib_include_folder, "sys")
  libc_env.Install(sys_folder, sys_headers)
  libc_env.Alias('install', sys_headers)

def build_default_env():
  global at_header_preproc
  env = Environment()
  env['CC'] = 'clang'
  env['CXX'] = 'clang++'
  env['CPPPATH'] = '#'
  env['LINK'] = 'g++'
  env['AS'] = 'as'
  env['ASFLAGS'] = '--64'
  env['RANLIBCOM'] = ''
  env['ASCOMSTR'] =   "Assembling:   $TARGET"
  env['CCCOMSTR'] =   "Compiling:    $TARGET"
  env['CXXCOMSTR'] =  "Compiling:    $TARGET"
  env['LINKCOMSTR'] = "Linking:      $TARGET"
  env['ARCOMSTR'] =   "(pre-linking) $TARGET"
  env['RANLIBCOMSTR'] = "Indexing:     $TARGET"
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

def construct_variables():
  var = Variables(["azalea_config/default_config.py", "variables.cache" ], ARGUMENTS)
  var.AddVariables(
    PathVariable("sys_image_root",
                 "Root of Azalea system image. Look for include files, libraries and installation locations here.",
                 None,
                 PathVariable.PathIsDir))

  e = Environment(variables = var)

  var.Save("variables.cache", e)

  return e

vars = construct_variables()

main_build_script(vars)