00631ca4 mov eax, dword ptr [edi + 0x388]
00631caa and eax, 2
00631cad mov dword ptr [ebp - 0x330], 0
00631cb7 or eax, 0
00631cba je 0x63213e
00631cc0 call 0x6c3d90
00631cc5 mov ecx, dword ptr [0xbfd65c]
00631ccb lea esi, [edi + 0x294]
00631cd1 push eax
00631cd2 push 0
00631cd4 push 0
00631cd6 push 0xc02fec
00631cdb push esi
00631cdc push 1
00631cde push 0x3e8
00631ce3 call 0x422e20
00631ce8 movups xmm0, xmmword ptr [0xbfec58]
00631cef mov ecx, dword ptr [edi + 0x314]
00631cf5 push 0
00631cf7 push 0
00631cf9 push 4
00631cfb sub esp, 0x10
00631cfe mov dword ptr [ebp - 0x330], eax
00631d04 mov eax, esp
00631d06 movups xmmword ptr [eax], xmm0
00631d09 test ecx, ecx
00631d0b je 0x631d10
00631d0d push ecx
00631d0e jmp 0x631d11
00631d10 push edi
00631d11 mov ecx, dword ptr [0xbfd65c]
00631d17 push 1
00631d19 sub esp, 8
00631d1c mov dword ptr [esp + 4], 0x42700000
00631d24 mov dword ptr [esp], 0x42480000
00631d2b push esi
00631d2c call 0x6d1750
00631d31 mov eax, dword ptr [edi + 0x38c]
00631d37 and dword ptr [edi + 0x388], 0xfffffffd
00631d3e mov dword ptr [edi + 0x38c], eax
