006a2023 mulss xmm1, dword ptr [edi + 0x28]
006a2028 mulss xmm2, dword ptr [edi + 0x28]
006a202d addss xmm1, xmm0
006a2031 subss xmm4, xmm2
006a2035 movss dword ptr [ebp - 0x38], xmm1
006a203a movss dword ptr [ebp - 0x34], xmm4
006a203f mov ecx, dword ptr [ebx + 8]
006a2042 movss xmm0, dword ptr [edi + 0x60]
006a2047 addss xmm0, dword ptr [ecx]
006a204b push 0
006a204d push 0xbeabf4
006a2052 push 0xbeab18
006a2057 push 0
006a2059 push eax
006a205a push 0
006a205c push dword ptr [ebp - 0x14]
006a205f lea eax, [ebp - 0x38]
006a2062 movss dword ptr [ebp - 0x30], xmm0
006a2067 movss xmm0, dword ptr [edi + 0x64]
006a206c addss xmm0, dword ptr [ecx + 4]
006a2071 mov ecx, dword ptr [0xbfd65c]
006a2077 push eax
006a2078 lea eax, [ebp - 0x30]
006a207b push eax
006a207c push dword ptr [edi + 0x94]
006a2082 movss dword ptr [ebp - 0x2c], xmm0
006a2087 push 9
006a2089 call 0x422e20
006a208e push eax
006a208f call 0x9ec34c
006a2094 jmp 0x6a1c64
006a2099 call 0x6c3d90
006a209e mov ecx, dword ptr [ebx + 0xc]
006a20a1 mov edi, dword ptr [ebx + 0x14]
006a20a4 mov esi, dword ptr [ebp - 0x14]
006a20a7 push 0
006a20a9 movss xmm3, dword ptr [ecx + 4]
006a20ae movss xmm4, dword ptr [ecx]
006a20b2 movaps xmm0, xmm3
006a20b5 mulss xmm0, dword ptr [0xb6a2f8]
006a20bd movaps xmm1, xmm4
006a20c0 mov ecx, dword ptr [ebx + 8]
006a20c3 mulss xmm1, dword ptr [0xb6a60c]
006a20cb push 0xbeabf4
006a20d0 mulss xmm0, dword ptr [edi + 0x28]
006a20d5 push 0xbeab18
006a20da mulss xmm4, dword ptr [0xb6a2f8]
006a20e2 push 0
006a20e4 mulss xmm3, dword ptr [0xb6a60c]
006a20ec subss xmm1, xmm0
006a20f0 push eax
006a20f1 movss xmm0, dword ptr [edi + 0x60]
006a20f6 lea eax, [ebp - 0x38]
006a20f9 addss xmm0, dword ptr [ecx]
006a20fd mulss xmm4, dword ptr [edi + 0x28]
006a2102 push 0
006a2104 push esi
006a2105 push eax
006a2106 movss dword ptr [ebp - 0x30], xmm0
006a210b lea eax, [ebp - 0x30]
006a210e movss xmm0, dword ptr [edi + 0x64]
006a2113 addss xmm4, xmm3
006a2117 addss xmm0, dword ptr [ecx + 4]
006a211c mov ecx, dword ptr [0xbfd65c]
006a2122 push eax
006a2123 push dword ptr [edi + 0x94]
006a2129 movss dword ptr [ebp - 0x38], xmm1
006a212e push 9
006a2130 movss dword ptr [ebp - 0x34], xmm4
006a2135 movss dword ptr [ebp - 0x2c], xmm0
006a213a call 0x422e20
006a213f push eax
006a2140 call 0x9ec34c
006a2145 add esp, 0x14
006a2148 mov dword ptr [ebp - 0x24], eax
006a214b lea eax, [ebp - 0x24]
006a214e lea ecx, [ebp - 0x4c]
006a2151 push eax
006a2152 push 0
006a2154 call 0x426fb0
006a2159 call 0x6c3d90
006a215e mov ecx, dword ptr [ebx + 0xc]
006a2161 push 0
006a2163 push 0xbeabf4
006a2168 push 0xbeab18
006a216d movss xmm4, dword ptr [ecx + 4]
006a2172 movss xmm2, dword ptr [ecx]
006a2176 movaps xmm1, xmm4
006a2179 mulss xmm1, dword ptr [0xb6a2f8]
006a2181 movaps xmm0, xmm2
006a2184 mov ecx, dword ptr [ebx + 8]
006a2187 mulss xmm0, dword ptr [0xb6a60c]
006a218f push 0
006a2191 mulss xmm1, dword ptr [edi + 0x28]
006a2196 push eax
006a2197 mulss xmm2, dword ptr [0xb6a2f8]
006a219f lea eax, [ebp - 0x38]
006a21a2 push 0
006a21a4 mulss xmm4, dword ptr [0xb6a60c]
006a21ac addss xmm1, xmm0
006a21b0 push esi
006a21b1 movss xmm0, dword ptr [edi + 0x60]
006a21b6 addss xmm0, dword ptr [ecx]
006a21ba mulss xmm2, dword ptr [edi + 0x28]
006a21bf push eax
006a21c0 movss dword ptr [ebp - 0x38], xmm1
006a21c5 movss dword ptr [ebp - 0x30], xmm0
006a21ca subss xmm4, xmm2
006a21ce movss xmm0, dword ptr [edi + 0x64]
006a21d3 addss xmm0, dword ptr [ecx + 4]
006a21d8 movss dword ptr [ebp - 0x34], xmm4
006a21dd movss dword ptr [ebp - 0x2c], xmm0
006a21e2 mov ecx, dword ptr [0xbfd65c]
006a21e8 lea eax, [ebp - 0x30]
006a21eb push eax
006a21ec push dword ptr [edi + 0x94]
006a21f2 push 9
006a21f4 call 0x422e20
006a21f9 push eax
006a21fa call 0x9ec34c
006a21ff mov esi, dword ptr [ebp - 0x48]
006a2202 add esp, 0x14
006a2205 mov dword ptr [ebp - 0x24], eax
006a2208 cmp esi, dword ptr [ebp - 0x44]
006a220b je 0x6a2217
006a220d mov dword ptr [esi], eax
006a220f add esi, 4
006a2212 mov dword ptr [ebp - 0x48], esi
006a2215 jmp 0x6a2227
006a2217 lea eax, [ebp - 0x24]
006a221a push eax
006a221b push esi
006a221c lea ecx, [ebp - 0x4c]
006a221f call 0x426fb0
006a2224 mov esi, dword ptr [ebp - 0x48]
006a2227 call 0x6c3d90
006a222c mov ecx, dword ptr [ebx + 0xc]
006a222f movss xmm5, dword ptr [0xb6a5a4]
006a2237 push 0
006a2239 push 0xbeabf4
006a223e movss xmm3, dword ptr [ecx + 4]
006a2243 movss xmm4, dword ptr [ecx]
006a2247 movaps xmm0, xmm3
006a224a mulss xmm0, dword ptr [0xb6a43c]
006a2252 movaps xmm1, xmm4
006a2255 mov ecx, dword ptr [ebx + 8]
006a2258 mulss xmm1, dword ptr [0xb6a5b0]
006a2260 push 0xbeab18
006a2265 mulss xmm4, dword ptr [0xb6a43c]
006a226d push 0
006a226f mulss xmm3, dword ptr [0xb6a5b0]
006a2277 push eax
006a2278 mulss xmm0, xmm5
006a227c lea eax, [ebp - 0x38]
006a227f push 0
006a2281 push dword ptr [ebp - 0x14]
006a2284 mulss xmm1, xmm5
006a2288 push eax
006a2289 mulss xmm0, dword ptr [edi + 0x28]
006a228e lea eax, [ebp - 0x30]
006a2291 push eax
006a2292 push dword ptr [edi + 0x94]
006a2298 mulss xmm4, xmm5
006a229c push 9
006a229e subss xmm1, xmm0
006a22a2 mulss xmm3, xmm5
006a22a6 movss xmm0, dword ptr [edi + 0x60]
006a22ab addss xmm0, dword ptr [ecx]
006a22af mulss xmm4, dword ptr [edi + 0x28]
006a22b4 movss dword ptr [ebp - 0x38], xmm1
006a22b9 movss dword ptr [ebp - 0x30], xmm0
006a22be addss xmm4, xmm3
006a22c2 movss xmm0, dword ptr [edi + 0x64]
006a22c7 addss xmm0, dword ptr [ecx + 4]
006a22cc mov ecx, dword ptr [0xbfd65c]
006a22d2 movss dword ptr [ebp - 0x34], xmm4
006a22d7 movss dword ptr [ebp - 0x2c], xmm0
006a22dc call 0x422e20
006a22e1 push eax
006a22e2 call 0x9ec34c
006a22e7 add esp, 0x14
006a22ea mov dword ptr [ebp - 0x24], eax
006a22ed cmp esi, dword ptr [ebp - 0x44]
006a22f0 je 0x6a22fc
006a22f2 mov dword ptr [esi], eax
006a22f4 add esi, 4
006a22f7 mov dword ptr [ebp - 0x48], esi
006a22fa jmp 0x6a230c
006a22fc lea eax, [ebp - 0x24]
006a22ff push eax
006a2300 push esi
006a2301 lea ecx, [ebp - 0x4c]
006a2304 call 0x426fb0
006a2309 mov esi, dword ptr [ebp - 0x48]
006a230c call 0x6c3d90
006a2311 mov ecx, dword ptr [ebx + 0xc]
006a2314 movss xmm5, dword ptr [0xb6a5a4]
006a231c movss xmm4, dword ptr [ecx + 4]
006a2321 movss xmm2, dword ptr [ecx]
006a2325 movaps xmm1, xmm4
006a2328 mulss xmm1, dword ptr [0xb6a43c]
006a2330 movaps xmm0, xmm2
006a2333 mulss xmm0, dword ptr [0xb6a5b0]
006a233b mulss xmm4, dword ptr [0xb6a5b0]
006a2343 mulss xmm2, dword ptr [0xb6a43c]
006a234b mulss xmm1, xmm5
006a234f mulss xmm0, xmm5
006a2353 mulss xmm4, xmm5
006a2357 mulss xmm2, xmm5
006a235b jmp 0x6a2023
