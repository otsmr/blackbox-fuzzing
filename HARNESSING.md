```sh
# Start in docker container
$ docker run -ti -v $PWD/:/share forallsecure/fuzzing-firmware

# Install cross compiler for mipsel
$ apt update
$ apt install -y gcc-mipsel-linux-gnu

# Cross compile as shared library
$ mipsel-linux-gnu-gcc http_recv_hook.c -o http_recv_hook.o -shared -fPIC

# Create sample corpus
$ echo "AAABBBCCC" > corpus.txt

$ chroot root /qemu-mipsel-static -strace /usr/bin/wscd -d 3 -i eth0 -m 1

$ cp fuzzing/http_recv_hook.o root/http_recv_hook.o
$ chroot root /qemu-mipsel-static -E LD_PRELOAD=/http_recv_hook.o /usr/bin/wscd
/usr/bin/wscd: can\'t load library 'libc.so.6'

$ cp /usr/mipsel-linux-gnu/lib/ld.so.1 root/lib/

    $ cp /usr/mipsel-linux-gnu/lib/libc.so.6 root/lib/
    /usr/bin/wscd: '/lib/libc.so.6' library contains unsupported TLS
    /usr/bin/wscd: '/lib/libc.so.6' library contains unsupported TLS
    /usr/bin/wscd: can\'t load library 'libc.so.6'

$ cp root/lib/libc.so.0 root/lib/libc.so.6


$ chroot root /qemu-mipsel-static -E LD_PRELOAD=/http_recv_hook.o /usr/bin/wscd
qemu: uncaught target signal 11 (Segmentation fault) - core dumped
```


# Debugging

find / -name libreadline.so.7
cp /lib/x86_64-linux-gnu/libreadline.so.7 root/lib/x86_64-linux-gnu/libreadline.so.7

cp -r /lib/x86_64-linux-gnu/ root/lib/
cp -r /usr/lib/x86_64-linux-gnu root/usr/lib

```sh

# NOT WORKING
$ chroot root /qemu-mipsel-static -g 1234 -E LD_PRELOAD=/http_recv_hook.o /usr/bin/wscd

# On another screen
$ docker exec -it 84 /bin/bash
$ cp /usr/bin/gdb-multiarch root
$ gdb-multiarch
(gdb) source fuzzing/gdb_hook_init.gdb
(gdb) c
Continuing.

Breakpoint 1, 0x00433fd0 in __uClibc_main (

# Finding in which function the seq fault is
# Stepping over the function
(gdb) ni
0x00413224 in http_RecvMessage ()
(gdb) disas
...
   0x00413218 <+160>:   move    a0,s6
   0x0041321c <+164>:   addiu   a1,sp,24
   0x00413220 <+168>:   li      a2,2048
=> 0x00413224 <+172>:   bal     0x421364 <sock_read>
   0x00413228 <+176>:   move    a3,s7
   0x0041322c <+180>:   lw      gp,16(sp)
   0x00413230 <+184>:   blez    v0,0x4132ac <http_RecvMessage+308>
...
(gdb) ni
Program received signal SIGSEGV, Segmentation fault.
0x0042106c in ?? ()
```
