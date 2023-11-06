#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

/* int http_RecvMessage(int socket,request *buffer,int is_first,int timeout?,int *out_statuscode); */

void __uClibc_main(void *main, int argc, char** argv)
{
  /* char req[4096 + 1]; */
  /* int32_t in_addr; */

  // http_RecvMessage
  int socket = 0;
  uint8_t * buffer[240];

  // make sure parser_request_init is called
  int is_first = 8;

  int timeout = 0;
  int statuscode = 400;

  // Create function pointer to the fuzz target
  int (*http_RecvMessage)(int, void *, int, int, int*) = (void *) 0x00413178;

  // Call the function
  printf("Calling fuzz target");
  int status = http_RecvMessage(socket, buffer, is_first, timeout, &statuscode);
  printf("Response is %d", status);

  exit(0);
}
