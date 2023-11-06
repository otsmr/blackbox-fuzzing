# chroot root /qemu-mipsel-static -E LD_PRELOAD=/parser_parse_hook.o /usr/bin/wscd
# mipsel-linux-gnu-gcc fuzzing/parser_parse_hook.c -o root/parser_parse_hook.o -shared -fPIC

hook=httpd_parser_main
corpus_file="/corpus/httpd/login_base64.txt"
# corpus_file="/corpus/crashes/01"
target=/usr/bin/httpd

## https -> parser_main
mipsel-linux-gnu-gcc fuzzing/$hook.c -o root/$hook.o -shared -fPIC

# execute using debugger
kill -9 $(pidof qemu-x86_64)

# Check if the specified folder exists
if [ ! -f "root/$corpus_file" ]; then
  echo "corpus_file not found!"
  exit 1
fi

chroot root /qemu-mipsel-static -E LD_PRELOAD="/$hook.o" $target "$corpus_file"
# chroot root /qemu-mipsel-static -strace -g 1234 -E LD_PRELOAD="/$hook.o" $target "$corpus_file"

