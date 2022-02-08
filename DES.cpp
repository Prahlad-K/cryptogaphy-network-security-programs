/* C167227 CNS LAB CYCLE -1 ASSIGNMENT - DES*/
#include<bits/stdc++.h>
#include <gmp.h>
#include <stdio.h>


using namespace std;

string hex2bin(string s){ 
        // hexadecimal to binary conversion 
    map<char, string> mp; 
    mp['0']= "0000"; 
    mp['1']= "0001"; 
    mp['2']= "0010"; 
    mp['3']= "0011"; 
    mp['4']= "0100"; 
    mp['5']= "0101"; 
    mp['6']= "0110"; 
    mp['7']= "0111"; 
    mp['8']= "1000"; 
    mp['9']= "1001"; 
    mp['A']= "1010"; 
    mp['B']= "1011"; 
    mp['C']= "1100"; 
    mp['D']= "1101"; 
    mp['E']= "1110"; 
    mp['F']= "1111"; 
    string bin=""; 
    for(int i=0; i<s.size(); i++){ 
        bin+= mp[s[i]]; 
    } 
    return bin; 
} 
string bin2hex(string s){ 
        // binary to hexadecimal conversion 
    map<string, string> mp; 
    mp["0000"]= "0"; 
    mp["0001"]= "1"; 
    mp["0010"]= "2"; 
    mp["0011"]= "3"; 
    mp["0100"]= "4"; 
    mp["0101"]= "5"; 
    mp["0110"]= "6"; 
    mp["0111"]= "7"; 
    mp["1000"]= "8"; 
    mp["1001"]= "9"; 
    mp["1010"]= "A"; 
    mp["1011"]= "B"; 
    mp["1100"]= "C"; 
    mp["1101"]= "D"; 
    mp["1110"]= "E"; 
    mp["1111"]= "F"; 
    string hex=""; 
    for(int i=0; i<s.length(); i+=4){ 
        string ch=""; 
        ch+= s[i]; 
        ch+= s[i+1]; 
        ch+= s[i+2]; 
        ch+= s[i+3]; 
        hex+= mp[ch]; 
    } 
    return hex; 
} 

string permute(string k, int* arr, int n){ 
    string per=""; 
    for(int i=0; i<n ; i++){ 
        per+= k[arr[i]-1]; 
    } 
    return per; 
} 

string binxor(string a, string b)
{
	string result = "";
	for(int i=0;i<a.length();i++)
	{
		if(a[i]==b[i])
			result += "0";
		else
			result += "1";
	}
	return result;
}

string encrypt(string plaintext, vector<string>roundkeys, vector<string>roundkeysHex)
{

	plaintext = hex2bin(plaintext);
	int ip_table[64] =
	{    58,50,42,34,26,18,10,2, 
        60,52,44,36,28,20,12,4, 
        62,54,46,38,30,22,14,6, 
        64,56,48,40,32,24,16,8, 
        57,49,41,33,25,17,9,1, 
        59,51,43,35,27,19,11,3, 
        61,53,45,37,29,21,13,5, 
        63,55,47,39,31,23,15,7 
    }; 

    plaintext= permute(plaintext, ip_table, 64);

	string lefthalf = plaintext.substr(0, 32);
    string righthalf = plaintext.substr(32);

    int expperm_box[48] =
    {
    	 32,1,2,3,4,5,4,5, 
        6,7,8,9,8,9,10,11, 
        12,13,12,13,14,15,16,17, 
        16,17,18,19,20,21,20,21, 
        22,23,24,25,24,25,26,27, 
        28,29,28,29,30,31,32,1 
    };

    int sboxes[8][4][16]= 
    {{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
  
  
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }}; 

    int perm_box[32] = 
    {
    	16,7,20,21, 
        29,12,28,17, 
        1,15,23,26, 
        5,18,31,10, 
        2,8,24,14, 
        32,27,3,9, 
        19,13,30,6, 
        22,11,4,25 
    };

    for(int i=0;i<16;i++)
    {
    	cout<<"L"<<i<<": "<<bin2hex(lefthalf)<<"\t"<<"R"<<i<<": "<<bin2hex(righthalf)<<"\tRound key: "<<roundkeysHex[i]<<endl;

    	string rightcopy = righthalf;

    	righthalf = permute(righthalf, expperm_box, 48);

    	righthalf = binxor(righthalf, roundkeys[i]);

    	string result = "";
    	for(int j=0;j<8;j++)
    	{
	   		string part = righthalf.substr(j*6, 6);
    		int row = (part[0] - '0')*2 + (part[5] - '0');
    		int col = (part[1] - '0')*8 + (part[2] - '0')*4 + (part[3] - '0')*2 + (part[4] - '0');

    		int decword = sboxes[j][row][col];
    		string word = "";
    		for(int k=0;k<4;k++)
    		{
    			int r = decword%2;
    			if(r==0)
    				word = word + "0";
    			else
    				word = word + "1";1
    			decword = decword/2;
    		}
    		reverse(word.begin(), word.end());
    		result = result + word;
    	}

    	righthalf = result;

    	righthalf = permute(righthalf, perm_box, 32);
    	righthalf = binxor(lefthalf, righthalf);

    	lefthalf = rightcopy;
    }

    swap(lefthalf, righthalf);

    cout<<"L"<<16<<": "<<bin2hex(lefthalf)<<"\t"<<"R"<<16<<": "<<bin2hex(righthalf)<<endl;
    string ciphertext;

    ciphertext = lefthalf + righthalf;

    int fp_table[64]=  
    {    40,8,48,16,56,24,64,32, 
        39,7,47,15,55,23,63,31, 
        38,6,46,14,54,22,62,30, 
        37,5,45,13,53,21,61,29, 
        36,4,44,12,52,20,60,28, 
        35,3,43,11,51,19,59,27, 
        34,2,42,10,50,18,58,26, 
        33,1,41,9,49,17,57,25 
    }; 

    ciphertext = permute(ciphertext, fp_table, 64);

    return ciphertext;

}

int main()
{
	string key = "AABB09182736CCDD";
	string plaintext = "111111BBBB222222";

	key = hex2bin(key);

	int pc1[56]=  
    {    57,49,41,33,25,17,9, 
        1,58,50,42,34,26,18, 
        10,2,59,51,43,35,27, 
        19,11,3,60,52,44,36,           
        63,55,47,39,31,23,15, 
        7,62,54,46,38,30,22, 
        14,6,61,53,45,37,29, 
        21,13,5,28,20,12,4 
    }; 

    int pc2[48]= 
    {    14,17,11,24,1,5, 
        3,28,15,6,21,10, 
        23,19,12,4,26,8, 
        16,7,27,20,13,2, 
        41,52,31,37,47,55, 
        30,40,51,45,33,48, 
        44,49,39,56,34,53, 
        46,42,50,36,29,32 
    }; 

    key = permute(key, pc1, 56);

    int lshift_table[16]= 
    {    1, 1, 2, 2, 
        2, 2, 2, 2,  
        1, 2, 2, 2,  
        2, 2, 2, 1 
    }; 
    
    vector<string> roundkeys;
    vector<string> roundkeysHex;

    //Obtain all the round keys first, decryption becomes easy
    for(int i=0;i<16;i++)
    {
    	int bits_to_lshift = lshift_table[i];

    	string left_key = key.substr(0, 28);
    	string right_key = key.substr(28);
    	
    	string shifted_left = left_key.substr(bits_to_lshift, 28-bits_to_lshift) + left_key.substr(0, bits_to_lshift);
		string shifted_right = right_key.substr(bits_to_lshift, 28-bits_to_lshift) + right_key.substr(0, bits_to_lshift);
		
		string roundkey = shifted_left + shifted_right;

		key  = roundkey;

		roundkey = permute(roundkey, pc2, 48);

		roundkeys.push_back(roundkey);
		roundkeysHex.push_back(bin2hex(roundkey));
    }

    cout<<"\nEncrypting...\n";
    string ciphertext = encrypt(plaintext, roundkeys, roundkeysHex);
    cout<<"Ciphertext is "<<bin2hex(ciphertext)<<endl;

    reverse(roundkeys.begin(), roundkeys.end());
    reverse(roundkeysHex.begin(), roundkeysHex.end());

    cout<<"\nDecrypting...\n";
    plaintext = encrypt(bin2hex(ciphertext), roundkeys, roundkeysHex);
    cout<<"Plaintext is "<<bin2hex(plaintext)<<endl;

    cout<<"Avalanche effect is thus observed. \n";
	return 0;
}