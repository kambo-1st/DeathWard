0088b1c0 push ebp
0088b1c1 mov ebp, esp
0088b1c3 push ebx
0088b1c4 push esi
0088b1c5 push edi
0088b1c6 mov edi, ecx
0088b1c8 cmp byte ptr [edi + 0x11], 0
0088b1cc jne 0x88b23b
0088b1ce mov edx, dword ptr [ebp + 0x10]
0088b1d1 test edx, edx
0088b1d3 je 0x88b23b
0088b1d5 mov ecx, dword ptr [edi + 8]
0088b1d8 mov eax, dword ptr [edi + 4]
0088b1db mov ebx, dword ptr [ebp + 8]
0088b1de cmp eax, ecx
0088b1e0 je 0x88b1ef
0088b1e2 mov edx, dword ptr [ebx]
0088b1e4 cmp dword ptr [eax], edx
0088b1e6 je 0x88b242
0088b1e8 add eax, 0xc
0088b1eb cmp eax, ecx
0088b1ed jne 0x88b1e4
0088b1ef push ebx
0088b1f0 lea ecx, [edi + 4]
0088b1f3 call 0x5b6180
0088b1f8 mov ecx, dword ptr [edi + 8]
0088b1fb mov eax, 0x2aaaaaab
0088b200 mov esi, dword ptr [edi + 4]
0088b203 sub ecx, esi
0088b205 imul ecx
0088b207 mov ecx, dword ptr [ebp + 0x10]
0088b20a sar edx, 1
0088b20c mov eax, edx
0088b20e shr eax, 0x1f
0088b211 add eax, edx
0088b213 lea eax, [eax + eax*2]
0088b216 mov dword ptr [esi + eax*4 - 8], ecx
0088b21a mov ecx, dword ptr [edi + 0x14]
0088b21d test ecx, ecx
0088b21f je 0x88b230
0088b221 cmp byte ptr [ebp + 0xc], 0
0088b225 je 0x88b230
0088b227 push 0
0088b229 push dword ptr [ebx]
0088b22b call 0x7296d0
0088b230 mov eax, dword ptr [ebx]
0088b232 mov eax, dword ptr [eax + 0x54]
0088b235 or dword ptr [edi], eax
0088b237 mov byte ptr [edi + 0x10], 1
0088b23b pop edi
0088b23c pop esi
0088b23d pop ebx
0088b23e pop ebp
0088b23f ret 0xc
0088b242 mov edx, dword ptr [ebp + 0x10]
0088b245 cmp eax, ecx
0088b247 je 0x88b1ef
0088b249 add dword ptr [eax + 4], edx
0088b24c mov ecx, dword ptr [ebx + 8]
0088b24f add dword ptr [eax + 8], ecx
0088b252 mov eax, dword ptr [ebx]
0088b254 mov eax, dword ptr [eax + 0x54]
0088b257 or dword ptr [edi], eax
0088b259 mov byte ptr [edi + 0x10], 1
0088b25d pop edi
0088b25e pop esi
0088b25f pop ebx
0088b260 pop ebp
0088b261 ret 0xc
