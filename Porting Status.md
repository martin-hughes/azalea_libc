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
- mmap only maps, it doesn't look at any of the flags or other nice features. It also can't memory map files!
- In the kernel build, errno is shared amongst all threads (in user builds, it is per-thread)
- There is incomplete support for pthread, which means some locks are not valid - there are places in the code marked
  with /* PTHREAD where locking code has been commented out.

## Minor deficiencies

- Futexes do not support the private flag, nor waking more than one thread at a time. (see __futexwait and __wake)
- mremap doesn't support moved or shrinking remaps, only expanding ones.

Various other minor deficiencies can be found by searching "Azalea deficiency" in the source tree.

## Features grouped by header

### C99 Headers

Note: At this point, basically none of these features have been thoroughly tested. Having a status of Completed doesn't
necessarily mean working properly!

Status | Tested? | File name | Notes
-------|---------|-----------|-------
Completed | No | assert.h | Should now work.
Completed | No | complex.h | Compiled in but untested.
Completed | No | ctype.h | Compiles but not tested.
Broken | No | errno.h | Only one errno per process is given. Better thread support is needed in order to re-enable per-thread errno.
Completed | Partial | fenv.h | All functions added, but only very basic testing completed.
Completed | N/A | float.h | Header doesn't declare new functionality, only constants.
Completed | No | inttypes.h | No changes from musl version
Completed | No | iso646.h | No changes from musl version
Completed | No | limits.h | No changes from musl version
Completed | No | locale.h | Included in the library, but not tested.
Completed | Partial | math.h | All functions are included. Only basic floating point testing completed.
not started | No | setjmp.h | Ought not be too bad.
not started | No | signal.h | Probably a fair amount of work - we don't do "signals" as such.
Completed | No | stdalign.h | No changes from musl version
Completed | No | stdarg.h | Not tested, but should just work
not started | No | stdatomic.h | Not part of the musl library?
Completed | No | stdbool.h | No changes from musl version
Completed | No | stddef.h | Not tested, but should just work
Completed | No | stdint.h | No changes made, not expecting any.
incomplete | No | stdio.h | A fair amount of work left, although a large proportion of file-based functionality works.
Completed | No | stdlib.h | I think all parts of this are included in the library now, but I may be wrong.
Completed | No | stdnoreturn.h | No changes from musl version. Only a single macro.
Completed | No | string.h | Ported but not fully tested
Completed | No | tgmath.h | Untested. I think this is simply a set of macro definitions around math.h and complex.h
not started | No | threads.h | Plenty of work, although largely I think it's a case of swapping syscalls - and extending the Azalea calls that are available.
incomplete | No | time.h | Most functions work, but setting timers does not. Other minor omissions too.
not started | No | uchar.h | Looks like not too much work.
not started | No | wchar.h | Could be quite a lot of work.
not started | No | wctype.h | Oughtn't be too bad.

### Other Headers

Status | Tested? | File name | Notes
-------|---------|-----------|-------
incomplete | No | getopt.h | Should just work.
incomplete | NO! | pthread.h | Large chunks of the pthread library compile, but they really aren't tested and could expose some comical bugs.
completed | No | regex.h | Seems to compile cleanly with no changes, but is completely untested.
incomplete | No | termios.h | Some pretty minimal work has been completed - tc(get|set)attr are implemented but only support a trivial set of flags.
incomplete | No | unistd.h | It's highly recommended to avoid using this header. Most of the supported functions have been quickly hacked together and probably don't work correctly. Frankly a bit of a mess.

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
- ucontext.h
- ulimit.h
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
