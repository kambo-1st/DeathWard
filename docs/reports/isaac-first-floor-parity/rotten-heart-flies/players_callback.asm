0091aa70 push ebp
0091aa71 mov ebp, esp
0091aa73 push -1
0091aa75 push 0xa0141d
0091aa7a mov eax, dword ptr fs:[0]
0091aa80 push eax
0091aa81 sub esp, 0x14
0091aa84 push ebx
0091aa85 push esi
0091aa86 push edi
0091aa87 mov eax, dword ptr [0xbaa3b4]
0091aa8c xor eax, ebp
0091aa8e push eax
0091aa8f lea eax, [ebp - 0xc]
0091aa92 mov dword ptr fs:[0], eax
0091aa98 mov esi, ecx
0091aa9a mov edx, dword ptr [esi + 0x14]
0091aa9d xor edi, edi
0091aa9f mov ebx, dword ptr [esi + 0x10]
0091aaa2 mov eax, edx
0091aaa4 sub eax, ebx
0091aaa6 sar eax, 2
0091aaa9 test eax, eax
0091aaab je 0x91aaf3
0091aaad mov eax, edx
0091aaaf nop 
0091aab0 sub edx, ebx
0091aab2 cmp edx, 4
0091aab5 jae 0x91aac9
0091aab7 push 0xb3f4d0
0091aabc push 3
0091aabe call 0x95e330
0091aac3 mov eax, dword ptr [esi + 0x14]
0091aac6 add esp, 8
0091aac9 mov ecx, dword ptr [esi + 0x10]
0091aacc sub eax, ecx
0091aace sar eax, 2
0091aad1 cmp edi, eax
0091aad3 jae 0x91aad8
0091aad5 lea ecx, [ecx + edi*4]
0091aad8 mov ecx, dword ptr [ecx]
0091aada call 0x76e140
0091aadf mov edx, dword ptr [esi + 0x14]
0091aae2 inc edi
0091aae3 mov ebx, dword ptr [esi + 0x10]
0091aae6 mov ecx, edx
0091aae8 sub ecx, ebx
0091aaea mov eax, edx
0091aaec sar ecx, 2
0091aaef cmp edi, ecx
0091aaf1 jb 0x91aab0
0091aaf3 push 0
0091aaf5 push 1
0091aaf7 push -1
0091aaf9 push -1
0091aafb push 3
0091aafd lea eax, [ebp - 0x1c]
0091ab00 push eax
0091ab01 mov eax, dword ptr [0xbfd65c]
0091ab06 mov ecx, dword ptr [eax + 0x18190]
0091ab0c add ecx, 0x1218
0091ab12 call 0x415ed0
0091ab17 mov dword ptr [ebp - 4], 0
0091ab1e xor esi, esi
0091ab20 mov ebx, dword ptr [ebp - 0x10]
0091ab23 mov edi, dword ptr [ebp - 0x18]
0091ab26 test ebx, ebx
0091ab28 je 0x91ab3d
0091ab2a nop word ptr [eax + eax]
0091ab30 mov ecx, dword ptr [edi + esi*4]
0091ab33 call 0x609f80
0091ab38 inc esi
0091ab39 cmp esi, ebx
0091ab3b jb 0x91ab30
0091ab3d cmp byte ptr [ebp - 0x1c], 0
0091ab41 jne 0x91ab4c
0091ab43 push edi
0091ab44 call 0x9eace5
0091ab49 add esp, 4
0091ab4c mov ecx, dword ptr [ebp - 0xc]
0091ab4f mov dword ptr fs:[0], ecx
0091ab56 pop ecx
0091ab57 pop edi
0091ab58 pop esi
0091ab59 pop ebx
0091ab5a mov esp, ebp
0091ab5c pop ebp
0091ab5d ret 
