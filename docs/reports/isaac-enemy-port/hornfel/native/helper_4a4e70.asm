; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.
; Literal float/string comments describe bytes, not inferred native field meanings.
004a4e70 push ebx
004a4e71 mov ebx, esp
004a4e73 sub esp, 8
004a4e76 and esp, 0xfffffff8
004a4e79 add esp, 4
004a4e7c push ebp
004a4e7d mov ebp, dword ptr [ebx + 4]
004a4e80 mov dword ptr [esp + 4], ebp
004a4e84 mov ebp, esp
004a4e86 push -1
004a4e88 push 0x9ee50d
004a4e8d mov eax, dword ptr fs:[0]
004a4e93 push eax
004a4e94 push ebx
004a4e95 sub esp, 0x28
004a4e98 mov eax, dword ptr [0xbaa3b4] ; [0xbaa3b4] f32=-0.00294341473
004a4e9d xor eax, ebp
004a4e9f mov dword ptr [ebp - 0x14], eax
004a4ea2 push esi
004a4ea3 push edi
004a4ea4 push eax
004a4ea5 lea eax, [ebp - 0xc]
004a4ea8 mov dword ptr fs:[0], eax
004a4eae mov edi, ecx
004a4eb0 mov dword ptr [ebp - 0x38], edi
004a4eb3 mov dword ptr [ebp - 0x20], 0
004a4eba mov dword ptr [ebp - 0x1c], 0
004a4ec1 mov dword ptr [ebp - 0x18], 0
004a4ec8 lea eax, [ebp - 0x28]
004a4ecb mov dword ptr [ebp - 4], 0
004a4ed2 push eax
004a4ed3 push 0
004a4ed5 lea ecx, [ebp - 0x20]
004a4ed8 mov dword ptr [ebp - 0x28], 0
004a4edf mov dword ptr [ebp - 0x24], 6
004a4ee6 call 0x48d900
004a4eeb mov ecx, dword ptr [ebp - 0x1c]
004a4eee xor eax, eax
004a4ef0 mov edx, dword ptr [ebp - 0x20]
004a4ef3 mov esi, ecx
004a4ef5 sub esi, edx
004a4ef7 sar esi, 3
004a4efa test esi, esi
004a4efc je 0x4a4f0b
004a4efe nop 
004a4f00 cmp dword ptr [edx + eax*8], 8
004a4f04 je 0x4a4f33
004a4f06 inc eax
004a4f07 cmp eax, esi
004a4f09 jb 0x4a4f00
004a4f0b mov dword ptr [ebp - 0x28], 8
004a4f12 mov dword ptr [ebp - 0x24], 3
004a4f19 cmp ecx, dword ptr [ebp - 0x18]
004a4f1c je 0x4a4f44
004a4f1e mov dword ptr [ecx], 8
004a4f24 mov dword ptr [ecx + 4], 3
004a4f2b add ecx, 8
004a4f2e mov dword ptr [ebp - 0x1c], ecx
004a4f31 jmp 0x4a4f57
004a4f33 add dword ptr [edx + eax*8 + 4], 3
004a4f38 jns 0x4a4f57
004a4f3a mov dword ptr [edx + eax*8 + 4], 0
004a4f42 jmp 0x4a4f57
004a4f44 lea eax, [ebp - 0x28]
004a4f47 push eax
004a4f48 push ecx
004a4f49 lea ecx, [ebp - 0x20]
004a4f4c call 0x48d900
004a4f51 mov ecx, dword ptr [ebp - 0x1c]
004a4f54 mov edx, dword ptr [ebp - 0x20]
004a4f57 mov esi, ecx
004a4f59 xor eax, eax
004a4f5b sub esi, edx
004a4f5d sar esi, 3
004a4f60 test esi, esi
004a4f62 je 0x4a4f6f
004a4f64 cmp dword ptr [edx + eax*8], 0x10
004a4f68 je 0x4a4f97
004a4f6a inc eax
004a4f6b cmp eax, esi
004a4f6d jb 0x4a4f64
004a4f6f mov dword ptr [ebp - 0x28], 0x10
004a4f76 mov dword ptr [ebp - 0x24], 1
004a4f7d cmp ecx, dword ptr [ebp - 0x18]
004a4f80 je 0x4a4fa8
004a4f82 mov dword ptr [ecx], 0x10
004a4f88 mov dword ptr [ecx + 4], 1
004a4f8f add ecx, 8
004a4f92 mov dword ptr [ebp - 0x1c], ecx
004a4f95 jmp 0x4a4fb5
004a4f97 add dword ptr [edx + eax*8 + 4], 1
004a4f9c jns 0x4a4fb5
004a4f9e mov dword ptr [edx + eax*8 + 4], 0
004a4fa6 jmp 0x4a4fb5
004a4fa8 lea eax, [ebp - 0x28]
004a4fab push eax
004a4fac push ecx
004a4fad lea ecx, [ebp - 0x20]
004a4fb0 call 0x48d900
004a4fb5 call 0x6c3d90
004a4fba movq xmm0, qword ptr [0xa08c44] ; [0xa08c44] f32=7.00649232e-45
004a4fc2 lea ecx, [ebp - 0x20]
004a4fc5 or eax, 1
004a4fc8 movq qword ptr [ebp - 0x2c], xmm0
004a4fcd mov dword ptr [ebp - 0x30], eax
004a4fd0 sub esp, 0x10
004a4fd3 mov eax, dword ptr [0xa08c4c] ; [0xa08c4c] f32=9.80908925e-45
004a4fd8 mov dword ptr [ebp - 0x24], eax
004a4fdb mov eax, esp
004a4fdd movups xmm0, xmmword ptr [ebp - 0x30]
004a4fe1 movups xmmword ptr [eax], xmm0
004a4fe4 call 0x489420 ; PickOutcome
004a4fe9 mov dword ptr [ebp - 4], 0xffffffff
004a4ff0 mov esi, eax
004a4ff2 mov edx, dword ptr [ebp - 0x20]
004a4ff5 mov dword ptr [ebp - 0x24], esi
004a4ff8 test edx, edx
004a4ffa je 0x4a502e
004a4ffc mov ecx, dword ptr [ebp - 0x18]
004a4fff mov eax, edx
004a5001 sub ecx, edx
004a5003 and ecx, 0xfffffff8
004a5006 cmp ecx, 0x1000
004a500c jb 0x4a5024
004a500e mov edx, dword ptr [edx - 4]
004a5011 add ecx, 0x23
004a5014 sub eax, edx
004a5016 add eax, -4
004a5019 cmp eax, 0x1f
004a501c jbe 0x4a5024
004a501e call dword ptr [0xa065ac] ; [0xa065ac] f32=1.12523062e-38
004a5024 push ecx
004a5025 push edx
004a5026 call 0x9eb08e
004a502b add esp, 8
004a502e call 0x6c3d90
004a5033 mov ecx, dword ptr [0xbfd65c]
004a5039 push eax
004a503a push 0
004a503c push edi
004a503d push 0xc02fec
004a5042 lea eax, [edi + 0x294]
004a5048 push eax
004a5049 push esi
004a504a push 4
004a504c call 0x422e20
004a5051 mov esi, eax
004a5053 mov ecx, dword ptr [esi + 0x314]
004a5059 lea edi, [esi + 0x314]
004a505f mov byte ptr [esi + 0x169], 0
004a5066 mov dword ptr [esi + 0x180], 0
004a5070 mov dword ptr [esi + 0x17c], 0
004a507a mov dword ptr [esi + 0x360], 0x23
004a5084 mov dword ptr [esi + 0x364], 0x23
004a508e test ecx, ecx
004a5090 je 0x4a50a4
004a5092 lea eax, [ebp - 0x34]
004a5095 mov dword ptr [ebp - 0x34], edi
004a5098 push eax
004a5099 add ecx, 0x324
004a509f call 0x4bc3c0
004a50a4 mov ecx, dword ptr [ebp - 0x38]
004a50a7 mov dword ptr [edi], ecx
004a50a9 test ecx, ecx
004a50ab je 0x4a50b3
004a50ad push edi
004a50ae call 0x4bae70
004a50b3 mov eax, dword ptr [ebp - 0x24]
004a50b6 cmp eax, 8
004a50b9 jne 0x4a50c4
004a50bb movups xmm0, xmmword ptr [0xbc4c70] ; [0xbc4c70] f32=5.87747175e-39
004a50c2 jmp 0x4a50d0
004a50c4 cmp eax, 0x10
004a50c7 jne 0x4a50de
004a50c9 movups xmm0, xmmword ptr [0xbc4c20] ; [0xbc4c20] f32=2.5243549e-29
004a50d0 mov byte ptr [esi + 0x3b3], 1
004a50d7 movups xmmword ptr [esi + 0x388], xmm0
004a50de mov eax, dword ptr [esi + 0x164]
004a50e4 or dword ptr [esi + 0x160], 0x20
004a50eb mov dword ptr [esi + 0x164], eax
004a50f1 mov eax, esi
004a50f3 mov ecx, dword ptr [ebp - 0xc]
004a50f6 mov dword ptr fs:[0], ecx
004a50fd pop ecx
004a50fe pop edi
004a50ff pop esi
004a5100 mov ecx, dword ptr [ebp - 0x14]
004a5103 xor ecx, ebp
004a5105 call 0x9eacd7
004a510a mov esp, ebp
004a510c pop ebp
004a510d mov esp, ebx
004a510f pop ebx
004a5110 ret 4
