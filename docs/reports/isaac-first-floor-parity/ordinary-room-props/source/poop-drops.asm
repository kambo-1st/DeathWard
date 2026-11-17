006e7f7e mov ecx, dword ptr [0xbfd65c]
006e7f84 movss xmm0, dword ptr [0xb6a2cc]
006e7f8c push 1
006e7f8e push 0
006e7f90 lea ecx, [ecx + 0x1ba40]
006e7f96 movss dword ptr [ebp - 8], xmm0
006e7f9b push 0x18
006e7f9d call 0x91d550
006e7fa2 test eax, eax
006e7fa4 je 0x6e7fdf
006e7fa6 mov ecx, dword ptr [0xbfd65c]
006e7fac push 0x18
006e7fae lea ecx, [ecx + 0x1ba40]
006e7fb4 call 0x91db10
006e7fb9 movd xmm0, eax
006e7fbd cvtdq2ps xmm0, xmm0
006e7fc0 mulss xmm0, dword ptr [0xb6a2cc]
006e7fc8 addss xmm0, dword ptr [0xb6a350]
006e7fd0 maxss xmm0, dword ptr [0xb6a2cc]
006e7fd8 movss dword ptr [ebp - 8], xmm0
006e7fdd jmp 0x6e7fe4
006e7fdf movss xmm0, dword ptr [ebp - 8]
006e7fe4 mov ecx, dword ptr [0xbfd65c]
006e7fea push 1
006e7fec push 0
006e7fee push 2
006e7ff0 lea ecx, [ecx + 0x1ba40]
006e7ff6 movss dword ptr [ebp - 0x10], xmm0
006e7ffb call 0x91d550
006e8000 test eax, eax
006e8002 je 0x6e803a
006e8004 mov ecx, dword ptr [0xbfd65c]
006e800a push 2
006e800c lea ecx, [ecx + 0x1ba40]
006e8012 call 0x91db10
006e8017 movd xmm0, eax
006e801b cvtdq2ps xmm0, xmm0
006e801e mulss xmm0, dword ptr [0xb6a2cc]
006e8026 addss xmm0, dword ptr [0xb6a434]
006e802e maxss xmm0, dword ptr [ebp - 0x10]
006e8033 movss dword ptr [ebp - 8], xmm0
006e8038 jmp 0x6e803f
006e803a movss xmm0, dword ptr [ebp - 0x10]
006e803f cmp esi, 1
006e8042 jle 0x6e8057
006e8044 movss xmm1, dword ptr [0xb6a350]
006e804c maxss xmm1, xmm0
006e8050 movss dword ptr [ebp - 8], xmm1
006e8055 jmp 0x6e805c
006e8057 movss xmm1, dword ptr [ebp - 8]
006e805c cmp byte ptr [ebp + 0xc], 0
006e8060 je 0x6e806f
006e8062 movss xmm1, dword ptr [0xb6a214]
006e806a movss dword ptr [ebp - 8], xmm1
006e806f test edi, edi
006e8071 jne 0x6e8088
006e8073 push 0xb4d6c4
006e8078 push 3
006e807a call 0x95e330
006e807f add esp, 8
006e8082 int3 
006e8083 movss xmm1, dword ptr [ebp - 8]
006e8088 mov ecx, dword ptr [ebp - 0x28]
006e808b mov eax, edi
006e808d mov ebx, dword ptr [ebp - 0x24]
006e8090 mov esi, dword ptr [ebp - 0x30]
006e8093 shr eax, cl
006e8095 mov ecx, ebx
006e8097 xor eax, edi
006e8099 movss xmm2, dword ptr [0xb6a198]
006e80a1 mov edx, eax
006e80a3 shl edx, cl
006e80a5 mov ecx, esi
006e80a7 xor edx, eax
006e80a9 mov edi, edx
006e80ab shr edi, cl
006e80ad xor edi, edx
006e80af mov eax, edi
006e80b1 mov dword ptr [ebp - 0x10], edi
006e80b4 shr eax, 0x1f
006e80b7 mov dword ptr [ebp - 0x2c], edi
006e80ba movd xmm0, edi
006e80be cvtdq2pd xmm0, xmm0
006e80c2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006e80cb cvtpd2ps xmm0, xmm0
006e80cf mulss xmm0, xmm2
006e80d3 comiss xmm1, xmm0
006e80d6 jbe 0x6e8374
006e80dc test edi, edi
006e80de jne 0x6e80f0
006e80e0 push 0xb4d6c4
006e80e5 push 3
006e80e7 call 0x95e330
006e80ec add esp, 8
006e80ef int3 
006e80f0 mov ecx, dword ptr [ebp - 0x28]
006e80f3 mov eax, edi
006e80f5 shr eax, cl
006e80f7 mov ecx, ebx
006e80f9 xor eax, edi
006e80fb mov edx, eax
006e80fd shl edx, cl
006e80ff mov ecx, esi
006e8101 xor edx, eax
006e8103 mov eax, 0xcccccccd
006e8108 mov edi, edx
006e810a shr edi, cl
006e810c xor edi, edx
006e810e mul edi
006e8110 mov eax, edi
006e8112 mov dword ptr [ebp - 0x10], edi
006e8115 shr edx, 4
006e8118 mov dword ptr [ebp - 0x2c], edi
006e811b lea ecx, [edx + edx*4]
006e811e shl ecx, 2
006e8121 sub eax, ecx
006e8123 jne 0x6e8170
006e8125 mov esi, dword ptr [0xbfd65c]
006e812b mov eax, dword ptr [esi + 0x1ad58]
006e8131 cmp byte ptr [eax + 0x14], 0
006e8135 je 0x6e8170
006e8137 cmp byte ptr [eax + 0x15], 0
006e813b je 0x6e8170
006e813d mov byte ptr [eax + 0x14], 0
006e8141 dec dword ptr [esi + 0x1ad64]
006e8147 call 0x6c3d90
006e814c mov ebx, dword ptr [ebp - 0xc]
006e814f mov ecx, esi
006e8151 push eax
006e8152 push 2
006e8154 push 0
006e8156 push 0xc02fec
006e815b push ebx
006e815c push 0x15e
006e8161 push 5
006e8163 call 0x422e20
006e8168 mov esi, dword ptr [ebp - 0x18]
006e816b jmp 0x6e7db8
006e8170 test edi, edi
006e8172 jne 0x6e8184
006e8174 push 0xb4d6c4
006e8179 push 3
006e817b call 0x95e330
006e8180 add esp, 8
006e8183 int3 
006e8184 mov ecx, dword ptr [ebp - 0x28]
006e8187 mov eax, edi
006e8189 shr eax, cl
006e818b mov ecx, ebx
006e818d mov ebx, dword ptr [ebp - 0x30]
006e8190 xor eax, edi
006e8192 mov edx, eax
006e8194 movss xmm1, dword ptr [0xb6a38c]
006e819c shl edx, cl
006e819e mov ecx, ebx
006e81a0 xor edx, eax
006e81a2 mov esi, edx
006e81a4 shr esi, cl
006e81a6 xor esi, edx
006e81a8 mov eax, esi
006e81aa shr eax, 0x1f
006e81ad movd xmm0, esi
006e81b1 cvtdq2pd xmm0, xmm0
006e81b5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006e81be cvtpd2ps xmm0, xmm0
006e81c2 mulss xmm0, dword ptr [0xb6a198]
006e81ca comiss xmm1, xmm0
006e81cd jbe 0x6e8332
006e81d3 mov ebx, dword ptr [ebp - 0x40]
006e81d6 test ebx, ebx
006e81d8 je 0x6e8224
006e81da mov edx, dword ptr [ebx]
006e81dc test edx, edx
006e81de jne 0x6e81f6
006e81e0 push 0xb4d6c4
006e81e5 push 3
006e81e7 call 0x95e330
006e81ec mov edx, dword ptr [ebx]
006e81ee add esp, 8
006e81f1 test edx, edx
006e81f3 jne 0x6e81f6
006e81f5 int3 
006e81f6 mov ecx, dword ptr [ebx + 4]
006e81f9 mov eax, edx
006e81fb shr eax, cl
006e81fd mov ecx, dword ptr [ebx + 8]
006e8200 xor eax, edx
006e8202 mov edx, eax
006e8204 shl edx, cl
006e8206 mov ecx, dword ptr [ebx + 0xc]
006e8209 xor edx, eax
006e820b mov eax, edx
006e820d shr eax, cl
006e820f mov ecx, 5
006e8214 xor eax, edx
006e8216 xor edx, edx
006e8218 mov dword ptr [ebx], eax
006e821a div ecx
006e821c test edx, edx
006e821e jne 0x6e832f
006e8224 mov ebx, dword ptr [ebp - 0x44]
006e8227 test ebx, ebx
006e8229 je 0x6e8275
006e822b mov edx, dword ptr [ebx]
006e822d test edx, edx
006e822f jne 0x6e8247
006e8231 push 0xb4d6c4
006e8236 push 3
006e8238 call 0x95e330
006e823d mov edx, dword ptr [ebx]
006e823f add esp, 8
006e8242 test edx, edx
006e8244 jne 0x6e8247
006e8246 int3 
006e8247 mov ecx, dword ptr [ebx + 4]
006e824a mov eax, edx
006e824c shr eax, cl
006e824e mov ecx, dword ptr [ebx + 8]
006e8251 xor eax, edx
006e8253 mov edx, eax
006e8255 shl edx, cl
006e8257 mov ecx, dword ptr [ebx + 0xc]
006e825a xor edx, eax
006e825c mov eax, edx
006e825e shr eax, cl
006e8260 mov ecx, 3
006e8265 xor eax, edx
006e8267 xor edx, edx
006e8269 mov dword ptr [ebx], eax
006e826b div ecx
006e826d test edx, edx
006e826f jne 0x6e832f
006e8275 test esi, esi
006e8277 jne 0x6e8289
006e8279 push 0xb4d6c4
006e827e push 3
006e8280 call 0x95e330
006e8285 add esp, 8
006e8288 int3 
006e8289 mov ecx, dword ptr [ebp - 0x28]
006e828c mov edx, esi
006e828e shr edx, cl
006e8290 mov ecx, dword ptr [ebp - 0x24]
006e8293 xor edx, esi
006e8295 mov eax, edx
006e8297 shl eax, cl
006e8299 mov ecx, dword ptr [ebp - 0x30]
006e829c mov ebx, dword ptr [ebp - 0xc]
006e829f xor eax, edx
006e82a1 mov edi, eax
006e82a3 shr edi, cl
006e82a5 xor edi, eax
006e82a7 lea eax, [ebp - 0x3c]
006e82aa push edi
006e82ab push 0
006e82ad push 0
006e82af push eax
006e82b0 push ebx
006e82b1 push 0xa
006e82b3 mov ecx, dword ptr [0xbfd65c]
006e82b9 push 5
006e82bb mov dword ptr [ebp - 0x2c], edi
006e82be mov dword ptr [ebp - 0x10], edi
006e82c1 call 0x422e20
006e82c6 call 0x6c3d90
006e82cb movd xmm0, eax
006e82cf cvtdq2pd xmm0, xmm0
006e82d3 shr eax, 0x1f
006e82d6 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006e82df cvtpd2ps xmm0, xmm0
006e82e3 mulss xmm0, dword ptr [0xb6a19c]
006e82eb mulss xmm0, dword ptr [0xb6a874]
006e82f3 addss xmm0, xmm0
006e82f7 movss dword ptr [ebp - 0x1c], xmm0
006e82fc call 0x411fe0
006e8301 movss dword ptr [ebp - 8], xmm0
006e8306 movss xmm0, dword ptr [ebp - 0x1c]
006e830b call 0x412010
006e8310 movss xmm1, dword ptr [ebp - 8]
006e8315 addss xmm0, xmm0
006e8319 mov esi, dword ptr [ebp - 0x18]
006e831c addss xmm1, xmm1
006e8320 movss dword ptr [ebp - 0x38], xmm0
006e8325 movss dword ptr [ebp - 0x3c], xmm1
006e832a jmp 0x6e7db8
006e832f mov ebx, dword ptr [ebp - 0x30]
006e8332 test esi, esi
006e8334 jne 0x6e8346
006e8336 push 0xb4d6c4
006e833b push 3
006e833d call 0x95e330
006e8342 add esp, 8
006e8345 int3 
006e8346 mov ecx, dword ptr [ebp - 0x28]
006e8349 mov edx, esi
006e834b shr edx, cl
006e834d mov ecx, dword ptr [ebp - 0x24]
006e8350 xor edx, esi
006e8352 mov eax, edx
006e8354 shl eax, cl
006e8356 mov ecx, ebx
006e8358 mov ebx, dword ptr [ebp - 0xc]
006e835b xor eax, edx
006e835d mov edi, eax
006e835f shr edi, cl
006e8361 xor edi, eax
006e8363 lea eax, [ebp - 0x3c]
006e8366 push edi
006e8367 push 0
006e8369 push 0
006e836b push eax
006e836c push ebx
006e836d push 0x14
006e836f jmp 0x6e82b3
