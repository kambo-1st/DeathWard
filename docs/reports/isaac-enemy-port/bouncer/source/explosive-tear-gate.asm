0064dd2a lea edx, [edi + 0x378]
0064dd30 push 0xbc4ca0
0064dd35 lea ecx, [ebp - 0xec]
0064dd3b call 0x412050
0064dd40 add esp, 4
0064dd43 mov ecx, dword ptr [eax]
0064dd45 or ecx, dword ptr [eax + 4]
0064dd48 jne 0x64dd52
0064dd4a mov ecx, dword ptr [eax + 8]
0064dd4d or ecx, dword ptr [eax + 0xc]
0064dd50 je 0x64dd81
0064dd52 push 0xbc4ce0
0064dd57 lea edx, [edi + 0x378]
0064dd5d lea ecx, [ebp - 0xdc]
0064dd63 call 0x412050
0064dd68 add esp, 4
0064dd6b mov ecx, dword ptr [eax]
0064dd6d or ecx, dword ptr [eax + 4]
0064dd70 jne 0x64dd81
0064dd72 mov ecx, dword ptr [eax + 8]
0064dd75 or ecx, dword ptr [eax + 0xc]
0064dd78 mov byte ptr [ebp - 0xb1], 1
0064dd7f je 0x64dd88
0064dd81 mov byte ptr [ebp - 0xb1], 0
