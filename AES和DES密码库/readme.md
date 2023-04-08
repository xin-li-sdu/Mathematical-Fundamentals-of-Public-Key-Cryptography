# AES和DED




[TOC]



## 环境配置

​       编程IDE：Visual studio 2022

​       实现环境：Windows 11 22H2

​        处理器：AMD Ryzen 7 5800H with Radeon Graphics   3.20 GHz

## 调用 DES，加密学号

### DES密码算法的数学原理概述

　　DES（Data Encryption Standard）是一种对称密钥加密算法，使用56位的密钥和一个固定长度的64位输入块，加密时将输入块分成16个子块进行加密，每个子块采用相同的加密过程。其加密过程涉及以下数学原理：

1. 替代（Substitution）：替代是指将输入的一组数据映射到另一组数据的过程。DES中使用了8个不同的替代盒（S-box），每个替代盒接受6位输入并产生4位输出。这个过程旨在打乱输入数据的结构，增加密码的难度。
2. 置换（Permutation）：置换是指重新排列一组数据的过程。DES中使用了一个固定的置换表（P-box），将每个输入块中的32位数据重新排列。这个过程是为了进一步增加密码的难度，使加密后的数据更难被破解。
3. Feistel结构：Feistel结构是一种经典的块密码结构，采用分组加密和迭代加密的方式进行数据加密。DES中采用了Feistel结构，将输入块分成两半，经过一系列轮函数（Round Function）处理，最终产生密文。每个轮函数包含以下步骤：替代、置换、异或和加密。
4. 异或（XOR）：异或是一种基本的逻辑运算，当两个输入位不同时输出为1，否则输出为0。在DES中，异或运算用于将子密钥与轮函数产生的数据进行加密。
5. 子密钥生成：DES中采用了一个密钥调度算法，将64位密钥转换成16个48位子密钥。这个算法涉及到位移、压缩和选择，目的是生成具有高度随机性的子密钥。

### DES的编写与加密

​      根据老师实验样例中给出的AES_128范例代码，修改调用的密码类型cipher_type，定义密码加密函数：des_test(MBEDTLS_CIPHER_DES_CBC)，同时修改密钥长度为8位，修改iv数组为8位，修改输出函数dump_buf()为8位一组，经过测试，发现出现如下错误：

![image-20230311112208435](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311112208435.png)

​     即第二组DES加密时输出为空。

​     经过调试和追踪中间数据变化，研究各加密函数作用，发现函数mbedtls_cipher_update()完成的是满足整组明文的DES加密，而函数mbedtls_cipher_finish()实现了不满整组的尾项的填充加密，但在范例AES加密实现中，第二次finish给定的输出空间与第一次update给定的输出空间均为output_buf，造成数据的覆盖，问题代码如下：

```python
 ret = mbedtls_cipher_finish(&ctx, output_buf, &len);
```

​     解决方法为在调用finish()之前的输出加密数据腾出空间，数组传参由output_buf修改为 output_buf+olen，经过测试成功解决问题：

![image-20230311112849700](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311112849700.png)

​      最终DES加密学号得到密文：01 26 41 A6 A0 50 7D E3 44 1D D0 92 F6 8F 11 E3

## 调用 RSA，加密学号

### RSA密码加密算法的数学原理概述

​      RSA加密是一种非对称加密算法，它的加密原理基于数学中的数论问题。RSA算法需要一对密钥：公钥和私钥。公钥可以公开，任何人都可以获得，私钥必须由密钥持有者保密。

​      加密过程如下：

1. 选择两个不同的质数p和q，并计算它们的乘积n = p * q。
2. 计算n的欧拉函数φ(n) = (p - 1) * (q - 1)。
3. 选择一个整数e，1 < e < φ(n)，且e和φ(n)互质，即它们的最大公约数为1。
4. 计算e的模反元素d，满足d * e ≡ 1 mod φ(n)。
5. 公钥为(n,e)，私钥为(n,d)。
6. 将明文M转换为一个整数m，满足0 ≤ m < n。
7. 加密明文m得到密文c，c ≡ m^e mod n。
8. 发送密文c。

### RSA的编写与加密

​      对已经给出的RSA加密算法进行阅读和修改，首先修改明文参数msg=202100460065，之后利用mbedtls_rsa_init()初始化加密，选择MBEDTLS_RSA_PKCS_V21和MBEDTLS_MD_SHA256为参数。

​      第二步，使用预先设定的端口pers更新种子，之后生成各项随机数以及RSA密钥对。

![image-20230311144216645](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311144216645.png)

​      第三步， 利用内置函数mbedtls_rsa_pkcs1_encrypt将要加密的明文编码并加密。

​      得到加密后的密文如下：

![image-20230311144147967](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311144147967.png)

## 调用 RSA，对学号进行签名

###  RSA密码签名算法的数学原理概述

​     RSA签名是一种数字签名算法，它使用RSA加密算法来生成签名。RSA签名原理与RSA加密原理类似，但用于不同的目的。

​     RSA签名过程如下：

1. 选择两个不同的质数p和q，并计算它们的乘积n = p * q。
2. 计算n的欧拉函数φ(n) = (p - 1) * (q - 1)。
3. 选择一个整数e，1 < e < φ(n)，且e和φ(n)互质，即它们的最大公约数为1。
4. 计算e的模反元素d，满足d * e ≡ 1 mod φ(n)。
5. 私钥为(n,d)，公钥为(n,e)。
6. 选择一个哈希算法（如SHA-256），对待签名的消息进行哈希处理，得到消息的摘要。
7. 对消息摘要进行数字签名，使用私钥对摘要进行加密，得到签名。签名S = M^d mod n。
8. 发送消息和签名。

###  调用 RSA对学号进行签名

​       与 Part 3 结构类似，首先修改明文参数msg=202100460065，之后利用mbedtls_rsa_init()初始化加密，选择MBEDTLS_RSA_PKCS_V21和MBEDTLS_MD_SHA256为参数。

​        使用预先设定的端口pers和函数mbedtls_ctr_drbg_seed更新种子，之后利用函数mbedtls_rsa_gen_key()生成各项随机数以及RSA密钥对。

![image-20230311144824770](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311144824770.png)

​       第二步，利用生成的各项参数，调用函数mbedtls_rsa_pkcs1_sign对学号明文进行签名。

​       ![image-20230311144830767](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311144830767.png)



##   利用 DH 密钥协商协议和 ARIA 密码算法对学号进行加解密

​      要求：利用 DH 密钥协商协议协商一个密钥，并利用 SHA512 对协商的秘密信息做哈希，得到一个密钥，利用这个密钥和 ARIA 密码算法对学号进行加密、解密。

### 编程思路

​     编程思路如下：

1. 生成 DH 密钥协商算法的参数，例如质数 p 和底数 g，然后双方 Alice 和 Bob 都协商一个共享的密钥。
2. Alice 和 Bob 各自生成一个私钥 a 和 b，然后公开交换自己的公钥 A 和 B，计算共享的密钥 $K = g^{ab} mod p$。
3. 使用 SHA512 哈希算法对共享的密钥 K 进行哈希，生成一个 512 位的密钥。
4. 将要加密的信息分成固定大小的块，使用 ARIA 密码算法对每个块进行加密，使用生成的密钥作为密钥。
5. 将加密后的信息发送给接收方。
6. 接收方收到信息后，使用同样的密钥对每个块进行解密，得到原始信息。

### 具体实现 

​    首先，为了便于各c文件之间传参，使用跨文件全局变量extern uint8_t client_secret[256]和extern unsigned char digest[32]，前者为哈希函数与DH函数之间传递哈希值，后者为aria函数与DH函数之间传递加密解密值。

​     DH协议部分使用老师编写的demo程序，生成全局共享密钥。下面简述的哈希函数和ARIA加密函数的编写：

​     第一小步，利用ret = mbedtls_shax_test(MBEDTLS_MD_SHA256)语句，对生成的密钥做哈希，并将哈希值传回DH函数。

​    第二步，调用头文件库aria.h，先利用内置函数mbedtls_aria_setkey_enc(&aria_ctx, digest, key_bitlen)处理密钥，再调用加密函数mbedtls_aria_crypt_ecb(&aria_ctx, plaintext, ciphertext1)对学号进行加密。

​     第三步，利用内置函数 mbedtls_aria_setkey_dec(&aria_ctx, digest, key_bitlen)生成解密密钥，再次调用加密函数，得到解密的学号。

​     伪代码如下：

```c
    mbedtls_dhm_test();
    ret = mbedtls_shax_test(MBEDTLS_MD_SHA256);
    /*   aria   */
    unsigned char plaintext[12] = "202100460065";
    mbedtls_aria_context aria_ctx;
    mbedtls_aria_init(&aria_ctx);
    int key_bitlen = 256; // 密钥长度为512位
    mbedtls_aria_setkey_enc(&aria_ctx, digest, key_bitlen);
    unsigned char ciphertext1[16] = {0};
    mbedtls_aria_crypt_ecb(&aria_ctx, plaintext, ciphertext1);
    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++) 
    {
        printf("%02x", ciphertext1[i]);
    }
    printf("\n");
    unsigned char ciphertext2[16] = { 0 };
    mbedtls_aria_setkey_dec(&aria_ctx, digest, key_bitlen);
    mbedtls_aria_crypt_ecb(&aria_ctx, ciphertext1, ciphertext2);
    for (int i = 0; i < 12; i++)
    {
        printf("%d ", ciphertext2[i]);
    }
    printf("\n");
```

最后各步骤实验结果展示如下：

公共密钥：

![image-20230311174320831](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311174320831.png)

哈希值：![image-20230311174338608](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311174338608.png)

密文：![image-20230311174359585](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311174359585.png)

解密后的明文：![image-20230311174428274](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311174428274.png)

整体输出结果：

![image-20230311174502548](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311174502548.png)

## 使用密码库实现任意加密/解密协议

  选择课程上学习过的AES_CBC加密解密协议，调用aes.h库进行实现

###  实现AES加密/解密协议

​      首先，对老师已经初步完成的demo程序进行修改，和Part 2 相同，在finish函数的输出中加入偏移量，ret = mbedtls_cipher_finish(&ctx, output_buf+olen, &len)，以解决覆盖输出的问题。

​      第二步，分析给出加密代码各步骤作用：

​       1.初始化加密算法结构，mbedtls_cipher_init(&ctx);

​       2.获得加密算法的类型，info = mbedtls_cipher_info_from_type(cipher_type);

​       3.设置密码结构，ret = mbedtls_cipher_setup(&ctx, info)；

​       4.设置密钥数组和iv数组，

​       ret = mbedtls_cipher_setkey(&ctx, key, sizeof(key) * 8, MBEDTLS_ENCRYPT);

​       ret = mbedtls_cipher_set_iv(&ctx, iv, sizeof(iv));

​       5.加密明文，

​       ret = mbedtls_cipher_update(&ctx, (unsigned char*)input, strlen(input), output_buf, &len);

​       ret = mbedtls_cipher_finish(&ctx, output_buf+olen, &len);

​       通过老师给出的demo程序可以初步实现AES的加密，下面编写AES的解密程序：

​        1.与加密相同，初始化加密算法结构和类型：

```c
    mbedtls_cipher_init(&ctx);
    info = mbedtls_cipher_info_from_type(cipher_type);
    ret = mbedtls_cipher_setup(&ctx, info);
    if (ret != 0) 
    {
        goto exit;
    }
    olen = 0;
```

​        2.设置解密密钥和iv数组：

```c
    ret = mbedtls_cipher_setkey(&ctx, key, sizeof(key) * 8, MBEDTLS_DECRYPT);
    if (ret != 0) {
        goto exit;
    }
    ret = mbedtls_cipher_set_iv(&ctx, iv, sizeof(iv));
    if (ret != 0) {
        goto exit;
    }
```

​        3.由于update函数的参数格式限制，要将 uint8_t类型的密文强制转换为unsigned char类型：

```c
    for (int i = 0; i < 16; i++)
    {
        input2[i] = (unsigned char) output_buf[i];
        //printf("%02x ", input2[i]);
    }
```

​        4.运行解密函数，并输出解密值：

```c
    ret = mbedtls_cipher_update(&ctx, (unsigned char*)input2, strlen(input2),         output_buf2, &len)；
    olen += len;
    dump_buf2(output_buf2, m);
```

​       运行结果如下：

![image-20230311190614810](C:\Users\waldeinsamkeit\AppData\Roaming\Typora\typora-user-images\image-20230311190614810.png)

​       可以看到明文为学号"202100460065"，经过编码变为32 30 32 31 30 30 34 36 30 30 36 35,通过AES协议加密，得到目标密文 FF 28 F3 A3 81 FE 8F 7E 3E B0 21 0F 08 33 C8 94，再通过同一协议进行解密，反解出原始明文202100460065。



**参考文献:** 

［1］  [加]Douglas R.Stinson. 密码学原理与实践[M]. 冯登国.北京:电子工业出版社, 2003.
