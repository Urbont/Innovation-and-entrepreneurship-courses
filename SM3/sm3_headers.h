/*
 * sm3_headers.h
 *
 *  Created on: Jul 21, 2022
 *      Author: gg
 */

#ifndef SRC_SM3_HEADERS_H_
#define SRC_SM3_HEADERS_H_

#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include <xmmintrin.h>

using namespace std;

typedef int it;

string find_chart(char x);
void chart_find(int arr, string* res);
void Hex2Bin(string hex, it* inp, int len);
it* Dec2Bin(int a);
it Bin2Dec(it* inp, int len);
it* padding_inp(string plaintext);
it* left_loop(it tar[], int len, int stride);
it* and_op(it* a, it* b, int len);
it* or_op(it* a, it* b, int len);
it* xor_op(it* tar1, it* tar2, it len);
it* not_op(it* tar, int len);
it* mod_add(it* a, it* b, it len);
it* func_P1(it inp[], int len);
it* func_P0(it* inp, int len);
it* func_FF(it* a, it* b, it* c, int x, int len);
it* func_GG(it* a, it* b, it* c, int x, int len);
it* T(it j);
it* compress_data(it* tar1, it* tar2, int N);
it* extend_inp(it* inp);
it* func_itea(it* inp, int num);
it* sm3_encode(it* inp);
/* birthday attack and Rho attack*/
bool birth_attc(int len, int try_times);
bool check_len(int img, int ori_img, int len);
bool check_rou(int a[], int b[], int len);
bool Rho_attc(int len);
/*length extension attack*/

/*SIMD accelerate*/
/* It seems impossible
it* simd_ll(it* inp, int len, int s){
	// move 4 int one time
	if(inp == NULL || len <= 0) return NULL;
	__m128i* x = (__m128i*) inp;
	__m128i loadx;
	int block = len / 4, block_s = s / 4;
	int rest = len % 4, rest_s = s % 4;
	for(int i = 0;i < block_s; i ++){
		loadx = _mm_load_si128(x);
		loadx = loadx << block_s;// internal or ext
		++x;
	}
	it* tmp;
	return left_loop(tmp, len, rest_s);
}
*/

it* simd_xor(it* a,it* b, int len);

it* simd_mod_add(it* a, it* b, it len);

it* simd_and(it* a, it* b,  int len);

it* simd_or(it* a, it* b, int len);

it* simd_not(it* inp, int len);

it* simd_FF(it* a, it* b, it* c, int x, int len);

it* simd_GG(it* a, it* b, it* c, int x ,int len);

it* simd_P0(it* inp, int len);

it* simd_P1(it inp[], int len);

it* simd_compress(it* tar1, it* tar2, int N);

it* simd_extend(it* inp);

it* simd_itea(it* inp, int num);

it* acc_sm3(it* inp);

#endif /* SRC_SM3_HEADERS_H_ */
