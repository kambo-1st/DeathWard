004f9194 mov edx, dword ptr [edi + 0xaf0]
004f919a test edx, edx
004f919c jg 0x4f93e9
004f91a2 mov eax, dword ptr [edi + 0x160]
004f91a8 and eax, 0x1000a00
004f91ad or eax, 0
004f91b0 jne 0x4f93e9
004f91b6 cmp dword ptr [edi + 0xe6c], -1
004f91bd je 0x4f91d1
004f91bf push 7
004f91c1 push eax
004f91c2 mov ecx, edi
004f91c4 call 0x6a15a0
004f91c9 test al, al
004f91cb je 0x4f95dc
004f91d1 cmp dword ptr [edi + 0xe6c], -1
004f91d8 movss xmm0, dword ptr [0xc02fec]
004f91e0 movss xmm1, dword ptr [0xc02ff0]
004f91e8 movss dword ptr [ebp - 0x124], xmm0
004f91f0 movss dword ptr [ebp - 0x11c], xmm1
004f91f8 je 0x4f922b
004f91fa movss xmm2, dword ptr [0xb6a2cc]
004f9202 lea eax, [ebp - 0x120]
004f9208 push eax
004f9209 mov ecx, edi
004f920b call 0x6af380
004f9210 movss xmm0, dword ptr [eax]
004f9214 movss dword ptr [ebp - 0x124], xmm0
004f921c movss xmm0, dword ptr [eax + 4]
004f9221 movss dword ptr [ebp - 0x11c], xmm0
004f9229 jmp 0x4f928f
004f922b movss xmm1, dword ptr [edi + 0x2b8]
004f9233 movss xmm2, dword ptr [edi + 0x2bc]
004f923b movaps xmm0, xmm1
004f923e mulss xmm0, xmm1
004f9242 movaps xmm1, xmm2
004f9245 mulss xmm1, xmm2
004f9249 addss xmm0, xmm1
004f924d call 0x4228c0
004f9252 movaps xmm1, xmm0
004f9255 xorps xmm2, xmm2
004f9258 comiss xmm1, xmm2
004f925b jbe 0x4f9287
004f925d movss xmm0, dword ptr [edi + 0x2b8]
004f9265 divss xmm0, xmm1
004f9269 movss dword ptr [ebp - 0x124], xmm0
004f9271 movss xmm0, dword ptr [edi + 0x2bc]
004f9279 divss xmm0, xmm1
004f927d movss dword ptr [ebp - 0x11c], xmm0
004f9285 jmp 0x4f928f
004f9287 movss xmm0, dword ptr [ebp - 0x11c]
004f928f movss xmm1, dword ptr [ebp - 0x124]
004f9297 ucomiss xmm1, dword ptr [0xc02fec]
004f929e lahf 
004f929f test ah, 0x44
004f92a2 jp 0x4f92b5
004f92a4 ucomiss xmm0, dword ptr [0xc02ff0]
004f92ab lahf 
004f92ac test ah, 0x44
004f92af jnp 0x4f95dc
004f92b5 cmp dword ptr [edi + 0x28], 0xb
004f92b9 jne 0x4f92df
004f92bb cmp dword ptr [edi + 0xe6c], -1
004f92c2 je 0x4f92c8
004f92c4 xor edx, edx
004f92c6 jmp 0x4f92d6
004f92c8 call 0x6c3d90
004f92cd xor edx, edx
004f92cf mov ecx, 0x14
004f92d4 div ecx
004f92d6 lea eax, [edx + 0x28]
004f92d9 mov dword ptr [edi + 0xaf0], eax
004f92df lea ecx, [ebp - 0x118]
004f92e5 call 0x430d70
004f92ea cmp dword ptr [edi + 0x28], 0xee
004f92f1 mov dword ptr [ebp - 0x10c], 0x3e99999a
004f92fb mov dword ptr [ebp - 0x110], 0xc0a00000
004f9305 jne 0x4f934c
004f9307 cmp dword ptr [edi + 0xe6c], -1
004f930e je 0x4f9314
004f9310 xor edx, edx
004f9312 jmp 0x4f9322
004f9314 call 0x6c3d90
004f9319 xor edx, edx
004f931b mov ecx, 0x1e
004f9320 div ecx
004f9322 movaps xmm0, xmmword ptr [0xb6c330]
004f9329 lea eax, [edx + 0x3c]
004f932c or dword ptr [ebp - 0xc0], 2
004f9333 mov dword ptr [edi + 0xaf0], eax
004f9339 mov eax, dword ptr [ebp - 0xbc]
004f933f mov dword ptr [ebp - 0xbc], eax
004f9345 movups xmmword ptr [ebp - 0xdc], xmm0
004f934c call 0x690cc0
004f9351 sub eax, 6
004f9354 je 0x4f936c
004f9356 sub eax, 0x15
004f9359 je 0x4f936c
004f935b sub eax, 1
004f935e jne 0x4f9376
004f9360 mov dword ptr [ebp - 0x84], 3
004f936a jmp 0x4f9376
004f936c mov dword ptr [ebp - 0x84], 4
004f9376 movss xmm1, dword ptr [ebp - 0x124]
004f937e lea eax, [ebp - 0x118]
004f9384 mulss xmm1, dword ptr [0xb6a8f4]
004f938c mov ecx, edi
004f938e push eax
004f938f push 0
004f9391 lea eax, [ebp - 0x128]
004f9397 movss dword ptr [ebp - 0x128], xmm1
004f939f movss xmm1, dword ptr [ebp - 0x11c]
004f93a7 mulss xmm1, dword ptr [0xb6a8f4]
004f93af push eax
004f93b0 lea eax, [edi + 0x294]
004f93b6 push eax
004f93b7 movss dword ptr [ebp - 0x124], xmm1
004f93bf call 0x6a1a20
004f93c4 push ecx
004f93c5 mov dword ptr [esp], 0x3f800000
004f93cc push 0
004f93ce push 2
004f93d0 push ecx
004f93d1 mov dword ptr [esp], 0x3f800000
004f93d8 mov ecx, edi
004f93da push 0xb2
004f93df call 0x6ad720
004f93e4 jmp 0x4f95dc
004f93e9 cvttss2si eax, dword ptr [edi + 0x2fc]
004f93f1 cvttss2si ecx, dword ptr [edi + 0x2f8]
004f93f9 sub ecx, eax
004f93fb add ecx, edx
004f93fd mov dword ptr [edi + 0xaf0], ecx
004f9403 jmp 0x4f95dc
