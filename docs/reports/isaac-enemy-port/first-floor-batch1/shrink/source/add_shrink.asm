0068cfb0 push ebp
0068cfb1 mov ebp, esp
0068cfb3 and esp, 0xfffffff8
0068cfb6 sub esp, 0x10
0068cfb9 push esi
0068cfba mov esi, dword ptr [ebp + 8]
0068cfbd push edi
0068cfbe push esi
0068cfbf mov edi, ecx
0068cfc1 call 0x684b00
0068cfc6 test al, al
0068cfc8 jne 0x68d158
0068cfce mov eax, dword ptr [edi]
0068cfd0 mov ecx, edi
0068cfd2 mov eax, dword ptr [eax + 0x48]
0068cfd5 call eax
0068cfd7 test al, al
0068cfd9 jne 0x68d158
0068cfdf push esi
0068cfe0 push dword ptr [ebp + 0xc]
0068cfe3 mov ecx, edi
0068cfe5 call 0x685020
0068cfea mov ecx, edi
0068cfec mov edx, eax
0068cfee mov esi, edi
0068cff0 call 0x681710
0068cff5 test al, al
0068cff7 je 0x68d00f
0068cff9 mov ecx, dword ptr [edi + 0x314]
0068cfff test ecx, ecx
0068d001 je 0x68d00f
0068d003 mov esi, ecx
0068d005 mov ecx, dword ptr [esi + 0x314]
0068d00b test ecx, ecx
0068d00d jne 0x68d003
0068d00f mov ecx, dword ptr [esi + 0x160]
0068d015 mov eax, ecx
0068d017 and eax, 0x1000800
0068d01c mov byte ptr [esp + 0xb], 1
0068d021 or eax, 0
0068d024 jne 0x68d02b
0068d026 mov byte ptr [esp + 0xb], 0
0068d02b test edx, edx
0068d02d je 0x68d158
0068d033 mov eax, ecx
0068d035 and eax, 1
0068d038 or eax, 0
0068d03b jne 0x68d158
0068d041 cmp dword ptr [esi + 0x230], eax
0068d047 jg 0x68d158
0068d04d mov ecx, dword ptr [esi + 0x234]
0068d053 test edx, edx
0068d055 jle 0x68d066
0068d057 lea eax, [ecx + edx]
0068d05a mov ecx, 0x96
0068d05f cmp eax, ecx
0068d061 cmovl ecx, eax
0068d064 jmp 0x68d06d
0068d066 neg edx
0068d068 cmp ecx, edx
0068d06a cmovl ecx, edx
0068d06d mov dword ptr [esi + 0x234], ecx
0068d073 mov ecx, dword ptr [esi + 0x160]
0068d079 mov eax, ecx
0068d07b and eax, 0x1000000
0068d080 or eax, 0
0068d083 jne 0x68d0fb
0068d085 mov eax, dword ptr [esi + 0x164]
0068d08b or ecx, 0x1000000
0068d091 mov dword ptr [esi + 0x160], ecx
0068d097 mov dword ptr [esi + 0x164], eax
0068d09d mov eax, dword ptr [edi + 0x288]
0068d0a3 mov dword ptr [edi + 0x310], 0x3eaa7efa
0068d0ad movss xmm0, dword ptr [0xbc7a28]
0068d0b5 xorps xmm0, xmmword ptr [0xb6c9b0]
0068d0bc movss dword ptr [esp + 0x10], xmm0
0068d0c2 movss xmm0, dword ptr [0xbc7a2c]
0068d0ca xorps xmm0, xmmword ptr [0xb6c9b0]
0068d0d1 movss dword ptr [esp + 0x14], xmm0
0068d0d7 movss xmm0, dword ptr [eax + 0x38]
0068d0dc mulss xmm0, dword ptr [edi + 0x30c]
0068d0e4 push -1
0068d0e6 push dword ptr [esp + 0x18]
0068d0ea push dword ptr [esp + 0x18]
0068d0ee push ecx
0068d0ef mov ecx, edi
0068d0f1 movss dword ptr [esp], xmm0
0068d0f6 call 0x6843a0
0068d0fb mov eax, dword ptr [esi]
0068d0fd mov ecx, esi
0068d0ff mov eax, dword ptr [eax + 0x48]
0068d102 call eax
0068d104 test al, al
0068d106 je 0x68d112
0068d108 mov dword ptr [esi + 0x230], 0xf0
0068d112 mov ecx, esi
0068d114 call 0x681390
0068d119 cmp dword ptr [esi + 0x234], 0
0068d120 jle 0x68d158
0068d122 cmp byte ptr [esp + 0xb], 0
0068d127 jne 0x68d158
0068d129 mov eax, dword ptr [esi + 0x28]
0068d12c sub eax, 0xa
0068d12f cmp eax, 0x3dd
0068d134 ja 0x68d158
0068d136 push 0
0068d138 push 0xbeab70
0068d13d push 0xbeab18
0068d142 push 0
0068d144 push esi
0068d145 call 0x9ec34c
0068d14a add esp, 0x14
0068d14d test eax, eax
0068d14f je 0x68d158
0068d151 mov ecx, eax
0068d153 call 0x680df0
0068d158 pop edi
0068d159 pop esi
0068d15a mov esp, ebp
0068d15c pop ebp
0068d15d ret 8
