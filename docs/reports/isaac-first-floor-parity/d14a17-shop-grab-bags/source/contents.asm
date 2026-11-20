006b3179 cmp edi, 0x45
006b317c jne 0x6b3673
006b3182 mov dword ptr [ebp - 0xa0], 0
006b318c mov dword ptr [ebp - 0x9c], 0
006b3196 mov dword ptr [ebp - 0x98], 0
006b31a0 mov byte ptr [ebp - 4], 4
006b31a4 lea ecx, [ebp - 0xa0]
006b31aa mov eax, dword ptr [ebp - 0xa4]
006b31b0 mov dword ptr [ebp - 0xac], 0x28
006b31ba mov dword ptr [ebp - 0xa8], 0xf
006b31c4 cmp dword ptr [eax + 0x30], 2
006b31c8 lea eax, [ebp - 0xac]
006b31ce push eax
006b31cf push 0
006b31d1 jne 0x6b3351
006b31d7 call 0x48d900
006b31dc mov eax, dword ptr [ebp - 0x9c]
006b31e2 xor ecx, ecx
006b31e4 mov edi, dword ptr [ebp - 0xa0]
006b31ea mov edx, eax
006b31ec sub edx, edi
006b31ee sar edx, 3
006b31f1 test edx, edx
006b31f3 je 0x6b3203
006b31f5 cmp dword ptr [edi + ecx*8], 0x6000a
006b31fc je 0x6b3237
006b31fe inc ecx
006b31ff cmp ecx, edx
006b3201 jb 0x6b31f5
006b3203 mov dword ptr [ebp - 0xac], 0x6000a
006b320d mov dword ptr [ebp - 0xa8], 0xa
006b3217 cmp eax, dword ptr [ebp - 0x98]
006b321d je 0x6b3248
006b321f mov dword ptr [eax], 0x6000a
006b3225 mov dword ptr [eax + 4], 0xa
006b322c add eax, 8
006b322f mov dword ptr [ebp - 0x9c], eax
006b3235 jmp 0x6b3267
006b3237 add dword ptr [edi + ecx*8 + 4], 0xa
006b323c jns 0x6b3267
006b323e mov dword ptr [edi + ecx*8 + 4], 0
006b3246 jmp 0x6b3267
006b3248 lea ecx, [ebp - 0xac]
006b324e push ecx
006b324f push eax
006b3250 lea ecx, [ebp - 0xa0]
006b3256 call 0x48d900
006b325b mov eax, dword ptr [ebp - 0x9c]
006b3261 mov edi, dword ptr [ebp - 0xa0]
006b3267 mov edx, eax
006b3269 xor ecx, ecx
006b326b sub edx, edi
006b326d sar edx, 3
006b3270 test edx, edx
006b3272 je 0x6b3282
006b3274 cmp dword ptr [edi + ecx*8], 0xb000a
006b327b je 0x6b32b6
006b327d inc ecx
006b327e cmp ecx, edx
006b3280 jb 0x6b3274
006b3282 mov dword ptr [ebp - 0xac], 0xb000a
006b328c mov dword ptr [ebp - 0xa8], 5
006b3296 cmp eax, dword ptr [ebp - 0x98]
006b329c je 0x6b32c7
006b329e mov dword ptr [eax], 0xb000a
006b32a4 mov dword ptr [eax + 4], 5
006b32ab add eax, 8
006b32ae mov dword ptr [ebp - 0x9c], eax
006b32b4 jmp 0x6b32e6
006b32b6 add dword ptr [edi + ecx*8 + 4], 5
006b32bb jns 0x6b32e6
006b32bd mov dword ptr [edi + ecx*8 + 4], 0
006b32c5 jmp 0x6b32e6
006b32c7 lea ecx, [ebp - 0xac]
006b32cd push ecx
006b32ce push eax
006b32cf lea ecx, [ebp - 0xa0]
006b32d5 call 0x48d900
006b32da mov eax, dword ptr [ebp - 0x9c]
006b32e0 mov edi, dword ptr [ebp - 0xa0]
006b32e6 mov edx, eax
006b32e8 xor ecx, ecx
006b32ea sub edx, edi
006b32ec sar edx, 3
006b32ef test edx, edx
006b32f1 je 0x6b32fe
006b32f3 cmp dword ptr [edi + ecx*8], 0x46
006b32f7 je 0x6b3339
006b32f9 inc ecx
006b32fa cmp ecx, edx
006b32fc jb 0x6b32f3
006b32fe mov dword ptr [ebp - 0xac], 0x46
006b3308 mov dword ptr [ebp - 0xa8], 0xf
006b3312 cmp eax, dword ptr [ebp - 0x98]
006b3318 je 0x6b3543
006b331e mov dword ptr [eax], 0x46
006b3324 mov dword ptr [eax + 4], 0xf
006b332b add eax, 8
006b332e mov dword ptr [ebp - 0x9c], eax
006b3334 jmp 0x6b355c
006b3339 add dword ptr [edi + ecx*8 + 4], 0xf
006b333e jns 0x6b355c
006b3344 mov dword ptr [edi + ecx*8 + 4], 0
006b334c jmp 0x6b355c
006b3351 call 0x48d900
006b3356 mov eax, dword ptr [ebp - 0x9c]
006b335c xor ecx, ecx
006b335e mov edi, dword ptr [ebp - 0xa0]
006b3364 mov edx, eax
006b3366 sub edx, edi
006b3368 sar edx, 3
006b336b test edx, edx
006b336d je 0x6b337b
006b336f nop
006b3370 cmp dword ptr [edi + ecx*8], 0x1e
006b3374 je 0x6b33af
006b3376 inc ecx
006b3377 cmp ecx, edx
006b3379 jb 0x6b3370
006b337b mov dword ptr [ebp - 0xac], 0x1e
006b3385 mov dword ptr [ebp - 0xa8], 0x14
006b338f cmp eax, dword ptr [ebp - 0x98]
006b3395 je 0x6b33c0
006b3397 mov dword ptr [eax], 0x1e
006b339d mov dword ptr [eax + 4], 0x14
006b33a4 add eax, 8
006b33a7 mov dword ptr [ebp - 0x9c], eax
006b33ad jmp 0x6b33df
006b33af add dword ptr [edi + ecx*8 + 4], 0x14
006b33b4 jns 0x6b33df
006b33b6 mov dword ptr [edi + ecx*8 + 4], 0
006b33be jmp 0x6b33df
006b33c0 lea ecx, [ebp - 0xac]
006b33c6 push ecx
006b33c7 push eax
006b33c8 lea ecx, [ebp - 0xa0]
006b33ce call 0x48d900
006b33d3 mov eax, dword ptr [ebp - 0x9c]
006b33d9 mov edi, dword ptr [ebp - 0xa0]
006b33df mov edx, eax
006b33e1 xor ecx, ecx
006b33e3 sub edx, edi
006b33e5 sar edx, 3
006b33e8 test edx, edx
006b33ea je 0x6b33fb
006b33ec nop dword ptr [eax]
006b33f0 cmp dword ptr [edi + ecx*8], 0x14
006b33f4 je 0x6b342f
006b33f6 inc ecx
006b33f7 cmp ecx, edx
006b33f9 jb 0x6b33f0
006b33fb mov dword ptr [ebp - 0xac], 0x14
006b3405 mov dword ptr [ebp - 0xa8], 0xf
006b340f cmp eax, dword ptr [ebp - 0x98]
006b3415 je 0x6b3440
006b3417 mov dword ptr [eax], 0x14
006b341d mov dword ptr [eax + 4], 0xf
006b3424 add eax, 8
006b3427 mov dword ptr [ebp - 0x9c], eax
006b342d jmp 0x6b345f
006b342f add dword ptr [edi + ecx*8 + 4], 0xf
006b3434 jns 0x6b345f
006b3436 mov dword ptr [edi + ecx*8 + 4], 0
006b343e jmp 0x6b345f
006b3440 lea ecx, [ebp - 0xac]
006b3446 push ecx
006b3447 push eax
006b3448 lea ecx, [ebp - 0xa0]
006b344e call 0x48d900
006b3453 mov eax, dword ptr [ebp - 0x9c]
006b3459 mov edi, dword ptr [ebp - 0xa0]
006b345f mov edx, eax
006b3461 xor ecx, ecx
006b3463 sub edx, edi
006b3465 sar edx, 3
006b3468 test edx, edx
006b346a je 0x6b347b
006b346c nop dword ptr [eax]
006b3470 cmp dword ptr [edi + ecx*8], 0x5a
006b3474 je 0x6b34af
006b3476 inc ecx
006b3477 cmp ecx, edx
006b3479 jb 0x6b3470
006b347b mov dword ptr [ebp - 0xac], 0x5a
006b3485 mov dword ptr [ebp - 0xa8], 4
006b348f cmp eax, dword ptr [ebp - 0x98]
006b3495 je 0x6b34c0
006b3497 mov dword ptr [eax], 0x5a
006b349d mov dword ptr [eax + 4], 4
006b34a4 add eax, 8
006b34a7 mov dword ptr [ebp - 0x9c], eax
006b34ad jmp 0x6b34df
006b34af add dword ptr [edi + ecx*8 + 4], 4
006b34b4 jns 0x6b34df
006b34b6 mov dword ptr [edi + ecx*8 + 4], 0
006b34be jmp 0x6b34df
006b34c0 lea ecx, [ebp - 0xac]
006b34c6 push ecx
006b34c7 push eax
006b34c8 lea ecx, [ebp - 0xa0]
006b34ce call 0x48d900
006b34d3 mov eax, dword ptr [ebp - 0x9c]
006b34d9 mov edi, dword ptr [ebp - 0xa0]
006b34df mov edx, eax
006b34e1 xor ecx, ecx
006b34e3 sub edx, edi
006b34e5 sar edx, 3
006b34e8 test edx, edx
006b34ea je 0x6b34fe
006b34ec nop dword ptr [eax]
006b34f0 cmp dword ptr [edi + ecx*8], 0x12c
006b34f7 je 0x6b3532
006b34f9 inc ecx
006b34fa cmp ecx, edx
006b34fc jb 0x6b34f0
006b34fe mov dword ptr [ebp - 0xac], 0x12c
006b3508 mov dword ptr [ebp - 0xa8], 4
006b3512 cmp eax, dword ptr [ebp - 0x98]
006b3518 je 0x6b3543
006b351a mov dword ptr [eax], 0x12c
006b3520 mov dword ptr [eax + 4], 4
006b3527 add eax, 8
006b352a mov dword ptr [ebp - 0x9c], eax
006b3530 jmp 0x6b355c
006b3532 add dword ptr [edi + ecx*8 + 4], 4
006b3537 jns 0x6b355c
006b3539 mov dword ptr [edi + ecx*8 + 4], 0
006b3541 jmp 0x6b355c
006b3543 lea ecx, [ebp - 0xac]
006b3549 push ecx
006b354a push eax
006b354b lea ecx, [ebp - 0xa0]
006b3551 call 0x48d900
006b3556 mov edi, dword ptr [ebp - 0xa0]
006b355c push 2
006b355e mov ecx, esi
006b3560 call 0x7a7d50
006b3565 add eax, 2
006b3568 mov dword ptr [ebp - 0xf0], eax
006b356e test eax, eax
006b3570 jle 0x6b3650
006b3576 mov ecx, esi
006b3578 call 0x7a7e20
006b357d movq xmm0, qword ptr [0xa08c44]
006b3585 sub esp, 0x10
006b3588 mov ecx, esp
006b358a mov dword ptr [ecx], eax
006b358c mov eax, dword ptr [0xa08c4c]
006b3591 movq qword ptr [ecx + 4], xmm0
006b3596 mov dword ptr [ecx + 0xc], eax
006b3599 lea ecx, [ebp - 0xa0]
006b359f call 0x489420
006b35a4 mov edi, eax
006b35a6 mov ecx, esi
006b35a8 movzx eax, di
006b35ab mov dword ptr [ebp - 0xdc], eax
006b35b1 shr edi, 0x10
006b35b4 call 0x7a7e20
006b35b9 mov ecx, esi
006b35bb call 0x7a7e20
006b35c0 push 0
006b35c2 push eax
006b35c3 push edi
006b35c4 push dword ptr [ebp - 0xdc]
006b35ca lea ecx, [ebp - 0xd8]
006b35d0 push 5
006b35d2 call 0x68f5d0
006b35d7 mov eax, dword ptr [ebp - 0xa4]
006b35dd mov edi, dword ptr [ebp - 0xa0]
006b35e3 cmp dword ptr [eax + 0x30], 2
006b35e7 jne 0x6b3643
006b35e9 cmp dword ptr [ebp - 0xdc], 0xa
006b35f0 jne 0x6b3643
006b35f2 mov ecx, dword ptr [ebp - 0x9c]
006b35f8 xor eax, eax
006b35fa sub ecx, edi
006b35fc sar ecx, 3
006b35ff test ecx, ecx
006b3601 je 0x6b3643
006b3603 cmp dword ptr [edi + eax*8], 0x6000a
006b360a je 0x6b3613
006b360c inc eax
006b360d cmp eax, ecx
006b360f jb 0x6b3603
006b3611 jmp 0x6b3622
006b3613 add dword ptr [edi + eax*8 + 4], -0xa
006b3618 jns 0x6b3622
006b361a mov dword ptr [edi + eax*8 + 4], 0
006b3622 xor eax, eax
006b3624 cmp dword ptr [edi + eax*8], 0xb000a
006b362b je 0x6b3634
006b362d inc eax
006b362e cmp eax, ecx
006b3630 jb 0x6b3624
006b3632 jmp 0x6b3643
006b3634 add dword ptr [edi + eax*8 + 4], -5
006b3639 jns 0x6b3643
006b363b mov dword ptr [edi + eax*8 + 4], 0
006b3643 sub dword ptr [ebp - 0xf0], 1
006b364a jne 0x6b3576
006b3650 mov byte ptr [ebp - 4], 0
006b3654 test edi, edi
006b3656 je 0x6b47d9
006b365c mov eax, dword ptr [ebp - 0x98]
006b3662 sub eax, edi
006b3664 sar eax, 3
006b3667 push eax
006b3668 push edi
006b3669 call 0x421f90
006b366e jmp 0x6b47d9
