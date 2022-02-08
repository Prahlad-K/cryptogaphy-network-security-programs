/* C167227 CNS LAB CYCLE -1 ASSIGNMENT - Hill Cipher*/
#include <iostream> 
#include <math.h>
using namespace std; 
#define N 3

int gcdExtended(int a, int b, int *x, int *y)  
{  
    if (a == 0)  
    {  
        *x = 0;  
        *y = 1;  
        return b;  
    }  
  
    int x1, y1; 
    int gcd = gcdExtended(b%a, a, &x1, &y1);  
  
    *x = y1 - (b/a) * x1;  
    *y = x1;  
  
    return gcd;  
}

int modInverse(int a, int m) 
{ 
    int x, y; 
    int g = gcdExtended(a, m, &x, &y); 
    if (g != 1) 
    {
        cout << "Inverse doesn't exist"; 
        return 0;
    }
    else
    { 
        int res = (x%m + m) % m; 
        //cout << "Modular multiplicative inverse of "<<a<<" is " << res<<endl; 
        return res;
    } 
} 
// Function to get cofactor of A[p][q] in temp[][]. n is current 
// dimension of A[][] 
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n) 
{ 
    int i = 0, j = 0; 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
  
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 
  
/* Recursive function for finding determinant of matrix. 
   n is current dimension of A[][]. */
int determinant(int A[N][N], int n) 
{ 
    int D = 0; 
  
    if (n == 1) 
        return A[0][0]; 
  
    int temp[N][N]; 
  
    int sign = 1;   
    for (int f = 0; f < n; f++) 
    { 
        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n - 1); 
  
        sign = -sign; 
    } 
  
    return D; 
} 
  
void adjoint(int A[N][N],int adj[N][N],int n, int detinv) 
{ 
    if (N == 1) 
    { 
        adj[0][0] = 1; 
        return; 
    } 
  
    int sign = 1, temp[N][N]; 
  
    for (int i=0; i<n; i++) 
    { 
        for (int j=0; j<n; j++) 
        { 
            getCofactor(A, temp, i, j, n); 
  
            sign = ((i+j)%2==0)? 1: -1; 

            adj[j][i] = (sign)*(determinant(temp, n-1));

            adj[j][i] *= detinv;
            adj[j][i] = adj[j][i] % 26;

            if(adj[j][i]<0)
                adj[j][i] +=26; 
        } 
    } 
} 
  
bool modular_inverse(int A[N][N], int inverse[N][N], int n) 
{ 
    int det = determinant(A, n); 
    if (det == 0) 
    { 
        cout << "Singular matrix, can't find its inverse"; 
        return false; 
    } 
    
    int detinv = modInverse(det, 26);
  
    adjoint(A, inverse, n, detinv); 
    
    return true; 
} 
  
template<class T> 
void display(T A[N][N], int n) 
{ 
    for (int i=0; i<n; i++) 
    { 
        for (int j=0; j<n; j++) 
            cout << A[i][j] << " "; 
        cout << endl; 
    } 
} 

void getKeyMatrix(string key, int keyMatrix[N][N], int n) 
{ 
    int k = 0; 
    for (int i = 0; i < n; i++)  
    { 
        for (int j = 0; j < n; j++)  
        { 
            keyMatrix[i][j] = (key[k]) % 65; 
            k++; 
        } 
    } 
} 
  
void getCipherVector(int ciphertextVector[][1], 
             int keyMatrix[N][N],  
             int plaintextVector[][1], int n) 
{ 
    int x, i, j; 
    for (i = 0; i < n; i++)  
    { 
        for (j = 0; j < 1; j++) 
        { 
            ciphertextVector[i][j] = 0; 
           
             for (x = 0; x < n; x++) 
            { 
                ciphertextVector[i][j] +=  
                     keyMatrix[i][x] * plaintextVector[x][j]; 
            } 
          
            ciphertextVector[i][j] = ciphertextVector[i][j] % 26; 
        } 
    } 
} 

void getPlainVector(int plaintextVector[][1], 
             int keyMatrix[N][N],  
             int ciphertextVector[][1], int n) 
{ 
    int x, i, j; 
    for (i = 0; i < n; i++)  
    { 
        for (j = 0; j < 1; j++) 
        { 
            plaintextVector[i][j] = 0; 
             for (x = 0; x < n; x++) 
            { 
                plaintextVector[i][j] +=  
                     keyMatrix[i][x] * ciphertextVector[x][j]; 
            } 

            plaintextVector[i][j] = plaintextVector[i][j] % 26; 
        } 
    } 
} 
string encipher(string plaintext, string key, int n) 
{ 
    int keyMatrix[N][N];

    getKeyMatrix(key, keyMatrix, n); 
  
    int plaintextVector[n][1]; 
  
    for (int i = 0; i < n; i++) 
        plaintextVector[i][0] = (plaintext[i]) % 65; 
  
    int ciphertextVector[n][1]; 
  
    getCipherVector(ciphertextVector, keyMatrix, plaintextVector, n); 
  
    string ciphertext; 
  
    for (int i = 0; i < n; i++) 
        ciphertext += ciphertextVector[i][0] + 65; 
  
    return ciphertext;
} 

string decipher(string ciphertext, string key, int n) 
{ 
    int keyMatrix[N][N];
    getKeyMatrix(key, keyMatrix, n); 

    int inverseMatrix[N][N];
    modular_inverse(keyMatrix, inverseMatrix, n);
    //display(inverseMatrix, n);

    int ciphertextVector[n][1]; 
    for (int i = 0; i < n; i++) 
        ciphertextVector[i][0] = (ciphertext[i]) % 65; 
  
    int plaintextVector[n][1]; 
  
    getPlainVector(plaintextVector, inverseMatrix, ciphertextVector, n); 

    string plaintext; 
  
    for (int i = 0; i < n; i++) 
        plaintext += plaintextVector[i][0] + 65; 
    return plaintext;
} 
  
int main() 
{ 
    string plaintext, ciphertext, key;
    cout<<"Enter the plaintext: ";
    cin>>plaintext;

    int n;
    n = plaintext.length();

    cout<<"Enter a "<<n*n<<" length key: ";
    cin>>key;

    ciphertext = encipher(plaintext, key, n); 

    cout<<"Enciphering...."<<endl;
    cout<<"Ciphertext is "<<ciphertext<<endl<<endl;
    
    plaintext = decipher(ciphertext, key, n);

    cout<<"Deciphering..."<<endl;
    cout<<"Plaintext is "<<plaintext<<endl;

    return 0; 
} 
