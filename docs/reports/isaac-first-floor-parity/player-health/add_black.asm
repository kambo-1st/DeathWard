00725380 push ebp
00725381 mov ebp, esp
00725383 and esp, 0xfffffff8
00725386 sub esp, 0xc
00725389 push ebx
0072538a push esi
0072538b push edi
0072538c mov esi, ecx
0072538e nop 
00725390 mov edx, dword ptr [esi + 0x130c]
00725396 cmp edx, 0x28
00725399 jne 0x7253a9
0072539b mov eax, dword ptr [esi + 0x1d80]
007253a1 test eax, eax
007253a3 je 0x7253a9
007253a5 mov esi, eax
007253a7 jmp 0x725390
007253a9 mov ecx, esi
007253ab call 0x78cdc0
007253b0 cmp eax, 2
007253b3 je 0x72552e
007253b9 cmp edx, 0x10
007253bc jne 0x7253d1
007253be mov esi, dword ptr [esi + 0x1cb8]
007253c4 test esi, esi
007253c6 jne 0x725390
007253c8 pop edi
007253c9 pop esi
007253ca pop ebx
007253cb mov esp, ebp
007253cd pop ebp
007253ce ret 4
007253d1 mov ecx, esi
007253d3 call 0x78cdc0
007253d8 cmp eax, 3
007253db jne 0x725404
007253dd push 0
007253df lea eax, [esi + 0x294]
007253e5 push eax
007253e6 mov eax, dword ptr [ebp + 8]
007253e9 lea eax, [eax*4 + 1]
007253f0 cdq 
007253f1 sub eax, edx
007253f3 sar eax, 1
007253f5 push eax
007253f6 call 0x725cc0
007253fb pop edi
007253fc pop esi
007253fd pop ebx
007253fe mov esp, ebp
00725400 pop ebp
00725401 ret 4
00725404 mov eax, dword ptr [esi + 0x129c]
0072540a mov ecx, eax
0072540c and ecx, 1
0072540f mov dword ptr [esp + 0x14], 0
00725417 lea ebx, [eax + 1]
0072541a cmove ebx, eax
0072541d mov eax, dword ptr [ebp + 8]
00725420 and eax, 1
00725423 mov dword ptr [esp + 0x10], eax
00725427 test ecx, 1
0072542d je 0x725447
0072542f mov dword ptr [esp + 0x10], eax
00725433 test eax, eax
00725435 je 0x725447
00725437 mov dword ptr [esp + 0x14], 0xffffffff
0072543f mov dword ptr [esp + 0x10], 0
00725447 mov ecx, dword ptr [esi + 0x1ca8]
0072544d mov eax, dword ptr [esi + 0x1290]
00725453 push 0
00725455 lea edi, [eax + ecx*2]
00725458 mov ecx, esi
0072545a call 0x78cc70
0072545f dec eax
00725460 lea ecx, [ebx + edi]
00725463 cmp ecx, eax
00725465 jl 0x7254e3
00725467 xor eax, eax
00725469 dec ebx
0072546a mov dword ptr [esp + 0x10], eax
0072546e test ebx, ebx
00725470 jle 0x725516
00725476 lea edi, [ebx - 1]
00725479 nop dword ptr [eax]
00725480 cmp eax, dword ptr [ebp + 8]
00725483 jge 0x725516
00725489 cmp ebx, dword ptr [esi + 0x129c]
0072548f jg 0x7254b3
00725491 cmp ebx, 1
00725494 jb 0x7254b3
00725496 test bl, 1
00725499 je 0x7254b3
0072549b mov eax, edi
0072549d cdq 
0072549e sub eax, edx
007254a0 mov edx, 1
007254a5 sar eax, 1
007254a7 mov ecx, eax
007254a9 shl edx, cl
007254ab test dword ptr [esi + 0x12a0], edx
007254b1 jne 0x7254d3
007254b3 mov eax, dword ptr [esi + 0x12a0]
007254b9 mov ecx, ebx
007254bb shr ecx, 1
007254bd bts eax, ecx
007254c0 mov dword ptr [esi + 0x12a0], eax
007254c6 mov eax, dword ptr [esp + 0x10]
007254ca add eax, 2
007254cd mov dword ptr [esp + 0x10], eax
007254d1 jmp 0x7254d7
007254d3 mov eax, dword ptr [esp + 0x10]
007254d7 sub ebx, 2
007254da sub edi, 2
007254dd test ebx, ebx
007254df jg 0x725480
007254e1 jmp 0x725516
007254e3 mov eax, dword ptr [esp + 0x10]
007254e7 add eax, ebx
007254e9 add eax, dword ptr [ebp + 8]
007254ec cdq 
007254ed sub eax, edx
007254ef mov edi, eax
007254f1 mov eax, dword ptr [esp + 0x14]
007254f5 add eax, ebx
007254f7 sar edi, 1
007254f9 cdq 
007254fa sub eax, edx
007254fc sar eax, 1
007254fe cmp eax, edi
00725500 jge 0x725516
00725502 mov ecx, dword ptr [esi + 0x12a0]
00725508 bts ecx, eax
0072550b inc eax
0072550c cmp eax, edi
0072550e jl 0x725508
00725510 mov dword ptr [esi + 0x12a0], ecx
00725516 push dword ptr [ebp + 8]
00725519 mov ecx, esi
0072551b call 0x725130
00725520 mov ecx, esi
00725522 call 0x78c810
00725527 mov ecx, esi
00725529 call 0x78cb90
0072552e pop edi
0072552f pop esi
00725530 pop ebx
00725531 mov esp, ebp
00725533 pop ebp
00725534 ret 4
00725537 int3 
00725538 int3 
00725539 int3 
0072553a int3 
0072553b int3 
0072553c int3 
0072553d int3 
0072553e int3 
0072553f int3 
