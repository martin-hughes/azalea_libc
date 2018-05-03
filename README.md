# Azalea libc

[Project Azalea](https://github.com/martin-hughes/project_azalea) has reached
the point where it is starting to need a standard C library to accompany it.
Rather than recreate the whole thing from scratch it was decided to base the
new libary on an established one - musl.

Details about musl can be seen below.

In the early phases only small parts of the library will actually be built into
an object file. Nonetheless, it was decided to keep the entire source tree as
close as possible to the original, to simplify merging upstream changes in the
future.

It's quite unlikely that Azalea will ever become interesting enough that the
musl developers would be interested in merging Azalea-specific work back
upstream, but maintaining the same folder structure would certainly make it
easier.

In order to avoid confusion between this project and the musl upstream project,
this project will try to use the name "Azalea libc" so far as possible.

# musl libc

musl, pronounced like the word "mussel", is an MIT-licensed
implementation of the standard C library targetting the Linux syscall
API, suitable for use in a wide range of deployment environments. musl
offers efficient static and dynamic linking support, lightweight code
and low runtime overhead, strong fail-safe guarantees under correct
usage, and correctness in the sense of standards conformance and
safety. musl is built on the principle that these goals are best
achieved through simple code that is easy to understand and maintain.

The 1.1 release series for musl features coverage for all interfaces
defined in ISO C99 and POSIX 2008 base, along with a number of
non-standardized interfaces for compatibility with Linux, BSD, and
glibc functionality.

For basic installation instructions, see the included INSTALL file.
Information on full musl-targeted compiler toolchains, system
bootstrapping, and Linux distributions built on musl can be found on
the project website:

    http://www.musl-libc.org/
