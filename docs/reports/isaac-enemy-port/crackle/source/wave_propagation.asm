005c2176 mov ecx, dword ptr [ebp - 0xeb8]
005c217c mov byte ptr [ecx + 0x169], 0
005c2183 mov ecx, dword ptr [ebp - 0xeb8]
005c2189 call 0x682200
005c218e and eax, 0x80000001
005c2193 jns 0x5c219a
005c2195 dec eax
005c2196 or eax, 0xfffffffe
005c2199 inc eax
005c219a test eax, eax
005c219c jne 0x5c2448
005c21a2 mov ecx, dword ptr [0xbfd65c]
005c21a8 call 0x4023f0
005c21ad mov dword ptr [ebp - 0x1884], eax
005c21b3 push 0xc02fec
005c21b8 mov ecx, dword ptr [ebp - 0xeb8]
005c21be add ecx, 0x28c
005c21c4 call 0x962c70
005c21c9 movzx edx, al
005c21cc test edx, edx
005c21ce je 0x5c21ed
005c21d0 mov eax, dword ptr [ebp - 0xeb8]
005c21d6 add eax, 0x294
005c21db push eax
005c21dc mov ecx, dword ptr [ebp - 0xeb8]
005c21e2 add ecx, 0x28c
005c21e8 call 0x962cd0
005c21ed movss xmm0, dword ptr [0xb6aa0c]
005c21f5 movss dword ptr [ebp - 0x2508], xmm0
005c21fd lea ecx, [ebp - 0x2508]
005c2203 push ecx
005c2204 lea edx, [ebp - 0x405c]
005c220a push edx
005c220b mov eax, dword ptr [ebp - 0xeb8]
005c2211 push ecx
005c2212 movss xmm0, dword ptr [eax + 0x3c4]
005c221a movss dword ptr [esp], xmm0
005c221f lea ecx, [ebp - 0x4064]
005c2225 push ecx
005c2226 call 0x9627f0
005c222b add esp, 8
005c222e mov ecx, eax
005c2230 call 0x962b50
005c2235 push eax
005c2236 mov ecx, dword ptr [ebp - 0xeb8]
005c223c add ecx, 0x28c
005c2242 call 0x962a90
005c2247 mov edx, dword ptr [ebp - 0xeb8]
005c224d add edx, 0x28c
005c2253 push edx
005c2254 push ecx
005c2255 xorps xmm0, xmm0
005c2258 movss dword ptr [esp], xmm0
005c225d push ecx
005c225e xorps xmm0, xmm0
005c2261 movss dword ptr [esp], xmm0
005c2266 push ecx
005c2267 xorps xmm0, xmm0
005c226a movss dword ptr [esp], xmm0
005c226f mov eax, dword ptr [ebp - 0xeb8]
005c2275 add eax, 0x28c
005c227a push eax
005c227b lea ecx, [ebp - 0x406c]
005c2281 push ecx
005c2282 xorps xmm3, xmm3
005c2285 mov ecx, dword ptr [ebp - 0x1884]
005c228b call 0x7cec10
005c2290 mov ecx, eax
005c2292 call 0x962c70
005c2297 movzx edx, al
005c229a test edx, edx
005c229c je 0x5c2435
005c22a2 mov eax, dword ptr [ebp - 0xeb8]
005c22a8 mov ecx, dword ptr [eax + 0x290]
005c22ae push ecx
005c22af mov edx, dword ptr [eax + 0x28c]
005c22b5 push edx
005c22b6 mov ecx, dword ptr [ebp - 0x1884]
005c22bc call 0x7aee40
005c22c1 cmp eax, 1
005c22c4 jg 0x5c2435
005c22ca mov ecx, dword ptr [ebp - 0xeb8]
005c22d0 call 0x682200
005c22d5 cvtsi2ss xmm0, eax
005c22d9 movss dword ptr [ebp - 0x250c], xmm0
005c22e1 movss xmm0, dword ptr [ebp - 0x250c]
005c22e9 mulss xmm0, dword ptr [0xb6a248]
005c22f1 movss xmm1, dword ptr [0xb6a614]
005c22f9 subss xmm1, xmm0
005c22fd movss dword ptr [ebp - 0x1888], xmm1
005c2305 call 0x659280
005c230a push eax
005c230b mov eax, dword ptr [ebp - 0xeb8]
005c2311 mov ecx, dword ptr [eax + 0x30]
005c2314 push ecx
005c2315 mov edx, dword ptr [ebp - 0xeb8]
005c231b mov eax, dword ptr [edx + 0x320]
005c2321 push eax
005c2322 push 0xc02fec
005c2327 mov ecx, dword ptr [ebp - 0xeb8]
005c232d add ecx, 0x28c
005c2333 push ecx
005c2334 push 0x93
005c2339 push 0x3e8
005c233e mov ecx, dword ptr [0xbfd65c]
005c2344 call 0x422e20
005c2349 mov dword ptr [ebp - 0x10f4], eax
005c234f mov edx, dword ptr [ebp - 0xeb8]
005c2355 mov eax, dword ptr [edx + 0x34]
005c2358 push eax
005c2359 mov ecx, dword ptr [ebp - 0x10f4]
005c235f call 0x4424b0
005c2364 mov ecx, dword ptr [ebp - 0xeb8]
005c236a mov edx, dword ptr [ecx + 0x38]
005c236d push edx
005c236e mov ecx, dword ptr [ebp - 0x10f4]
005c2374 call 0x4a3f60
005c2379 push 0xbc7a28
005c237e lea edx, [ebp - 0x1888]
005c2384 lea ecx, [ebp - 0x4074]
005c238a call 0x4120b0
005c238f add esp, 4
005c2392 push eax
005c2393 mov ecx, dword ptr [ebp - 0x10f4]
005c2399 call 0x427330
005c239e mov ecx, dword ptr [ebp - 0xeb8]
005c23a4 add ecx, 0x3c
005c23a7 call 0x4023b0
005c23ac push eax
005c23ad mov ecx, dword ptr [ebp - 0x10f4]
005c23b3 call 0x427440
005c23b8 mov ecx, eax
005c23ba call 0x402370
005c23bf mov ecx, 2
005c23c4 call 0x659230
005c23c9 test eax, eax
005c23cb setne al
005c23ce movzx ecx, al
005c23d1 push ecx
005c23d2 mov ecx, dword ptr [ebp - 0x10f4]
005c23d8 call 0x427440
005c23dd mov ecx, eax
005c23df call 0x427280
005c23e4 push 0
005c23e6 push 0x20000000
005c23eb mov ecx, dword ptr [ebp - 0xeb8]
005c23f1 call 0x4122f0
005c23f6 movzx edx, al
005c23f9 test edx, edx
005c23fb je 0x5c240f
005c23fd push 0
005c23ff push 0x20000000
005c2404 mov ecx, dword ptr [ebp - 0x10f4]
005c240a call 0x4122a0
005c240f movss xmm0, dword ptr [0xb6a350]
005c2417 comiss xmm0, dword ptr [ebp - 0x1888]
005c241e jbe 0x5c2433
005c2420 mov eax, dword ptr [ebp - 0xeb8]
005c2426 mov edx, dword ptr [eax]
005c2428 mov ecx, dword ptr [ebp - 0xeb8]
005c242e mov eax, dword ptr [edx + 0x28]
005c2431 call eax
005c2433 jmp 0x5c2448
005c2435 mov ecx, dword ptr [ebp - 0xeb8]
005c243b mov edx, dword ptr [ecx]
005c243d mov ecx, dword ptr [ebp - 0xeb8]
005c2443 mov eax, dword ptr [edx + 0x28]
005c2446 call eax
005c2448 jmp 0x5e9122
