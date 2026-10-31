00405e90 push ebp
00405e91 mov ebp, esp
00405e93 push ecx
00405e94 push ebx
00405e95 mov ebx, ecx
00405e97 push esi
00405e98 push edi
00405e99 mov dword ptr [ebp - 4], ebx
00405e9c cmp dword ptr [ebx + 4], 0
00405ea0 jne 0x405eb1
00405ea2 push 0xa081ec
00405ea7 push 3
00405ea9 call 0x95e330
00405eae add esp, 8
00405eb1 mov esi, dword ptr [ebx]
00405eb3 xor edi, edi
00405eb5 mov ebx, dword ptr [esi + 0x90]
00405ebb test ebx, ebx
00405ebd je 0x405f03
00405ebf mov esi, dword ptr [esi + 0x8c]
00405ec5 cmp dword ptr [esi + 0x14], 0x10
00405ec9 mov eax, esi
00405ecb jb 0x405ecf
00405ecd mov eax, dword ptr [esi]
00405ecf mov ecx, dword ptr [ebp + 8]
00405ed2 mov dl, byte ptr [eax]
00405ed4 cmp dl, byte ptr [ecx]
00405ed6 jne 0x405ef2
00405ed8 test dl, dl
00405eda je 0x405eee
00405edc mov dl, byte ptr [eax + 1]
00405edf cmp dl, byte ptr [ecx + 1]
00405ee2 jne 0x405ef2
00405ee4 add eax, 2
00405ee7 add ecx, 2
00405eea test dl, dl
00405eec jne 0x405ed2
00405eee xor eax, eax
00405ef0 jmp 0x405ef7
00405ef2 sbb eax, eax
00405ef4 or eax, 1
00405ef7 test eax, eax
00405ef9 je 0x405f0e
00405efb inc edi
00405efc add esi, 0x18
00405eff cmp edi, ebx
00405f01 jb 0x405ec5
00405f03 xor al, al
00405f05 pop edi
00405f06 pop esi
00405f07 pop ebx
00405f08 mov esp, ebp
00405f0a pop ebp
00405f0b ret 4
00405f0e test edi, edi
00405f10 js 0x405f03
00405f12 mov ecx, edi
00405f14 mov eax, 1
00405f19 shl eax, cl
00405f1b mov ecx, dword ptr [ebp - 4]
00405f1e pop edi
00405f1f pop esi
00405f20 pop ebx
00405f21 test dword ptr [ecx + 0x18], eax
00405f24 setne al
00405f27 mov esp, ebp
00405f29 pop ebp
00405f2a ret 4
00405f2d int3 
00405f2e int3 
00405f2f int3 
00405f30 push ebp
00405f31 mov ebp, esp
00405f33 push ecx
00405f34 push ebx
00405f35 mov ebx, ecx
00405f37 push esi
00405f38 push edi
00405f39 mov dword ptr [ebp - 4], ebx
00405f3c cmp dword ptr [ebx + 4], 0
00405f40 jne 0x405f51
00405f42 push 0xa081ec
00405f47 push 3
00405f49 call 0x95e330
00405f4e add esp, 8
00405f51 mov esi, dword ptr [ebx]
00405f53 xor edi, edi
00405f55 mov ebx, dword ptr [esi + 0x90]
00405f5b test ebx, ebx
00405f5d je 0x405fa3
00405f5f mov esi, dword ptr [esi + 0x8c]
00405f65 cmp dword ptr [esi + 0x14], 0x10
00405f69 mov eax, esi
00405f6b jb 0x405f6f
00405f6d mov eax, dword ptr [esi]
00405f6f mov ecx, dword ptr [ebp + 8]
00405f72 mov dl, byte ptr [eax]
00405f74 cmp dl, byte ptr [ecx]
00405f76 jne 0x405f92
00405f78 test dl, dl
00405f7a je 0x405f8e
00405f7c mov dl, byte ptr [eax + 1]
00405f7f cmp dl, byte ptr [ecx + 1]
00405f82 jne 0x405f92
00405f84 add eax, 2
00405f87 add ecx, 2
00405f8a test dl, dl
00405f8c jne 0x405f72
00405f8e xor eax, eax
00405f90 jmp 0x405f97
00405f92 sbb eax, eax
00405f94 or eax, 1
00405f97 test eax, eax
00405f99 je 0x405fae
00405f9b inc edi
00405f9c add esi, 0x18
00405f9f cmp edi, ebx
00405fa1 jb 0x405f65
00405fa3 xor al, al
00405fa5 pop edi
00405fa6 pop esi
00405fa7 pop ebx
00405fa8 mov esp, ebp
00405faa pop ebp
00405fab ret 4
00405fae test edi, edi
00405fb0 js 0x405fa3
00405fb2 mov ecx, edi
00405fb4 mov eax, 1
00405fb9 shl eax, cl
00405fbb mov ecx, dword ptr [ebp - 4]
00405fbe pop edi
00405fbf pop esi
00405fc0 pop ebx
00405fc1 test dword ptr [ecx + 0x1c], eax
00405fc4 setne al
00405fc7 mov esp, ebp
00405fc9 pop ebp
