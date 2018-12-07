# Libc porting status

This file contains details of the status of the project to port musl to form Azalea libc. A simple file is used so as
to avoid a large number of tracking issues - this way, the bug tracker can be used for actual bugs.

## Contents

- [Overview](#overview)
- [Major deficiencies](#major-deficiencies)
- [Minor deficiencies](#minor-deficiencies)
- [Features grouped by header](#features-grouped-by-header)
  - [C99 header files](#c99-headers)
  - [Other header files](#other-headers)

## Overview

At present, this project is in very early stages. Most features do not work at all in Azalea - details of those that do
can be found in the section [Features grouped by header](#features-grouped-by-header).

It is also notable that no significant testing has been carried out.

## Major deficiencies

These deficiencies represent features that are incompletely ported compared to how the library should work if it had
been fully ported to Azalea.

- There is no support for the "aux" variable.
- Exit codes are not supported.
- Thread IDs are always set to zero.
- There are a whole load of warnings generated.
- File mode flags are basically unsupported.
- mmap only maps, it doesn't look at any of the flags or other nice features.

## Minor deficiencies

- Futexes do not support the private flag, nor waking more than one thread at a time. (see __futexwait and __wake)
- mremap doesn't support moved or shrinking remaps, only expanding ones.

Various other minor deficiencies can be found by searching "Azalea deficiency" in the source tree.

## Features grouped by header

### C99 Headers

Status | File name | Notes
---------|-----------|------
not started | assert.h | Requires files support
not started | complex.h | Needs floating point support to work first
incomplete | ctype.h | Compiles but not tested.
incomplete | errno.h | Not tested, but should just work
not started | fenv.h | Needs floating point support to work first
not started | float.h | Needs floating point support to work first
not started | inttypes.h | Not expecting changes from musl version
Completed | iso646.h | No changes from musl version
Completed | limits.h | No changes from musl version
not started | locale.h | Lots of things, but at first glance doesn't look too system dependent.
not started | math.h | Requires floating point math, and a careful check not to duplicate anything.
not started | setjmp.h | Ought not be too bad.
not started | signal.h | Probably a fair amount of work - we don't do "signals" as such.
Completed | stdalign.h | No changes from musl version
incomplete | stdarg.h | Not tested, but should just work
not started | stdatomic.h | Not part of the musl library?
Completed | stdbool.h | No changes from musl version
incomplete | stddef.h | Not tested, but should just work
incomplete | stdint.h | No changes made, not expecting any.
incomplete | stdio.h | A fair amount of work. Malloc/free do now work. Printf works, using a pretty generic path
incomplete | stdlib.h | Some parts ported but not fully tested. Malloc-type and math functions still to come.
Completed | stdnoreturn.h | No changes from musl version. Only a single macro.
incomplete | string.h | Ported but not fully tested
not started | tgmath.h | Probably not too much work
not started | threads.h | Plenty of work, although largely I think it's a case of swapping syscalls - and extending the Azalea calls that are available.
not started | time.h | Requires quite a lot of work on the kernel
not started | uchar.h | Looks like not too much work.
not started | wchar.h | Could be quite a lot of work.
not started | wctype.h | Oughtn't be too bad.

### Other Headers

No deliberate progress has been made on any of the following headers.

- aio.h
- alloca.h
- ar.h
- byteswap.h
- cpio.h
- crypt.h
- dirent.h
- dlfcn.h
- elf.h
- endian.h
- err.h
- fcntl.h
- features.h
- fmtmsg.h
- fnmatch.h
- ftw.h
- getopt.h
- glob.h
- grp.h
- iconv.h
- ifaddrs.h
- langinfo.h
- lastlog.h
- libgen.h
- libintl.h
- link.h
- malloc.h
- memory.h
- mntent.h
- monetary.h
- mqueue.h
- netdb.h
- nl_types.h
- paths.h
- poll.h
- pthread.h
- pty.h
- pwd.h
- regex.h
- resolv.h
- sched.h
- search.h
- semaphore.h
- shadow.h
- spawn.h
- stdc-predef.h
- stdio_ext.h
- strings.h
- stropts.h
- syscall.h
- sysexits.h
- syslog.h
- tar.h
- termios.h
- ucontext.h
- ulimit.h
- unistd.h
- utime.h
- utmp.h
- utmpx.h
- values.h
- wait.h
- wordexp.h
- sys/xattr.h
- sys/wait.h
- sys/vt.h
- sys/vfs.h
- sys/utsname.h
- sys/user.h
- sys/un.h
- sys/uio.h
- sys/ucontext.h
- sys/types.h
- sys/ttydefaults.h
- sys/timex.h
- sys/times.h
- sys/timerfd.h
- sys/time.h
- sys/timeb.h
- sys/termios.h
- sys/sysmacros.h
- sys/syslog.h
- sys/sysinfo.h
- sys/syscall.h
- sys/swap.h
- sys/stropts.h
- sys/statvfs.h
- sys/stat.h
- sys/statfs.h
- sys/soundcard.h
- sys/socket.h
- sys/signal.h
- sys/signalfd.h
- sys/shm.h
- sys/sendfile.h
- sys/sem.h
- sys/select.h
- sys/resource.h
- sys/reg.h
- sys/reboot.h
- sys/random.h
- sys/quota.h
- sys/ptrace.h
- sys/procfs.h
- sys/prctl.h
- sys/poll.h
- sys/personality.h
- sys/param.h
- sys/mtio.h
- sys/msg.h
- sys/mount.h
- sys/mman.h
- sys/klog.h
- sys/kd.h
- sys/ipc.h
- sys/io.h
- sys/ioctl.h
- sys/inotify.h
- sys/fsuid.h
- sys/file.h
- sys/fcntl.h
- sys/fanotify.h
- sys/eventfd.h
- sys/errno.h
- sys/epoll.h
- sys/dir.h
- sys/cachectl.h
- sys/auxv.h
- sys/acct.h
- scsi/sg.h
- scsi/scsi_ioctl.h
- scsi/scsi.h
- net/route.h
- netpacket/packet.h
- netinet/udp.h
- netinet/tcp.h
- netinet/ip_icmp.h
- netinet/ip.h
- netinet/ip6.h
- netinet/in_systm.h
- netinet/in.h
- netinet/igmp.h
- netinet/if_ether.h
- netinet/icmp6.h
- netinet/ether.h
- net/if.h
- net/if_arp.h
- net/ethernet.h
- arpa/tftp.h
- arpa/telnet.h
- arpa/nameser.h
- arpa/nameser_compat.h
- arpa/inet.h
- arpa/ftp.h
