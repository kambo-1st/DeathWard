0068d260 push ebx
0068d261 mov ebx, esp
0068d263 sub esp, 8
0068d266 and esp, 0xfffffff8
0068d269 add esp, 4
0068d26c push ebp
0068d26d mov ebp, dword ptr [ebx + 4]
0068d270 mov dword ptr [esp + 4], ebp
0068d274 mov ebp, esp
0068d276 sub esp, 0xc
0068d279 push esi
0068d27a mov esi, ecx
0068d27c push -1
0068d27e and dword ptr [esi + 0x160], 0xfeffffff
0068d288 mov eax, dword ptr [esi + 0x164]
0068d28e mov dword ptr [esi + 0x164], eax
0068d294 movss xmm0, dword ptr [0xbc7a28]
0068d29c xorps xmm0, xmmword ptr [0xb6c9b0]
0068d2a3 mov eax, dword ptr [esi + 0x288]
0068d2a9 movss dword ptr [ebp - 8], xmm0
0068d2ae movss xmm0, dword ptr [0xbc7a2c]
0068d2b6 xorps xmm0, xmmword ptr [0xb6c9b0]
0068d2bd movss dword ptr [ebp - 4], xmm0
0068d2c2 push dword ptr [ebp - 4]
0068d2c5 movss xmm0, dword ptr [eax + 0x38]
0068d2ca push dword ptr [ebp - 8]
0068d2cd push ecx
0068d2ce movss dword ptr [esp], xmm0
0068d2d3 call 0x6843a0
0068d2d8 mov dword ptr [esi + 0x310], 0x3f800000
0068d2e2 pop esi
0068d2e3 mov esp, ebp
0068d2e5 pop ebp
0068d2e6 mov esp, ebx
0068d2e8 pop ebx
0068d2e9 ret 
