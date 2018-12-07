Import('libc_env')

dependencies = [
    "crt/crt1.c",

    Glob("src/ctype/*.c"),

    "src/env/__environ.c",
    "src/env/__init_tls.c",
    "src/env/__libc_start_main.c",
    "src/env/clearenv.c",
    "src/env/getenv.c",
    "src/env/putenv.c",
    "src/env/setenv.c",
    "src/env/unsetenv.c",

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

    "src/stdio/__fmodeflags.c",
    "src/stdio/__fdopen.c",
    "src/stdio/__lockfile.c",
    "src/stdio/__stdio_close.c",
    "src/stdio/__stdio_exit.c",
    "src/stdio/__stdio_read.c",
    "src/stdio/__stdio_seek.c",
    "src/stdio/__stdio_write.c",
    "src/stdio/__toread.c",
    "src/stdio/__towrite.c",
    "src/stdio/__uflow.c",
    "src/stdio/fclose.c",
    "src/stdio/fflush.c",
    "src/stdio/fgetc.c",
    "src/stdio/fgets.c",
    "src/stdio/fopen.c",
    "src/stdio/fputs.c",
    "src/stdio/fseek.c",
    "src/stdio/fwrite.c",
    "src/stdio/getc.c",
    "src/stdio/getchar.c",
    "src/stdio/getchar_unlocked.c",
    "src/stdio/getdelim.c",
    "src/stdio/getline.c",
    "src/stdio/ofl.c",
    "src/stdio/ofl_add.c",
    "src/stdio/printf.c",
    "src/stdio/snprintf.c",
    "src/stdio/stderr.c",
    "src/stdio/stdin.c",
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