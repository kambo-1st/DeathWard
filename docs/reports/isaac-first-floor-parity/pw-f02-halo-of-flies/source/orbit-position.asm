005f521e lea eax, [eax + eax*4]
005f5221 addss xmm1, dword ptr [eax*4 + 0xbc4540]
005f522a movaps xmm0, xmm1
005f522d movss dword ptr [esp + 0xc], xmm1
005f5233 call 0x411fe0
005f5238 mulss xmm0, dword ptr [ebx + 0xcb4]
005f5240 mov esi, dword ptr [ebp + 0xc]
005f5243 mov edi, dword ptr [ebp + 8]
005f5246 addss xmm0, dword ptr [esi]
005f524a movss dword ptr [edi], xmm0
005f524e movss xmm0, dword ptr [esp + 0xc]
005f5254 call 0x412010
005f5259 mulss xmm0, dword ptr [ebx + 0xcb8]
005f5261 mov eax, edi
005f5263 addss xmm0, dword ptr [esi + 4]
005f5268 movss dword ptr [edi + 4], xmm0
005f526d pop edi
005f526e pop esi
005f526f pop ebx
005f5270 mov esp, ebp
005f5272 pop ebp
