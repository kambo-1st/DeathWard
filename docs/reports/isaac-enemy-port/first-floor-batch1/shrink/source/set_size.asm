006843a0 push ebp
006843a1 mov ebp, esp
006843a3 and esp, 0xfffffff8
006843a6 movss xmm2, dword ptr [ebp + 0xc]
006843ab sub esp, 0x1c
006843ae movss xmm0, dword ptr [0xb6ae44]
006843b6 movss xmm1, dword ptr [ebp + 0x10]
006843bb ucomiss xmm2, xmm0
006843be push ebx
006843bf push esi
006843c0 push edi
006843c1 mov ebx, ecx
006843c3 lahf 
006843c4 test ah, 0x44
006843c7 jp 0x6843ec
006843c9 ucomiss xmm1, xmm0
006843cc lahf 
006843cd test ah, 0x44
006843d0 jp 0x6843ec
006843d2 mov eax, dword ptr [ebx + 0x288]
006843d8 movss xmm2, dword ptr [eax + 0x3c]
006843dd movss dword ptr [ebp + 0xc], xmm2
006843e2 movss xmm1, dword ptr [eax + 0x40]
006843e7 movss dword ptr [ebp + 0x10], xmm1
006843ec mov edi, dword ptr [ebp + 0x14]
006843ef cmp edi, -1
006843f2 jne 0x684400
006843f4 mov eax, dword ptr [ebx + 0x288]
006843fa mov edi, dword ptr [eax + 0x48]
006843fd mov dword ptr [ebp + 0x14], edi
00684400 movss xmm0, dword ptr [ebx + 0x2c8]
00684408 movss xmm3, dword ptr [ebp + 8]
0068440d ucomiss xmm0, xmm3
00684410 lahf 
00684411 test ah, 0x44
00684414 jp 0x68443c
00684416 movss xmm0, dword ptr [ebx + 0x2cc]
0068441e ucomiss xmm0, xmm2
00684421 lahf 
00684422 test ah, 0x44
00684425 jp 0x68443c
00684427 movss xmm0, dword ptr [ebx + 0x2d0]
0068442f ucomiss xmm0, xmm1
00684432 lahf 
00684433 test ah, 0x44
00684436 jnp 0x684615
0068443c movss dword ptr [ebx + 0x2c8], xmm3
00684444 lea esi, [ebx + 0x170]
0068444a mov eax, dword ptr [esi]
0068444c mov dword ptr [esi + 4], eax
0068444f xor eax, eax
00684451 movss dword ptr [ebx + 0x2cc], xmm2
00684459 movss xmm2, dword ptr [0xb6a874]
00684461 movss dword ptr [ebx + 0x2d0], xmm1
00684469 mov dword ptr [esp + 0xc], eax
0068446d test edi, edi
0068446f jle 0x68453e
00684475 movd xmm1, edi
00684479 cvtdq2ps xmm1, xmm1
0068447c movss dword ptr [esp + 0x14], xmm1
00684482 xorps xmm0, xmm0
00684485 cvtsi2ss xmm0, eax
00684489 addss xmm0, xmm0
0068448d mulss xmm0, xmm2
00684491 divss xmm0, xmm1
00684495 cvtps2pd xmm0, xmm0
00684498 movsd qword ptr [esp + 0x20], xmm0
0068449e call 0x9ec382
006844a3 movss xmm1, dword ptr [ebx + 0x2c8]
006844ab mulss xmm1, dword ptr [ebx + 0x2cc]
006844b3 cvtsd2ss xmm0, xmm0
006844b7 mulss xmm0, xmm1
006844bb movss dword ptr [esp + 0x10], xmm0
006844c1 movss dword ptr [esp + 0x18], xmm0
006844c7 movsd xmm0, qword ptr [esp + 0x20]
006844cd call 0x9ec3a0
006844d2 mov eax, dword ptr [esi + 4]
006844d5 xorps xmm1, xmm1
006844d8 cvtsd2ss xmm1, xmm0
006844dc movss xmm0, dword ptr [ebx + 0x2c8]
006844e4 mulss xmm0, dword ptr [ebx + 0x2d0]
006844ec mulss xmm1, xmm0
006844f0 movss dword ptr [esp + 0x1c], xmm1
006844f6 cmp eax, dword ptr [esi + 8]
006844f9 je 0x684510
006844fb movss xmm0, dword ptr [esp + 0x10]
00684501 movss dword ptr [eax], xmm0
00684505 movss dword ptr [eax + 4], xmm1
0068450a add dword ptr [esi + 4], 8
0068450e jmp 0x68451d
00684510 lea ecx, [esp + 0x18]
00684514 push ecx
00684515 push eax
00684516 mov ecx, esi
00684518 call 0x422130
