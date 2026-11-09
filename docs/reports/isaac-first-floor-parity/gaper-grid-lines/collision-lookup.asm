007aeec0 push ebp
007aeec1 mov ebp, esp
007aeec3 mov eax, dword ptr [ecx + 4]
007aeec6 mov eax, dword ptr [eax + 0x10]
007aeec9 test eax, eax
007aeecb je 0x7aeed8
007aeecd cmp dword ptr [eax + 8], 0x10
007aeed1 jne 0x7aeed8
007aeed3 cmp dword ptr [eax], 0x23
007aeed6 je 0x7aef1e
007aeed8 mov eax, dword ptr [ebp + 8]
007aeedb test eax, eax
007aeedd jns 0x7aeee8
007aeedf mov eax, 4
007aeee4 pop ebp
007aeee5 ret 4
007aeee8 mov edx, dword ptr [ecx + eax*4 + 0x24]
007aeeec test edx, edx
007aeeee jne 0x7aef24
007aeef0 mov eax, dword ptr [ecx + eax*4 + 0x76c]
007aeef7 cmp eax, 0xbb8
007aeefc jl 0x7aef0e
007aeefe cmp eax, 0xf9f
007aef03 jg 0x7aef15
007aef05 mov eax, 1
007aef0a pop ebp
007aef0b ret 4
007aef0e cmp eax, 0x3e8
007aef13 jl 0x7aef1e
007aef15 mov eax, 3
007aef1a pop ebp
007aef1b ret 4
007aef1e xor eax, eax
007aef20 pop ebp
007aef21 ret 4
007aef24 mov eax, dword ptr [edx + 0x3c]
007aef27 pop ebp
