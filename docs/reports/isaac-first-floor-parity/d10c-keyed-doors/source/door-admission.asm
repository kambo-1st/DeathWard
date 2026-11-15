006e112e mov al, byte ptr [ebp + 0xc]
006e1131 test al, al
006e1133 jne 0x6e11fe
006e1139 mov ecx, dword ptr [edi + 0xc]
006e113c cmp ecx, 2
006e113f je 0x6e13a4
006e1145 mov edx, dword ptr [edi + 8]
006e1148 cmp edx, 1
006e114b je 0x6e1156
006e114d cmp edx, 2
006e1150 jne 0x6e13a4
006e1156 cmp byte ptr [edi + 0x278], 0
006e115d je 0x6e1199
006e115f cmp ecx, 3
006e1162 jne 0x6e1199
006e1164 lea eax, [edi + 0x164]
006e116a push 0xb4a808
006e116f mov ecx, eax
006e1171 call 0x405640
006e1176 test al, al
006e1178 jne 0x6e13a4
006e117e push 0xb4a81c
006e1183 lea ecx, [edi + 0x164]
006e1189 call 0x405640
006e118e test al, al
006e1190 jne 0x6e13a4
006e1196 mov al, byte ptr [ebp + 0xc]
006e1199 test byte ptr [edi + 0x288], 1
006e11a0 je 0x6e11ad
006e11a2 cmp dword ptr [esi + 0x12b8], 0
006e11a9 jg 0x6e11fe
006e11ab jmp 0x6e11c3
006e11ad cmp dword ptr [edi + 0x15c], 2
006e11b4 jne 0x6e11c3
006e11b6 push 0x53
006e11b8 mov ecx, esi
006e11ba call 0x78d4c0
006e11bf test eax, eax
006e11c1 jg 0x6e11fb
006e11c3 cmp dword ptr [edi + 0x15c], 5
006e11ca jne 0x6e11df
006e11cc cmp dword ptr [edi + 0x27c], 0
006e11d3 jl 0x6e11df
006e11d5 mov eax, dword ptr [0xbfd65c]
006e11da cmp dword ptr [eax], 9
006e11dd je 0x6e11fb
006e11df test byte ptr [edi + 0x288], 1
006e11e6 jne 0x6e13a4
006e11ec mov ecx, esi
006e11ee call 0x726070
006e11f3 test al, al
006e11f5 je 0x6e13a4
006e11fb mov al, byte ptr [ebp + 0xc]
006e11fe test byte ptr [edi + 0x288], 1
006e1205 je 0x6e1219
006e1207 test al, al
006e1209 jne 0x6e121d
006e120b push -1
006e120d mov ecx, esi
006e120f call 0x725740
006e1214 mov al, byte ptr [ebp + 0xc]
006e1217 jmp 0x6e1224
006e1219 test al, al
006e121b je 0x6e1224
006e121d mov byte ptr [edi + 0x27a], 1
006e1224 cmp dword ptr [edi + 8], 2
006e1228 jne 0x6e124c
006e122a cmp dword ptr [edi + 0xc], 3
006e122e je 0x6e124c
006e1230 test al, al
006e1232 jne 0x6e124c
006e1234 mov ecx, edi
006e1236 mov dword ptr [edi + 0xc], 3
006e123d call 0x6df520
006e1242 mov al, 1
006e1244 pop edi
006e1245 pop esi
006e1246 mov esp, ebp
006e1248 pop ebp
006e1249 ret 8
