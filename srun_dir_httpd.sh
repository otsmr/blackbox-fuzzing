

# chroot root /qemu-mipsel-static -E LD_PRELOAD=/parser_parse_hook.o /usr/bin/wscd
# mipsel-linux-gnu-gcc fuzzing/parser_parse_hook.c -o root/parser_parse_hook.o -shared -fPIC

hook=httpd_parser_main
corpus_dir="root/corpus/httpd"
target=/usr/bin/httpd

## https -> parser_main
mipsel-linux-gnu-gcc fuzzing/$hook.c -o root/$hook.o -shared -fPIC


# execute using debugger
# kill -9 $(pidof qemu-x86_64)
# chroot root /qemu-mipsel-static -strace -g 1234 -E LD_PRELOAD=/httpd_parser_main.o /usr/bin/httpd /httpd_corpus.txt

# Check if the specified folder exists
if [ ! -d "$corpus_dir" ]; then
  echo "Folder not found!"
  exit 1
fi

# Loop through each file in the folder
for file in "$corpus_dir"/*; do
  if [ -f "$file" ]; then
    file=$(echo "$file" | sed 's/root\///')
    printf "\n---- $file ----\n\n"
    chroot root /qemu-mipsel-static -E LD_PRELOAD="/$hook.o" $target "$file"
  fi
done

