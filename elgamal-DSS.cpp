#include <bits/stdc++.h>
#include <gmp.h>
#include <time.h>
#include<openssl/sha.h>

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

void doSHA512(const char* string, char* mdString)
{
	unsigned char digest[SHA512_DIGEST_LENGTH];
    
    SHA512((unsigned char*)&string, strlen(string), (unsigned char*)&digest);    
 
    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
 
    printf("SHA512 digest: %s\n", mdString);
}


int main()
{
	mpz_t q, alpha;

	mpz_init_set_str(q, "10375039676004850895153180219140825871832424447991559740017057480128913835806851959289793274985265665777122921936941938022987986088961250820311707667977663", 10);
	mpz_init_set_str(alpha, "3489494002834111451509114829193233051117747768439168837412006394274759575652051518038030330723614924696942312359936737919658157609986927981108133394482327", 10);

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


	/*unsigned char message_digest[512];
	SHA512((const unsigned char*)message.c_str(), message.length(), message_digest);

	for(int i=0;i<512;i++)
	{
		cout<<message_digest[i];
	}
	cout<<endl;
	Must hash properly
*/
	char mdString[SHA512_DIGEST_LENGTH*2+1];
	doSHA512(message.c_str(), mdString);

	mpz_t M;
	mpz_init_set_str(M, mdString, 16);

	cout<<"\nMessage: "<<M<<endl;
	cout<<"_____________________________________________________________________________"<<endl;

	// A constructs signature for message M

	mpz_t K, qminus1;
	mpz_inits(K, qminus1, NULL);

	mpz_sub_ui(qminus1, q, 1);
	mpz_set_ui(K, 2);

	mpz_t x, y;
	mpz_init(x);
    mpz_init(y);
	while(mpz_cmp(K, qminus1)<0)
	{
		mpz_t ans;
		mpz_init(ans);
		gcd(K, qminus1, ans, x, y);
		if(mpz_cmp_ui(ans, 1)==0)
			break;
		else
			mpz_add_ui(K, K, 1);
	}

	mpz_t Kinv;
	mpz_init(Kinv);

	if(mpz_cmp_si(x, 0)<0)
		mpz_add(Kinv, x, qminus1);
	else
		mpz_set(Kinv, x);

	mpz_t S1, S2;
	mpz_inits(S1, S2, NULL);

	mpz_powm(S1, alpha, K, q);
	//K -1 (m - X A S 1 ) mod q-1

	mpz_t prod;	
	mpz_init(prod);

	mpz_mul(prod, XA, S1);
	mpz_sub(S2, M, prod);
	mpz_mul(S2, Kinv, S2);
	mpz_mod(S2, S2, qminus1);

	cout<<"S1: "<<S1<<endl;
	cout<<"_____________________________________________________________________________"<<endl;
	cout<<"S2: "<<S2<<endl;
	cout<<"_____________________________________________________________________________"<<endl;

	//B verifies the signature as follows

	mpz_t V1, V2;
	mpz_inits(V1, V2, NULL);

	mpz_powm(V1, alpha, M, q);

	mpz_powm(V2, YA, S1, q);
	mpz_powm(prod, S1, S2, q);
	mpz_mul(V2, V2, prod);
	mpz_mod(V2, V2, q);

	cout<<"V1: "<<V1<<endl;
	cout<<"_____________________________________________________________________________"<<endl;
	cout<<"V2: "<<V2<<endl;
	cout<<"_____________________________________________________________________________"<<endl;


	if(mpz_cmp(V1, V2)==0)
	{
		cout<<"Signature is valid!"<<endl;
	}

	return 0;
}