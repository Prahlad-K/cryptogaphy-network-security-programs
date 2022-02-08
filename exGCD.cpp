#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
#include <stdio.h>

using namespace std;

void gcd(mpz_t a, mpz_t b, mpz_t c, mpz_t x, mpz_t y) 
{ 
    if (mpz_cmp_si(a, 0) == 0) 
    {
        mpz_set_si(x, 0);
        mpz_set_si(y, 1);
        mpz_set(c, b);
    }
    else
    {
	    mpz_t modvalue;
	    mpz_init(modvalue);

        mpz_t x1, y1;
        mpz_init(x1);
        mpz_init(y1);
        
	    mpz_mod(modvalue, b, a); 
	    gcd(modvalue, a, c, x1, y1); 
        
        mpz_t bdiva;
        mpz_init(bdiva);
        mpz_fdiv_q(bdiva, b, a);

        mpz_t mulx1;
        mpz_init(mulx1);
        mpz_mul(mulx1, x1, bdiva);

        mpz_sub(x, y1, mulx1);
        mpz_set(y, x1);
	}
} 
  
int main() 
{ 
    mpz_t a, b, c, x, y; 

    mpz_init(a);
    mpz_init(b);
    mpz_init_set_ui(c, 0);
    mpz_init(x);
    mpz_init(y);
    //gmp_scanf("%Zd ", a);
    //gmp_scanf("%Zd ", b);

	cout<<"Enter the first number:";
	cin>>a;
    cout<<"Enter the second number:";
	cin>>b;
    gcd(a, b, c, x, y);

    cout << "GCD(" << a << ", " << b << ") = " <<  c << endl; 
    cout<< "x is "<<x<<" and y is "<<y<<endl;
    return 0; 
} 