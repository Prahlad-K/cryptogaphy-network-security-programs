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
	mpz_init_set_ui(largemod, 1000000007)
	
	mpz_t tryupto;
	mpz_init(tryupto);
	mpz_powm_ui(tryupto, base, 512, 1000000007);

	mpz_t number;
	mpz_init(number, 3);

	mpz_t p, q;
	mpz_init(p);
	mpz_init(q);

	while(mpz_cmp(number, tryupto)<=0)
	{
		if(mr(number, 100))
		{
			mpz_set(p, q);
			mpz_set(q, number);
		}
		mpz_add_ui(number, 1);
	}

	gmp_printf("%Zd", p);
	printf("\n");
	gmp_printf("%Zd", q);

/*
	mpz_t p, q, pminus1, qminus1;
	mpz_init(p);
	mpz_init(q);
	mpz_init(pminus1);
	mpz_init(qminus1);

	cout<<"Enter two large prime numbers: ";
	cin>>p;
	cin>>q;

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
	while(mpz_cmp(e, phi)<0)
	{
		mpz_t ans;
		mpz_init(ans);
		gcd(e, phi, ans);
		cout<<ans<<endl;
		if(mpz_cmp_ui(ans, 1)==0)
			break;
		else
			mpz_add_ui(e, e, 1);
	}

	cout<<e<<endl;
	
	mpz_t k;
	mpz_init_set_ui(k, 2);

	mpz_t d;
	mpz_init(d);

	mpz_t ktimesphi;
	mpz_init(ktimesphi);

	mpz_mul(ktimesphi, k, phi);
	mpz_add_ui(ktimesphi, ktimesphi, 1);
	mpz_fdiv_q(d, ktimesphi, e);

	mpz_t message;
	mpz_init(message);

	cout<<"Enter your message: ";
	cin>>message;

	mpz_t c;
	mpz_init(c);

	mpz_powm(c, message, e, n);
	cout<<"Encrypted data: "<<c<<endl;

	mpz_t m;
	mpz_init(m);

	mpz_powm(m, c, d, n);
	cout<<"Original message: "<<m<<endl;
	return 0;
	*/
}