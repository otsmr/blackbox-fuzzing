
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
/* #include <stdlib.h> */

typedef struct
{
  int _a;
  int _b;
  int socket;
  int ip;
  int mac;
  unsigned char body[0x1004];
  int ptr;
  FILE *socket_out;
} HttpMainT;

// Store this global
HttpMainT fuzzInput;

int rdp_getObj(int, char *id, char *output, char *input)
{
  if (strstr(input, "adminPwd") != 0)
  {
    char adminData[] = "adminName=admin\nadminPwd=admin\n\x00";
    memcpy(input, adminData, sizeof(adminData));
  }
  else
  {
    printf("rdp_getObj is called with: %s to get %s\n", id, input);
  }
  return 0;
}

int rdp_getObjStruct(char *id, char *output, char *input)
{
  /* printf("rdp_getObjStruct is called with: %s to get %s\n", id); */
  return 0;
}

// slows afl-fuzz significantly down
// exex speed from 30/s up to 500/s
void rsa_gdpr_generate_key()
{
}

int aes_tmp_decrypt_buf_nopadding_new(void *input, void *output, int *len, int _key, int _iv)
{
  printf("AES:DEC: %p %p %p\n", input, output, len);
  if (*len > 0 && *len < 0x1000)
  {
    strncpy(output, input, *len);
  }
  return 0; // OK
}

// Replacing the logic with b64_decode
int rsa_tmp_decrypt_bypart(uint8_t *input, int input_len, uint8_t *output)
{ // other params just key data

  /* int b64_decode(byte *out,int max_out_len,byte *input,size_t input_len) */
  int (*b64_decode)(uint8_t *, int, uint8_t *, int) = (void *)0x0040bf00;
  b64_decode(output, 0x1000, input, input_len);

  int *seqnumber = (int *)0x00444db0;
  *seqnumber = 0x3ac28e29 - input_len + 12;

  return 0; // says it was okay
}

int rdp_netChkIpInAllLanSubnet()
{
  // must be wrapped will crash
  return 1; // must be one
}

int select(int, void *)
{
  // called at the end of http_init_main
  // blocks

  int status = http_parser_main(&fuzzInput);

  printf("\nResponse is %d\n", status);

  exit(0);
}

void __uClibc_main(void *main, int argc, char **argv)
{

  // Verify that a filename is provided
  if (argc != 2)
  {
    printf("No input file provided\n");
    exit(1);
  }

  // Open the fuzz input file
  int fuzzer_fd = open(argv[1], O_RDONLY);

  // Harness

  // Create function pointer to the fuzz target
  int (*http_parser_main)(void *) = (void *)0x00405ee8;
  void (*http_init_main)() = (void *)0x004034f8;

  fuzzInput.socket = fuzzer_fd;
  fuzzInput.socket_out = stdout;

  /* *((unsigned int *)0x4060d0) = 0x00; */
  /* set *(unsigned char*)0x80FFDDEE = 0x90 */

  /* uint8_t parsed_data[220]; // memset in parser_request_init and size of struct in ghidra */
  http_init_main();

  // Fuzzing start  is in select

  exit(0);
}
