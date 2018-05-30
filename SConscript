Import('libc_env')

dependencies = [
    "crt/crt1.c",

    Glob("src/ctype/*.c"),

    "src/env/__environ.c",
    "src/env/__init_tls.c",
    "src/env/__libc_start_main.c",

    Glob("src/errno/*.c"),

    "src/exit/_Exit.c",
    "src/exit/exit.c",

    "src/internal/libc.c",

    "src/locale/__lctrans.c",
    "src/locale/locale_map.c",

    "src/malloc/expand_heap.c",
    "src/malloc/malloc.c",

    "src/math/__fpclassify.c",
    "src/math/__fpclassifyl.c",
    "src/math/__signbit.c",
    "src/math/__signbitl.c",
    "src/math/frexpl.c",

    "src/mman/madvise.c",
    "src/mman/mmap.c",
    "src/mman/mremap.c",
    "src/mman/munmap.c",

    Glob("src/multibyte/*.c"),

    "src/stdio/__fdopen.c",
    "src/stdio/__lockfile.c",
    "src/stdio/__stdio_exit.c",
    "src/stdio/__towrite.c",
    "src/stdio/fopen.c",
    "src/stdio/fwrite.c",
    "src/stdio/ofl.c",
    "src/stdio/printf.c",
    "src/stdio/snprintf.c",
    "src/stdio/stdout.c",
    "src/stdio/vfprintf.c",
    "src/stdio/vsnprintf.c",
    Glob("src/stdlib/*.c"),
    Glob("src/string/*.c"),

    "src/thread/x86_64/__set_thread_area.cpp",
    "src/thread/__lock.c",
    "src/thread/__wait.c",
  ]

at_header_obj = libc_env.AlltypesHeaderBuilder("bits/alltypes", ["#/arch/x86_64/bits/alltypes", "#/include/alltypes"])
lib_obj = libc_env.StaticLibrary("azalea_libc/azalea_libc", dependencies)
libc_env.Depends("*.c", "bits/alltypes.h")

Return ('lib_obj')