00742830 push 0x32
00742832 mov ecx, esi
00742834 call 0x88b600
00742839 test al, al
0074283b je 0x7428ee
00742841 cmp byte ptr [edi + 0x188], 0
00742848 movss xmm2, dword ptr [ebp - 0x68]
0074284d movss xmm1, dword ptr [ebp - 0x48]
00742852 mulss xmm2, dword ptr [0xb6a274]
0074285a mulss xmm1, dword ptr [0xb6a274]
00742862 addss xmm2, dword ptr [ebp - 0x40]
00742867 addss xmm1, dword ptr [edi + 0x2bc]
0074286f movss dword ptr [edi + 0x2b8], xmm2
00742877 movss dword ptr [edi + 0x2bc], xmm1
0074287f je 0x7428ee
00742881 movss xmm5, dword ptr [edi + 0x190]
00742889 movss xmm4, dword ptr [edi + 0x18c]
00742891 movaps xmm0, xmm5
00742894 movss xmm2, dword ptr [edi + 0x198]
0074289c movaps xmm3, xmm4
0074289f movss xmm1, dword ptr [edi + 0x194]
007428a7 mulss xmm3, xmm1
007428ab mulss xmm0, xmm2
007428af addss xmm3, xmm0
007428b3 movaps xmm0, xmm3
007428b6 mulss xmm3, xmm2
007428ba mulss xmm0, xmm1
007428be mulss xmm3, dword ptr [0xb6a560]
007428c6 mulss xmm0, dword ptr [0xb6a560]
007428ce addss xmm3, xmm3
007428d2 addss xmm0, xmm0
007428d6 subss xmm5, xmm3
007428da subss xmm4, xmm0
007428de movss dword ptr [edi + 0x2bc], xmm5
007428e6 movss dword ptr [edi + 0x2b8], xmm4
