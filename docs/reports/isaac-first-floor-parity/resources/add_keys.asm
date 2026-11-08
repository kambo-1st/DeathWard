007258c0 push ebp
007258c1 mov ebp, esp
007258c3 sub esp, 8
007258c6 mov eax, dword ptr [ebp + 8]
007258c9 lea edx, [ebp + 8]
007258cc add eax, dword ptr [ecx + 0x12ac]
007258d2 cmp eax, 0x63
007258d5 mov dword ptr [ebp + 8], eax
007258d8 push esi
007258d9 lea esi, [ebp - 4]
007258dc mov dword ptr [ebp - 4], 0x63
007258e3 cmovge edx, esi
007258e6 mov dword ptr [ebp - 8], 0
007258ed lea eax, [ebp - 8]
007258f0 push 2
007258f2 cmp dword ptr [edx], 0
007258f5 cmovg eax, edx
007258f8 mov eax, dword ptr [eax]
007258fa mov dword ptr [ecx + 0x12ac], eax
00725900 call 0x725af0
00725905 mov eax, dword ptr [0xbfd65c]
0072590a pop esi
0072590b cmp dword ptr [eax + 0x101904], 2
00725912 je 0x725928
00725914 mov dword ptr [eax + 0x101904], 1
0072591e mov dword ptr [eax + 0x10190c], 2
00725928 mov esp, ebp
0072592a pop ebp
0072592b ret 4
0072592e int3 
0072592f int3 
