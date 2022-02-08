/* C167227 CNS LAB CYCLE -1 ASSIGNMENT QUESTION 8*/
#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
#include <stdio.h>

using namespace std;

void inv(mpz_t a, mpz_t b, mpz_t c, mpz_t x, mpz_t y) 
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
	    inv(modvalue, a, c, x1, y1); 
        
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
	int n;

	gmp_printf("Enter the number of elements: ");
	scanf("%d", &n);

	mpz_t num[n], rem[n], pp, prod, result, c, x, y, temp;
	mpz_init_set_ui(prod, 1);
	mpz_init(pp);
	mpz_init_set_ui(result, 0);
	mpz_init(temp);
	mpz_init_set_ui(c, 0);
    mpz_init(x);
    mpz_init(y);


	gmp_printf("Enter the elements of num and rem: \n");
	
	for(int i=0;i<n;i++)
	{
		//assuming the input is pairwise coprime
		mpz_init(num[i]);
		gmp_scanf("%Zd", num[i]);
		mpz_init(rem[i]); 	
		gmp_scanf("%Zd", rem[i]);
	}	

	for(int i=0;i<n;i++)
		mpz_mul(prod, prod, num[i]);

	for(int i=0;i<n;i++)
	{
		mpz_fdiv_q(pp, prod, num[i]);
		mpz_mul(temp, rem[i], pp);
		inv(pp, num[i], c, x, y);
		mpz_mod(x, x, num[i]);
    	mpz_add(x, x, num[i]);
    	mpz_mod(x, x, num[i]);
		mpz_mul(temp, temp, x);
		mpz_add(result, result, temp);
	}

	mpz_mod(result, result, prod);
	gmp_printf("The value of x found is: %Zd\n", result);

}