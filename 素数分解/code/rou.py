def f(x,n):
    y=(x*x+1)%n
    return y
import random
n=int(input())
hello=True
a=random.randint(1,n)
a=1;
print(a)
b=[0,a]
i=1
pan=True
while(pan):
    b.append(f(b[i],n))
    print(b[i+1])
    if(i%2==0):
        if(b[i]==b[i/2]):
            pan=False
    i=i+1
for j in b:
    c=j-b[1]
    if(c<0):
        c=c+n
    if(j!=0&(c!=0)):
        print("hello:    ",j,"  ",c ,'\n',gcd(c,n))
        if(gcd(c,n)!=1)&(c!=0):
            print(gcd(c,n))
            hello=False
            break