#include <stdarg.h>
#include <wchar.h>

#include <stdint.h>

[[noreturn]] void panic(const char *message,
                        bool override_address = false,
                        uint64_t k_rsp = 0,
                        uint64_t r_rip = 0,
                        uint64_t r_rsp = 0);

int swprintf(wchar_t *s, size_t n, const wchar_t *fmt, ...)
{
	panic("swprintf in kernel - C++ library fault", false, 0, 0, 0);
}
