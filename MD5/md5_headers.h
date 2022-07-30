/*
 * md5_headers.h
 *
 *  Created on: Jul 19, 2022
 *      Author: gg
 */

#ifndef MD5_HEADERS_H_
#define MD5_HEADERS_H_

#include<iostream>
#include<string>
#include<thread>
using namespace std;

typedef int it;
typedef string str;

//The initial var
string ti[64] = {
		//FF
		"0xd76aa478",
	  	"0xe8c7b756",
	  	"0x242070db",
		"0xc1bdceee",
		"0xf57c0faf",
		"0x4787c62a",
		"0xa8304613",
		"0xfd469501",
		"0x698098d8",
		"0x8b44f7af",
		"0xffff5bb1",
		"0x895cd7be",
		"0x6b901122",
		"0xfd987193",
		"0xa679438e",
		"0x49b40821",
		//GG
		"0xf61e2562",
		"0xc040b340",
		"0x265e5a51",
		"0xe9b6c7aa",
		"0xd62f105d",
		"0xd8a1e681",
		"0xe7d3fbc8",
		"0x21e1cde6",
		"0xc33707d6",
		"0xf4d50d87",
		"0xa9e3e905",
		"0xfcefa3f8",
		"0x676f02d9",
		"0x8d2a4c8a",
		//HH
		"0xfffa3942",
		"0x8771f681",
		"0x6d9d6122",
		"0xfde5380c",
		"0xa4beea44",
		"0x4bdecfa9",
		"0xf6bb4b60",
		"0xbebfbc70",
		"0x289b7ec6",
		"0xeaa127fa",
		"0xd4ef3085",
		"0x04881d05",
		"0xd9d4d039",
		"0xe6db99e5",
		"0x1fa27cf8",
		"0xc4ac5665",
		//II
		"0xf4292244",
		"0x432aff97",
		"0xab9423a7",
		"0xfc93a039",
		"0x655b59c3",
		"0x8f0ccc92",
		"0xffeff47d",
		"0x85845dd1",
		"0x6fa87e4f",
		"0xfe2ce6e0",
		"0xa3014314",
		"0x4e0811a1",
		"0xf7537e82",
		"0xbd3af235",
		"0x2ad7d2bb",
		"0xeb86d391"
};
int s[64] = { 
			7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
			12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14,
			20,5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4,
			11, 16, 23, 4, 11, 16, 23, 6, 10,15, 21, 6, 10, 15,
			21, 6, 10, 15, 21, 6, 10, 15, 21
};

void str_to_arr(str input, it* res);
string padding_inp(string inp, int inplen, int wrstrlen);
void fulfill_inp(it* inp, int len, int* res);
string bin2hex(it* inp, int len);
void chart_find(it* inp);
string find_chart(char x);
void hex2bin(char* hex,it* inp, int len);
int getndex(char ch);
int hex2dec(string x);
void func_F(it*x, it*y, it*z, it*res, int len);
void func_G(it*x, it*y, it*z, it*res, int len);
void func_H(it*x, it*y, it*z, it*res, int len);
void func_I(it*x, it*y, it*z, it*res, int len);
void and_op(int* a, int* b, int len, int* res);
void not_op(int* a, int len, int* res);
void xor_op(int* a, int* b, int len, int* res);
void or_op(int* a, int* b, int len, int* res);
void left_loop(it* inp, int len, int s);
bool add_op(int* a, int* b, int* res, int len);
void func_FF(it *a, it* b, it* c, it* d, it* Mi, int si, it* ti_bin, int len);
void func_GG(it *a, it* b, it* c, it* d, it* Mi, int si, it* ti_bin, int len);
void func_HH(it *a, it* b, it* c, it* d, it* Mi, int si, it* ti_bin, int len);
void func_II(it *a, it* b, it* c, it* d, it* Mi, int si, it* ti_bin, int len);
string md5_encode(string plaintext);
void length_expand_attc(string inp, string append);
#endif /* MD5_HEADERS_H_ */
