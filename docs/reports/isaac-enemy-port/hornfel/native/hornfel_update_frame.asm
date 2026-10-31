; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.
; Literal float/string comments describe bytes, not inferred native field meanings.
004a8000 push ebp
004a8001 mov ebp, esp
004a8003 and esp, 0xfffffff8
004a8006 push ecx
004a8007 push ebx
004a8008 push esi
004a8009 mov esi, ecx
004a800b push edi
004a800c cmp dword ptr [esi + 0xab4], 0xa
004a8013 mov edi, dword ptr [esi + 0x32c]
004a8019 jne 0x4a8043
004a801b mov ecx, dword ptr [esi + 0xb3c]
004a8021 test ecx, ecx
004a8023 je 0x4a8043
004a8025 push 0xa
004a8027 call 0x4a8620
004a802c mov eax, dword ptr [esi + 0xb3c]
004a8032 mov ecx, dword ptr [eax + 0x314]
004a8038 test ecx, ecx
004a803a je 0x4a8043
004a803c push 0xa
004a803e call 0x4a8620
004a8043 test edi, edi
004a8045 je 0x4a813b
004a804b cmp byte ptr [esi + 0x169], 0
004a8052 je 0x4a80e9
004a8058 movss xmm1, dword ptr [0xb6aa3c] ; [0xb6aa3c] f32=40
004a8060 movss xmm2, dword ptr [edi + 0x294]
004a8068 movss xmm3, dword ptr [edi + 0x298]
004a8070 subss xmm2, xmm1
004a8074 subss xmm3, dword ptr [0xb6ab20] ; [0xb6ab20] f32=120
004a807c mov eax, dword ptr [0xbfd65c]
004a8081 divss xmm2, xmm1
004a8085 mov eax, dword ptr [eax + 0x18190]
004a808b mov ebx, dword ptr [eax + 0xc]
004a808e mov edi, dword ptr [eax + 0x10]
004a8091 divss xmm3, xmm1
004a8095 addss xmm2, dword ptr [0xb6a480] ; [0xb6a480] f32=0.5
004a809d addss xmm3, dword ptr [0xb6a480] ; [0xb6a480] f32=0.5
004a80a5 cvttss2si edx, xmm2
004a80a9 cvttss2si ecx, xmm3
004a80ad cmp edx, 1
004a80b0 jl 0x4a80c5
004a80b2 lea eax, [ebx - 1]
004a80b5 cmp edx, eax
004a80b7 jge 0x4a80c9
004a80b9 cmp ecx, 1
004a80bc jl 0x4a80d0
004a80be lea eax, [edi - 1]
004a80c1 cmp ecx, eax
004a80c3 jl 0x4a813b
004a80c5 test edx, edx
004a80c7 js 0x4a80db
004a80c9 lea eax, [ebx - 1]
004a80cc cmp edx, eax
004a80ce jg 0x4a80db
004a80d0 test ecx, ecx
004a80d2 js 0x4a80db
004a80d4 lea eax, [edi - 1]
004a80d7 cmp ecx, eax
004a80d9 jle 0x4a813b
004a80db mov ecx, esi
004a80dd call 0x4a5a10
004a80e2 pop edi
004a80e3 pop esi
004a80e4 pop ebx
004a80e5 mov esp, ebp
004a80e7 pop ebp
004a80e8 ret 
004a80e9 cmp dword ptr [edi + 0xab4], 0
004a80f0 jne 0x4a80f9
004a80f2 mov ecx, edi
004a80f4 call 0x4bba40
004a80f9 mov dword ptr [edi + 0xab4], 3
004a8103 mov eax, dword ptr [esi + 0x28c]
004a8109 mov dword ptr [edi + 0x294], eax
004a810f mov eax, dword ptr [esi + 0x290]
004a8115 mov dword ptr [edi + 0x298], eax
004a811b movss xmm0, dword ptr [0xc02fec]
004a8123 movss dword ptr [edi + 0x2b8], xmm0
004a812b movss xmm0, dword ptr [0xc02ff0]
004a8133 movss dword ptr [edi + 0x2bc], xmm0
004a813b pop edi
004a813c pop esi
004a813d pop ebx
004a813e mov esp, ebp
004a8140 pop ebp
004a8141 ret 
