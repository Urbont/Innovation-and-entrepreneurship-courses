#include<iostream>
#include<string>
#include <cmath>
#include"sm3_headers.h"
using namespace std;

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

void chart_find(int arr, string* res)
{
	switch (arr)
	{
	case 0:*res += "0"; break;
	case 1:*res += "1"; break;
	case 2:*res += "2"; break;
	case 3:*res += "3"; break;
	case 4:*res += "4"; break;
	case 5:*res += "5"; break;
	case 6:*res += "6"; break;
	case 7:*res += "7"; break;
	case 8:*res += "8"; break;
	case 9:*res += "9"; break;
	case 10:*res += "a"; break;
	case 11:*res += "b"; break;
	case 12:*res += "c"; break;
	case 13:*res += "d"; break;
	case 14:*res += "e"; break;
	case 15:*res += "f"; break;
	}
}

void Hex2Bin(string hex, it* inp, int len){
	for(int i = 2;i < len;i ++){
		for(int j = 0;j < 4;j ++)
			inp[i] = find_chart(hex[i])[j] - '0';
	}

}

it* Dec2Bin(int a){
	it* res = new it[64];
	int i = 0;
	while (a != 0) {
		res[63 - i] = (a % 2 == 0 ? 0 : 1);
		a /= 2;
		i++;
	}
	return res;
}

it* padding_inp(string plaintext){
	int len = plaintext.length();
	it* bin_inp = new it[len];
	Hex2Bin(plaintext, bin_inp, len);
	int N = 448 - (len % 512);
	it* part_2 = new it[N];
	for(int i = 0; i < N; i ++){
		part_2[i] = 0;
	}
	it* part_3 = Dec2Bin(plaintext.length());
	int len2 = len / 512 + 512;
	it* bin_data = new it[len2];

	for(int i = 0 ; i <  len2; i ++){
		if(i < len)
			bin_data[i] = bin_inp[i];
		if(len < i && i < len + N)
			bin_data[i] = part_2[i];
		else
			bin_data[i] = part_3[i];
	}
	return bin_data;
}

it* left_loop(it tar[], int len, int stride){
	//（i + k) % length is the target
	it tmp = 0;
	it* res = new it[len];
	for(int j = 0; j < stride; j ++){
		tmp = tar[0];
		for(int i = 0; i < len - 1 ;i ++){
			res[i] = tar[i + 1];
		}
		res[len - 1] = tmp;
	}
	return res;
}

it* and_op(it* a, it* b, int len){
	it* res = new it[len];
	for(int i = 0 ; i < len; i ++){
		if(a[i] == 0 && b[i] == 0){
			res[i] = 1;
		}
		else{
			res[i] = 0;
		}
	}
	return res;
}

it* or_op(it* a, it* b, int len){
	it* res = new it[len];
	for(int i = 0 ; i < len; i ++){
		if(a[i] == 0 || b[i] == 0){
			res[i] = 0;
		}
		else{
			res[i] = 1;
		}
	}
	return res;
}

it* xor_op(it* tar1, it* tar2, it len){
	it* res = new it[len];
	for(int i = 0; i < len; i ++){
		if(tar1[i] == tar2[i])
			res[i] = 0;
		else
			res[i] = 1;
	}
	return res;
}

it* not_op(it* tar, int len){
	it* res = new it[len];
	for(int i =0 ;i < len; i ++){
		if(tar[i] == 1)
			res[i] = 0;
		else
			res[i] = 1;
	}
	return res;
}

it* func_P1(it inp[], int len){
	return xor_op(xor_op(inp, left_loop(inp, 8, 15), 8), left_loop(inp, 8, 15), 8);
	//release the room
}

it* mod_add(it* a, it* b, it len){
	it* res = new it[len];
	it tmp = 0;
	for(int i = 0; i < len; i ++){
		if(a[i] == 1 && b[i] == 1){
			res[i] = 0;
			tmp = 1;
		}
		if(a[i] == 1 && b[i] == 0 && tmp == 0){
			res[i] = 1;
			tmp = 0;
		}
		if(a[i] == 0 && b[i] == 1 && tmp == 0){
			res[i] = 1;
			tmp = 0;
		}
		if(a[i] == 0 && b[i] == 0 && tmp == 0){
			res[i] = 0;
			tmp = 0;
		}
		if(a[i] == 1 && b[i] == 0 && tmp == 1){
			res[i] = 0;
			tmp = 0;
		}
		if(a[i] == 0 && b[i] == 1 && tmp == 1){
			res[i] = 0;
			tmp = 0;
		}
		if(a[i] == 0 && b[i] == 0 && tmp == 1){
			res[i] = 1;
			tmp = 0;
		}
	}
	int* x = Dec2Bin(32);
	res = xor_op(res, x , len);
	return res;
}

it* func_FF(it* a, it* b, it* c, int x, int len){
	if(0 <= x && x <= 15){
		return xor_op(xor_op(a, b, len), c, len);
	}
	else{
		return or_op(or_op(and_op(a, b, len), and_op(a, c, len), len), and_op(b, c, len), len);
	}
}

it* func_GG(it* a, it* b, it* c, int x ,int len){
	if( 0 <= x && x <= 15){
		return xor_op(xor_op(a, b, len), c, len);
	}
	else{
		return or_op(and_op(a, b, len), and_op(not_op(a, len), c, len), len);
	}
}

it* T(it j){
	string p1 = "79cc4519";
	string p2 = "7a879d8a";
	int len = p1.length();
	it* res = new it[len];

	if(0 <= j && j <=15)
		Hex2Bin(p1, res, len);
	else
		Hex2Bin(p2, res, len);
	return res;
}

it* func_P0(it* inp, int len){
	return xor_op(xor_op(inp, left_loop(inp, len, 9), len), left_loop(inp, len, 17), len);
}

it* compress_data(it* tar1, it* tar2, int N){
	//num = (N + 1)*512;
	it** B = new it*[(N + 1) * 64];
	for(int i = 0; i < (N + 1) * 64; i ++){
			B[i] = new it[64];
	}
	for(int i = 0 ; i < 8; i ++){
		for(int j = 0; j < 64; j ++){
			B[i][j] = tar2[i * 64 + j];
		}
	}
	it* res = new it[512];
	it** V = new it*[8];
	for(int i = 0; i < 8; i ++){
		V[i] = new it[64];
	}
	for(int i = 0 ; i < 8; i ++){
		for(int j = 0; j < 64; j ++){
			V[i][j] = tar2[i * 64 + j];
		}//a,b,c,d,e,f,g
	}
	it* SS1, *SS2, *TT1, *TT2;
	for(int i =0 ; i< 64; i ++){
		SS1 = left_loop(mod_add(mod_add(left_loop(V[0], 64, 12),V[4] ,64),left_loop(T(i), 64, (i % 32)), 64), 64, 7);
		SS2 = xor_op(SS1, left_loop(V[0], 64, 12), 64);
		//mod_add(func_FF(V[0], V[1], V[2], i, 64), V[3], 64);
		//mod_add(mod_add(func_FF(V[0], V[1], V[2], i, 64), V[3], 64), SS2, 64);
		TT1 = mod_add(mod_add(mod_add(func_FF(V[0], V[1], V[2], i, 64), V[3], 64), SS2, 64), B[(i + 68)], 64);
		TT2 = mod_add(mod_add(mod_add(func_FF(V[4], V[5], V[6], i, 64), V[7], 64), SS2, 64), B[i], 64);
		for(int i = 0 ; i< 64; i ++){
			V[3][i] = V[2][i];
		}//D = C
		for(int i = 0 ; i< 64; i ++){
			V[2][i] = left_loop(V[1], 64, 9)[i];
		}//C
		for(int i = 0 ; i< 64; i ++){
			V[1][i] = V[0][i];
		}//B = A
		for(int i = 0 ; i< 64; i ++){
			V[0][i] = TT1[i];
		}//A = TT1
		for(int i = 0 ; i< 64; i ++){
			V[7][i] = V[6][i];
		}//H = G
		for(int i = 0 ; i< 64; i ++){
			V[6][i] = left_loop(V[5], 64, 19)[i];
		}//G
		for(int i = 0 ; i< 64; i ++){
			V[5][i] = V[4][i];
		}//F = E
		for(int i = 0 ; i< 64; i ++){
			V[4][i] = func_P0(TT2, 64)[i];
		}//E = p0
	}

	for(int i = 0; i < 8; i ++){
		for(int j = 0; j < 64; j ++){
			res[i * 8 + j] = V[i][j];
		}
	}

	//release the room
		for(int i = 0; i < (N + 1) * 64; i ++){
			delete []B[i];
		}
		delete []B;
		B = NULL;
		for(int i = 0; i < 8; i ++){
			delete []V[i];
		}
		delete []V;
		V = NULL;


	return res;
}

it* extend_inp(it* inp){
	//divide into W0-W15 (128bits input)
	it** W = new it*[132];
	for(int i = 0; i < 132; i ++)
		W[i] = new it[8];
	for(int i = 0; i < 16; i ++){
		for(int j = 0; j < 8; j ++){
			W[i][j] = inp[i * 8 + j];
		}
	}
	for(int i = 17; i < 68 ;i ++){
		for(int j = 0; j < 8; j ++){
			W[i][j] = xor_op(func_P1(xor_op(xor_op(W[i - 16], W[i - 9], 8), left_loop(W[i - 3], 8, 15), 8), 8), xor_op(left_loop(W[i - 13], 8, 7), W[i - 13], 8), 8)[j];
		}
	}
	for(int i = 0; i < 63; i ++){
		for(int j = 0; j < 8; j ++){
			W[i][j] = xor_op(W[i], W[i + 4], 8)[j];
		}
	}
	it* B = new it[1056];
	for(int i = 0; i < 132; i ++){
		for(int j = 0; j < 8; j ++){
			B[i * 8 + j] = W[i][j];
		}
	}
	//release the room
	for(int i = 0; i < 132;i ++){
		delete[] W[i];
	}
	delete[] W;
	W = NULL;
	return B;
}

it* func_itea(it* inp, int num){
	string V0 = "7380166f4914b2b9172442d7da8a0600a96f30bc163138aae38dee4db0fb0e4e";
	int len = V0.length();
	it* V = new it[len];
	Hex2Bin(V0, V ,len);
	it** B = new it*[num];
	for(int i = 0; i < num; i ++)
		B[i] = new it[128];
	for(int i = 0; i < num; i ++){
		V = xor_op(compress_data(extend_inp(B[i]), V ,8), V, 8);
	}
	return V;
}

it* sm3_encode(it* inp = NULL){
	string plaintext;
	if(inp != NULL)
		plaintext = to_string(*inp);//?
	else
		plaintext = "0123456789abcdef";
	it* tmp = padding_inp(plaintext);
	it* res = func_itea(tmp, plaintext.length());
	//Print the answer
	return res;
}

bool check_len(it* img, it* ori_img, int len){
	it* image, *ori_image;
	image = sm3_encode(img);
	ori_image = sm3_encode(ori_img);
	for(int i = 0; i < len; i ++){
		if(image[i] != ori_image[i])
			return 0;
		else
			continue;
	}
	return 1;
}

bool birth_attc(int len, int try_times){
	srand(time(NULL));
	int t = try_times, image_int = rand() % 2^len, ori_image_int = rand() % 2^len;
	it* img, * ori_img;
	//int tmp = - (t * (t - 1)) / pow(2, (len + 1));
	//float percentage = exp(tmp);
	for(int i = 0; i < t; i ++){
		if(image_int == ori_image_int){
			image_int = rand() % 2^len;//?
			ori_image_int = rand() % 2^len;
		}
		img = Dec2Bin(image_int);
		ori_img = Dec2Bin(ori_image_int);
		if(check_len(img, ori_img, len))
			return 1;
		else
			continue;
	}
	return 0;
}

bool check_rou(int a[], int b[], int len){
	int x = Bin2Dec(a, len);
	int y = Bin2Dec(b, len);
	if(x == y)
		return 1;
	else
		return 0;

}

bool Rho_attc(int len){
	srand(time(NULL));
	int x = rand() % 2^len;
	int y = rand() % 2^len;
	it* check;
	while(x == y){
		x = rand() % 2^len;
		y = rand() % 2^len;
	}
	while(1){
		x = x * x;
		y = y * y;
		check = sm3_encode(Dec2Bin(x - y));
		if(check_rou(check, Dec2Bin(x - y), len)){
			//Print result!
			return 1;
		}
		else{
			return 0;
		}
	}
}

it Bin2Dec(it* inp, int len){
	it sum = 0;
	for(int i = 0; i < len; i ++){
		if(inp[i] == 1){
			sum += 2^i;
		}
		else{
			continue;
		}
	}
	return sum;
}

it* simd_xor(it* a,it* b, int len){
	if(a == NULL || len <= 0 || b == NULL) return NULL;
	__m128i* xa = (__m128i*) a;
	__m128i* xb = (__m128i*) b;
	__m128i loadxa, loadxb;
	__m128i xidres = _mm_setzero_si128();
	int block = len / 4;
	//int rest = len % 4;
	for(int i = 0;i < block; i += 4){
		loadxa = _mm_load_si128(xa);
		loadxb = _mm_load_si128(xb);
		xidres = _mm_xor_si128(loadxa, loadxb);
		++ xa;
		++ xb;
	}
	int* tmp = new it[len];
	_mm_storeu_si128((__m128i* )tmp, xidres);
	for(int i = block * 4; i < len; i ++){
		if(a[i] != b[i])
			tmp[i] = 1;
		else
			tmp[i] = 0;
	}
	return tmp;
}

it* simd_mod_add(it* a, it* b, it len){
	it* res = new it[len];
	it tmp = 0;
	for(int i = 0; i < len; i ++){
		if(a[i] == 1 && b[i] == 1){
			res[i] = 0;
			tmp = 1;
		}
		if(a[i] == 1 && b[i] == 0 && tmp == 0){
			res[i] = 1;
			tmp = 0;
		}
		if(a[i] == 0 && b[i] == 1 && tmp == 0){
			res[i] = 1;
			tmp = 0;
		}
		if(a[i] == 0 && b[i] == 0 && tmp == 0){
			res[i] = 0;
			tmp = 0;
		}
		if(a[i] == 1 && b[i] == 0 && tmp == 1){
			res[i] = 0;
			tmp = 0;
		}
		if(a[i] == 0 && b[i] == 1 && tmp == 1){
			res[i] = 0;
			tmp = 0;
		}
		if(a[i] == 0 && b[i] == 0 && tmp == 1){
			res[i] = 1;
			tmp = 0;
		}
	}
	int* x = Dec2Bin(32);
	res =simd_xor(res, x , len);
	return res;
}

it* simd_and(it* a, it* b,  int len){
	if(a == NULL || len <= 0 || b == NULL) return NULL;
		__m128i* xa = (__m128i*) a;
		__m128i* xb = (__m128i*) b;
		__m128i loadxa, loadxb;
		__m128i xidres = _mm_setzero_si128();
		int block = len / 4;
		//int rest = len % 4;
		for(int i = 0;i < block; i += 4){
			loadxa = _mm_load_si128(xa);
			loadxb = _mm_load_si128(xb);
			xidres = _mm_and_si128(loadxa, loadxb);
			++ xa;
			++ xb;
		}
		int* tmp = new it[len];
		_mm_storeu_si128((__m128i* )tmp, xidres);
		for(int i = block * 4; i < len; i ++){
			if(a[i] == 1 && b[i] == 1)
				tmp[i] = 1;
			else
				tmp[i] = 0;
		}
		return tmp;

}

it* simd_or(it* a, it* b, int len){
	if(a == NULL || len <= 0 || b == NULL) return NULL;
		__m128i* xa = (__m128i*) a;
		__m128i* xb = (__m128i*) b;
		__m128i loadxa, loadxb;
		__m128i xidres = _mm_setzero_si128();
		int block = len / 4;
		//int rest = len % 4;
		for(int i = 0;i < block; i += 4){
			loadxa = _mm_load_si128(xa);
			loadxb = _mm_load_si128(xb);
			xidres = _mm_or_si128(loadxa, loadxb);
			++ xa;
			++ xb;
		}
		int* tmp = new it[len];
		_mm_storeu_si128((__m128i* )tmp, xidres);
		for(int i = block * 4 ; i < len; i ++){
			if(a[i] == 1 || b[i] == 1)
				tmp[i] = 1;
			else
				tmp[i] = 0;
		}
		return tmp;
}

it* simd_not(it* inp, int len){
	it* tmp = new it[len];
	for(int i = 0; i < len; i ++){
		tmp[i] = 1;
	}
	if(inp == NULL || len <= 0) return NULL;
		__m128i* x = (__m128i*) inp;
		__m128i loadx, loadtmp;
		__m128i xidres = _mm_setzero_si128();
		int block = len / 4;
		//int rest = len % 4;
	for(int i = 0; i < block; i += 4){
		loadx = _mm_load_si128(x);
		loadtmp = _mm_load_si128((__m128i*)tmp);
		xidres = _mm_xor_si128(loadx, loadtmp);
	}
	int* tmp1 = new it[len];
	_mm_storeu_si128((__m128i* )tmp1, xidres);
	for(int i = block * 4 ;  i < len; i ++){
		if(inp[i] == 0)
			tmp1[i] = 1;
		else
			tmp1[i] = 0;
	}
	return tmp1;
}

it* simd_FF(it* a, it* b, it* c, int x, int len){
	if(0 <= x && x <= 15){
		return simd_xor(simd_xor(a, b, len), c, len);
	}
	else{
		return simd_or(simd_or(simd_and(a, b, len), simd_and(a, c, len), len), simd_and(b, c, len), len);
	}
}

it* simd_GG(it* a, it* b, it* c, int x ,int len){
	if( 0 <= x && x <= 15){
		return simd_xor(simd_xor(a, b, len), c, len);
	}
	else{
		return simd_or(simd_and(a, b, len), simd_and(simd_not(a, len), c, len), len);
	}
}

it* simd_P0(it* inp, int len){
	return simd_xor(simd_xor(inp, left_loop(inp, len, 9), len), left_loop(inp, len, 17), len);
}

it* simd_P1(it inp[], int len){
	return simd_xor(simd_xor(inp, left_loop(inp, 8, 15), 8), left_loop(inp, 8, 15), 8);
	//release the room
}

it* simd_compress(it* tar1, it* tar2, int N){
	//num = (N + 1)*512;
	it** B = new it*[(N + 1) * 64];
	for(int i = 0; i < (N + 1) * 64; i ++){
			B[i] = new it[64];
	}
	for(int i = 0 ; i < 8; i ++){
		for(int j = 0; j < 64; j ++){
			B[i][j] = tar2[i * 64 + j];
		}
	}
	it* res = new it[512];
	it** V = new it*[8];
	for(int i = 0; i < 8; i ++){
		V[i] = new it[64];
	}
	for(int i = 0 ; i < 8; i ++){
		for(int j = 0; j < 64; j ++){
			V[i][j] = tar2[i * 64 + j];
		}//a,b,c,d,e,f,g
	}
	it* SS1, *SS2, *TT1, *TT2;
	for(int i =0 ; i< 64; i ++){
		SS1 = left_loop(simd_mod_add(simd_mod_add(left_loop(V[0], 64, 12),V[4] ,64),left_loop(T(i), 64, (i % 32)), 64), 64, 7);
		SS2 = simd_xor(SS1, left_loop(V[0], 64, 12), 64);
		//mod_add(func_FF(V[0], V[1], V[2], i, 64), V[3], 64);
		//mod_add(mod_add(func_FF(V[0], V[1], V[2], i, 64), V[3], 64), SS2, 64);
		TT1 = simd_mod_add(simd_mod_add(simd_mod_add(func_FF(V[0], V[1], V[2], i, 64), V[3], 64), SS2, 64), B[(i + 68)], 64);
		TT2 = simd_mod_add(simd_mod_add(simd_mod_add(func_FF(V[4], V[5], V[6], i, 64), V[7], 64), SS2, 64), B[i], 64);
		for(int i = 0 ; i< 64; i ++){
			V[3][i] = V[2][i];
		}//D = C
		for(int i = 0 ; i< 64; i ++){
			V[2][i] = left_loop(V[1], 64, 9)[i];
		}//C
		for(int i = 0 ; i< 64; i ++){
			V[1][i] = V[0][i];
		}//B = A
		for(int i = 0 ; i< 64; i ++){
			V[0][i] = TT1[i];
		}//A = TT1
		for(int i = 0 ; i< 64; i ++){
			V[7][i] = V[6][i];
		}//H = G
		for(int i = 0 ; i< 64; i ++){
			V[6][i] = left_loop(V[5], 64, 19)[i];
		}//G
		for(int i = 0 ; i< 64; i ++){
			V[5][i] = V[4][i];
		}//F = E
		for(int i = 0 ; i< 64; i ++){
			V[4][i] = func_P0(TT2, 64)[i];
		}//E = p0
	}

	for(int i = 0; i < 8; i ++){
		for(int j = 0; j < 64; j ++){
			res[i * 8 + j] = V[i][j];
		}
	}

	//release the room
		for(int i = 0; i < (N + 1) * 64; i ++){
			delete []B[i];
		}
		delete []B;
		B = NULL;
		for(int i = 0; i < 8; i ++){
			delete []V[i];
		}
		delete []V;
		V = NULL;


	return res;
}

it* simd_extend(it* inp){
	//divide into W0-W15 (128bits input)
	it** W = new it*[132];
	for(int i = 0; i < 132; i ++)
		W[i] = new it[8];
	for(int i = 0; i < 16; i ++){
		for(int j = 0; j < 8; j ++){
			W[i][j] = inp[i * 8 + j];
		}
	}
	for(int i = 17; i < 68 ;i ++){
		for(int j = 0; j < 8; j ++){
			W[i][j] = simd_xor(func_P1(simd_xor(simd_xor(W[i - 16], W[i - 9], 8), left_loop(W[i - 3], 8, 15), 8), 8), simd_xor(left_loop(W[i - 13], 8, 7), W[i - 13], 8), 8)[j];
		}
	}
	for(int i = 0; i < 63; i ++){
		for(int j = 0; j < 8; j ++){
			W[i][j] = simd_xor(W[i], W[i + 4], 8)[j];
		}
	}
	it* B = new it[1056];
	for(int i = 0; i < 132; i ++){
		for(int j = 0; j < 8; j ++){
			B[i * 8 + j] = W[i][j];
		}
	}
	//release the room
	for(int i = 0; i < 132;i ++){
		delete[] W[i];
	}
	delete[] W;
	W = NULL;
	return B;
}

it* simd_itea(it* inp, int num){
	string V0 = "7380166f4914b2b9172442d7da8a0600a96f30bc163138aae38dee4db0fb0e4e";
	int len = V0.length();
	it* V = new it[len];
	Hex2Bin(V0, V ,len);
	it** B = new it*[num];
	for(int i = 0; i < num; i ++)
		B[i] = new it[128];
	for(int i = 0; i < num; i ++){
		V = simd_xor(simd_compress(simd_extend(B[i]), V ,8), V, 8);
	}
	return V;
}

it* acc_sm3(it* inp = NULL){
	/*padding part skipped (input is after padding)*/
string plaintext;
	if(inp != NULL)
		plaintext = to_string(*inp);//?
	else
		plaintext = "0123456789abcdef";
	it* tmp = padding_inp(plaintext);
	it* res = simd_itea(tmp, plaintext.length());
	//Print the answer
	return res;
	//Print the answer
}

int main(){
	//sm3_encode();
	//acc_sm3();
	cout<<"Hello world!"<<endl;
	return 0;
}
