Import('libc_env')

dependencies = [
    "crt/crt1.c",

    "src/env/__environ.c",
    "src/env/__init_tls.c",
    "src/env/__libc_start_main.c",

    "src/errno/__errno_location.c",

    "src/exit/_Exit.cpp",
    "src/exit/exit.c",

    "src/internal/libc.c",

    "src/string/memcpy.c",
    "src/string/memset.c",
    "src/string/strlen.c",

    "src/thread/x86_64/__set_thread_area.cpp",
  ]

at_header_obj = libc_env.AlltypesHeaderBuilder("bits/alltypes", ["#/arch/x86_64/bits/alltypes", "#/include/alltypes"])
syscall_header_obj = libc_env.SyscallHeaderBuilder("bits/syscall", ["#/arch/x86_64/bits/syscall", ])
lib_obj = libc_env.StaticLibrary("azalea_libc/azalea_libc", dependencies)
libc_env.Depends("*.c", "bits/alltypes.h")
libc_env.Depends("*.c", "bits/syscall.h")

Return ('lib_obj')