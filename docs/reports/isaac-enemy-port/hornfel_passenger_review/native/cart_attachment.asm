; Installed-binary disassembly; field interpretations require the source review.
004bc2d0 push ebp
004bc2d1 mov ebp, esp
004bc2d3 push ecx
004bc2d4 push ebx
004bc2d5 mov ebx, ecx
004bc2d7 mov ecx, dword ptr [ebx + 0x318]
004bc2dd push esi
004bc2de push edi
004bc2df lea edi, [ebx + 0x318]
004bc2e5 test ecx, ecx
004bc2e7 je 0x4bc329
004bc2e9 mov eax, dword ptr [ecx + 0x32c]
004bc2ef lea esi, [ecx + 0x32c]
004bc2f5 test eax, eax
004bc2f7 je 0x4bc313
004bc2f9 lea ecx, [ebp - 4]
004bc2fc mov dword ptr [ebp - 4], esi
004bc2ff push ecx
004bc300 lea ecx, [eax + 0x324]
004bc306 call 0x4bc3c0
004bc30b mov dword ptr [esi], 0
004bc311 mov ecx, dword ptr [edi]
004bc313 test ecx, ecx
004bc315 je 0x4bc329
004bc317 lea eax, [ebp - 4]
004bc31a mov dword ptr [ebp - 4], edi
004bc31d push eax
004bc31e add ecx, 0x324
004bc324 call 0x4bc3c0
004bc329 mov esi, dword ptr [ebp + 8]
004bc32c mov dword ptr [edi], esi
004bc32e test esi, esi
004bc330 je 0x4bc33a
004bc332 push edi
004bc333 mov ecx, esi
004bc335 call 0x4bae70
004bc33a mov ecx, dword ptr [esi + 0x32c]
004bc340 add esi, 0x32c
004bc346 cmp ecx, ebx
004bc348 je 0x4bc36a
004bc34a test ecx, ecx
004bc34c je 0x4bc360
004bc34e lea eax, [ebp + 8]
004bc351 mov dword ptr [ebp + 8], esi
004bc354 push eax
004bc355 add ecx, 0x324
004bc35b call 0x4bc3c0
004bc360 push esi
004bc361 mov ecx, ebx
004bc363 mov dword ptr [esi], ebx
004bc365 call 0x4bae70
004bc36a pop edi
004bc36b pop esi
004bc36c pop ebx
004bc36d mov esp, ebp
004bc36f pop ebp
004bc370 ret 4
