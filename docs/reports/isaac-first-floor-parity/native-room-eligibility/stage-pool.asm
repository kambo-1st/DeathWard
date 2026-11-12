007e79c0 push ebp
007e79c1 mov ebp, esp
007e79c3 mov eax, dword ptr [ebp + 8]
007e79c6 cmp eax, -1
007e79c9 jne 0x7e79f0
007e79cb mov eax, dword ptr [0xbfd65c]
007e79d0 test eax, eax
007e79d2 je 0x7e79e4
007e79d4 mov eax, dword ptr [eax + 0x243624]
007e79da cmp eax, 2
007e79dd je 0x7e79f5
007e79df cmp eax, 3
007e79e2 je 0x7e79f5
007e79e4 cmp ecx, 0xd
007e79e7 jne 0x7e7a39
007e79e9 mov eax, 0x23
007e79ee pop ebp
007e79ef ret
007e79f0 cmp eax, 1
007e79f3 jne 0x7e79e4
007e79f5 cmp ecx, 7
007e79f8 jne 0x7e79ff
007e79fa lea eax, [ecx + 0x12]
007e79fd pop ebp
007e79fe ret
007e79ff cmp ecx, 6
007e7a02 jne 0x7e7a09
007e7a04 lea eax, [ecx + 0x12]
007e7a07 pop ebp
007e7a08 ret
007e7a09 cmp ecx, 5
007e7a0c jne 0x7e7a13
007e7a0e lea eax, [ecx + 9]
007e7a11 pop ebp
007e7a12 ret
007e7a13 cmp edx, 4
007e7a16 jne 0x7e7a21
007e7a18 lea eax, [ecx*2 + 0x19]
007e7a1f pop ebp
007e7a20 ret
007e7a21 cmp edx, 5
007e7a24 jne 0x7e7a2f
007e7a26 lea eax, [ecx*2 + 0x1a]
007e7a2d pop ebp
007e7a2e ret
007e7a2f lea eax, [ecx - 1]
007e7a32 lea eax, [edx + eax*2]
007e7a35 add eax, ecx
007e7a37 pop ebp
007e7a38 ret
007e7a39 cmp ecx, 9
007e7a3c jge 0x7e7a66
007e7a3e dec ecx
007e7a3f cmp edx, 4
007e7a42 jne 0x7e7a4c
007e7a44 and ecx, 0xfffffffe
007e7a47 lea eax, [ecx + 0x1b]
007e7a4a pop ebp
007e7a4b ret
007e7a4c shr ecx, 1
007e7a4e cmp edx, 5
007e7a51 jne 0x7e7a5c
007e7a53 lea eax, [ecx*2 + 0x1c]
007e7a5a pop ebp
007e7a5b ret
007e7a5c lea eax, [edx + 1]
007e7a5f lea eax, [eax + ecx*2]
007e7a62 add eax, ecx
007e7a64 pop ebp
007e7a65 ret
007e7a66 jne 0x7e7a7a
007e7a68 cmp edx, 4
007e7a6b mov eax, 0xd
007e7a70 mov ecx, 0x24
007e7a75 cmove eax, ecx
007e7a78 pop ebp
007e7a79 ret
007e7a7a cmp ecx, 0xc
007e7a7d jne 0x7e7a86
007e7a7f mov eax, 0x1a
007e7a84 pop ebp
007e7a85 ret
007e7a86 lea eax, [ecx - 3]
007e7a89 lea eax, [edx + eax*2]
007e7a8c pop ebp
007e7a8d ret
