006868f5 movss xmm1, dword ptr [edi + 0x30c]
006868fd movss xmm0, dword ptr [edi + 0x310]
00686905 mov eax, dword ptr [edi + 0x234]
0068690b subss xmm0, xmm1
0068690f mulss xmm0, dword ptr [0xb6a8f4]
00686917 mulss xmm0, dword ptr [0xb6a25c]
0068691f addss xmm0, xmm1
00686923 movss dword ptr [edi + 0x30c], xmm0
0068692b test eax, eax
0068692d jle 0x68694d
0068692f dec eax
00686930 mov dword ptr [edi + 0x234], eax
00686936 test eax, eax
00686938 jg 0x68694d
0068693a mov ecx, edi
0068693c call 0x68d260
00686941 mov ecx, dword ptr [edi + 0x160]
00686947 mov edx, dword ptr [edi + 0x164]
