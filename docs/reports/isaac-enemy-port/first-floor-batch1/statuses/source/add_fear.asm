00685ae0 push ebp
00685ae1 mov ebp, esp
00685ae3 and esp, 0xfffffff8
00685ae6 sub esp, 0x3c
00685ae9 mov eax, dword ptr [0xbaa3b4]
00685aee xor eax, esp
00685af0 mov dword ptr [esp + 0x38], eax
00685af4 push ebx
00685af5 mov ebx, dword ptr [ebp + 8]
00685af8 push esi
00685af9 push edi
00685afa push ebx
00685afb mov esi, ecx
00685afd mov dword ptr [esp + 0x18], ebx
00685b01 call 0x684b00
00685b06 test al, al
00685b08 jne 0x685c89
00685b0e cmp dword ptr [esi + 0x28], 1
00685b12 jne 0x685b2a
00685b14 push 0
00685b16 push 0x278
00685b1b mov ecx, esi
00685b1d call 0x73af30
00685b22 test al, al
00685b24 jne 0x685c89
00685b2a push ebx
00685b2b push dword ptr [ebp + 0xc]
00685b2e mov ecx, esi
00685b30 call 0x685020
00685b35 mov ecx, esi
00685b37 mov ebx, eax
00685b39 call 0x681710
00685b3e test al, al
00685b40 je 0x685b5c
00685b42 mov ecx, dword ptr [esi + 0x314]
00685b48 test ecx, ecx
00685b4a je 0x685b5c
00685b4c nop dword ptr [eax]
00685b50 mov esi, ecx
00685b52 mov ecx, dword ptr [esi + 0x314]
00685b58 test ecx, ecx
00685b5a jne 0x685b50
00685b5c test ebx, ebx
00685b5e je 0x685c89
00685b64 mov eax, dword ptr [esi + 0x160]
00685b6a and eax, 1
00685b6d or eax, 0
00685b70 jne 0x685c89
00685b76 cmp dword ptr [esi + 0x230], eax
00685b7c jg 0x685c89
00685b82 push eax
00685b83 push 0x1000800
00685b88 mov ecx, esi
00685b8a call 0x4122f0
00685b8f mov edi, dword ptr [esi + 0x228]
00685b95 mov byte ptr [esp + 0x13], al
00685b99 test ebx, ebx
00685b9b jle 0x685bac
00685b9d lea ecx, [edi + ebx]
00685ba0 mov edi, 0x78
00685ba5 cmp ecx, edi
00685ba7 cmovl edi, ecx
00685baa jmp 0x685bb3
00685bac neg ebx
00685bae cmp edi, ebx
00685bb0 cmovl edi, ebx
00685bb3 push 1
00685bb5 mov dword ptr [esi + 0x228], edi
00685bbb lea ecx, [esp + 0x1c]
00685bbf movss xmm3, dword ptr [0xb6a480]
00685bc7 movss xmm2, dword ptr [0xb6a2cc]
00685bcf movaps xmm1, xmm3
00685bd2 mov edx, dword ptr [esi]
00685bd4 push 0
00685bd6 push 0xff
00685bdb push edi
00685bdc call 0x427080
00685be1 push eax
00685be2 mov ecx, esi
00685be4 call dword ptr [edx + 0x38]
00685be7 mov eax, dword ptr [esi + 0x164]
00685bed mov ecx, esi
00685bef or dword ptr [esi + 0x160], 0x800
00685bf9 mov dword ptr [esi + 0x164], eax
00685bff mov eax, dword ptr [esi]
00685c01 mov eax, dword ptr [eax + 0x48]
00685c04 call eax
00685c06 test al, al
00685c08 je 0x685c43
00685c0a mov eax, dword ptr [0xbfd65c]
00685c0f mov dword ptr [esi + 0x230], 0xf0
00685c19 cmp dword ptr [eax + 0x1c319c], 0x1e
00685c20 jne 0x685c43
00685c22 mov ecx, dword ptr [esp + 0x14]
00685c26 cmp dword ptr [ecx], 1
00685c29 jne 0x685c43
00685c2b cmp dword ptr [ecx + 4], 0
00685c2f mov edx, 0x5a
00685c34 mov eax, dword ptr [esi + 0x230]
00685c3a cmove eax, edx
00685c3d mov dword ptr [esi + 0x230], eax
00685c43 mov ecx, esi
00685c45 call 0x681390
00685c4a cmp dword ptr [esi + 0x228], 0
00685c51 jle 0x685c89
00685c53 cmp byte ptr [esp + 0x13], 0
00685c58 jne 0x685c89
00685c5a mov eax, dword ptr [esi + 0x28]
00685c5d sub eax, 0xa
00685c60 cmp eax, 0x3dd
00685c65 ja 0x685c89
00685c67 push 0
00685c69 push 0xbeab70
00685c6e push 0xbeab18
00685c73 push 0
00685c75 push esi
00685c76 call 0x9ec34c
00685c7b add esp, 0x14
00685c7e test eax, eax
00685c80 je 0x685c89
00685c82 mov ecx, eax
00685c84 call 0x680df0
00685c89 mov ecx, dword ptr [esp + 0x44]
00685c8d pop edi
00685c8e pop esi
00685c8f pop ebx
00685c90 xor ecx, esp
00685c92 call 0x9eacd7
00685c97 mov esp, ebp
00685c99 pop ebp
00685c9a ret 8
