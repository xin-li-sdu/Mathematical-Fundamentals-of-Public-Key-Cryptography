

# 破解Vigenere密码





摘　要：

维吉尼亚密码是使用一系列凯撒密码组成密码字母表的加密算法，属于多表密码的一种简单形式。其以简单易用而著称，同时初学者通常难以破解，本报告以特定密文为切入点，利用重合指数法对维吉尼亚密码进行密码分析和破解，并对维吉尼亚的安全性进行分析。

关键词：

维吉尼亚密码；重合指数；密码分析；




[TOC]



## 组员分工与环境配置

### 组员信息与分工情况

​      小组成员A：LSC，负责密码分析，python 破解程序编写，结论总结。

​      小组成员B：LX，负责算法分析，数据处理，作业报告编写。

### 环境配置

​       编程语言：Python 3.10

​       实现环境：Windows 11 & VScode

## Vigenere密码的原理

### Vigenere密码的数学原理

　　Vigenere密码是一种简单的多表代换密码(由26个类似的Caesar密码的代换表组成)。

------

​      Vigenere密码体制：设m为整数，定义$P=C=K=(Z_26)^m$，对于密钥$K=(k_1,k_2,...,k_m)$，

​      定义：
$$
e_k(x_1,x_2,...,x_m)=(x_1+k_1,x_2+k_2,...,x_m+k_m) \\ d_k(y_1,y_2,...,y_m)=(y_1-k_1,y_2-k_2,...,y_m-k_m)
$$

​      以上运算均为在$Z_{26}$上进行。

------

​      综上，Vigenere密码的数学原理基于模运算和字符替换。通过将明文和密钥转换为数字形式，使用模运算计算每个密文字母，最后将密文字母转换回字母形式，实现加密和解密过程。

### Vigenere密码的保密性分析

​      下面从密码保密性，密钥空间大小，频率分析三个方面分析Vigenere密码

1. 密钥的保密性：Vigenere密码的保密性基于密钥的保密性。如果攻击者不知道密钥，他们将很难破解密文。因此，为了确保安全性，必须保护好密钥，并将其保密地传输给通信双方。

2. 密钥空间的大小：从古典密码的角度上看，Vigenere密码的密钥空间足够大，可以提供足够的安全性。密钥空间的大小取决于明文的长度和密钥字母表的大小。如果明文长度为 n，密钥字母表大小为 m，则维吉尼亚密码的密钥空间大小为 $m^n$。因此，如果密钥长度足够长，Vigenere密码可以提供足够的安全性，以防止攻击者猜测密钥。

3.  频率分析攻击：虽然Vigenere密码的密钥空间很大，但是如果明文长度较小，并且攻击者知道密文中某些字符的频率分布，那么他们可能会使用频率分析来破解密码。因此，为了提高安全性，可以使用填充技术来增加明文长度，以防止攻击者使用频率分析攻击。

​      综上所述，Vigenere密码可以提供一定的安全性，但是在使用时应该注意密钥保密性和避免重复使用密钥。此外，应该使用填充技术来增加明文长度，以防止频率分析攻击。

## Vigenere密码的破解过程

　　Vigenere密码的破解过程分为为寻找目标密文，确定密钥长度，确定具体密钥，解密密文四个步骤。

### 寻找目标密文

　　由‎目标密文规则，密文序号$=(5+5)  mod 10=0$,得到目标密文序号为$0$，定义目标密文为C，则：C=Cbkznkiyjsrofgnqadnzuqigscvxizgsjwucusrdkxuahgzrhywtvdjeiuwsrrtnpszbvpzncngztbvsrnzuqigscvfjwqgjwcytwdazuqigscvfjwqgjwjhkfdylmcbmhonbmbvdnvbmwbnacjaphhonbmbvdnvbmwbnaublsbdnjjneoroyfmxfhixpzpcozzuqigscvxcvhdmfgxmgovzsqmvzyvwyzmsczoajsejifoakdcrehwhgdehvmtnmvvmesvzifutzfjzoalwqztunwvdvmfhesvzifutzfjzoalwqztunpsnoyfleoxdetbwfsoyfjmfhjuxuagnarsfqydoyfjzsrzeujmfhjuubihrjdfinwsnepcawdnkbobvnmzucmghijjmbscjejnapddehlmqddmfxncqbfpxwfejifpqzhikiyaiozimubwuzufazsdjwdiudzmztivcmgp

### 利用重合指数法确定密钥长度

​      定义重合指数为字符串中两个随机元素相同的概率，记为$I_c(x)$。

​      假设$f_0,f_1,...f_{25}$分别为$A,B,...Z$在字串$x$中出现的频数，则对于每个$i$，$0≤i≤25$，共$$C_{f_i}^{2}$$有种方法使得所选两个元素皆为$i$，故有$I_c(x)=\frac{\sum_{i=0}^{25}{f_i(f_{i}-1})}{n(n-1)}$.

​      对于串$x$，$A,B,...Z$ 在字串$y_i$中出现的概率期望为$p_0,p_1,...p_{25}$，其$I_c(x)≈\sum_{i=0}^{25}{p_i^2}=0.065$.

​      假设使用的维吉尼亚密码加密密文串为$y=\overline{y_1y_2y_3...}$，将$y$分割成$m$个长度相同的字串，分别为$y_1,y_2,...y_m$，并组成一个$m×(n/m)$的矩阵，矩阵每一行对应字串$y_i$，$0≤i≤m$，即：
$$
&y_ 1=\overline{a_1a_{m+1}a_{2m+1}...}\\
&y_ 2=\overline{a_2a_{m+2}a_{2m+2}...}\\
&. . .\\
&y_m=\overline{a_ma_{2m}a_{3m}a_{4m}...}
$$
​        若$y_1,y_2,..y_m$按如上方法构造，则$m$实际上就是密钥长度，且每个$I_c(y_i)≈0.065$。

​        若m不为密钥长度，则字串$y_i$更随机，对于一个完全由A~Z字母组成的随机串，其重合指数$I_c(x)=26(\frac{1}{26})^2=0.038$，与$0.065$差别较大，即可判断密钥长度。

​        此题中，利用**1.5**$python$代码中函数find_len()和cal_p()可得各长度对应重合指数平均值$I_c$：

|   m   |   1   |   2   |   3   | 4     |   5   |   6   |        7         |   8   | 9     |  10   |  11   |  12   | 13    |
| :---: | :---: | :---: | :---: | ----- | :---: | :---: | :--------------: | :---: | ----- | :---: | :---: | :---: | ----- |
| $I_c$ | 0.042 | 0.042 | 0.042 | 0.042 | 0.042 | 0.042 | **<u>0.074</u>** | 0.041 | 0.042 | 0.037 | 0.040 | 0.038 | 0.076 |

| m     | **14** | **15** | **16** | **17** | **18** | **19** | **20** | **21** | **22** | **23** | **24** | **25** | **26** |
| ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| $I_c$ | 0.038  | 0.039  | 0.038  | 0.039  | 0.039  | 0.039  | 0.076  | 0.036  | 0.040  | 0.041  | 0.040  | 0.041  | 0.036  |

​        可知$m=7$时，$I_c=0.074$与$0.065$最接近，密钥长度最可能为7.

### 利用重合指数法判断密钥偏移量

#### 利用重合复指数判断密钥字相对位移

​      假设密钥长度为$m$，令$0≤i≤m$，假设$f_0,f_1,...f_{25}$分别为$A,B,...Z$在字串$y_i$中出现的频数，令$n^，=n/m$代表串$y_i$的长度，则$26$个字母在$y_i$中的概率分布为$\frac{f_{0}}{n^,},...,\frac{f_{25}}{n^,}$。令$k_i$为$y_i$由对应明文移动$k_i$个位置所得，移动后的概率分布为$\frac{f_{k_i}}{n^,},...,\frac{f_{25+k_i}}{n^,}$。 

​       定义数值$M_c(C_i,C_j)=\sum_{t=0}^{25}\frac{f_{i,t}f_{j,t-s}}{n_in_j}$，若相对偏移量s猜对，则$M_c(C_i,C_j)≈0.065$，否则一般小于$0.065$。利用其来判断不同密钥字的相对偏移量。

​       此题中，利用**5.1**附件$python$代码函数cal_dev()和find_key()可得$M_c(C_i,C_j)$：

|  i   |  j   | $M_c(C_i,C_j)$                                               |
| :--: | :--: | ------------------------------------------------------------ |
|  0   |  1   | 0.045  0.053  0.033  0.031  0.045  0.036  0.029  0.032  0.049  0.032  0.022  0.039  **<u>0.061</u>**  0.047 0.031  0.042  0.051  0.034  0.029    0.038  0.043  0.024  0.034  0.040  0.041  0.038 |
|  0   |  2   | 0.025  0.032  0.052  0.035  0.031  0.039  **<u>0.061</u>**  0.046  0.040  0.034  0.047  0.029  0.030  0.035  0.034  0.032  0.041  0.048  0.039  0.040  0.049  0.052  0.035  0.030  0.038  0.028 |
|  0   |  3   | 0.026  0.021  0.036  0.034  0.027  0.043  0.053  0.039  0.040  0.054  0.058  0.030  0.022  0.045  0.028  0.024  0.026  0.054  0.030  0.028  0.047  **<u>0.072</u>**  0.043  0.032  0.038  0.050 |
|  0   |  4   | 0.056  0.030  0.037  0.049  0.032  0.024  0.033  0.042  0.027  0.035  0.046  0.047  0.041  0.046  0.054  0.038  0.023  0.038  0.029  0.028  0.029  0.045  0.034  0.024  0.045  **<u>0.069</u>** |
|  0   |  5   | 0.033  0.036  0.035  **<u>0.060</u>**  0.046  0.037  0.033  0.038  0.038  0.036  0.034  0.029  0.036  0.046  0.048  0.037  0.044  0.051  0.046  0.030  0.031  0.041  0.033  0.024  0.032  0.047 |
|  0   |  6   | 0.037  0.034  0.029  0.041  0.051  0.036  0.045  0.054  0.056  0.028  0.023  0.047  0.029  0.025  0.032  0.054  0.029  0.027  0.043  **<u>0.068</u>**  0.039  0.036  0.038  0.048  0.025  0.024 |

​      得密钥字相对偏移量(即密钥本身)为[0,12, 6, 21, 25, 3, 19]。

​      有方程组：
$$
\left\{
\begin{matrix}
k_1-k_2=12 \\
k_1-k_3=6 \\ k_1-k_4=21\\ k_1-k_5=25 \\ k_1-k_6=3 \\k_1-k_7=19
\end{matrix}
\right.
$$
​      $k_0$取遍$Z_{26}$,得到26组不同的解密值，再结合自然语言字母概率概率 $p_i$ 计算其重合指数，可以得到密钥字为绝对偏移为[$20, 8, 14, 25, 21, 17, 1$]。

​     在判断$k_0$初始偏移量时，除用自然语言重合概率$p_0$计算外，也可以使用python中的polyglot库来实现，Polyglot 库支持多种自然语言的快速识别，可以快速分辨出26段可能序列中的正确序列，此处使用npl库进行语种检测从而判断解密成功。

#### 利用重合复指数与$p_i$直接判断密钥字绝对偏移量

　　与**3.3.1**中相同，假设密钥长度为$m$，令$0≤i≤m$，假设$f_0,f_1,...f_{25}$分别为$A,B,...Z$在字串$y_i$中出现的频数，令$n^，=n/m$代表串$y_i$的长度，则$26$个字母在$y_i$中的概率分布为$\frac{f_{0}}{n^,},...,\frac{f_{25}}{n^,}$。令$k_i$为$y_i$由对应明文移动$k_i$个位置所得，移动后的概率分布为$\frac{f_{k_i}}{n^,},...,\frac{f_{25+k_i}}{n^,}$，

​       假设$0≤g≤25$，定义数值$|M_g|=\sum_{i=0}^{25}\frac{p_if_{i+g}}{n^,}$，若$g=k$，偏移量正确，则$M_g≈0.065$，否则一般小于$0.065$。利用$|M_g|$来判断密钥每一位的偏移量。

​      此题中，利用**5.1**附件$python$代码中函数cal_dev1()和find_key1()可得$|M_g|$：

| i    |                         $|M_g(y_i)|$                         |
| :--- | :----------------------------------------------------------: |
| 1    | 0.034  0.037  0.036  0.029  0.036  0.045  0.037  0.041  0.047  0.053  0.033  0.031  0.041  0.036  0.030  0.032  0.046  0.031  0.029  0.037  **<u>0.059</u>**  0.044  0.037  0.037  0.046  0.034 |
| 2    | 0.039  0.040  0.031  0.033  0.045  0.038  0.029  0.039  **<u>0.065</u>**  0.043  0.026  0.036  0.043  0.035  0.034  0.040  0.036  0.033  0.043  0.045  0.039  0.037  0.047  0.042  0.032  0.029 |
| 3    | 0.034  0.042  0.045  0.044  0.040  0.039  0.032  0.035  0.037  0.028  0.039  0.036  0.035  0.038  **<u>0.068</u>**  0.041  0.028  0.035  0.055  0.035  0.033  0.034  0.031  0.030  0.039  0.047 |
| 4    | 0.046  0.033  0.032  0.054  0.032  0.034  0.032  0.033  0.021  0.037  0.052  0.041  0.039  0.043  0.051  0.041  0.037  0.033  0.038  0.026  0.030  0.046  0.037  0.024  0.032  **<u>0.075</u>** |
| 5    | 0.034  0.038  0.037  0.025  0.024  0.047  0.046  0.037  0.039  0.052  0.044  0.037  0.032  0.035  0.034  0.031  0.035  0.040  0.036  0.023  0.041  **<u>0.072</u>**  0.049  0.029  0.038  0.047 |
| 6    | 0.034  0.036  0.038  0.038  0.044  0.037  0.047  0.040  0.043  0.030  0.033  0.040  0.038  0.041  0.032  0.030  0.039  **<u>0.066</u>**  0.041  0.032  0.036  0.053  0.035  0.031  0.031  0.035 |
| 7    | 0.034  <u>**0.074**</u>  0.042  0.035  0.030  0.048  0.033  0.035  0.032  0.036  0.028  0.032  0.049  0.043  0.043  0.037  0.051  0.040  0.037  0.039  0.042  0.027  0.028  0.046  0.036  0.026 |

​       得密钥字绝对偏移量(即密钥本身)为[$20, 8, 14, 25, 21, 17, 1$]=[$u,i,o,z,v,r,b$]。

###  利用密钥解密维吉尼亚密码

​       由**3.2**和**3.3/3.4**计算可知密钥对应偏移量$K=(u,i,o,z,v,r,b)=(20, 8, 14, 25, 21, 17, 1)$，带入**2.1** 中Vigenere密码的解密公式 $Dec(y_1,y_2,...y_m)=(y_1-k_1,...,y_m-k_m)$，得到原文为：

​       It was the best of times, it was the worst of times. It was the age of wisdom, it was the age of foolishness. It was the epoch of belief, it was the epoch of incredulity. It was the season of light, it was the season of darkness. It was the spring of hope, it was the winter of despair. We had everything before us, we had nothing before us. We were all going direct to heaven, we were all going direct the other way. In short, the period was so far like the present period that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.

## 实验结论与分析

​     本次实验中，我们利用自然语言以及单表置换后的自然语言所具有的特征，完成了对维吉尼亚密码的破解。

​      回顾整个解密流程，我们不难发现，如果明文空间以及其单表置换后的密文空间具有某些统计学特征（如英语的重合指数0.065），我们就可以利用这种特征确定加密密钥的长度和具体内容。但是，如果明文的统计学特征不明显（如完全随机文本），或者特意避开统计学上的特征（如《盖茨比》（一本没有e的英文书）），类似的破解手段就会失效。



## 附录

### 破解维吉尼亚密码python代码

```python
ss = 'Cbkznkiyjsrofgnqadnzuqigscvxizgsjwucusrdkxuahgzrhywtvdjeiuwsrrtnpszbvpzncngztbvsrnzuqigscvfjwqgjwcytwdazuqigscvfjwqgjwjhkfdylmcbmhonbmbvdnvbmwbnacjaphhonbmbvdnvbmwbnaublsbdnjjneoroyfmxfhixpzpcozzuqigscvxcvhdmfgxmgovzsqmvzyvwyzmsczoajsejifoakdcrehwhgdehvmtnmvvmesvzifutzfjzoalwqztunwvdvmfhesvzifutzfjzoalwqztunpsnoyfleoxdetbwfsoyfjmfhjuxuagnarsfqydoyfjzsrzeujmfhjuubihrjdfinwsnepcawdnkbobvnmzucmghijjmbscjejnapddehlmqddmfxncqbfpxwfejifpqzhikiyaiozimubwuzufazsdjwdiudzmztivcmgp'
p0 =[0.08167,0.01492,0.02782,0.04253,0.12705,0.02228,0.02015,0.06094,0.06996,0.00153,0.00772,0.04025,0.02406,0.06749,0.07507,0.01929,0.0009,0.05987,0.06327,0.09056,0.02758,0.00978,0.02360,0.0015,0.01974,0.00074]

from polyglot.detect import  Detector
from polyglot.detect.base import logger as polyglot_logger
from numpy import matrix
polyglot_logger.setLevel("ERROR")
def p(cnt,n):
    return sum([i*(i-1) for i in cnt])/(n*(n-1) if n != 1 else 1)

def div(st):
    #print(st)
    cnt = [0]*26
    for j in range(len(st)):
        tmp = ord(st[j])-ord("a")
        if(st[j].isupper()):
            tmp = ord(st[j])-ord("A")
        cnt[tmp] += 1
    return cnt

def cal(st):
    cnt = div(st)
    return p(cnt,len(st))

def cal_p(s,i):
    sum_ = 0
    st = [""] * i
    for j in range(len(s)):
        st[j%i] += s[j]
    for j in range(i):
        #print(len(s)//i,len(st[j]))
        #print(cal(st[j]))
        sum_ += cal(st[j])
    return sum_/i

def find_len(st):
    p_tmp = 10086
    l_tmp = 0
    for i in range(1,15):
        tmp = abs(cal_p(st,i)-0.065)
        if(tmp<p_tmp):
            l_tmp = i
            p_tmp = tmp
    print("probably length of key = {},p = {}".format(l_tmp,p_tmp))
    return l_tmp


def cal_dev(st1,st2):
    cnt1 = div(st1)
    ave_tmp = 10086
    dev_tmp = 0
    for i in range(26):
        tmp = ''
        for j in st2:
            if(j.isupper()):
                tmp += chr(ord("A")+(ord(j)-ord("A")+i)%26)
            else:
                tmp += chr(ord("a")+(ord(j)-ord("a")+i)%26)
        cnt2 = div(tmp)
        ave = abs(sum([(cnt1[k]*cnt2[k])/(len(st1)*len(st2))for k in range(26)])-0.065)
        #print(ave+0.065,end=',')
        if(ave<ave_tmp):
            dev_tmp = i
            ave_tmp = ave
    #print()
    if(ave_tmp<0.008):
        return dev_tmp
    else: 
        return None
        
def dec(chiper,key):
    tmp = [None]*len(chiper)
    for i in range(len(chiper)):
        tmp[i] = chr((ord(chiper[i])-ord(key[i%len(key)])+26)%26+ord('a'))
    st = ''
    for i in tmp:
        st += i
    return st

def find_dev(dev,n):
    for i in range(n):
        for j in range(n):
            for k in range(n):
                if dev[i][j]!=None:
                    continue
                if((i!=j) & (dev[i][k]!=None) & (dev[k][j]!=None)):
                    dev[i][j] = (dev[i][k] + dev[k][j]) % 26
    return dev[0][1:]


def find_key(s,i):
    st = [""] * i
    dev = [[] for j in range(i)]
    for j in range(len(s)):
        st[j%i] += s[j]
    for j in range(i):
        for k in range(i):
            if(j!=k):
                dev[j].append(cal_dev(st[j],st[k]))
            else:
                dev[j].append(None)
    print(matrix(dev))
    dev = find_dev(dev,i)
    print(dev)
    for j in range(26):
        key = chr(ord("a")+j)
        for k in dev:
            key += chr(ord("a")+(j-k+26)%26)
        tmp = dec(s,key)
        try:
            a = Detector(tmp,quiet=True).language
        except:
            pass
        else:
            if(a.code=='en'):
                print("key is {}, plaintext is {}".format(key,tmp))
    
    ave_tmp = 10086
    key_tmp = 0
    for j in range(26):
        key = chr(ord("a")+j)
        for k in dev:
            key += chr(ord("a")+(j-k+26)%26)
        tmp = dec(s,key)
        cnt1 = div(tmp)
        ave = abs(sum([(p0[k]*cnt1[k])/len(tmp)for k in range(26)])-0.065)
        #print(ave+0.065,end=',')
        if(ave<ave_tmp):
            key_tmp = key
            ave_tmp = ave
    print("key is {}, plaintext is {}".format(key_tmp,dec(s,key_tmp)))


def cal_dev1(st1):
    #print(st1)
    cnt1 = div(st1)
    #print(cnt1)
    ave_tmp = 10086
    dev_tmp = 0
    for i in range(26):
        ave = abs(sum([(p0[k]*cnt1[(k+i)%26])/len(st1)for k in range(26)])-0.065)
        #print(ave+0.065,end=',')
        if(ave<ave_tmp):
            dev_tmp = i
            ave_tmp = ave
    #print(ave_tmp)
    return dev_tmp

def find_key1(s,i):
    st = [""] * i
    dev = []
    for j in range(len(s)):
        st[j%i] += s[j]
    for j in range(0,i):
        dev.append(cal_dev1(st[j]))
    print(dev)
    key = ''
    for k in dev:
        key += chr(ord("a")+(k+26)%26)
    tmp = dec(s,key)
    print("key is {}, plaintext is {}".format(key,tmp))


s1 = ss.lower()
l = find_len(s1)
find_key(s1,l)
find_key1(s1,l)

```

**参考文献:** 

［1］  [加]Douglas R.Stinson. 密码学原理与实践[M]. 冯登国.北京:电子工业出版社, 2003.
