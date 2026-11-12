007066d9 movq xmm0, qword ptr [0xa08b30]
007066e1 lea ebx, [edi + 0x14]
007066e4 imul eax, eax, 0xb8
007066ea movq qword ptr [ebp - 0x18], xmm0
007066ef add ebx, eax
007066f1 mov eax, dword ptr [ebp + 0x10]
007066f4 mov dword ptr [ebp - 0x1c], eax
007066f7 mov ecx, ebx
007066f9 mov eax, dword ptr [0xa08b38]
007066fe mov dword ptr [ebp - 0x10], eax
00706701 lea eax, [ebp - 0x1c]
00706704 push eax
00706705 mov dword ptr [ebp - 0xc], ebx
00706708 call 0x705d10
