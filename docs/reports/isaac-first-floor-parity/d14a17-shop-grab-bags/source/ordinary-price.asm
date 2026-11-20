007d0d19 xor edx, edx
007d0d1b cmp edi, 0x45
007d0d1e sete dl
007d0d21 lea edx, [edx*2 + 5]
007d0d28 mov eax, edx
007d0d2a pop edi
007d0d2b pop esi
007d0d2c pop ebx
007d0d2d mov esp, ebp
007d0d2f pop ebp
007d0d30 ret 0xc
