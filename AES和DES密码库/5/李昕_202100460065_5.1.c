#include "mbedtls/cipher.h"
#include "mbedtls/dhm.h"
#include "mbedtls/md.h"
extern uint8_t client_secret[256];
extern unsigned char digest[32];
int main()
{
  // aes_test(MBEDTLS_CIPHER_AES_128_ECB); /*无填充， 修改输入长度为分组长度倍数 */
   aes_test(MBEDTLS_CIPHER_AES_128_CBC);
  // des_test(MBEDTLS_CIPHER_DES_CBC);
   // mbedtls_rsa_test();
    //mbedtls_rsa_sign_test();
   // mbedtls_dhm_test();
    //five();
        return 0;
}

