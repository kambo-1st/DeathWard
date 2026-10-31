00697c60 push ebp
00697c61 mov ebp, esp
00697c63 and esp, 0xfffffff8
00697c66 sub esp, 0x30
00697c69 mov eax, dword ptr [0xbaa3b4]
00697c6e xor eax, esp
00697c70 mov dword ptr [esp + 0x2c], eax
00697c74 mov eax, dword ptr [ebp + 0x14]
00697c77 mov edx, dword ptr [ebp + 0xc]
00697c7a push esi
00697c7b mov esi, ecx
00697c7d mov ecx, dword ptr [ebp + 0x10]
00697c80 push edi
00697c81 mov edi, dword ptr [ebp + 8]
00697c84 cmp edi, dword ptr [esi + 0x28]
00697c87 jne 0x697cb4
00697c89 cmp edx, dword ptr [esi + 0x2c]
00697c8c jne 0x697cb4
00697c8e cmp ecx, dword ptr [esi + 0x30]
00697c91 jne 0x697cb4
00697c93 test eax, eax
00697c95 js 0x697c9f
00697c97 cmp eax, dword ptr [esi + 0xbb4]
00697c9d jne 0x697cb4
00697c9f xor al, al
00697ca1 pop edi
00697ca2 pop esi
00697ca3 mov ecx, dword ptr [esp + 0x2c]
00697ca7 xor ecx, esp
00697ca9 call 0x9eacd7
00697cae mov esp, ebp
00697cb0 pop ebp
00697cb1 ret 0x10
00697cb4 mov dword ptr [esi + 0x28], edi
00697cb7 mov dword ptr [esi + 0x2c], edx
00697cba mov dword ptr [esi + 0x30], ecx
00697cbd test eax, eax
00697cbf js 0x697cce
00697cc1 mov dword ptr [esi + 0xbb4], eax
00697cc7 mov byte ptr [esi + 0xbb3], 1
00697cce push ecx
00697ccf mov ecx, dword ptr [0xbfd680]
00697cd5 push edx
00697cd6 push edi
00697cd7 lea ecx, [ecx + 0x29f88]
00697cdd call 0x66d910
00697ce2 test eax, eax
00697ce4 je 0x697cfd
00697ce6 cmp byte ptr [eax + 0x34], 0
00697cea jne 0x697cfd
00697cec mov dword ptr [esi + 0xbb4], 0xffffffff
00697cf6 mov byte ptr [esi + 0xbb3], 0
00697cfd xor eax, eax
00697cff mov dword ptr [esi + 0xbb8], 0
00697d09 mov word ptr [esi + 0xbc4], ax
00697d10 mov ecx, esi
00697d12 mov eax, dword ptr [esi]
00697d14 mov dword ptr [esi + 0xbbc], 0
00697d1e mov dword ptr [esi + 0xbc0], 0x3f800000
00697d28 mov dword ptr [esi + 0xafc], 0x3f800000
00697d32 mov dword ptr [esi + 0xaf8], 0
00697d3c call dword ptr [eax + 0x5c]
00697d3f movss xmm1, dword ptr [esi + 0x30c]
00697d47 mov ecx, esi
00697d49 movaps xmm0, xmm1
00697d4c mov dword ptr [esi + 0xb88], 0x3f800000
00697d56 mulss xmm0, dword ptr [0xbc7a28]
00697d5e mulss xmm1, dword ptr [0xbc7a2c]
00697d66 movss dword ptr [esi + 0xd8], xmm0
00697d6e movss dword ptr [esi + 0xdc], xmm1
00697d76 mov eax, dword ptr [esi]
00697d78 call dword ptr [eax + 0x60]
00697d7b movss xmm0, dword ptr [esi + 0xe94]
00697d83 lea eax, [esi + 0x2dc]
00697d89 mulss xmm0, dword ptr [eax]
00697d8d lea ecx, [esi + 0x2d8]
00697d93 mov dword ptr [esi + 0xbac], 0
00697d9d movss dword ptr [eax], xmm0
00697da1 comiss xmm0, dword ptr [ecx]
00697da4 cmova eax, ecx
00697da7 mov eax, dword ptr [eax]
00697da9 mov dword ptr [ecx], eax
00697dab mov eax, dword ptr [esi + 0x1a4]
00697db1 cmp eax, dword ptr [esi + 0x1a8]
00697db7 je 0x697dd5
00697db9 mov edx, dword ptr [esi]
00697dbb lea ecx, [esp + 8]
00697dbf push 1
00697dc1 push 0
00697dc3 push 0xfffffc18
00697dc8 push 1
00697dca call 0x402120
00697dcf push eax
00697dd0 mov ecx, esi
00697dd2 call dword ptr [edx + 0x38]
00697dd5 lea ecx, [esi + 0x364]
00697ddb call 0x7a34f0
00697de0 push dword ptr [esi + 0x2c]
00697de3 mov ecx, dword ptr [0xbfd680]
00697de9 push dword ptr [esi + 0x28]
00697dec add ecx, 0x14
00697def call 0x8861d0
00697df4 push esi
00697df5 mov byte ptr [esi + 0xbb0], 1
00697dfc call 0x6d94d0
00697e01 test al, al
00697e03 je 0x697e0c
00697e05 push ecx
00697e06 push esi
00697e07 call 0x6d9590
00697e0c mov ecx, dword ptr [esp + 0x34]
00697e10 mov al, 1
00697e12 pop edi
00697e13 pop esi
00697e14 xor ecx, esp
00697e16 call 0x9eacd7
00697e1b mov esp, ebp
00697e1d pop ebp
00697e1e ret 0x10
