def pm1_attack(n,b):
  p = [2,3,5,7,11,13,17]; i=19; a=2
  while i<b:
    if is_prime(i,10): p.append(i)
    i+=2;
  k = sp.uint64(np.prod(p)); q = power2(a,k,n)
  g = euc_al_i((q-1),n)
  print ("product pi: ",k)
  print ("q: ",q)
  print ("g: ",g)
  #return a

print ("pollard_pm1_attack(n,b): ",pollard_pm1_attack(n,2000))
