/* C167227 CNS LAB CYCLE -1 ASSIGNMENT - POLYNOMIAL ARITHMETIC*/
#include <bits/stdc++.h>
#include <gmp.h>
#include <stdio.h>


using namespace std;

void multiply(mpz_t i, mpz_t j, mpz_t N, mpz_t ip, mpz_t result)
{
	mpz_t base, one, two, ileftshift, Nby2, ixorip, Nminus1, icopy;
	mpz_init_set_ui(base, 2);
	mpz_init_set_ui(one, 1);
	mpz_init_set_ui(two, 2);
	mpz_init(ileftshift);
	mpz_init(Nby2);
	mpz_init(Nminus1);
	mpz_sub(Nminus1, N, one);
	mpz_init(ixorip);
	mpz_init(icopy);
	mpz_set(icopy, i);

	mpz_t temp;
	mpz_init(temp);


	mpz_fdiv_q(Nby2, N, two);

	mpz_and(temp, j, one);
	if(mpz_cmp_ui(temp, 1)==0)
		mpz_set(result, i);
	else
		mpz_set_ui(result, 0);
	
	while(mpz_cmp(base, N)<0)
	{
		mpz_mul(ileftshift, icopy, two);
		mpz_and(temp, icopy, Nby2);
		if(mpz_cmp(temp, Nby2)==0)
			mpz_xor(ixorip, ileftshift, ip);
		else
			mpz_set(ixorip, ileftshift);

		mpz_and(temp, j, base);
		if(mpz_cmp(temp, base)==0)
			mpz_xor(result, result, ixorip);

		mpz_mul(base, base, two);
		mpz_set(icopy, ixorip);
	}

	mpz_and(result, result, Nminus1);

}


int main()
{
	mpz_t n, N, mod, base, axorb, ip, result, Nby2, ileftshift, two, one, ixorip, temp;
	mpz_init(n);
	mpz_init(N);
	mpz_init(mod);
	mpz_init(axorb);
	mpz_init(ileftshift);
	mpz_init(Nby2);
	mpz_init(ixorip);
	mpz_init(temp);
	mpz_init(result);
	mpz_init(ip);
	mpz_init_set_ui(base, 2);
	mpz_init_set_ui(two, 2);
	mpz_init_set_ui(one, 1);


	printf("Enter the value of n: ");
	gmp_scanf("%Zd", n);

	printf("Enter the IP in decimal: ");
	gmp_scanf("%Zd", ip);

	mpz_init_set_ui(mod, 6700417); //6700417 is a prime number
	mpz_powm(N, base, n, mod);
	mpz_fdiv_q(Nby2, N, base);

	gmp_printf("2 power n: %Zd\n", N);

	mpz_t i, j; 
	mpz_init_set_ui(i, 0);
	mpz_init_set_ui(j, 0);

	printf("+  ");
	while(mpz_cmp(i, N)<0)
	{
		gmp_printf("%Zd ", i);
		mpz_add_ui(i, i, 1);
	}
	printf("\n");
	mpz_set_ui(i, 0);
	while(mpz_cmp(i, N)<0)
	{
		gmp_printf("%Zd: ", i);
		while(mpz_cmp(j, N)<0)
		{
			mpz_xor(axorb, i, j);
			gmp_printf("%Zd ", axorb);
			mpz_add_ui(j, j, 1);
		}
		printf("\n");
		mpz_add_ui(i, i, 1);
		mpz_set_ui(j, 0);
	}
	printf("\n");

    printf("Multiplicative group table:\n");

	mpz_set_ui(i, 1);
	mpz_set_ui(j, 1);

	printf("*  ");
	while(mpz_cmp(i, N)<0)
	{
		gmp_printf("%Zd ", i);
		mpz_add_ui(i, i, 1);
	}
	printf("\n");
	mpz_set_ui(i, 1);

	while(mpz_cmp(i, N)<0)
	{
		gmp_printf("%Zd: ", i);

		while(mpz_cmp(j, N)<0)
		{
			multiply(i, j, N, ip, result);
			gmp_printf("%Zd ", result);
			mpz_add_ui(j, j, 1);
		}
		printf("\n");
		mpz_add_ui(i, i, 1);
		mpz_set_ui(j, 1);
	}
}
