00405330 push esi
00405331 mov esi, ecx
00405333 mov dword ptr [esi + 0x10], 0
0040533a mov dword ptr [esi + 0x18], 0
00405341 mov dword ptr [esi + 0x1c], 0
00405348 call 0x403a90
0040534d mov eax, dword ptr [esi + 4]
00405350 xor ecx, ecx
00405352 cmp dword ptr [eax + 0x1c], ecx
00405355 jbe 0x405373
00405357 nop word ptr [eax + eax]
00405360 mov eax, dword ptr [esi + 8]
00405363 mov dword ptr [eax + ecx*4], 0
0040536a inc ecx
0040536b mov eax, dword ptr [esi + 4]
0040536e cmp ecx, dword ptr [eax + 0x1c]
00405371 jb 0x405360
00405373 xor ecx, ecx
00405375 cmp dword ptr [eax + 0x24], ecx
00405378 jbe 0x405393
0040537a nop word ptr [eax + eax]
00405380 mov eax, dword ptr [esi + 0xc]
00405383 mov dword ptr [eax + ecx*4], 0
0040538a inc ecx
0040538b mov eax, dword ptr [esi + 4]
0040538e cmp ecx, dword ptr [eax + 0x24]
00405391 jb 0x405380
00405393 pop esi
00405394 ret 
00405395 int3 
00405396 int3 
00405397 int3 
00405398 int3 
00405399 int3 
0040539a int3 
0040539b int3 
0040539c int3 
0040539d int3 
0040539e int3 
0040539f int3 
004053a0 push ebp
004053a1 mov ebp, esp
004053a3 push esi
004053a4 mov esi, ecx
004053a6 push edi
004053a7 cmp dword ptr [esi + 4], 0
004053ab jne 0x4053bc
