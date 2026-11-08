00725740 push ebp
00725741 mov ebp, esp
00725743 sub esp, 8
00725746 push ebx
00725747 push esi
00725748 push edi
00725749 mov edi, dword ptr [ebp + 8]
0072574c mov ebx, ecx
0072574e test edi, edi
00725750 jle 0x725785
00725752 call 0x78cdc0
00725757 cmp eax, 3
0072575a jne 0x725785
0072575c mov esi, dword ptr [ebx + 0x1294]
00725762 lea eax, [edi + edi]
00725765 push 0
00725767 push eax
00725768 call 0x724f00
0072576d mov eax, dword ptr [ebx + 0x1294]
00725773 mov ecx, edi
00725775 sub eax, esi
00725777 xor edi, edi
00725779 cdq 
0072577a sub eax, edx
0072577c sar eax, 1
0072577e sub ecx, eax
00725780 test ecx, ecx
00725782 cmovg edi, ecx
00725785 mov ecx, dword ptr [0xbfd65c]
0072578b mov esi, dword ptr [ebx + 0x12b8]
00725791 add ecx, 0x1ba40
00725797 push 1
00725799 push ecx
0072579a add esi, edi
0072579c push 0x1a0
007257a1 mov dword ptr [ebp + 8], esi
007257a4 call 0x91d340
007257a9 neg eax
007257ab mov dword ptr [ebp - 8], 0
007257b2 lea edx, [ebp - 4]
007257b5 sbb eax, eax
007257b7 lea ecx, [ebp + 8]
007257ba and eax, 0x384
007257bf add eax, 0x63
007257c2 cmp esi, eax
007257c4 mov dword ptr [ebp - 4], eax
007257c7 lea eax, [ebp - 8]
007257ca cmovge ecx, edx
007257cd push 1
007257cf cmp dword ptr [ecx], 0
007257d2 cmovg eax, ecx
007257d5 mov ecx, ebx
007257d7 mov eax, dword ptr [eax]
007257d9 mov dword ptr [ebx + 0x12b8], eax
007257df call 0x725af0
007257e4 mov eax, dword ptr [0xbfd65c]
007257e9 cmp dword ptr [eax + 0x101904], 2
007257f0 je 0x725806
007257f2 mov dword ptr [eax + 0x101904], 1
007257fc mov dword ptr [eax + 0x10190c], 2
00725806 pop edi
00725807 pop esi
00725808 pop ebx
00725809 mov esp, ebp
0072580b pop ebp
