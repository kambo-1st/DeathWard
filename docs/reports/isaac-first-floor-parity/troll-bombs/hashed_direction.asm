006592f0 push ebp
006592f1 mov ebp, esp
006592f3 and esp, 0xfffffff8
006592f6 sub esp, 0x14
006592f9 movq xmm0, qword ptr [0xa08b78]
00659301 push ebx
00659302 mov ebx, dword ptr [0xa08b80]
00659308 push esi
00659309 mov esi, edx
0065930b movq qword ptr [esp + 0x10], xmm0
00659311 push edi
00659312 mov edi, ecx
00659314 test esi, esi
00659316 jne 0x659328
00659318 push 0xb4d6c4
0065931d push 3
0065931f call 0x95e330
00659324 add esp, 8
00659327 int3 
00659328 mov ecx, dword ptr [esp + 0x14]
0065932c mov edx, esi
0065932e shr edx, cl
00659330 mov ecx, dword ptr [esp + 0x18]
00659334 xor edx, esi
00659336 mov eax, edx
00659338 shl eax, cl
0065933a mov ecx, ebx
0065933c xor eax, edx
0065933e mov edx, eax
00659340 shr edx, cl
00659342 xor edx, eax
00659344 movd xmm0, edx
00659348 cvtdq2pd xmm0, xmm0
0065934c shr edx, 0x1f
0065934f addsd xmm0, qword ptr [edx*8 + 0xb6c940]
00659358 cvtpd2ps xmm0, xmm0
0065935c mulss xmm0, dword ptr [0xb6a198]
00659364 mulss xmm0, dword ptr [0xb6a874]
0065936c addss xmm0, xmm0
00659370 movss dword ptr [esp + 0xc], xmm0
00659376 call 0x411fe0
0065937b movss dword ptr [edi], xmm0
0065937f movss xmm0, dword ptr [esp + 0xc]
00659385 call 0x412010
0065938a movss dword ptr [edi + 4], xmm0
0065938f mov eax, edi
00659391 pop edi
00659392 pop esi
00659393 pop ebx
00659394 mov esp, ebp
00659396 pop ebp
00659397 ret 
