#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

/* int http_RecvMessage(int socket,request *buffer,int is_first,int timeout?,int *out_statuscode); */

void __uClibc_main(void *main, int argc, char** argv)
{

  // Verify that a filename is provided
  if (argc != 2) {
    printf("No input file provided\n");
    exit(1);
  }


  // Create function pointer to the fuzz target
  int (*parser_request_init)(void *, int) = (void *) 0x00412564;
  int (*parser_append)(void *, void *, int) = (void *) 0x00412e98;


  // Open the fuzz input file
  int fd = open(argv[1], O_RDONLY);
  char fuzz_buf[2048 + 1];

  int fuzz_buf_len = read(fd, fuzz_buf, sizeof(fuzz_buf) - 1);
  if (fuzz_buf_len < 0) {
    printf("Error reading\n");
    exit(1);
  }
  fuzz_buf[fuzz_buf_len] = 0;


  uint8_t parsed_data[220]; // memset in parser_request_init and size of struct in ghidra

  // Initialize the parser
  parser_request_init(parsed_data, 8);

  // socket_read max: 2048

  int status = parser_append(parsed_data, fuzz_buf, fuzz_buf_len);

  printf("Response is %d\n", status);

  exit(0);
}
