00788353 movzx eax, dl
00788356 mov ecx, edi
00788358 lea eax, [eax*4 + 4]
0078835f push eax
00788360 call 0x725130
00788365 mov ecx, edi
00788367 call 0x770d60
0078836c movss xmm2, dword ptr [0xb6a614]
00788374 push ecx
00788375 mov dword ptr [esp], 0x3f800000
0078837c push 0
0078837e push 2
00788380 push dword ptr [ebp - 0x150]
00788386 call 0x68d750
0078838b jmp 0x7882a7
00788390 mov eax, dword ptr [edi + 0x12b4]
00788396 mov esi, dword ptr [edi + 0x12ac]
0078839c mov cl, byte ptr [edi + 0x12b1]
007883a2 mov dword ptr [edi + 0x12ac], eax
007883a8 mov al, byte ptr [edi + 0x12b0]
007883ae mov dword ptr [edi + 0x12b4], esi
007883b4 mov byte ptr [edi + 0x12b1], al
007883ba mov byte ptr [edi + 0x12b0], cl
007883c0 test dl, dl
007883c2 je 0x7883e8
007883c4 lea eax, [esi + 1]
007883c7 mov ecx, edi
007883c9 cdq
007883ca sub eax, edx
007883cc sar eax, 1
007883ce push eax
007883cf call 0x725810
007883d4 mov eax, dword ptr [edi + 0x12ac]
007883da mov ecx, edi
007883dc inc eax
007883dd cdq
007883de sub eax, edx
007883e0 sar eax, 1
007883e2 push eax
007883e3 call 0x7258c0
007883e8 push 0x1e
007883ea mov ecx, edi
007883ec call 0x725af0
007883f1 mov ecx, edi
007883f3 call 0x770d60
007883f8 mov eax, dword ptr [0xbfd65c]
007883fd mov edx, dword ptr [ebp - 0x144]
00788403 mov esi, dword ptr [ebp - 0x148]
00788409 cmp dword ptr [eax + 0x101904], 2
00788410 je 0x7882b3
00788416 mov dword ptr [eax + 0x101904], 1
00788420 mov dword ptr [eax + 0x10190c], 2
0078842a jmp 0x7882b3
0078842f test dl, dl
00788431 je 0x78843c
00788433 push 6
00788435 mov ecx, edi
00788437 call 0x725130
0078843c mov ecx, edi
0078843e call 0x741770
00788443 jmp 0x788365
00788448 movzx eax, dl
0078844b mov ecx, edi
0078844d push 0
0078844f lea eax, [eax*2 + 2]
00788456 push eax
00788457 call 0x724d50
0078845c mov ecx, edi
0078845e call 0x770d60
00788463 movss xmm2, dword ptr [0xb6a614]
0078846b push ecx
0078846c mov dword ptr [esp], 0x3f800000
00788473 push 0
00788475 push 2
00788477 push dword ptr [ebp - 0x150]
0078847d call 0x68d750
00788482 lea ecx, [ebp - 0xdc]
00788488 call 0x402120
0078848d movaps xmm0, xmmword ptr [0xb6b990]
00788494 mov eax, ecx
00788496 push eax
00788497 lea ecx, [edi + 0x1608]
0078849d movups xmmword ptr [ebp - 0xcc], xmm0
007884a4 call 0x4021a0
007884a9 mov eax, dword ptr [edi]
007884ab lea ecx, [ebp - 0xdc]
007884b1 push 1
007884b3 push 1
007884b5 push 0xff
007884ba xorps xmm0, xmm0
007884bd mov dword ptr [ebp - 0xbc], 0x3f000000
007884c7 push 0xf
007884c9 movups xmmword ptr [ebp - 0xcc], xmm0
007884d0 push ecx
007884d1 movaps xmm0, xmmword ptr [0xb6c110]
007884d8 mov ecx, edi
007884da movups xmmword ptr [ebp - 0xdc], xmm0
007884e1 mov dword ptr [ebp - 0xb8], 0x3e800000
007884eb mov dword ptr [ebp - 0xb4], 0x3e800000
007884f5 call dword ptr [eax + 0x38]
007884f8 or dword ptr [edi + 0x14b8], 0x1000
00788502 jmp 0x7882a7
00788507 movzx eax, dl
0078850a mov ecx, edi
0078850c xor eax, 1
0078850f push 0
00788511 lea eax, [eax*2 - 4]
00788518 push eax
00788519 call 0x724d50
