; Repentance1.7.9b bounded native evidence. Candidate names are interpretations, not exported symbols.
004bb870 push ebx
004bb871 push esi
004bb872 mov esi, ecx
004bb874 push edi
004bb875 movss xmm1, dword ptr [esi + 0x2b8]
004bb87d ucomiss xmm1, dword ptr [0xc02fec]
004bb884 lahf 
004bb885 test ah, 0x44
004bb888 jp 0x4bb8a3
004bb88a movss xmm0, dword ptr [esi + 0x2bc]
004bb892 ucomiss xmm0, dword ptr [0xc02ff0]
004bb899 lahf 
004bb89a test ah, 0x44
004bb89d jnp 0x4bb97c
004bb8a3 cmp dword ptr [esi + 0xab4], 0x10
004bb8aa je 0x4bb97c
004bb8b0 movss xmm0, dword ptr [esi + 0x2bc]
004bb8b8 call 0x447a80
004bb8bd mulss xmm0, dword ptr [0xb6af30] ; f32=-57.2957764
004bb8c5 xorps xmm2, xmm2
004bb8c8 movss xmm1, dword ptr [0xb6ac40] ; f32=360
004bb8d0 comiss xmm2, xmm0
004bb8d3 jbe 0x4bb8de
004bb8d5 addss xmm0, xmm1
004bb8d9 comiss xmm2, xmm0
004bb8dc ja 0x4bb8d5
004bb8de comiss xmm0, xmm1
004bb8e1 jb 0x4bb8ec
004bb8e3 subss xmm0, xmm1
004bb8e7 comiss xmm0, xmm1
004bb8ea jae 0x4bb8e3
004bb8ec mulss xmm0, dword ptr [0xb6a9b0] ; f32=16
004bb8f4 divss xmm0, xmm1
004bb8f8 addss xmm0, dword ptr [0xb6a480] ; f32=0.5
004bb900 cvttss2si ecx, xmm0
004bb904 and ecx, 0x80000007
004bb90a jns 0x4bb911
004bb90c dec ecx
004bb90d or ecx, 0xfffffff8
004bb910 inc ecx
004bb911 mov edx, dword ptr [esi + 0xb10]
004bb917 cmp edx, ecx
004bb919 je 0x4bb97c
004bb91b mov eax, dword ptr [0xbfd65c]
004bb920 mov eax, dword ptr [eax + 0x1a30dc]
004bb926 sub eax, dword ptr [esi + 0x280]
004bb92c cmp eax, 1
004bb92f jg 0x4bb939
004bb931 mov dword ptr [esi + 0xb10], ecx
004bb937 jmp 0x4bb97c
004bb939 sub ecx, edx
004bb93b cmp ecx, -4
004bb93e jge 0x4bb950
004bb940 mov eax, 0xfffffffb
004bb945 sub eax, ecx
004bb947 shr eax, 3
004bb94a lea ecx, [ecx + eax*8]
004bb94d add ecx, 8
004bb950 cmp ecx, 4
004bb953 jl 0x4bb960
004bb955 lea eax, [ecx + 4]
004bb958 shr eax, 3
004bb95b neg eax
004bb95d lea ecx, [ecx + eax*8]
004bb960 lea eax, [edx + 7]
004bb963 test ecx, ecx
004bb965 js 0x4bb96a
004bb967 lea eax, [edx + 1]
004bb96a and eax, 0x80000007
004bb96f jns 0x4bb976
004bb971 dec eax
004bb972 or eax, 0xfffffff8
004bb975 inc eax
004bb976 mov dword ptr [esi + 0xb10], eax
004bb97c cmp dword ptr [esi + 0xab4], 0x10
004bb983 lea edi, [esi + 0x3c]
004bb986 mov eax, dword ptr [esi + 0xb10]
004bb98c jne 0x4bb9cb
004bb98e push 1
004bb990 push dword ptr [eax*4 + 0xa08400]
004bb997 mov ecx, edi
004bb999 call 0x405740
004bb99e test al, al
004bb9a0 je 0x4bba32
004bb9a6 mov eax, dword ptr [edi + 0x34]
004bb9a9 test eax, eax
004bb9ab je 0x4bba32
004bb9b1 lea ecx, [edi + 0x30]
004bb9b4 xorps xmm1, xmm1
004bb9b7 call 0x403c00
004bb9bc mov eax, dword ptr [edi + 0x34]
004bb9bf test eax, eax
004bb9c1 je 0x4bba32
004bb9c3 mov byte ptr [edi + 0x44], 0
004bb9c7 pop edi
004bb9c8 pop esi
004bb9c9 pop ebx
004bb9ca ret 
004bb9cb mov esi, dword ptr [edi + 0x34]
004bb9ce mov ebx, dword ptr [eax*4 + 0xa08400]
004bb9d5 test esi, esi
004bb9d7 je 0x4bba18
004bb9d9 cmp dword ptr [esi + 0x14], 0x10
004bb9dd mov eax, esi
004bb9df jb 0x4bb9e3
004bb9e1 mov eax, dword ptr [esi]
004bb9e3 mov ecx, ebx
004bb9e5 mov dl, byte ptr [eax]
004bb9e7 cmp dl, byte ptr [ecx]
004bb9e9 jne 0x4bba05
004bb9eb test dl, dl
004bb9ed je 0x4bba01
004bb9ef mov dl, byte ptr [eax + 1]
004bb9f2 cmp dl, byte ptr [ecx + 1]
004bb9f5 jne 0x4bba05
004bb9f7 add eax, 2
004bb9fa add ecx, 2
004bb9fd test dl, dl
004bb9ff jne 0x4bb9e5
004bba01 xor eax, eax
004bba03 jmp 0x4bba0a
004bba05 sbb eax, eax
004bba07 or eax, 1
004bba0a test eax, eax
004bba0c jne 0x4bba18
004bba0e cmp byte ptr [esi + 0x34], al
004bba11 je 0x4bba32
004bba13 cmp byte ptr [edi + 0x44], al
004bba16 jne 0x4bba32
004bba18 push 1
004bba1a push ebx
004bba1b mov ecx, edi
004bba1d call 0x405740
004bba22 test al, al
004bba24 je 0x4bba32
004bba26 lea ecx, [edi + 0x30]
004bba29 call 0x405330
004bba2e mov byte ptr [edi + 0x44], 1
004bba32 pop edi
004bba33 pop esi
004bba34 pop ebx
004bba35 ret 
