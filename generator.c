#include <gmp.h>
#include <stdio.h>
#include <unistd.h>

#include <time.h>

void generator(mpz_t pminus1, mpz_t q, mpz_t alpha)
{
	int found = 0;

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed;
	seed = time(NULL);
	gmp_randseed_ui(state, seed);

	while(!found)
	{
		found = 1;
		mpz_t temp;
		mpz_init(temp);

		mpz_urandomm(temp, state, pminus1);

		//divide with 2
		mpz_t div;
		mpz_init(div);
		mpz_fdiv_q_ui(div, pminus1, 2);

		mpz_t b;
		mpz_init(b);
		mpz_powm(b, temp, div, pminus1);

		if(mpz_cmp_ui(b, 1)==0)
			found = 0;

		//divide with q
		mpz_fdiv_q(div, pminus1, q);
		mpz_powm(b, temp, div, pminus1);

		if(mpz_cmp_ui(b, 1)==0)
			found = 0;

		if(found)
			mpz_set(alpha, temp);
	}

}

int main()
{

	//find a safe prime p 
	mpz_t p, alpha;
	mpz_t q;
	mpz_inits(p, alpha, q, NULL);

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed;
	seed= time(NULL);
	gmp_randseed_ui(state, seed);

	int safe= 0;
	while(!safe)
	{
		safe = 1;
		mpz_urandomb(q, state, 1023);
		mpz_nextprime(q, q);
		mpz_add(p, q, q);
		mpz_add_ui(p, p, 1);

		if(mpz_probab_prime_p(p, 100)==0)
			safe = 0;
	}

	gmp_printf("Prime number: %Zd\n", p);
	gmp_printf("Prime number2: %Zd\n", q);

	mpz_t pminus1;
	mpz_inits(pminus1, NULL);

	mpz_sub_ui(pminus1, p, 1);

	generator(pminus1, q, alpha);

	gmp_printf("Prime number: %Zd\n", p);
	gmp_printf("Generator: %Zd\n", alpha);

	return 0;
}