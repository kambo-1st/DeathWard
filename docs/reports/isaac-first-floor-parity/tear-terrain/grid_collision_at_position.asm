007aee40 push ebp
007aee41 mov ebp, esp
007aee43 movss xmm2, dword ptr [0xb6aa3c]
007aee4b movss xmm0, dword ptr [ebp + 8]
007aee50 subss xmm0, xmm2
007aee54 push esi
007aee55 divss xmm0, xmm2
007aee59 addss xmm0, dword ptr [0xb6a480]
007aee61 cvttss2si esi, xmm0
007aee65 movss xmm0, dword ptr [ebp + 0xc]
007aee6a subss xmm0, dword ptr [0xb6ab20]
007aee72 divss xmm0, xmm2
007aee76 addss xmm0, dword ptr [0xb6a480]
007aee7e cvttss2si edx, xmm0
007aee82 test esi, esi
007aee84 js 0x7aeea6
007aee86 mov eax, dword ptr [ecx + 0xc]
007aee89 cmp esi, eax
007aee8b jge 0x7aeea6
007aee8d test edx, edx
007aee8f js 0x7aeea6
007aee91 cmp edx, dword ptr [ecx + 0x10]
007aee94 jge 0x7aeea6
007aee96 imul eax, edx
007aee99 add eax, esi
007aee9b push eax
007aee9c call 0x7aeec0
007aeea1 pop esi
007aeea2 pop ebp
007aeea3 ret 8
007aeea6 or eax, 0xffffffff
007aeea9 push eax
007aeeaa call 0x7aeec0
007aeeaf pop esi
007aeeb0 pop ebp
007aeeb1 ret 8
007aeeb4 int3 
007aeeb5 int3 
007aeeb6 int3 
007aeeb7 int3 
007aeeb8 int3 
007aeeb9 int3 
007aeeba int3 
007aeebb int3 
007aeebc int3 
007aeebd int3 
007aeebe int3 
007aeebf int3 
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
