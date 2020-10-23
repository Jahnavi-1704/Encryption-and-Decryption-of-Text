/*
 * project2.cpp
 *
 *  Created on: 02-Nov-2019
 *      Author: Jahnavi Shah
 */
#include<iostream>
#include<cctype>
#include<stdlib.h>
#include<cassert>
#include<string.h>
#include<cmath>
char *encode(char *plaintext,unsigned long key);
char *decode(char *cihpertext,unsigned long key);



char *encode(char *plaintext, unsigned long key)
{
	int len=strlen(plaintext);

	int n;
	if(len%4!=0)
		n=4-(len%4);
	else
		n=0;


	unsigned char *ciphertext=new unsigned char[len+n]{};
	unsigned char *newarr=new unsigned char[len+n]{};

	for(int i=0;i<len;i++)
	{
		newarr[i]=plaintext[i];
	}


	for(int i=0;i<n;i++)
	{
		newarr[len+i]='\0';
		ciphertext[len+i]='\0';
	}


	int temp1,temp2,k,r,R;
	bool *key1=new bool[64];
	for(int l=0;l<64;l++)
	{
		key1[l]=key%2;
		key=key/2;
	}

	unsigned char *S=new unsigned char[256];
	for(int l=0;l<256;l++)
		S[l]=l;

	int i=0,j=0;
	for(int l=0;l<256;l++)
	{
		k=i%64;
		j=(j+S[i]+key1[k])%256;
		temp1=S[i];
		S[i]=S[j];
		S[j]=temp1;
		i++;
		i=i%256;
	}

	for(int l=0;l<len+n;l++)
	{
		i++;
		i=i%256;
		j=(j+S[i])%256;
		temp2=S[i];
		S[i]=S[j];
		S[j]=temp2;
		r=(S[i]+S[j])%256;
		R=S[r];
		ciphertext[l]=newarr[l]^R;
	}


	unsigned int sum=0;
	int v=0,a=4,m,s=0;

	int x=(len+n)/4;
	std::cout << "x is : " << x << std::endl;
	char* y = new char [(5*x)+1]{};

	for(int i=0;i<x;i++)
	{
		a=4+5*s;
		for(int j=0;j<4;j++)
		{
			if(j==3)
				sum=sum+ciphertext[j+v];
			else
				sum=(sum+ciphertext[j+v]) << (8U);
		}

		for(int u=0;u<5;u++)
		{
			m=sum%85;
			sum=sum/85;
			y[a]=m+'!';
			a--;
		}

		v=v+4;
		s++;
	}



	std::cout<<"After encoding and taking the armour:";


	char *h=new char[(5*x)+1];
	for(int i=0;i<(5*x);i++)
		h[i] = y[i];

	h[5*x]='\0';

	return (h);

}

char *decode(char *cihpertext,unsigned long key)
{
	int len=strlen(cihpertext);

	for(int i=0;i<len;i++)
	{
		cihpertext[i]=cihpertext[i]-'!';
	}


	int v=0,n=0;

	int x=len/5;

	unsigned char *plaintext=new unsigned char[4*x];

	for(int i=0;i<x;i++)
	{
		int y=4;
		unsigned int sum=0;
		for(int j=0;j<5;j++)
		{
			sum=sum+(cihpertext[j+v]*pow(85,y));
			y--;
		}
		v=v+5;

		for(int i=0;i<4;i++)
		{
			if(i==0)
				plaintext[i+n]=(sum) >> (24U);
			else if(i==1)
				plaintext[i+n]=(sum<<8) >> (24U);
			else if(i==2)
				plaintext[i+n]=(sum<<16) >> (24U);
			else if(i==3)
				plaintext[i+n]=(sum<<24) >> (24U);
		}
		n=n+4;
	}



	int temp1,temp2,k,r,R;
	bool *key1=new bool[64];
	for(int l=0;l<64;l++)
	{
		key1[l]=key%2;
		key=key/2;
	}

	unsigned char *S=new unsigned char[256];
	for(int l=0;l<256;l++)
		S[l]=l;

	int i=0,j=0;
	for(int l=0;l<256;l++)
	{
		k=i%64;
		j=(j+S[i]+key1[k])%256;
		temp1=S[i];
		S[i]=S[j];
		S[j]=temp1;
		i++;
		i=i%256;
	}

	char *y=new char[4*x];

	for(int l=0;l<(4*x);l++)
	{
		i++;
		i=i%256;
		j=(j+S[i])%256;
		temp2=S[i];
		S[i]=S[j];
		S[j]=temp2;
		r=(S[i]+S[j])%256;
		R=S[r];
		y[l]=plaintext[l]^R;
	}



	std::cout<<std::endl;

	std::cout<<"The original text is:";

	char *g=new char[(4*x)+1];
	for(int i=0;i<(4*x);i++)
		g[i]= y[i];

	g[4*x]='\0';

	return (g);
}

#ifndef MARMOSET_TESTING
int main()
{
	long key{89963221};
	char str0[]{"Sometimes, you're in the right\" " "\n\"place, at the right time, with \"" "\n\"the right knowledge to wave at \"" "\n\"the Street View camera"};

	char *str1{encode(str0,key)};
	std::cout<<str1;


	std::cout<<std::endl;


    char *str2{decode(str1,key)};
    std::cout<<str2;


    return 0;

}
#endif
