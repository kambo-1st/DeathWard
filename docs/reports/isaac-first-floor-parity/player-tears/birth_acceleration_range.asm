0075799f call 0x651770
007579a4 mov eax, dword ptr [edi + 0x13c4]
007579aa lea ecx, [esp + 0x30]
007579ae push 1
007579b0 push 0
007579b2 push 0xff
007579b7 mov dword ptr [esi + 0x368], eax
007579bd mov eax, dword ptr [esi]
007579bf push -1
007579c1 push ecx
007579c2 mov ecx, esi
007579c4 call dword ptr [eax + 0x38]
007579c7 mov eax, dword ptr [edi + 0x13c8]
007579cd mov ecx, dword ptr [esi + 0x314]
007579d3 mov dword ptr [esi + 0x770], eax
