/* C167227 CNS LAB CYCLE -1 ASSIGNMENT - Hill Cipher*/
#include <iostream> 
#include <bits/stdc++.h>

using namespace std;

int main()
{
	char table[5][5];
	string key, plaintext;
	int k = 0, a = 0;
	int key_ran_out = 0;

	cout<<"Enter the key: ";
	cin>>key;

	string alphabets = "abcdefghiklmnopqrstuvwxyz";

	cout<<"\nKey Table: \n";
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(!key_ran_out)
			{
				table[i][j] = key[k];
				alphabets.erase(alphabets.find(key[k]), 1);
				k++;
			}
			else
			{
				table[i][j] = alphabets[a++];
			}

			if(k==key.length())
			{
				key_ran_out = 1; 
			}

			cout<<table[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<"\nEnter the plaintext: ";
	cin>>plaintext;

	if(plaintext.length()%2==1)
	{
		plaintext = plaintext + "z";
	}

	vector<string> digrams;

	for(int i=0;i<plaintext.length()-1;i+=2)
	{
		string digram;
		digram.push_back(plaintext[i]);
		digram.push_back(plaintext[i+1]);
		digrams.push_back(digram);
	}

	string ciphertext = "";

	for(vector<string>::iterator it = digrams.begin();it!=digrams.end();it++)
	{
		string digram = *it;
		string encrypted_digram;
		char first = digram[0];
		char second = digram[1];

		int first_i, second_i, first_j, second_j;
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				if(first==table[i][j])
				{
					first_i = i;
					first_j = j;
				}

				if(second==table[i][j])
				{
					second_i = i;
					second_j = j;
				}
			}
		}

		if(first_j==second_j)
		{
			encrypted_digram.push_back(table[(first_i + 1)%5][first_j]);
			encrypted_digram.push_back(table[(second_i + 1)%5][second_j]);
		}
		else if(first_i==second_i)
		{
			encrypted_digram.push_back(table[first_i ][(first_j + 1)%5]);
			encrypted_digram.push_back(table[second_i][(second_j + 1)%5]);
		}
		else
		{
			encrypted_digram.push_back(table[first_i][second_j]);
			encrypted_digram.push_back(table[second_i][first_j]);
		}

		ciphertext = ciphertext + encrypted_digram;
	}

	cout<<"Enciphering...\n";
	cout<<"Ciphertext is "<<ciphertext<<endl;
}