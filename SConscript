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

    Glob("src/string/*.c"),

    "src/thread/x86_64/__set_thread_area.cpp",
  ]

at_header_obj = libc_env.AlltypesHeaderBuilder("bits/alltypes", ["#/arch/x86_64/bits/alltypes", "#/include/alltypes"])
lib_obj = libc_env.StaticLibrary("azalea_libc/azalea_libc", dependencies)
libc_env.Depends("*.c", "bits/alltypes.h")

Return ('lib_obj')