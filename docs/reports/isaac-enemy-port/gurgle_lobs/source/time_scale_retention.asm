0065c960 movaps xmm3, xmm1
0065c963 movaps xmm2, xmm0
0065c966 ucomiss xmm3, dword ptr [0xb6a614]
0065c96d lahf 
0065c96e test ah, 0x44
0065c971 jnp 0x65c989
0065c973 movaps xmm1, xmm2
0065c976 mulss xmm0, xmm3
0065c97a addss xmm1, xmm3
0065c97e subss xmm1, xmm0
0065c982 divss xmm2, xmm1
0065c986 movaps xmm0, xmm2
0065c989 ret 
