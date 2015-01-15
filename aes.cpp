#include "stdio.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <cstdlib> 
#include <sstream>
#include <iomanip>
using namespace std;

void inputbytes(string input[4][4], string block)
{
	int i,j;
	int p=0;
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			input[i][j]=block.substr(p,2);
			p+=2;				
		}
	}
}

void statearray(string state[4][4], string input[4][4])
{
	int i,j;
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			state[j][i]=input[j][i];
		}
	}
}

void outputbytes(unsigned char output[4][4], string state[4][4])
{
	int i,j,x;
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			istringstream is(state[j][i]);
			is >> hex >> x;
			output[j][i]=(unsigned char)x;
		}
	}
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
		cout << hex << uppercase << setfill('0') << setw(2) << (int)output[i][j];
		}
	}
}

void keyarray(string w[], string key, int nk)
{
	int i,j,p=0;
	for (i=0;i<nk;i++)
	{
		w[i]=key.substr(p,8);
		p+=8;
	}
}


void SubBytes(string state[4][4])
{
	string sbox[16][16]= {
	{"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
	{"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
	{"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
	{"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
	{"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
	{"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
	{"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
	{"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
	{"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
	{"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
	{"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
	{"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
	{"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
	{"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
	{"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
	{"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"},
	};	
	int i,j,k,l,x,y;
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			istringstream is(state[j][i].substr(0,1));
			is >> hex >> x;
			istringstream iss(state[j][i].substr(1,1));
			iss >> hex >> y;
			for (k=0;k<16;k++)
			{
				for (l=0;l<16;l++)
				{
					if (k==y && l==x)
					state[j][i]=sbox[l][k];
				}
			}
		}
	}	
}

void ShiftRows(string state[4][4])
{
	int i,j;
	string pom;
	pom=state[0][1];
	for (j=0;j<4;j++)
		{
			if (j==3) state[j][1]=pom;
			else state[j][1]=state[j+1][1];
		}
		
	for (i=0;i<2;i++)
	{
	pom=state[0][2];
	for (j=0;j<4;j++)
		{
			if (j==3) state[j][2]=pom;
			else state[j][2]=state[j+1][2];
		}
	}
	
	for (i=0;i<3;i++)
	{
	pom=state[0][3];
	for (j=0;j<4;j++)
		{
			if (j==3) state[j][3]=pom;
			else state[j][3]=state[j+1][3];
		}
	}
}

unsigned char mult(unsigned char liczba1, unsigned char liczba2)
{
	int i;
	unsigned char p=0;
	unsigned char przen;
	for (i=0;i<8;i++) 
	{
		if(liczba2 & 1) 
			p= p ^ liczba1;
		przen= liczba1 & 0x80; 
		liczba1= liczba1 << 1;
		if(przen!=0) 
			liczba1= liczba1 ^ 0x1b;
		liczba2= liczba2 >> 1;
	}
	return p;
}

void MixColumns(string state[4][4])
{
	int i,j,x;
	unsigned char tempstate[4][4];	
	unsigned char charstate[4][4];
	unsigned char temp, temp1, temp2, temp3;
	
	for (i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			istringstream iss(state[j][i]);
			iss >> hex >> x;
			charstate[j][i] = (unsigned char)x;
		}
	}
	
	for(i=0;i<4;i++)
	{
		
		temp=charstate[i][0];
		temp1=charstate[i][1];
		temp2=charstate[i][2];
		temp3=charstate[i][3];
		tempstate[i][0]=mult(0x02, temp) ^ mult(0x03, temp1) ^ temp2 ^ temp3;
		tempstate[i][1]=temp ^ mult(0x02, temp1) ^ mult(0x03, temp2) ^ temp3;
		tempstate[i][2]=temp ^ temp1 ^ mult(0x02, temp2) ^ mult(0x03, temp3);
		tempstate[i][3]=mult(0x03, temp) ^ temp1 ^ temp2 ^ mult (0x02, temp3);
	}
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			if(tempstate[j][i]<16)
			{
				ostringstream ss;
				ss << hex << (int)tempstate[j][i];
				state[j][i] = "0" + ss.str();
			}
			else
			{
				ostringstream ss;
				ss << hex << (int)tempstate[j][i];
				state[j][i] = ss.str();
			}
		}
	}
}

void AddRoundKey(string state[4][4], int nr, string w[], int round)
{
	int i,j,x,m=0,n=0;
	unsigned char charstate[4][4];
	unsigned char tempstate[4][4];
	unsigned char charw[4][4];
	
	for (i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			istringstream iss(state[j][i]);
			iss >> hex >> x;
			charstate[j][i] = (unsigned char)x;
		}
	}
	
	for (i=round*4;i<((round+1)*4);i++)
	{
		for (j=0;j<4;j++)
		{
			istringstream iss(w[i].substr(j*2,2));
			iss >> hex >> x;
			charw[n][j]= (unsigned char)x;
		}
		n++;
	}
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			tempstate[j][i] = charstate[j][i] ^ charw[j][i];
		}
	}
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			if(tempstate[j][i]<16)
			{
				ostringstream ss;
				ss << hex << (int)tempstate[j][i];
				state[j][i] = "0" + ss.str();
			}
			else
			{
				ostringstream ss;
				ss << hex << (int)tempstate[j][i];
				state[j][i] = ss.str();
			}
		}
	}
}

unsigned int Rcon(int i)
{
	unsigned int rcon[256] = {
0x8d000000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d};

	return rcon[i];
}


unsigned int SubWord(string el)
{
	string sbox[16][16]= {
	{"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
	{"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
	{"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
	{"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
	{"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
	{"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
	{"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
	{"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
	{"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
	{"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
	{"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
	{"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
	{"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
	{"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
	{"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
	{"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"},
	};	
	
	int j,k,l,x,y,p=0;
	string sub;
	unsigned int isub,z;

		for (j=0;j<4;j++)
		{
			istringstream is(el.substr(p,1));
			is >> hex >> x;
			istringstream iss(el.substr(p+1,1));
			iss >> hex >> y;
			for (k=0;k<16;k++)
			{
				for (l=0;l<16;l++)
				{
					if (k==y && l==x)
					sub=sub+sbox[l][k];
				}
			}
			p+=2;
		}
		
	istringstream iss(sub);
	iss >> hex >> z;
	isub = z;
	
	return isub;
}

string RotWord(string el)
{
	string rot;
	
	rot = el.substr(2,6) + el.substr(0,2);
	
	return rot;
}

void KeyExpansion(string w[], int nk, string key, int nr)
{
	unsigned int temp, temp2, temp3;
	unsigned int x;
	string s;
	int i,j;
	keyarray(w, key, nk);
	
	i=nk;
	
	while (i < 4*(nr+1))
	{
		istringstream iss(w[i]);
		iss >> hex >> x;
		temp2=x;
		
		istringstream is(w[i-1]);
		is >> hex >> x;
		temp=x;
		
		istringstream isss(w[i-nk]);
		isss >> hex >> x;
		temp3=x;
		
		if (i%nk==0)
			{
				temp = SubWord(RotWord(w[i-1])) ^ Rcon(i/nk);
			}
		else 
			{
				if((nk>6) && (i%nk==4))
				{
					temp = SubWord(w[i-1]);
				}
			}
		temp2 = temp3 ^ temp;

		ostringstream ss;
		ss << hex << temp2;
		s=ss.str();
		if(s.length()<8)
			{
				for(j=8-s.length();j>0;j--)
				{
					w[i] = w[i].append("0");
				}
				w[i] = w[i].append(ss.str());
			}
		else
			w[i] = ss.str();
		i++;
	}
	
}
void Cipher(string state[4][4], unsigned char output[4][4], string w[], int nr)
{
	int round;
	AddRoundKey(state, nr, w, 0);
	
	for (round=1;round<nr;round++)
		{
			SubBytes(state);
			ShiftRows(state);
			MixColumns(state);
			AddRoundKey(state, nr, w, round);
		}
	
	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, nr, w, round);
	
	outputbytes(output, state);
}



////////////////////////////////////////////DESZYFROWANIE////////////////////////////////////////////////////

void InvSubBytes(string state[4][4])
{
	string sbox[16][16] = {   
    {"52", "09", "6a", "d5", "30", "36", "a5", "38", "bf", "40", "a3", "9e", "81", "f3", "d7", "fb"},  
    {"7c", "e3", "39", "82", "9b", "2f", "ff", "87", "34", "8e", "43", "44", "c4", "de", "e9", "cb"},   
    {"54", "7b", "94", "32", "a6", "c2", "23", "3d", "ee", "4c", "95", "0b", "42", "fa", "c3", "4e"},   
    {"08", "2e", "a1", "66", "28", "d9", "24", "b2", "76", "5b", "a2", "49", "6d", "8b", "d1", "25"},   
    {"72", "f8", "f6", "64", "86", "68", "98", "16", "d4", "a4", "5c", "cc", "5d", "65", "b6", "92"},   
    {"6c", "70", "48", "50", "fd", "ed", "b9", "da", "5e", "15", "46", "57", "a7", "8d", "9d", "84"},   
    {"90", "d8", "ab", "00", "8c", "bc", "d3", "0a", "f7", "e4", "58", "05", "b8", "b3", "45", "06"},   
    {"d0", "2c", "1e", "8f", "ca", "3f", "0f", "02", "c1", "af", "bd", "03", "01", "13", "8a", "6b"},   
    {"3a", "91", "11", "41", "4f", "67", "dc", "ea", "97", "f2", "cf", "ce", "f0", "b4", "e6", "73"},   
    {"96", "ac", "74", "22", "e7", "ad", "35", "85", "e2", "f9", "37", "e8", "1c", "75", "df", "6e"},   
    {"47", "f1", "1a", "71", "1d", "29", "c5", "89", "6f", "b7", "62", "0e", "aa", "18", "be", "1b"},   
    {"fc", "56", "3e", "4b", "c6", "d2", "79", "20", "9a", "db", "c0", "fe", "78", "cd", "5a", "f4"},   
    {"1f", "dd", "a8", "33", "88", "07", "c7", "31", "b1", "12", "10", "59", "27", "80", "ec", "5f"},   
    {"60", "51", "7f", "a9", "19", "b5", "4a", "0d", "2d", "e5", "7a", "9f", "93", "c9", "9c", "ef"},   
    {"a0", "e0", "3b", "4d", "ae", "2a", "f5", "b0", "c8", "eb", "bb", "3c", "83", "53", "99", "61"},   
    {"17", "2b", "04", "7e", "ba", "77", "d6", "26", "e1", "69", "14", "63", "55", "21", "0c", "7d"}
	};
	
	int i,j,k,l,x,y;
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			istringstream is(state[j][i].substr(0,1));
			is >> hex >> x;
			istringstream iss(state[j][i].substr(1,1));
			iss >> hex >> y;
			for (k=0;k<16;k++)
			{
				for (l=0;l<16;l++)
				{
					if (k==y && l==x)
					state[j][i]=sbox[l][k];
				}
			}
		}
	}
}

void InvShiftRows(string state[4][4])
{
	int i,j;
	string pom;
	pom=state[3][1];
	for (j=3;j>=0;j--)
		{
			if (j==0) state[j][1]=pom;
			else state[j][1]=state[j-1][1];
		}
		
	for (i=0;i<2;i++)
	{
	pom=state[3][2];
	for (j=3;j>=0;j--)
		{
			if (j==0) state[j][2]=pom;
			else state[j][2]=state[j-1][2];
		}
	}
	
	for (i=0;i<3;i++)
	{
	pom=state[3][3];
	for (j=3;j>=0;j--)
		{
			if (j==0) state[j][3]=pom;
			else state[j][3]=state[j-1][3];
		}
	}
}	

void InvMixColumns(string state[4][4])
{
	int i,j,x;
	unsigned char charstate[4][4];
	unsigned char tempstate[4][4];
	unsigned char temp, temp1, temp2, temp3;
	
	for (i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			istringstream iss(state[j][i]);
			iss >> hex >> x;
			charstate[j][i] = (unsigned char)x;
		}
	}
	
	for(i=0;i<4;i++)
	{
		
		temp=charstate[i][0];
		temp1=charstate[i][1];
		temp2=charstate[i][2];
		temp3=charstate[i][3];
		tempstate[i][0]=mult(0x0e, temp) ^ mult(0x0b, temp1) ^ mult(0x0d, temp2) ^ mult(0x09, temp3);
		tempstate[i][1]=mult(0x09, temp) ^ mult(0x0e, temp1) ^ mult(0x0b, temp2) ^ mult(0x0d, temp3);
		tempstate[i][2]=mult(0x0d, temp) ^ mult(0x09, temp1) ^ mult(0x0e, temp2) ^ mult(0x0b, temp3);
		tempstate[i][3]=mult(0x0b, temp) ^ mult(0x0d, temp1) ^ mult(0x09, temp2) ^ mult(0x0e, temp3);
	}
	
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			if(tempstate[j][i]<16)
			{
				ostringstream ss;
				ss << hex << (int)tempstate[j][i];
				state[j][i] = "0" + ss.str();
			}
			else
			{
				ostringstream ss;
				ss << hex << (int)tempstate[j][i];
				state[j][i] = ss.str();
			}
		}
	}
}

void InvCipher(string state[4][4], unsigned char output[4][4], string w[], int nr)
{
	int round;
	round=nr;
	AddRoundKey(state, nr, w, round);
	
	for(int i=round-1;i>0;i--)
	{
		InvShiftRows(state);
		InvSubBytes(state);
		AddRoundKey(state, nr, w, i);
		InvMixColumns(state);
	}
	
	InvShiftRows(state);
	InvSubBytes(state);
	AddRoundKey(state, nr, w, 0);
	
	outputbytes(output, state);
}






//////////////////////////////////////////MAIN///////////////////////////////////////////

int main(int argc, char *argv[])
{
	string mode, length, key, block;
	string input[4][4];
	string state[4][4];
	unsigned char output[4][4];
	int NK,NR;
	
	mode = argv[1];
	length = argv[2];
	key = argv[3];
	block = argv[4];
	
	if(length=="L128")
	{
		NK=4;
		NR=10;
	}
	
	if(length=="L192")
	{
		NK=6;
		NR=12;
	}
	
	if(length=="L256")
	{
		NK=8;
		NR=14;
	}
	
	string w[4*(NR+1)];
	
	if(mode=="E")
	{
	inputbytes(input, block);
	statearray(state, input);
	keyarray(w, key, NK);
	KeyExpansion(w, NK, key, NR);
	Cipher(state, output, w, NR);
	}
	
	if(mode=="D")
	{
	inputbytes(input, block);
	statearray(state, input);
	keyarray(w, key, NK);
	KeyExpansion(w, NK, key, NR);
	InvCipher(state, output, w, NR);
	}
	
	return 0;
}
