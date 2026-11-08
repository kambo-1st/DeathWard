0067e8e1 mov eax, dword ptr [esi + 0x28]
0067e8e4 cmp eax, 1
0067e8e7 jne 0x67e9c2
0067e8ed mov eax, dword ptr [edi + 0x314]
0067e8f3 test eax, eax
0067e8f5 je 0x67e8fd
0067e8f7 cmp dword ptr [eax + 0x28], 3
0067e8fb je 0x67e896
0067e8fd cmp word ptr [edi + 0x380], 0
0067e905 jle 0x67e91d
0067e907 mov eax, 4
0067e90c mov word ptr [edi + 0x380], ax
0067e913 mov al, 1
0067e915 pop edi
0067e916 pop esi
0067e917 mov esp, ebp
0067e919 pop ebp
0067e91a ret 8
0067e91d movss xmm1, dword ptr [esi + 0x2b8]
0067e925 movss xmm2, dword ptr [esi + 0x2bc]
0067e92d mulss xmm1, dword ptr [0xb6a434]
0067e935 mulss xmm2, dword ptr [0xb6a434]
0067e93d addss xmm1, dword ptr [edi + 0x2b8]
0067e945 addss xmm2, dword ptr [edi + 0x2bc]
0067e94d movss dword ptr [edi + 0x2b8], xmm1
0067e955 movss dword ptr [edi + 0x2bc], xmm2
0067e95d cmp dword ptr [esi + 0x28], 0x194
0067e964 jne 0x67e973
0067e966 cmp dword ptr [esi + 0x34], 0x19b
0067e96d je 0x67e896
0067e973 push 0
0067e975 push 0x20000000
0067e97a mov ecx, esi
0067e97c call 0x4122f0
0067e981 test al, al
0067e983 jne 0x67e896
0067e989 mov eax, dword ptr [esi + 0x28]
0067e98c cmp eax, 0x123
0067e991 je 0x67e896
0067e997 mov ecx, dword ptr [ebp + 0xc]
0067e99a test cl, cl
0067e99c je 0x67f02e
0067e9a2 cmp eax, 4
0067e9a5 jne 0x67f025
0067e9ab cmp byte ptr [edi + 0x398], 0
0067e9b2 je 0x67f05e
0067e9b8 mov al, 1
0067e9ba pop edi
0067e9bb pop esi
0067e9bc mov esp, ebp
0067e9be pop ebp
0067e9bf ret 8
