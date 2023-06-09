/**
 * @brief   AES Function demo
 * @author  mculover666
 * @date    2020/09/23
*/

#if !defined(MBEDTLS_CONFIG_FILE)
//#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

//#if defined(MBEDTLS_CIPHER_C)

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mbedtls/cipher.h"

/* Private Key */// 采用不同加密算法时，注意修改密钥及分组长度。
uint8_t key[16] = {
    0x06, 0xa9, 0x21, 0x40, 0x36, 0xb8, 0xa1, 0x5b,
    0x51, 0x2e, 0x03, 0xd5, 0x34, 0x12, 0x00, 0x06
};

/* Intialization Vector */
uint8_t iv[16] = {//先把iv理解成一个常数
    0x3d, 0xaf, 0xba, 0x42, 0x9d, 0x9e, 0xb4, 0x30,
    0xb4, 0x22, 0xda, 0x80, 0x2c, 0x9f, 0xac, 0x41
};

static void dump_buf(uint8_t *buf, uint32_t len)//输出功能的函数
{
    int i;
    
    printf("buf:");
    
    for (i = 0; i < len; i++) {
        printf("%s%02X%s", i % 16 == 0 ? "\r\n\t" : " ", 
                           buf[i], 
                           i == len - 1 ? "\r\n" : "");
    }
}
static void dump_buf2(uint8_t* buf, uint32_t len)//输出功能的函数
{
    int i;

    printf("decypt:");

    for (i = 0; i < len; i++) {
        printf("%s%01X%s", i % 16 == 0 ? "\r\n\t" : " ",
            buf[i]-48,
            i == len - 1 ? "\r\n" : "");
    }
}

int aes_test(mbedtls_cipher_type_t cipher_type) //可选对称密码算法
{
    int ret;
    size_t len;
    int olen = 0;
    uint8_t output_buf[64];
    uint8_t output_buf2[64];
    const char input[] = "202100460065";//标准填充方案，填满128位
    int m = strlen(input);
    unsigned char input2[16];
    //const char input[] = "HelloWorld123456";
    //const char input[] = {'m', 'c', 'u', 'l', 'o', 'v', 'e', 'r', '6', '6', '6', ' ', 'i', 's'};
    
    mbedtls_cipher_context_t ctx;//关键结构体：密码结果上下文
    const mbedtls_cipher_info_t *info;//记录密码算法的类型
    
    /* 1. init cipher structuer */
    mbedtls_cipher_init(&ctx);
    
    /* 2. get info structuer from type */
    info = mbedtls_cipher_info_from_type(cipher_type);
    
    /* 3. setup cipher structuer */
    ret = mbedtls_cipher_setup(&ctx, info);
    if (ret != 0) {
        goto exit;
    }
    
    /* 4. set key */
    ret = mbedtls_cipher_setkey(&ctx, key, sizeof(key) * 8, MBEDTLS_ENCRYPT);
    if (ret != 0) {
        goto exit;
    }
    
    /* 5. set iv */
    ret = mbedtls_cipher_set_iv(&ctx, iv, sizeof(iv));
    if (ret != 0) {
        goto exit;
    }
    
    ///* 6. update cipher */// 采用ECB模式时，无自动填充，此处输入长度只能为分组的整数倍
    //ret = mbedtls_cipher_update(&ctx, (unsigned char *)input, 16, output_buf, &len);
    //if (ret != 0) {
    //    goto exit;
    //}
    //olen += len;

    /* 6. update cipher 真正的加密过程*/
    ret = mbedtls_cipher_update(&ctx, (unsigned char*)input, strlen(input), output_buf, &len);
    if (ret != 0) {
        goto exit;
    }
    olen += len;
    
    /* 7. finish cipher */
    ret = mbedtls_cipher_finish(&ctx, output_buf+olen, &len);
    if (ret != 0) {
        goto exit;
    }
    olen += len;
    //int m = olen;
    /* show */
    printf("\r\nsource_context: %s\r\n", input);
    dump_buf((uint8_t *)input, strlen(input));
    printf("cipher name: %s block size is: %d\r\n", mbedtls_cipher_get_name(&ctx), mbedtls_cipher_get_block_size(&ctx));
    dump_buf(output_buf, olen);
    
    /*     jie   */
    mbedtls_cipher_init(&ctx);
    info = mbedtls_cipher_info_from_type(cipher_type);
    ret = mbedtls_cipher_setup(&ctx, info);
    if (ret != 0) {
        goto exit;
    }
    olen = 0;
    ret = mbedtls_cipher_setkey(&ctx, key, sizeof(key) * 8, MBEDTLS_DECRYPT);
    if (ret != 0) {
        goto exit;
    }
    ret = mbedtls_cipher_set_iv(&ctx, iv, sizeof(iv));
    if (ret != 0) {
        goto exit;
    }
    for (int i = 0; i < 16; i++)
    {
        input2[i] = (unsigned char) output_buf[i];
        //printf("%02x ", input2[i]);
        
    }
   //printf("%d\n",olen);
    ret = mbedtls_cipher_update(&ctx, (unsigned char*)input2, strlen(input2), output_buf2, &len);
    if (ret != 0) {
        goto exit;
    }
    olen += len;
    dump_buf2(output_buf2, m);

    exit:
    /* 8. free cipher structure */
    mbedtls_cipher_free(&ctx);
    
    return ret;
}

int main()
{
    // aes_test(MBEDTLS_CIPHER_AES_128_ECB); /*无填充， 修改输入长度为分组长度倍数 */
   aes_test(MBEDTLS_CIPHER_AES_128_CBC);
    //des_test(MBEDTLS_CIPHER_DES_CBC);
    // mbedtls_rsa_test();
     //mbedtls_rsa_sign_test();
    // mbedtls_dhm_test();
     //five();
    return 0;
}

