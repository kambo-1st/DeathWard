007a4383 mov eax, dword ptr [ebp - 0x44]
007a4386 lea ecx, [ebp - 0x8c]
007a438c mov dword ptr [ebp - 0x4c], eax
007a438f lea eax, [ebp - 0x4c]
007a4392 push eax
007a4393 mov dword ptr [ebp - 0x48], 0
007a439a call 0x7a7bb0
007a439f mov esi, dword ptr [ebp - 0x8c]
007a43a5 mov byte ptr [ebx + 0x72d], 0
007a43ac cmp esi, dword ptr [ebp - 0x88]
007a43b2 je 0x7a451e
007a43b8 nop dword ptr [eax + eax]
007a43c0 cmp byte ptr [ebx + 0x72d], 0
007a43c7 jne 0x7a451e
007a43cd mov ecx, dword ptr [0xbfd65c]
007a43d3 mov eax, dword ptr [esi]
007a43d5 mov edi, dword ptr [esi + 4]
007a43d8 mov dword ptr [ebp - 0x30], eax
007a43db mov ecx, dword ptr [ecx + 0x18190]
007a43e1 mov dword ptr [ebp - 0x60], edi
007a43e4 mov eax, dword ptr [ecx + 0x10]
007a43e7 imul eax, dword ptr [ecx + 0xc]
007a43eb cdq
007a43ec sub eax, edx
007a43ee sar eax, 1
007a43f0 cmp edi, eax
007a43f2 jge 0x7a451e
007a43f8 lea ecx, [ebp - 0x8c]
007a43fe call 0x7a7aa0
007a4403 mov eax, dword ptr [0xbfd65c]
007a4408 mov ebx, dword ptr [eax + 0x18190]
007a440e mov eax, dword ptr [ebp - 0x30]
007a4411 cdq
007a4412 mov esi, dword ptr [ebx + 0xc]
007a4415 idiv esi
007a4417 mov ecx, eax
007a4419 lea eax, [edx - 1]
007a441c mov dword ptr [ebp - 0x30], eax
007a441f test eax, eax
007a4421 js 0x7a4440
007a4423 cmp eax, esi
007a4425 jge 0x7a4440
007a4427 test ecx, ecx
007a4429 js 0x7a4440
007a442b cmp ecx, dword ptr [ebx + 0x10]
007a442e jge 0x7a4440
007a4430 mov eax, esi
007a4432 imul eax, ecx
007a4435 add eax, dword ptr [ebp - 0x30]
007a4438 mov dword ptr [ebp - 0x20], eax
007a443b lea eax, [ecx - 1]
007a443e jmp 0x7a444e
007a4440 mov dword ptr [ebp - 0x20], 0xffffffff
007a4447 lea eax, [ecx - 1]
007a444a test edx, edx
007a444c js 0x7a4462
007a444e cmp edx, esi
007a4450 jge 0x7a4462
007a4452 test eax, eax
007a4454 js 0x7a4462
007a4456 cmp eax, dword ptr [ebx + 0x10]
007a4459 jge 0x7a4462
007a445b imul eax, esi
007a445e add eax, edx
007a4460 jmp 0x7a4465
007a4462 or eax, 0xffffffff
007a4465 mov dword ptr [ebp - 0x1c], eax
007a4468 lea eax, [edx + 1]
007a446b mov dword ptr [ebp - 0x30], eax
007a446e test eax, eax
007a4470 js 0x7a4489
007a4472 cmp eax, esi
007a4474 jge 0x7a4489
007a4476 test ecx, ecx
007a4478 js 0x7a4489
007a447a cmp ecx, dword ptr [ebx + 0x10]
007a447d jge 0x7a4489
007a447f mov eax, esi
007a4481 imul eax, ecx
007a4484 add eax, dword ptr [ebp - 0x30]
007a4487 jmp 0x7a448c
007a4489 or eax, 0xffffffff
007a448c mov dword ptr [ebp - 0x18], eax
007a448f lea eax, [ecx + 1]
007a4492 test edx, edx
007a4494 js 0x7a44aa
007a4496 cmp edx, esi
007a4498 jge 0x7a44aa
007a449a test eax, eax
007a449c js 0x7a44aa
007a449e cmp eax, dword ptr [ebx + 0x10]
007a44a1 jge 0x7a44aa
007a44a3 imul eax, esi
007a44a6 add eax, edx
007a44a8 jmp 0x7a44ad
007a44aa or eax, 0xffffffff
007a44ad mov dword ptr [ebp - 0x14], eax
007a44b0 xor esi, esi
007a44b2 mov ecx, dword ptr [ebp + esi*4 - 0x20]
007a44b6 mov ebx, dword ptr [ebp - 0x58]
007a44b9 mov dword ptr [ebp - 0x4c], ecx
007a44bc mov dword ptr [ebp - 0x48], edi
007a44bf test ecx, ecx
007a44c1 js 0x7a4506
007a44c3 mov eax, dword ptr [ebx + ecx*4 + 0x2c]
007a44c7 test eax, eax
007a44c9 js 0x7a4506
007a44cb cmp eax, 0x3b6
007a44d0 jge 0x7a4506
007a44d2 test eax, eax
007a44d4 jle 0x7a44df
007a44d6 cmp byte ptr [ebp - 0x23], 0
007a44da lea eax, [edi + 7]
007a44dd je 0x7a44e2
007a44df lea eax, [edi + 1]
007a44e2 mov dword ptr [ebp - 0x48], eax
007a44e5 neg eax
007a44e7 mov dword ptr [ebx + ecx*4 + 0x2c], eax
007a44eb cmp ecx, dword ptr [ebx + 0x20]
007a44ee jne 0x7a44f7
007a44f0 mov byte ptr [ebx + 0x72d], 1
007a44f7 lea eax, [ebp - 0x4c]
007a44fa push eax
007a44fb lea ecx, [ebp - 0x8c]
007a4501 call 0x7a7bb0
007a4506 inc esi
007a4507 cmp esi, 4
007a450a jb 0x7a44b2
007a450c mov esi, dword ptr [ebp - 0x8c]
007a4512 cmp esi, dword ptr [ebp - 0x88]
007a4518 jne 0x7a43c0
