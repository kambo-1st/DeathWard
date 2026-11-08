00659230 push esi
00659231 mov esi, ecx
00659233 test esi, esi
00659235 jne 0x65923b
00659237 xor eax, eax
00659239 pop esi
0065923a ret 
0065923b call 0x6c3d90
00659240 xor edx, edx
00659242 div esi
00659244 pop esi
00659245 mov eax, edx
00659247 ret 
