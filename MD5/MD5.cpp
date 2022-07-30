//============================================================================
// Name        : MD5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "md5_headers.h"
using namespace std;

void str_to_arr(string input, it* res){
	//To initialize the arr(transform data-type)
	int len = input.length();
	for(int i = 0;i < len;i ++){
		res[i] = input[i] - '0';
	}
	return;
}
void fulfill_inp(it* inp, int len, int* res){
	//To initialize the res-arr
	int N = len / 512;
	//cout<<"M:"<<N<<endl;
	//int R = len / 512;
	int len2 = (N+1)*512;
	it* tmp = new it[len2];
	for(int i = N*512;i < len2;i ++){
		if(i < len){
			tmp[i] = inp[i - N*512];
		}
		else if(i == len){
			tmp[i] = 1;
		}
		else if(i>len && i<448){
			tmp[i] = 0;
		}
		else{
			tmp[i] = inp[len - i];
		}
	}
	res = tmp;
}
void bin2hex(it* inp, string res, int len){

}
string find_chart(char x){
	string arr;
	switch(x){
	case'0':arr = "0000";break;
	case'1':arr = "0001";break;
	case'2':arr = "0010";break;
	case'3':arr = "0011";break;
	case'4':arr = "0100";break;
	case'5':arr = "0101";break;
	case'6':arr = "0110";break;
	case'7':arr = "0111";break;
	case'8':arr = "1000";break;
	case'9':arr = "1001";break;
	case'a':arr = "1010";break;
	case'b':arr = "1011";break;
	case'c':arr = "1100";break;
	case'd':arr = "1101";break;
	case'e':arr = "1110";break;
	case'f':arr = "1111";break;
	}
	return arr;
}
void chart_find(it* inp){

}
void hex2bin(string hex, it* inp, int len){
	for(int i = 2;i < len;i ++){
		for(int j = 0;j < 4;j ++)
			inp[i] = find_chart(hex[i])[j] - '0';
	}

}
void func_F(it*x, it*y, it*z, it*res, int len){
	it tmp1[64], tmp2[64], tmp3[64];
	and_op(x ,y ,len, tmp1);
	not_op(x, len, tmp2);
	and_op(tmp2, z, len, tmp3);
	or_op(tmp1, tmp3, len, res);
	//Release the room
}
void func_G(it*x, it*y, it*z, it*res, int len){
	it tmp1[64], tmp2[64], tmp3[64];
	and_op(x ,z ,len, tmp1);
	not_op(z, len, tmp2);
	and_op(tmp2, y, len, tmp3);
	or_op(tmp1, tmp3, len, res);
	//Release the room

}
void func_H(it*x, it*y, it*z, it*res, int len){
	it tmp1[64];
	xor_op(z, y, len, tmp1);
	xor_op(tmp1, z, len, res);
}
void func_I(it*x, it*y, it*z, it*res, int len){
	it tmp1[64], tmp2[64];
	not_op(z, len ,tmp1);
	or_op(tmp1, x, len, tmp2);
	xor_op(tmp1, tmp2, len, res);
	//Release the room
}
void and_op(int* a, int* b, int len, int* res){
	for(int i = 0;i < len;i ++){
		if(a[i] == 0 || b[i] == 0)
			res[i] = 0;
		else
			res[i] = 1;
	}
}
void not_op(int* a, int len, int* res){
	for(int i = 0;i < len;i ++){
		if(a[i] == 1)
			res[i] = 0;
		else
			res[i] = 1;
	}
}
void xor_op(int* a, int* b, int len, int* res){
	for(int i = 0;i < len;i ++){
		if(a[i] == b[i])
			res[i] = 0;
		else
			res[i] = 1;
	}

}
void or_op(int* a, int* b, int len, int* res){
	for(int i = 0;i < len;i ++){
			if(a[i] == 1 || b[i] == 1)
				res[i] = 1;
			else
				res[i] = 0;
		}
}
void left_loop(it* inp, int len, int s){
	it tmp1 = inp[0];
	for(int j = 0; j < s; j ++){
		for(int i = 0; i < len - 1;i ++){
			inp[i] = inp[i+1];
		}
		inp[len] = tmp1;
	}
}
bool add_op(int* a, int* b, int* res, int len){
	//A normal bin-add worker
	for(int i  = 0; i < len;i ++){
		res[i] = a[i] & b[i];
	}
	if(a[len - 1] && b[len - 1] == 1){
		//Check
		return 1;
	}
	else{
		return 0;
	}
}
string bin2hex(it* inp, int len){
	string tmp;
	for(int i = 0; i < len; i ++){
		tmp += inp[i] + "";
	}
	return tmp;
}
void func_FF(it *a, it* b, it* c, it* d, it* Mi, int si, it* ti_bin, int len){
	it tmp1[64], tmp2[64];
	func_F(b, c, d, tmp1, len);
	it num1 = 0,num2 = 0;
	for(int i = 0;i < len;i ++){
		num1 = a[i] + tmp1[i];
/*
		cout<<Mi[i]<<endl;
		cout<<ti_bin[i]<<endl;
*/
		num2 = Mi[i] + ti_bin[i];
		tmp2[i] = num1 + num2;
	}
	left_loop(tmp2, len, si);
	add_op(b, tmp2, a, len);
	//Release the room
}
void func_GG(it *a, it* b, it* c, it* d, it* Mi, int si, it* ti_bin, int len){
	it tmp1[64], tmp2[64];
		func_G(b, c, d, tmp1, len);
		it num1 = 0,num2 = 0;
		for(int i = 0;i < len;i ++){
			num1 = a[i] + tmp1[i];
			num2 = Mi[i] + ti_bin[i];
			tmp2[i] = num1 + num2;
		}
		left_loop(tmp2, len, si);
		add_op(b, tmp2, a, len);
		//Release the room
}
void func_HH(it *a, it* b, it* c, it* d, it* Mi, int si, it* ti_bin, int len){
	it tmp1[64], tmp2[64];
		func_H(b, c, d, tmp1, len);
		it num1 = 0,num2 = 0;
		for(int i = 0;i < len;i ++){
			num1 = a[i] + tmp1[i];
			num2 = Mi[i] + ti_bin[i];
			tmp2[i] = num1 + num2;
		}
		left_loop(tmp2, len, si);
		add_op(b, tmp2, a, len);
		//Release the room
}
void func_II(it *a, it* b, it* c, it* d, it* Mi, int si, it* ti_bin, int len){
	it tmp1[64], tmp2[64];
		func_I(b, c, d, tmp1, len);
		it num1 = 0,num2 = 0;
		for(int i = 0;i < len;i ++){
			num1 = a[i] + tmp1[i];
			num2 = Mi[i] + ti_bin[i];
			tmp2[i] = num1 + num2;
		}
		left_loop(tmp2, len, si);
		add_op(b, tmp2, a, len);
		//Release the room
}
string md5_encode(string plaintext){
	//Initialize the data
		int len1 = plaintext.length();
		int len = len1 * 4;
		it* inp = new it[len];
		hex2bin(plaintext, inp, len);
/*
		for(int i = 0; i < len; i ++)
				cout<<inp[i];
*/
		//Fulfill and classify the input
		int M[16][32];

		int N = len % 512;
		it* res = new it[(N + 1) * 512];

		fulfill_inp(inp, len, res);

		for(int i = 0; i < len; i ++)
				cout<<inp[i];

		/*initial M*/
		for(int i = 0; i < 16; i ++){
			for(int j = 0; j < 32; j ++){
				//cout<<res[i * 32 + j];
				M[i][j] = res[i * 32 + j];
			}
		}

		it* ti_bin = new it[len];
		it* a = new it[32];
		it* b = new it[32];
		it* c = new it[32];
		it* d = new it[32];
		string init[4] = {"0x1234567", "0x89abcdef", "0xfedcba98", "0x76543210"};
		hex2bin(init[0], a, len);
		hex2bin(init[1], b, len);
		hex2bin(init[2], c, len);
		hex2bin(init[3], d, len);
		hex2bin(ti[0], ti_bin, len);
	 	//For the part 1
		func_FF(a, b, c, d, M[0], s[0], ti_bin, len);
		hex2bin(ti[1], ti_bin, len);
		func_FF(d, a, b, c, M[1], s[1], ti_bin, len);
		hex2bin(ti[2], ti_bin, len);
		func_FF(c, d, a, b, M[2], s[2], ti_bin, len);
		hex2bin(ti[3], ti_bin, len);
		func_FF(b, c, d, a, M[3], s[3], ti_bin, len);
		hex2bin(ti[4], ti_bin, len);
		func_FF(a, b, c, d, M[4], s[4], ti_bin, len);
		hex2bin(ti[4], ti_bin, len);
		func_FF(d, a, b, c, M[5], s[5], ti_bin, len);
		hex2bin(ti[6], ti_bin, len);
		func_FF(c, d, a, b, M[6], s[6], ti_bin, len);
		hex2bin(ti[7], ti_bin, len);
		func_FF(b, c, d, a, M[7], s[7], ti_bin, len);
		hex2bin(ti[8], ti_bin, len);
		func_FF(a, b, c, d, M[8], s[8], ti_bin, len);
		hex2bin(ti[9], ti_bin, len);
		func_FF(d, a, b, c, M[9], s[9], ti_bin, len);
		hex2bin(ti[10], ti_bin, len);
		func_FF(c, d, a, b, M[10], s[10], ti_bin, len);
		hex2bin(ti[11], ti_bin, len);
		func_FF(b, c, d, a, M[11], s[11], ti_bin, len);
		hex2bin(ti[12], ti_bin, len);
		func_FF(a, b, c, d, M[12], s[12], ti_bin, len);
		hex2bin(ti[13], ti_bin, len);
		func_FF(d, a, b, c, M[13], s[13], ti_bin, len);
		hex2bin(ti[14], ti_bin, len);
		func_FF(c, d, a, b, M[14], s[14], ti_bin, len);
		hex2bin(ti[15], ti_bin, len);
		func_FF(b, c, d, a, M[15], s[15], ti_bin, len);
		//For the part 2
		hex2bin(ti[16], ti_bin, len);
		func_GG(a, b, c, d, M[0], s[16], ti_bin, len);
		hex2bin(ti[17], ti_bin, len);
		func_GG(d, a, b, c, M[1], s[17], ti_bin, len);
		hex2bin(ti[18], ti_bin, len);
		func_GG(c, d, a, b, M[2], s[18], ti_bin, len);
		hex2bin(ti[19], ti_bin, len);
		func_GG(b, c, d, a, M[3], s[19], ti_bin, len);
		hex2bin(ti[20], ti_bin, len);
		func_GG(a, b, c, d, M[4], s[20], ti_bin, len);
		hex2bin(ti[21], ti_bin, len);
		func_GG(d, a, b, c, M[5], s[21], ti_bin, len);
		hex2bin(ti[22], ti_bin, len);
		func_GG(c, d, a, b, M[6], s[22], ti_bin, len);
		hex2bin(ti[23], ti_bin, len);
		func_GG(b, c, d, a, M[7], s[23], ti_bin, len);
		hex2bin(ti[24], ti_bin, len);
		func_GG(a, b, c, d, M[8], s[24], ti_bin, len);
		hex2bin(ti[25], ti_bin, len);
		func_GG(d, a, b, c, M[9], s[25], ti_bin, len);
		hex2bin(ti[26], ti_bin, len);
		func_GG(c, d, a, b, M[10], s[26], ti_bin, len);
		hex2bin(ti[27], ti_bin, len);
		func_GG(b, c, d, a, M[11], s[27], ti_bin, len);
		hex2bin(ti[28], ti_bin, len);
		func_GG(a, b, c, d, M[12], s[28], ti_bin, len);
		hex2bin(ti[29], ti_bin, len);
		func_GG(d, a, b, c, M[13], s[29], ti_bin, len);
		hex2bin(ti[30], ti_bin, len);
		func_GG(c, d, a, b, M[14], s[30], ti_bin, len);
		hex2bin(ti[31], ti_bin, len);
		func_GG(b, c, d, a, M[15], s[31], ti_bin, len);
		hex2bin(ti[32], ti_bin, len);
		//For the part 3
		func_HH(a, b, c, d, M[0], s[32], ti_bin, len);
		hex2bin(ti[33], ti_bin, len);
		func_HH(d, a, b, c, M[1], s[33], ti_bin, len);
		hex2bin(ti[34], ti_bin, len);
		func_HH(c, d, a, b, M[2], s[34], ti_bin, len);
		hex2bin(ti[35], ti_bin, len);
		func_HH(b, c, d, a, M[3], s[35], ti_bin, len);
		hex2bin(ti[36], ti_bin, len);
		func_HH(a, b, c, d, M[4], s[36], ti_bin, len);
		hex2bin(ti[37], ti_bin, len);
		func_HH(d, a, b, c, M[5], s[37], ti_bin, len);
		hex2bin(ti[38], ti_bin, len);
		func_HH(c, d, a, b, M[6], s[38], ti_bin, len);
		hex2bin(ti[39], ti_bin, len);
		func_HH(b, c, d, a, M[7], s[39], ti_bin, len);
		hex2bin(ti[40], ti_bin, len);
		func_HH(a, b, c, d, M[8], s[40], ti_bin, len);
		hex2bin(ti[41], ti_bin, len);
		func_HH(d, a, b, c, M[9], s[41], ti_bin, len);
		hex2bin(ti[42], ti_bin, len);
		func_HH(c, d, a, b, M[10], s[42], ti_bin, len);
		hex2bin(ti[43], ti_bin, len);
		func_HH(b, c, d, a, M[11], s[43], ti_bin, len);
		hex2bin(ti[44], ti_bin, len);
		func_HH(a, b, c, d, M[12], s[44], ti_bin, len);
		hex2bin(ti[45], ti_bin, len);
		func_HH(d, a, b, c, M[13], s[45], ti_bin, len);
		hex2bin(ti[46], ti_bin, len);
		func_HH(c, d, a, b, M[14], s[46], ti_bin, len);
		hex2bin(ti[47], ti_bin, len);
		func_HH(b, c, d, a, M[15], s[47], ti_bin, len);
		hex2bin(ti[48], ti_bin, len);
		//For the part 4
		func_II(a, b, c, d, M[0], s[48], ti_bin, len);
		hex2bin(ti[49], ti_bin, len);
		func_II(d, a, b, c, M[1], s[49], ti_bin, len);
		hex2bin(ti[50], ti_bin, len);
		func_II(c, d, a, b, M[2], s[50], ti_bin, len);
		hex2bin(ti[51], ti_bin, len);
		func_II(b, c, d, a, M[3], s[51], ti_bin, len);
		hex2bin(ti[52], ti_bin, len);
		func_II(a, b, c, d, M[4], s[52], ti_bin, len);
		hex2bin(ti[53], ti_bin, len);
		func_II(d, a, b, c, M[5], s[53], ti_bin, len);
		hex2bin(ti[54], ti_bin, len);
		func_II(c, d, a, b, M[6], s[54], ti_bin, len);
		hex2bin(ti[55], ti_bin, len);
		func_II(b, c, d, a, M[7], s[55], ti_bin, len);
		hex2bin(ti[56], ti_bin, len);
		func_II(a, b, c, d, M[8], s[56], ti_bin, len);
		hex2bin(ti[57], ti_bin, len);
		func_II(d, a, b, c, M[9], s[57], ti_bin, len);
		hex2bin(ti[58], ti_bin, len);
		func_II(c, d, a, b, M[10], s[58], ti_bin, len);
		hex2bin(ti[59], ti_bin, len);
		func_II(b, c, d, a, M[11], s[59], ti_bin, len);
		hex2bin(ti[60], ti_bin, len);
		func_II(a, b, c, d, M[12], s[60], ti_bin, len);
		hex2bin(ti[61], ti_bin, len);
		func_II(d, a, b, c, M[13], s[61], ti_bin, len);
		hex2bin(ti[62], ti_bin, len);
		func_II(c, d, a, b, M[14], s[62], ti_bin, len);
		hex2bin(ti[63], ti_bin, len);
		func_II(b, c, d, a, M[15], s[63], ti_bin, len);

		//Print the result
		it* binres = new it[len* 4];
		for(int i = 0 ; i < len * 4; i ++){
			if(i < len)
				binres[i] = a[i];
			else if(i > len && i < 2 * len)
				binres[i] = b[i];
			else if(i > 2 * len && i < 3 * len)
				binres[i] = c[i];
			else
				binres[i] = d[i];
		}
		//Release the room
		string resul = bin2hex(binres, len * 4);
		return resul;
}
int getndex(char ch){
	 if(ch >= '0' && ch <= '9'){
	        return ch - '0';
	    }
	    if(ch >= 'A' && ch <='F') {
	        return ch - 'A' + 10;
	    }
	    if(ch >= 'a' && ch <= 'f'){
	        return ch - 'a' + 10;
	    }
	    return -1;
}
int hex2dec(string x){
	int res = 0;
	int len = x.length(), tmp = 1;
	for(int i = len - 1; i >= 0; i --){
		res += tmp * getndex(x[i]);
		tmp *= 16;
	}
	return res;
}
string padding_inp(string inp, int inplen, int wrstrlen){
		//int N = inplen % 512;
	int len = inp.length() * 8;
	int N = inplen % 512;
	if(N == 0){
		if(N < 448){
			inplen = len + 448 - N;
		}
		else{
			inplen = len + 512 - (N - 448);
		}
	}
	if(wrstrlen == 0)
		wrstrlen = inplen;
	int strlen = (inplen / 8) + 8;
	int i;
	string str;
	str.resize(strlen, '\0');
	int len2 = inp.length();
	for(i = 0 ; i < len2; i ++){
		str[i] = inp[i];
	}
	str[i ++] = 0x80;
	for(; i < strlen - 8; i ++){
		str[i ++] = 0;
	}
	for(i = strlen - 8; i < strlen; i ++, wrstrlen >>= 8){
		str[i] = 0xFF & wrstrlen;
	}
	return str;
}
void length_expand_attc(string inp, string append){
	string md5code = md5_encode(inp);
	it*  vec = new it[32];
	int i, j;
	for(i = 0; i < 32; i += 8){
		vec[i] = 0;
		for(j = 6; j >= 0; j-=2){
			vec[i] = 8;
			vec[i] = hex2dec(md5code.substr(i + j, 2));
		}
	}
	string padding_str = padding_inp(inp, 0, 0) + append;
	string res_mayb = padding_inp(append, 448, padding_str.length() * 8);
	//str is the md5 code that we guess!
}
int main(){
	md5_encode("0123456789abcdef");
	cout<<"Hello world!"<<endl;
	return 0;
}

