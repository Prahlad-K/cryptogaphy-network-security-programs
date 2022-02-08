#include <bits/stdc++.h>

using namespace std;

string binary(int n)
{
	string res= "";
	while(n>0)
	{
		int r = n%2;
		if(r == 0)
			res+= "0";
		else
			res += "1";
		n= n/2;
	}
	reverse(res.begin(), res.end());
	return res;
}

int main()
{
	int state = 1;

	int fp;
	int no_of_bits;

	cin>>no_of_bits>>fp;

	int period = pow(2, no_of_bits) -1;
	cout<<period<<endl;
	for(int i=0;i<period;i++)
	{
		state = state & period;
		int next_state = state >> 1;
		int output = state & 1;
		int xor_output = 0;

		int fp_copy = fp;
		int state_copy = state;
		while(state >0)
		{
			if(fp & 1 == 1)
				xor_output ^= (state & 1);
			fp = fp >> 1; 
			state = state >> 1;
		}
		fp= fp_copy;
		state = state_copy;

		if(xor_output)
			next_state = next_state | (int)(pow(2, no_of_bits - 1));
		cout<<binary(state)<<" "<<output<<endl;
		state = next_state;
	}
	cout<<"Last state: "<<state<<endl;
}