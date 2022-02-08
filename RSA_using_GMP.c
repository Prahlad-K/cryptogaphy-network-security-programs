#include <gmp.h>
#include <stdio.h>

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

unsigned urandom(void) {
  unsigned r;
  FILE *fp = fopen("/dev/urandom", "r");
  fread((void *)&r, sizeof r, 1, fp);
  fclose(fp);
  return r;
}

void factor2(mpz_t _n, unsigned long *r, mpz_t n) {
  mpz_set(n, _n);
  int is_odd = mpz_odd_p(n);
  if (is_odd)
    mpz_sub_ui(n, n, 1);

  *r = mpz_scan1(n, *(mp_bitcnt_t[]){0});
  mpz_fdiv_q_2exp(n, n, *r);
}

int mr(mpz_t n, unsigned long k) {
  if (mpz_cmp_ui(n, 3) <= 0 || mpz_even_p(n))
    return mpz_cmp_ui(n, 2) == 0 ||
           mpz_cmp_ui(n, 3) == 0;

  unsigned long r;
  mpz_t d, a, x;
  mpz_inits(d, a, x, NULL);
  factor2(n, &r, d);

  gmp_randstate_t rs;
  gmp_randinit_default(rs);
  gmp_randseed_ui(rs, urandom());

  mpz_t a_range; mpz_init_set(a_range, n);
  mpz_sub_ui(a_range, a_range, 3);

  mpz_t n_sub_1; mpz_init(n_sub_1);
  mpz_sub_ui(n_sub_1, n, 1);

  int is_prime = 1;

  for (unsigned long i = 0; i < k; i++) {
    mpz_urandomm(a, rs, a_range);
    mpz_add_ui(a, a, 2);

    mpz_powm(x, a, d, n);

    if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_sub_1) == 0)
      continue;

    is_prime = 0;
    for (unsigned long j = 0; j < r - 1; j++) {
      mpz_powm_ui(x, x, 2, n);
      if (mpz_cmp_ui(x, 1) == 0)
        break;
      if (mpz_cmp(x, n_sub_1) == 0) {
        is_prime = 1;
        break;
      }
    }
    if (!is_prime)
      break;
  }

  gmp_randclear(rs);
  mpz_clears(x, a, d, a_range, n_sub_1, NULL);
  return is_prime;
}
int main()
{

	mpz_t base;
	mpz_init_set_ui(base, 2);

	mpz_t largemod;
	mpz_init_set_ui(largemod, 1000000007);
	
	mpz_t tryupto;
	mpz_init(tryupto);

	mpz_powm_ui(tryupto, base, 512, largemod);

	mpz_t number;
	mpz_init(number);

	mpz_set(number, tryupto);

	mpz_t p, q;
	mpz_init(p);
	mpz_init(q);

	int both_primes_found = 0;
	int one_prime_found = 0;
	while(!both_primes_found)
	{
		if(!one_prime_found)
		{
			if(mr(number, 8))
			{
				mpz_set(q, number);
				one_prime_found = 1;
			}
		}
		else
		{
			if(mr(number, 8))
			{
				mpz_set(p, number);
				both_primes_found = 1;
			}
		}
		mpz_sub_ui(number, number, 2);
	}

	gmp_printf("P found from Miller Rabin Primality test: %Zd\n", p);
	gmp_printf("Q found from Miller Rabin Primality test: %Zd\n", q);

	mpz_t pminus1, qminus1;

	mpz_init(pminus1);
	mpz_init(qminus1);

	mpz_sub_ui(pminus1, p, 1);
	mpz_sub_ui(qminus1, q, 1);

	mpz_t n;
	mpz_init(n);
	mpz_mul(n, p, q);

	mpz_t e;
	mpz_init_set_ui(e, 2);

	mpz_t phi;
	mpz_init(phi);
	mpz_mul(phi, pminus1, qminus1);

	//e must be coprime to phi and smaller than phi
	mpz_t x, y;
	mpz_init(x);
    mpz_init(y);
	while(mpz_cmp(e, phi)<0)
	{
		mpz_t ans;
		mpz_init(ans);
		gcd(e, phi, ans, x, y);
		if(mpz_cmp_ui(ans, 1)==0)
			break;
		else
			mpz_add_ui(e, e, 1);
	}
	
	mpz_t d;
	mpz_init(d);

	if(mpz_cmp_si(x, 0)<0)
		mpz_add(d, x, phi);
	else
		mpz_set(d, x);

	mpz_t message;
	mpz_init(message);

	printf("Enter integer data: ");
	gmp_scanf("%Zd",message);

	mpz_t c;
	mpz_init(c);

	mpz_powm(c, message, e, n);
	gmp_printf("Encrypted data: %Zd\n", c);

	mpz_t m;
	mpz_init(m);

	mpz_powm(m, c, d, n);
	gmp_printf("Decrypted data: %Zd\n", m);
	return 0;
}