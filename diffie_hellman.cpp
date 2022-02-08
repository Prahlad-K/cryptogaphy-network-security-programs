#include <bits/stdc++.h>
#include <gmp.h>

using namespace std;

int main()
{

  mpz_t p, alpha;

  mpz_init_set_str(p, "10375039676004850895153180219140825871832424447991559740017057480128913835806851959289793274985265665777122921936941938022987986088961250820311707667977663", 10);
  mpz_init_set_str(alpha, "3489494002834111451509114829193233051117747768439168837412006394274759575652051518038030330723614924696942312359936737919658157609986927981108133394482327", 10);

  cout<<"\nPrime number: "<<p<<endl;
  cout<<"_____________________________________________________________________________"<<endl;
  cout<<"Generator: "<<alpha<<endl;
  cout<<"_____________________________________________________________________________"<<endl;

  mpz_t Xa, Xb, Ya, Yb;

  mpz_init(Xa);
  mpz_init(Xb);
  mpz_init(Ya);
  mpz_init(Yb);

  unsigned long int i, seed;
  gmp_randstate_t r_state;

  seed = time(NULL);

  gmp_randinit_mt(r_state);
  gmp_randseed_ui(r_state, seed);

  mpz_urandomm(Xa, r_state, p);
  mpz_urandomm(Xb, r_state, p);

  mpz_powm(Ya, alpha, Xa, p);
  mpz_powm(Yb, alpha, Xb, p);

  cout<<"Xa: "<<Xa<<endl;
  cout<<"_____________________________________________________________________________"<<endl;
  cout<<"Xb: "<<Xb<<endl;
  cout<<"_____________________________________________________________________________"<<endl;
  cout<<"Ya: "<<Ya<<endl;
  cout<<"_____________________________________________________________________________"<<endl;
  cout<<"Yb: "<<Yb<<endl;
  cout<<"_____________________________________________________________________________"<<endl;

  mpz_t key_a, key_b;
  mpz_init(key_a);
  mpz_init(key_b);

  mpz_powm(key_a, Yb, Xa, p);
  mpz_powm(key_b, Ya, Xb, p);

  cout<<"Generated key at A: "<<key_a<<endl;
  cout<<"_____________________________________________________________________________"<<endl;
  cout<<"Generated key at B: "<<key_b<<endl;
  cout<<"_____________________________________________________________________________"<<endl;

  if(mpz_cmp(key_a, key_b)==0)
    cout<<"The generated keys match!"<<endl;
  else
    cout<<"The generated keys do not match!"<<endl;

}
