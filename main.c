#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void RSA_Encrypt(int m) {

	int p=0, q=0, n=0, phin=0, d=0, e=0;

	//generate random primes p and q using rand() compositeness (miller) test
	p = rand()%20;	
//	p=5; //initialised p, q and e for testing only
	while(composite(p)!=1){
		p = rand();
	}
	q = rand()%20;
//	q = 13;
	while(composite(q)!=1){
		q = rand();
	}
	
	//decryption >> long int m = (int)pow(c,d)%n;

	n = p*q;
	phin = (p-1)*(q-1);

	//while (e<2){
	//	e = rand() % phin;
	//}
	e=5;
	
	//TODO: eea of e and phin = d
	int x, y;
	d = eea(e, phin, x, y);
//	d = (1%phin)/e; //easy way to get d without eea

	if(d<0){
		d += phin;
	}

	long int cipher = (int)pow((float)m, e)%n;
	
	printf("\n\nRSA vars:\nmessage = %d : p = %d : q = %d : n = %d : phi(n) = %d : d = %d : e = %d", m, p, q, n, phin, d, e); //print all vars to help with checking

	
	printf("\n\n\nCIPHER = %d", cipher);
	return;
}
/*
int RSA_Decrypt(int p, int q, int d, int c) {
	int message, mp, mq, yp, yq;
	
	mp = (int)pow((float)c, d%(p-1))%p;
	mq = (int)pow((float)c, d%(q-1))%q;
	
	eea(p, q, yp, yq);
	
	message = ((mp*yq*q)+(mq*yp*p))%n;
	
	printf("\n\n\nORIGINAL MESSAGE = %d", message);
}
*/

//EEA exported
int eea(int a, int b, int *x, int *y){
	
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}

	int _x, _y;
	int gcd = eea(b % a, a, &_x, &_y);

	*x = _y - (b/a) * _x;
	*y = _x;

	printf("\nEEA result: %d\n", gcd);
	
	return gcd;
}

//miller rabin ****REMARK: Who decides base 'a'?
int composite(int n){
	float a;
	int s=0, d=0, i=0;
	int r[s];

	//TODO: decide a
	a=7.0;

	d=n-1;

	do{
	 d=d/2;
	 s++;
	}
	while(d%2==0);

	printf("MILLER RESULT:\n n= %d, a= %d, d= %d, s= %d", n, (int)a, d, s);

	//print r values
	printf(", r = ");
	for(i=0; i<s; i++){
	 r[i]=i;
 	 printf("%d, ", r[i]);
	}

	//TODO: calculate the result for each r and add them????
	int x=0;
//	for(i=0; i<s; i++){
//	 x += (int)pow(a,pow(2,r[i])*d)%n;
//	}
	
	//break down x1 using fme in seperate function then x1=fme(a,d,n)
	if( (int)pow(a,d)%n !=1 && x !=-1 ){
		return 0;
	}else{
		return 1;
	}
}



int main(int argc, char *argv[]) {
	
	int menu = 2;
	
	printf("Enter 0 to encrypt message\nEnter 1 to decrypt message\n");
	scanf("%d", &menu); //can be edited to read line no matter what entry is (even char) then convert to int and return same error below if invalid
	
	while(menu != 0 && menu != 1){
		printf("Invalid entry!\nEnter 0 to encrypt message\nEnter 1 to decrypt message\n");
		scanf("%d", &menu);
	}
	
	int m = 0;
	int c = 0;
	if(menu == 0){
		printf("enter 'm' to encrypt: ");
		scanf("%d", &m);
		RSA_Encrypt(m);
	}//else{
		
	//}

return 0;
}
