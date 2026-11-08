00943a80 push ebp
00943a81 mov ebp, esp
00943a83 and esp, 0xfffffff8
00943a86 movups xmm0, xmmword ptr [ebp + 0x20]
00943a8a mov eax, dword ptr [ebp + 0x40]
00943a8d sub esp, 0x24
00943a90 mov ecx, esp
00943a92 push ecx
00943a93 movups xmmword ptr [ecx], xmm0
00943a96 movups xmm0, xmmword ptr [ebp + 0x30]
00943a9a movups xmmword ptr [ecx + 0x10], xmm0
00943a9e mov dword ptr [ecx + 0x20], eax
00943aa1 movss xmm0, dword ptr [ebp + 0x1c]
00943aa6 movss dword ptr [esp], xmm0
00943aab push dword ptr [ebp + 0x18]
00943aae push dword ptr [ebp + 0x14]
00943ab1 push dword ptr [ebp + 0x10]
00943ab4 push dword ptr [ebp + 0xc]
00943ab7 push dword ptr [ebp + 8]
00943aba call 0x74aef0
00943abf mov eax, dword ptr [ebp + 8]
00943ac2 add esp, 0x3c
00943ac5 mov esp, ebp
00943ac7 pop ebp
