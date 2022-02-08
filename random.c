#include <gmp.h>
#include <time.h>

int main()
{
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed;
	seed = time(NULL);
	gmp_randseed_ui(state,seed);
	mpz_t max,a,b,bits;
	mpz_inits(max,a,b,bits,NULL);

	mpz_set_ui(bits, 512);

	mpz_urandomb(a, state, 512);
	mpz_nextprime(a, a);
	mpz_nextprime(b, a);

	gmp_printf("a: %Zd\n", a);
	gmp_printf("b: %Zd\n", b);

	mpz_t n;
	mpz_init(n);
	mpz_mul(n, a, b);
	gmp_printf("n: %Zd\n", n);


}