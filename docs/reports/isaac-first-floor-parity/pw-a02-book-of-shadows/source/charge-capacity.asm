00757d80 push ebp
00757d81 mov ebp, esp
00757d83 mov eax, dword ptr [ebp + 0xc]
00757d86 push esi
00757d87 mov esi, dword ptr [ebp + 8]
00757d8a cmp esi, 0x11e
00757d90 je 0x757da2
00757d92 cmp esi, 0x107
00757d98 je 0x757da2
00757d9a cmp esi, 0x15c
00757da0 jne 0x757daa
00757da2 test eax, eax
00757da4 jg 0x757e38
00757daa cmp esi, 0x1e9
00757db0 jne 0x757dbe
00757db2 movzx eax, ax
00757db5 test eax, eax
00757db7 je 0x757e18
00757db9 pop esi
00757dba pop ebp
00757dbb ret 8
00757dbe cmp esi, 0x2c9
00757dc4 jne 0x757dd9
00757dc6 cmp dword ptr [ecx + 0x130c], 0x1a
00757dcd jne 0x757e18
00757dcf mov eax, 0x1e
00757dd4 pop esi
00757dd5 pop ebp
00757dd6 ret 8
00757dd9 cmp esi, 0x2d2
00757ddf jne 0x757e0b
00757de1 mov eax, dword ptr [ecx + 0x130c]
00757de7 cmp eax, 0x25
00757dea je 0x757df1
00757dec cmp eax, 0x27
00757def jne 0x757e18
00757df1 push 0
00757df3 push 0x26b
00757df8 call 0x73af30
00757dfd test al, al
00757dff je 0x757e18
00757e01 mov eax, 0x12c
00757e06 pop esi
00757e07 pop ebp
00757e08 ret 8
00757e0b cmp esi, 0x1a6
00757e11 jne 0x757e18
00757e13 cmp eax, 3
00757e16 jl 0x757e36
00757e18 mov ecx, dword ptr [0xbfd680]
00757e1e push esi
00757e1f lea ecx, [ecx + 0x29e84]
00757e25 call 0x6fe5e0
00757e2a test eax, eax
00757e2c je 0x757e36
00757e2e mov eax, dword ptr [eax + 0x74]
00757e31 pop esi
00757e32 pop ebp
00757e33 ret 8
00757e36 xor eax, eax
00757e38 pop esi
00757e39 pop ebp
00757e3a ret 8
00757e3d int3
00757e3e int3
00757e3f int3
