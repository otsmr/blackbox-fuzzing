
export AFL_AUTORESUME=1
# export AFL_DEBUG=1 && export AFL_NO_UI=1
unset AFL_DEBUG && unset AFL_NO_UI


QEMU_LD_PREFIX=/share/root AFL_PRELOAD=/share/root/httpd_parser_main.o \
  /AFLplusplus/afl-fuzz -Q \
  -i /share/root/corpus/httpd/ \
  -o /share/afl-out/httpd/ \
  -- /share/root/usr/bin/httpd @@

# chroot root /qemu-mipsel-static -E LD_PRELOAD=/httpd_parser_main.o /usr/bin/httpd /corpus/httpd/simple.txt
