// C167227 Elliptic Curve Cryptography Diffie Hellman CNS Lab Cycle 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gmp.h>
#include<time.h>

struct Point{
	mpz_t x;
	mpz_t y;
};

struct Elliptic_Curve{
	mpz_t a;	//y^2 = x^3 + a*x + b
	mpz_t b;
	mpz_t p;
	mpz_t n;	//Order
	struct Point G;	//Base Point
	mpz_t h;	//Cofactor
};

void Point_Addition(struct Elliptic_Curve EC, struct Point P,struct Point Q, struct Point *R);
void Point_Doubling(struct Elliptic_Curve EC, struct Point P,struct Point *R);
void Scalar_Multiplication(struct Elliptic_Curve EC, mpz_t m, struct Point P, struct Point *R);

int main(int argc, char * argv[]){
	srand(time(NULL)); //not crypto secure
	struct Elliptic_Curve secp192k1;

	mpz_init(secp192k1.a);
	mpz_init(secp192k1.b);
	mpz_init(secp192k1.p);
	mpz_init(secp192k1.n);
	mpz_init(secp192k1.G.x);
	mpz_init(secp192k1.G.y);
	mpz_init(secp192k1.h);

	//initializing important values
	mpz_set_str(secp192k1.a,"0", 16); //Elliptic Curve P-192
	mpz_set_str(secp192k1.b,"3", 16);
	mpz_set_str(secp192k1.p,"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37", 16);
	mpz_set_str(secp192k1.n,"FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D", 16);
	mpz_set_str(secp192k1.G.x,"DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", 16);
	mpz_set_str(secp192k1.G.y,"9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D", 16);
	mpz_set_str(secp192k1.h,"1", 16);

	printf("\n\n***** Diffie Hellman Key exchange using Elliptic Curve P-192 *****\n\n");

	mpz_t na, nb;		//priv
	struct Point Pa, Pb;	//pub

	mpz_init(na);
	mpz_init(nb);
	mpz_init(Pa.x);
	mpz_init(Pa.y);
	mpz_init(Pb.x);
	mpz_init(Pb.y);

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed;
	seed = time(NULL);
	gmp_randseed_ui(state,seed);

	mpz_urandomm(na, state, secp192k1.p); //Private Key of A
	mpz_urandomm(nb, state, secp192k1.p); //Private key of B

	//Calculating the public keys 
	Scalar_Multiplication(secp192k1, na, secp192k1.G, &Pa); 
	Scalar_Multiplication(secp192k1, nb, secp192k1.G, &Pb);

	gmp_printf("Private Key of A: %Zd\n", na);
	printf("___________________________________________________________________________________________________________\n");
	gmp_printf("Public Key of A: (%Zd, %Zd)\n", Pa.x, Pa.y);
	printf("___________________________________________________________________________________________________________\n");
	gmp_printf("Private Key of B: %Zd\n", nb);
	printf("___________________________________________________________________________________________________________\n");
	gmp_printf("Public Key of B: (%Zd, %Zd)\n", Pb.x, Pb.y);
	printf("___________________________________________________________________________________________________________\n");

	struct Point Ka, Kb;
	mpz_init(Ka.x);
	mpz_init(Ka.y);
	mpz_init(Kb.x);
	mpz_init(Kb.y);


	//A calculates secret key Ka
	Scalar_Multiplication(secp192k1, na, Pb, &Ka);
	//B calculates secret key Kb
	Scalar_Multiplication(secp192k1, nb, Pa, &Kb);

	gmp_printf("Secret Key calculated by A: (%Zd, %Zd)\n", Ka.x, Ka.y);
	printf("___________________________________________________________________________________________________________\n");

	gmp_printf("Secret Key calculated by B: (%Zd, %Zd)\n", Kb.x, Kb.y);
	printf("___________________________________________________________________________________________________________\n");

	//Both must match!
	if(mpz_cmp(Ka.x, Kb.x)==0 && mpz_cmp(Ka.y, Kb.y)==0)
	{
		printf("Secret key exchange successful!\n");

	}


	return 0;
}

void Point_Addition(struct Elliptic_Curve EC, struct Point P,struct Point Q,struct Point *R){
	mpz_mod(P.x,P.x,EC.p);
	mpz_mod(P.y,P.y,EC.p);
	mpz_mod(Q.x,Q.x,EC.p);
	mpz_mod(Q.y,Q.y,EC.p);
	mpz_t temp,slope;
	mpz_init(temp);
	mpz_init_set_ui(slope,0);
	if(mpz_cmp_ui(P.x,0)==0 && mpz_cmp_ui(P.y,0)==0){
		mpz_set(R->x,Q.x); mpz_set(R->y,Q.y);
		return;
	}
	if(mpz_cmp_ui(Q.x,0)==0 && mpz_cmp_ui(Q.y,0)==0){
		mpz_set(R->x,P.x);
		mpz_set(R->y,P.y);
		return;
	}
	if(mpz_cmp_ui(Q.y,0)!=0){
		mpz_sub(temp,EC.p,Q.y);
		mpz_mod(temp,temp,EC.p);
	}else
		mpz_set_ui(temp,0);
	if(mpz_cmp(P.y,temp)==0 && mpz_cmp(P.x,Q.x)==0){
		mpz_set_ui(R->x,0);
		mpz_set_ui(R->y,0);
		return;
	}
	if(mpz_cmp(P.x,Q.x)==0 && mpz_cmp(P.y,Q.y)==0){
		Point_Doubling(EC,P,R);
		return;
	}else{
		mpz_sub(temp,P.x,Q.x);
		mpz_mod(temp,temp,EC.p);
		mpz_invert(temp,temp,EC.p);
		mpz_sub(slope,P.y,Q.y);
		mpz_mul(slope,slope,temp);
		mpz_mod(slope,slope,EC.p);
		mpz_mul(R->x,slope,slope);
		mpz_sub(R->x,R->x,P.x);
		mpz_sub(R->x,R->x,Q.x);
		mpz_mod(R->x,R->x,EC.p);
		mpz_sub(temp,P.x,R->x);
		mpz_mul(R->y,slope,temp);
		mpz_sub(R->y,R->y,P.y);
		mpz_mod(R->y,R->y,EC.p);
		return;
	}
}

void Point_Doubling(struct Elliptic_Curve EC, struct Point P,struct Point *R){
	mpz_t slope,temp;
	mpz_init(temp);
	mpz_init(slope);
	if(mpz_cmp_ui(P.y,0)!=0){
		mpz_mul_ui(temp,P.y,2);
		mpz_invert(temp,temp,EC.p);
		mpz_mul(slope,P.x,P.x);
		mpz_mul_ui(slope,slope,3);
		mpz_add(slope,slope,EC.a);
		mpz_mul(slope,slope,temp);
		mpz_mod(slope,slope,EC.p);
		mpz_mul(R->x,slope,slope);
		mpz_sub(R->x,R->x,P.x);
		mpz_sub(R->x,R->x,P.x);
		mpz_mod(R->x,R->x,EC.p);
		mpz_sub(temp,P.x,R->x);
		mpz_mul(R->y,slope,temp);
		mpz_sub(R->y,R->y,P.y);
		mpz_mod(R->y,R->y,EC.p);
	}else{
		mpz_set_ui(R->x,0);
		mpz_set_ui(R->y,0);
	}
	
}

void Scalar_Multiplication(struct Elliptic_Curve EC, mpz_t m, struct Point P, struct Point *R){
	struct Point Q,T;
	mpz_init(Q.x);
	mpz_init(Q.y);
	mpz_init(T.x);
	mpz_init(T.y);
	long no_of_bits,loop;
	no_of_bits=mpz_sizeinbase(m,2);
	mpz_set_ui(R->x,0);
	mpz_set_ui(R->y,0);
	if(mpz_cmp_ui(m,0)==0)
		return;
	mpz_set(Q.x,P.x);
	mpz_set(Q.y,P.y);
	if(mpz_tstbit(m,0)==1){
		mpz_set(R->x,P.x);
		mpz_set(R->y,P.y);
	}
	for(loop=1;loop<no_of_bits;loop++){
		mpz_set_ui(T.x,0);
		mpz_set_ui(T.y,0);
		Point_Doubling(EC,Q,&T);
		mpz_set(Q.x,T.x);
		mpz_set(Q.y,T.y);
		mpz_set(T.x,R->x);
		mpz_set(T.y,R->y);
		if(mpz_tstbit(m,loop))
			Point_Addition(EC,T,Q,R);
	}
}
