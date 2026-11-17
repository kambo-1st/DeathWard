005b229c mov edi, dword ptr [ebp - 0x5e0]
005b22a2 mov eax, dword ptr [edi + 0x54]
005b22a5 or dword ptr [esi + 0x14b8], eax
005b22ab cmp byte ptr [ebp - 0x5b5], 0
005b22b2 mov eax, dword ptr [esi + 0x14b8]
005b22b8 je 0x5b22e0
005b22ba push 1
005b22bc push dword ptr [ebp - 0x88c]
005b22c2 lea ecx, [ebp - 0x123c]
005b22c8 push edi
005b22c9 call 0x427600
005b22ce push eax
005b22cf lea ecx, [esi + 0x1450]
005b22d5 call 0x88b1c0
005b22da mov eax, dword ptr [esi + 0x14b8]
005b22e0 test eax, eax
005b22e2 je 0x5b22eb
005b22e4 mov ecx, esi
005b22e6 call 0x72ed20
