#include "mbedtls/cipher.h"
#include "mbedtls/dhm.h"
#include "mbedtls/md.h"
extern uint8_t client_secret[256];
extern unsigned char digest[32];
int main()
{
  // aes_test(MBEDTLS_CIPHER_AES_128_ECB); /*����䣬 �޸����볤��Ϊ���鳤�ȱ��� */
   aes_test(MBEDTLS_CIPHER_AES_128_CBC);
  // des_test(MBEDTLS_CIPHER_DES_CBC);
   // mbedtls_rsa_test();
    //mbedtls_rsa_sign_test();
   // mbedtls_dhm_test();
    //five();
        return 0;
}

