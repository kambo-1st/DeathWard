0076e140 push ebp
0076e141 mov ebp, esp
0076e143 push -1
0076e145 push 0x9f8ad5
0076e14a mov eax, dword ptr fs:[0]
0076e150 push eax
0076e151 sub esp, 0x88
0076e157 mov eax, dword ptr [0xbaa3b4]
0076e15c xor eax, ebp
0076e15e mov dword ptr [ebp - 0x10], eax
0076e161 push esi
0076e162 push edi
0076e163 push eax
0076e164 lea eax, [ebp - 0xc]
0076e167 mov dword ptr fs:[0], eax
0076e16d mov edi, ecx
0076e16f mov dword ptr [ebp - 0x6c], edi
0076e172 push 0x8f
0076e177 call 0x78d4c0
0076e17c test eax, eax
0076e17e jg 0x76e4a6
0076e184 push 0
0076e186 push 0x287
0076e18b mov ecx, edi
0076e18d call 0x73af30
0076e192 test al, al
0076e194 jne 0x76e4a6
0076e19a xor ecx, ecx
0076e19c mov dword ptr [ebp - 0x58], ecx
0076e19f nop
0076e1a0 mov esi, dword ptr [0xbfd680]
0076e1a6 lea eax, [ecx*8]
0076e1ad sub eax, ecx
0076e1af mov dword ptr [ebp - 0x54], eax
0076e1b2 mov ecx, dword ptr [edi + eax*4 + 0x14c4]
0076e1b9 mov eax, dword ptr [0xbfd65c]
0076e1be test eax, eax
0076e1c0 je 0x76e1ec
0076e1c2 test ecx, ecx
0076e1c4 jns 0x76e1f4
0076e1c6 not ecx
0076e1c8 test ecx, ecx
0076e1ca js 0x76e1e8
0076e1cc mov edx, dword ptr [eax + 0x283c20]
0076e1d2 mov eax, dword ptr [eax + 0x283c24]
0076e1d8 sub eax, edx
0076e1da sar eax, 2
0076e1dd cmp ecx, eax
0076e1df jge 0x76e1e8
0076e1e1 mov eax, dword ptr [edx + ecx*4]
0076e1e4 mov eax, dword ptr [eax]
0076e1e6 jmp 0x76e210
0076e1e8 xor eax, eax
0076e1ea jmp 0x76e210
0076e1ec test ecx, ecx
0076e1ee js 0x76e496
0076e1f4 mov eax, dword ptr [esi + 0x29e88]
0076e1fa mov edx, dword ptr [esi + 0x29e84]
0076e200 sub eax, edx
0076e202 sar eax, 2
0076e205 cmp ecx, eax
0076e207 jge 0x76e496
0076e20d mov eax, dword ptr [edx + ecx*4]
0076e210 test eax, eax
0076e212 je 0x76e496
0076e218 mov eax, dword ptr [eax + 0xac]
0076e21e test eax, eax
0076e220 jne 0x76e484
0076e226 mov eax, dword ptr [0xbfd65c]
0076e22b mov esi, 1
0076e230 mov dword ptr [ebp - 0x64], esi
0076e233 mov eax, dword ptr [eax + 0x18190]
0076e239 cmp dword ptr [eax + 8], 0x11
0076e23d je 0x76e271
0076e23f mov eax, dword ptr [eax + 4]
0076e242 test eax, eax
0076e244 je 0x76e271
0076e246 mov eax, dword ptr [eax + 0x10]
0076e249 test eax, eax
0076e24b je 0x76e271
0076e24d mov eax, dword ptr [eax + 0x48]
0076e250 cmp eax, 8
0076e253 je 0x76e269
0076e255 cmp eax, 0xb
0076e258 je 0x76e269
0076e25a cmp eax, 0xc
0076e25d je 0x76e269
0076e25f cmp eax, 9
0076e262 je 0x76e269
0076e264 cmp eax, 0xa
0076e267 jne 0x76e271
0076e269 mov esi, 2
0076e26e mov dword ptr [ebp - 0x64], esi
0076e271 push 0x48
0076e273 mov ecx, edi
0076e275 call 0x78d4c0
0076e27a mov ecx, 0x10
0076e27f cmp eax, ecx
0076e281 cmovl ecx, eax
0076e284 mov dword ptr [ebp - 0x40], ecx
0076e287 test ecx, ecx
0076e289 jle 0x76e32a
0076e28f nop
0076e290 mov eax, dword ptr [edi + 0x16a8]
0076e296 sub eax, dword ptr [edi + 0x16a4]
0076e29c sar eax, 4
0076e29f cmp eax, 0x48
0076e2a2 jg 0x76e2b3
0076e2a4 push 0xb467f4
0076e2a9 push 3
0076e2ab call 0x95e330
0076e2b0 add esp, 8
0076e2b3 mov esi, dword ptr [edi + 0x16a4]
0076e2b9 add esi, 0x480
0076e2bf mov edx, dword ptr [esi]
0076e2c1 test edx, edx
0076e2c3 jne 0x76e2db
0076e2c5 push 0xb4d6c4
0076e2ca push 3
0076e2cc call 0x95e330
0076e2d1 mov edx, dword ptr [esi]
0076e2d3 add esp, 8
0076e2d6 test edx, edx
0076e2d8 jne 0x76e2db
0076e2da int3
0076e2db mov ecx, dword ptr [esi + 4]
0076e2de mov eax, edx
0076e2e0 shr eax, cl
0076e2e2 mov ecx, dword ptr [esi + 8]
0076e2e5 xor eax, edx
0076e2e7 mov edx, eax
0076e2e9 shl edx, cl
0076e2eb mov ecx, dword ptr [esi + 0xc]
0076e2ee xor edx, eax
0076e2f0 mov eax, edx
0076e2f2 shr eax, cl
0076e2f4 mov ecx, 0x14
0076e2f9 xor eax, edx
0076e2fb xor edx, edx
0076e2fd mov dword ptr [esi], eax
0076e2ff div ecx
0076e301 test edx, edx
0076e303 jne 0x76e318
0076e305 push 0x48
0076e307 mov ecx, edi
0076e309 call 0x78d4c0
0076e30e mov esi, dword ptr [ebp - 0x64]
0076e311 add esi, eax
0076e313 mov dword ptr [ebp - 0x64], esi
0076e316 jmp 0x76e31b
0076e318 mov esi, dword ptr [ebp - 0x64]
0076e31b mov ecx, dword ptr [ebp - 0x40]
0076e31e dec ecx
0076e31f mov dword ptr [ebp - 0x40], ecx
0076e322 test ecx, ecx
0076e324 jg 0x76e290
0076e32a mov eax, dword ptr [ebp - 0x58]
0076e32d cmp eax, 3
0076e330 jne 0x76e336
0076e332 xor eax, eax
0076e334 jmp 0x76e371
0076e336 cmp eax, 2
0076e339 jne 0x76e359
0076e33b cmp dword ptr [edi + 0x14fc], 0x244
0076e345 jne 0x76e359
0076e347 mov eax, dword ptr [0xbfd65c]
0076e34c cmp dword ptr [eax + 0x1c319c], 0x2c
0076e353 jne 0x76e359
0076e355 xor eax, eax
0076e357 jmp 0x76e371
0076e359 mov eax, dword ptr [ebp - 0x54]
0076e35c mov ecx, edi
0076e35e push dword ptr [edi + eax*4 + 0x14dc]
0076e365 push dword ptr [edi + eax*4 + 0x14c4]
0076e36c call 0x757d80
0076e371 push 3
0076e373 mov ecx, edi
0076e375 mov dword ptr [ebp - 0x64], eax
0076e378 call 0x78d4c0
0076e37d mov edx, dword ptr [ebp - 0x58]
0076e380 mov ecx, 3
0076e385 cmp eax, ecx
0076e387 cmovl ecx, eax
0076e38a mov dword ptr [ebp - 0x40], ecx
0076e38d test ecx, ecx
0076e38f jle 0x76e473
0076e395 lea ecx, [edx + 0xbe]
0076e39b lea eax, [ecx*8]
0076e3a2 sub eax, ecx
0076e3a4 mov ecx, dword ptr [ebp - 0x64]
0076e3a7 sub ecx, dword ptr [ebp - 0x40]
0076e3aa mov eax, dword ptr [edi + eax*4]
0076e3ad add eax, esi
0076e3af cmp eax, ecx
0076e3b1 jl 0x76e473
0076e3b7 mov eax, dword ptr [ebp - 0x40]
0076e3ba mov ecx, edi
0076e3bc push 0
0076e3be push 0
0076e3c0 push 0
0076e3c2 push edx
0076e3c3 add eax, esi
0076e3c5 push eax
0076e3c6 call 0x758030
0076e3cb test eax, eax
0076e3cd je 0x76e496
0076e3d3 mov esi, dword ptr [0xbfd680]
0076e3d9 lea ecx, [ebp - 0x40]
0076e3dc mov dword ptr [ebp - 0x40], 0xaa
0076e3e3 call 0x8b1340
0076e3e8 sub esp, 8
0076e3eb mov dword ptr [esp + 4], 0
0076e3f3 mov dword ptr [esp], 0x3f800000
0076e3fa push 0
0076e3fc push 2
0076e3fe push ecx
0076e3ff mov dword ptr [esp], 0x3f800000
0076e406 lea ecx, [esi + 0x29de0]
0076e40c push dword ptr [ebp - 0x40]
0076e40f call 0x888de0
0076e414 call 0x6c3d90
0076e419 mov ecx, dword ptr [0xbfd65c]
0076e41f push 0
0076e421 push 0xbeaaec
0076e426 push 0xbeab18
0076e42b push 0
0076e42d push eax
0076e42e push 1
0076e430 push 0
0076e432 push 0xc02fec
0076e437 lea eax, [edi + 0x294]
0076e43d push eax
0076e43e push 0x31
0076e440 push 0x3e8
0076e445 call 0x422e20
0076e44a push eax
0076e44b call 0x9ec34c
0076e450 add esp, 0x14
0076e453 mov dword ptr [eax + 0xd0], 0
0076e45d mov dword ptr [eax + 0xd4], 0xc1c00000
0076e467 mov dword ptr [eax + 0x2b0], 0x3f800000
0076e471 jmp 0x76e496
0076e473 push 0
0076e475 push 0
0076e477 push 0
0076e479 push edx
0076e47a push esi
0076e47b mov ecx, edi
0076e47d call 0x758030
0076e482 jmp 0x76e496
0076e484 cmp eax, 1
0076e487 jne 0x76e496
0076e489 mov edx, dword ptr [ebp - 0x58]
0076e48c mov ecx, edi
0076e48e push 0
0076e490 push edx
0076e491 call 0x7871c0
0076e496 mov ecx, dword ptr [ebp - 0x58]
0076e499 inc ecx
0076e49a mov dword ptr [ebp - 0x58], ecx
0076e49d cmp ecx, 4
0076e4a0 jb 0x76e1a0
