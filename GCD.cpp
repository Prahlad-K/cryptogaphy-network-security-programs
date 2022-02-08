#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
#include <stdio.h>

using namespace std;

void gcd(mpz_t a, mpz_t b, mpz_t c) 
{ 
    if (mpz_cmp_si(a, 0) == 0) 
         mpz_set(c, b);
    else
    {
	    mpz_t modvalue;
	    mpz_init(modvalue);

	    mpz_mod(modvalue, b, a); 
	    gcd(modvalue, a, c); 
	}
} 
  
int main() 
{ 
    mpz_t a, b, c; 

    mpz_init(a);
    mpz_init(b);
    mpz_init_set_ui(c, 0);

    //gmp_scanf("%Zd ", a);
    //gmp_scanf("%Zd ", b);

	cout<<"Enter the first number:";
	cin>>a;
    cout<<"Enter the second number:";
	cin>>b;
    gcd(a, b, c);

    mpz_abs(c, c);
    
    cout << "GCD(" << a << ", " << b << ") = " <<  c << endl; 
    return 0; 
} 