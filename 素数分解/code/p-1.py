void pollardp1(ZZ n) {
	ZZ a , b,d;
	long c ;
	int num;
	for (int i = 0; i < 1000; i++) {
		RandomBnd(a, ZZ(10));
		a =a+2;
		cout << "a:" << a << endl;
		c=(rand() % 2000000)+1;
		/*num = c;
		cout << "index:" << c << endl;
		for (int j = 1; j < num; j++) {
			c = c * j;
		}*/
		cout <<"index:" << c << endl;
		d=PowerMod(a, c,n);
		d = d - 1;
		cout <<"hello:" << d << endl;
		if (GCD(d, n) != 1) {
			cout << GCD(d, n);
			break;
		}
		cout <<"():" << GCD(d, n) << endl;
	}
}