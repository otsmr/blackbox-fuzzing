set solib-absolute-prefix /share/root/

# Show disas when stepping

file /share/root/usr/bin/httpd
target remote :1234
# break bevor fuzz target is called
# break __uClibc_main
# break http_parser_main
# break *(__uClibc_main+148)

# break at parser_parse
# c
display/4i $pc

# b *0x405f4c
b *0x40f3d0

# http_init_main
# b *0x004034f8
# b *0x00403684
# debug http_stream_fgets
# b *0x0040787c

# echo "source /share/fuzzing/gdb_hook_init.gdb" > ~/.gdbinit
