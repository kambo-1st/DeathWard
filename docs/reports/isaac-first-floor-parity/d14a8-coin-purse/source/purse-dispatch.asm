0072b944 mov ecx, dword ptr [ebp - 0x4c]
0072b947 test ecx, ecx
0072b949 js 0x72e439
0072b94f mov edi, ecx
0072b951 shl edi, 4
0072b954 add edi, dword ptr [esi + 0x1698]
0072b95a cmp dword ptr [esi + 0x2c], 0
0072b95e mov dword ptr [ebp - 0x50], edi
0072b961 jne 0x72e0a4
0072b967 cmp ecx, 0x12e
0072b96d jg 0x72c332
0072b973 je 0x72c322
0072b979 lea eax, [ecx - 0xc]
0072b97c cmp eax, 0xfb
0072b981 ja 0x72e057
0072b987 movzx eax, byte ptr [eax + 0x72e5f8]
0072b98e jmp dword ptr [eax*4 + 0x72e584]
