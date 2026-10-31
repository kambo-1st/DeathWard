00692a10 test al, al
00692a12 je 0x692a34
00692a14 mov eax, dword ptr [esi + 0x70]
00692a17 test eax, eax
00692a19 je 0x692a34
00692a1b lea ecx, [esi + 0x6c]
00692a1e xorps xmm1, xmm1
00692a21 call 0x403c00
00692a26 mov eax, dword ptr [esi + 0x70]
00692a29 test eax, eax
00692a2b je 0x692a34
00692a2d mov byte ptr [esi + 0x80], 0
00692a34 mov ecx, dword ptr [esi + 0x288]
00692a3a movss xmm0, dword ptr [0xb6a274]
00692a42 push 1
00692a44 movss dword ptr [ebp - 0x90], xmm0
00692a4c mov al, byte ptr [ecx + 0x58]
00692a4f mov byte ptr [esi + 0xb8c], al
00692a55 mov al, byte ptr [ecx + 0x2c]
00692a58 mov byte ptr [esi + 0xb8d], al
00692a5e mov eax, dword ptr [ecx + 0xe0]
00692a64 mov dword ptr [esi + 0xb90], eax
00692a6a mov eax, dword ptr [ecx + 0xe4]
00692a70 mov ecx, dword ptr [0xbfd65c]
00692a76 add ecx, 0x1ba40
00692a7c mov dword ptr [esi + 0xb94], eax
00692a82 push ecx
00692a83 push 0xd0
00692a88 call 0x91d340
00692a8d test eax, eax
