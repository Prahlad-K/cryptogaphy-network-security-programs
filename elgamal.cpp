#include <bits/stdc++.h>
#include <gmp.h>
#include <time.h>

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

	mpz_t q, alpha;

	//mpz_init_set_str(q, "10375039676004850895153180219140825871832424447991559740017057480128913835806851959289793274985265665777122921936941938022987986088961250820311707667977663", 10);
	//mpz_init_set_str(alpha, "3489494002834111451509114829193233051117747768439168837412006394274759575652051518038030330723614924696942312359936737919658157609986927981108133394482327", 10);

	mpz_init_set_str(q, "35542525914383146010822243008575608163241757706283604032444361514638092427956485708188083216373627895368548106596131119011327524475335690216667032265821713236779726877430224393084991821101341483101714118413388091687170422119262640043219420057816709619693967331474846416578934089380419004324776268652711122127", 10);
	mpz_init_set_str(alpha, "25121338972973693724770535088951293650143674639031927300286244944775430798721320551257198640361544000336679916560133111126650589700884419801425860834036839430933674761578952951333016148942574859585461599870733974378314802758697578808612882984773531996469634080850132545766263526484011266716463238940924705969", 10);

	cout<<"\nPrime number: "<<q<<endl;
	cout<<"_____________________________________________________________________________"<<endl;
	cout<<"Generator: "<<alpha<<endl;
	cout<<"_____________________________________________________________________________"<<endl;

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed;
	seed = time(NULL);
	gmp_randseed_ui(state,seed);

	mpz_t XA, YA;
	mpz_inits(XA, YA, NULL);

	mpz_urandomm(XA, state, q);
	mpz_powm(YA, alpha, XA, q);

	cout<<"Public key of A: "<<YA<<endl;
	cout<<"_____________________________________________________________________________"<<endl;
	//A sends it's pblic key YA to B

	string message;
	cout<<"Enter message (as an integer): ";
	cin>>message;

	mpz_t M;
	mpz_init_set_str(M, message.c_str(), 10);

	cout<<"\nMessage: "<<M<<endl;
	cout<<"_____________________________________________________________________________"<<endl;


	mpz_t k;
	mpz_init(k);
	mpz_urandomm(k, state, q);

	//cout<<"k: "<<k<<endl;
	//cout<<"_____________________________________________________________________________"<<endl;


	mpz_t K;
	mpz_init(K);
	mpz_powm(K, YA, k, q);

	//cout<<"K: "<<K<<endl;
	//cout<<"_____________________________________________________________________________"<<endl;


	mpz_t C1, C2;
	mpz_inits(C1, C2, NULL);
	mpz_powm(C1, alpha, k, q);

	cout<<"C1: "<<C1<<endl;
	cout<<"_____________________________________________________________________________"<<endl;


	mpz_mul(C2, K, M);
	mpz_mod(C2, C2, q);

	cout<<"C2: "<<C2<<endl;
	cout<<"_____________________________________________________________________________"<<endl;


	//B sends C1 and C2 to A
	//A calculates plaintext M as follows

	mpz_t Krec, Mrec;
	mpz_inits(Krec, Mrec, NULL);

	mpz_powm(Krec, C1, XA, q);

	cout<<"Krec: "<<Krec<<endl;
	cout<<"_____________________________________________________________________________"<<endl;


	mpz_t Kinv;
	mpz_init(Kinv);


	mpz_t c, y;
	mpz_inits(c, y, NULL);
	mpz_set_ui(c, 0);

	//gcd(Krec, q, c, Kinv, y);

	mpz_gcdext(c, Kinv, y, Krec, q);

	if(mpz_cmp_si(Kinv, 0)<0)
		mpz_add(Kinv, Kinv, q);

	cout<<"Kinv: "<<Kinv<<endl;
	cout<<"_____________________________________________________________________________"<<endl;


	mpz_mul(Mrec, C2, Kinv);
	mpz_mod(Mrec, Mrec, q);

	cout<<"Mrec: "<<Mrec<<endl;
	cout<<"_____________________________________________________________________________"<<endl;



	if(mpz_cmp(M, Mrec)==0)
	{
		printf("Elgamal encryption and decryption successful!\n");
	}
	return 0;
}