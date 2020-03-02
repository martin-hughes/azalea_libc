# SConstruct file for the Azalea Libc port of musl.
#
# I've chosen to use this because I'm more familiar with it than regular Makefiles, and I want to be able to move
# quickly. Once the project is more mature perhaps I will fall back on the old Makefile.

import os

shared_flags_list = [
  '-nostdlib',
  '-nostdinc',
  '-nodefaultlibs',
  '-mcmodel=large',
  '-ffreestanding',
  '-U _LINUX',
  '-U __linux__',
  '-D __AZALEA__',
  '-Wno-bitwise-op-parentheses',
  '-Wno-shift-op-parentheses',
]

kernel_extra_flags_list = [
  '-fno-exceptions',
  '-funwind-tables',
]

kernel_cxx_flags_list = [
  '-std=c++17',
]

user_extra_flags_list = [

]

user_cxx_flags_list = [
  '-std=c++17',
]

def main_build_script(vars):
  global dependencies
  core_env = build_default_env()
  core_env.AppendENVPath('CPATH', '#/include')
  core_env.AppendENVPath('CPATH', '#/output')
  core_env.AppendENVPath('CPATH', '#/arch/x86_64')
  core_env.AppendENVPath('CPATH', '#/arch/generic')
  core_env.AppendENVPath('CPATH', '#/src/internal')
  core_env.AppendENVPath('CPATH', os.path.join(vars['sys_image_root'], "apps", "developer", "kernel", "include"))

  kernel_env = core_env.Clone()
  kernel_env['CXXFLAGS'] = " ".join(shared_flags_list + kernel_extra_flags_list + kernel_cxx_flags_list)
  kernel_env['CFLAGS'] = " ".join(shared_flags_list + kernel_extra_flags_list)

  user_env = core_env.Clone()
  user_env['CXXFLAGS'] = " ".join(shared_flags_list + user_extra_flags_list + user_cxx_flags_list)
  user_env['CFLAGS'] = " ".join(shared_flags_list + user_extra_flags_list)

  # Construct 'core' objects for both user mode and kernel mode libraries.
  kernel_core_objects = kernel_env.SConscript("#SConscript-core", {'libc_env' : kernel_env}, variant_dir='output/kernel', duplicate=0)
  user_core_objects = user_env.SConscript("#SConscript-core", {'libc_env' : user_env}, variant_dir='output/user', duplicate=0)

  # Construct kernel mode objects only in kernel mode
  lib_kernel_objects = kernel_env.SConscript("#SConscript-kernel", {'libc_env' : kernel_env}, variant_dir='output/kernel', duplicate=0)

  # Construct user mode objects only in user mode
  lib_user_objects = user_env.SConscript("#SConscript-user", {'libc_env' : user_env}, variant_dir='output/user', duplicate=0)

  kernel_lib_objects = kernel_core_objects + lib_kernel_objects
  user_lib_objects = user_core_objects + lib_user_objects

  user_lib_complete = StaticLibrary("output/azalea_libc/azalea_libc", user_lib_objects)
  kernel_lib_complete = StaticLibrary("output/azalea_libc/azalea_libc_kernel", kernel_lib_objects)

  lib_folder = os.path.join(vars['sys_image_root'], "apps", "developer", "libc")
  lib_obj_folder = os.path.join(lib_folder, "lib")
  lib_include_folder = os.path.join(lib_folder, "include")
  core_env.Install(lib_obj_folder, user_lib_complete)
  core_env.Install(lib_obj_folder, kernel_lib_complete)
  core_env.Alias('install', lib_obj_folder)

  linux_shim_objects = user_env.SConscript("#SConscript-linux_shim", {'libc_env' : user_env}, variant_dir='output', duplicate=0)
  linux_shim_lib = StaticLibrary("output/azalea_libc/azalea_linux_shim", linux_shim_objects)
  core_env.Install(lib_obj_folder, linux_shim_lib)

  headers = core_env.File(Glob("include/*.h"))
  core_env.Install(lib_include_folder, headers)
  core_env.Alias('install', lib_include_folder)

  bits_headers = [
    core_env.File("output/bits/alltypes.h"),
    core_env.Glob("arch/x86_64/bits/*.h"),
    core_env.File("arch/generic/bits/errno.h"),
    core_env.File("arch/generic/bits/link.h"),
    core_env.File("arch/generic/bits/poll.h"),
    core_env.File("arch/generic/bits/resource.h"),
    core_env.File("arch/generic/bits/termios.h"),
    ]
  bits_folder = os.path.join(lib_include_folder, "bits")
  core_env.Install(bits_folder, bits_headers)
  core_env.Alias('install', bits_headers)

  sys_headers = [
    core_env.File("include/sys/file.h"),
    core_env.File("include/sys/param.h"),
    core_env.File("include/sys/poll.h"),
    core_env.File("include/sys/resource.h"),
    core_env.File("include/sys/time.h"),
    core_env.File("include/sys/types.h"),
    core_env.File("include/sys/select.h"),
    core_env.File("include/sys/stat.h"),
    core_env.File("include/sys/sysmacros.h"),

    ]
  sys_folder = os.path.join(lib_include_folder, "sys")
  core_env.Install(sys_folder, sys_headers)
  core_env.Alias('install', sys_headers)

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