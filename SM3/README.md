#SM3 Realize, attack and accelerate

## Experimental environment:

1. Intel(R) Core(TM) i7-10750H CPU @ 2.60GHz 59GHz
2. gcc 9.4.0
3. Virtual machine settings(2 core 2 processor)

## Experiment content:

1. Realize SM3 (c++)
2. Realize SM3 birthday attack and Rho attack
3. Realize SM3 (SIMD) accelerate


## Operation process(makefile already generated):

###SM3 ecryption:
    1. Brife introduction:
        The document mainly consists of two parts(main and header)
        SM3(mian-cpp):Call the function in the header file to encrypt.
        sm3_headers(header-h):Define relevant functions,including attack,encryption and accelerate.
    2. Operation processs(pic):
        (SM3 result.png)
###SM3 attack:
    (included in the SM3.cpp)
###SM3 accelerate(based on SIMD):
    (included in the SM3.cpp)
##Reference material:
    1.(website)https://blog.csdn.net/nicai_hualuo/article/details/121555000
    2.(website)https://zhuanlan.zhihu.com/p/457505686
    3.(website)https://zhuanlan.zhihu.com/p/379077249 
