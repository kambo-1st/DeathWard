006c3060 push ebp
006c3061 mov ebp, esp
006c3063 and esp, 0xfffffff8
006c3066 push ecx
006c3067 movss xmm0, dword ptr [ebp + 8]
006c306c comiss xmm0, dword ptr [0xb6a18c]
006c3073 push ebx
006c3074 push esi
006c3075 push edi
006c3076 mov esi, ecx
006c3078 jbe 0x6c3189
006c307e mov eax, dword ptr [ebp + 0xc]
006c3081 and eax, 0x1000004
006c3086 or eax, 0
006c3089 je 0x6c3189
006c308f mov edx, dword ptr [esi + 0x2c]
006c3092 cmp edx, 0x33
006c3095 je 0x6c30e8
006c3097 mov ecx, dword ptr [0xbfd65c]
006c309d push 1
006c309f push 0
006c30a1 push 0x88
006c30a6 lea ecx, [ecx + 0x1ba40]
006c30ac call 0x91d550
006c30b1 test eax, eax
006c30b3 je 0x6c315d
006c30b9 mov eax, dword ptr [esi + 0x2c]
006c30bc mov edx, eax
006c30be cmp eax, 0x3c
006c30c1 je 0x6c30e8
006c30c3 cmp eax, 0x32
006c30c6 je 0x6c30e8
006c30c8 cmp eax, 0x168
006c30cd je 0x6c30e8
006c30cf cmp eax, 0x35
006c30d2 je 0x6c30e8
006c30d4 cmp eax, 0x34
006c30d7 je 0x6c30e8
006c30d9 cmp eax, 0x36
006c30dc je 0x6c30e8
006c30de cmp eax, 0x37
006c30e1 je 0x6c30e8
006c30e3 cmp eax, 0x39
006c30e6 jne 0x6c315d
006c30e8 mov ebx, dword ptr [esi + 0x30]
006c30eb test ebx, ebx
006c30ed je 0x6c315d
006c30ef mov eax, dword ptr [ebp + 0x14]
006c30f2 xor edi, edi
006c30f4 mov ecx, dword ptr [eax + 0x24]
006c30f7 test ecx, ecx
006c30f9 je 0x6c310b
006c30fb call 0x681340
006c3100 test eax, eax
006c3102 je 0x6c310b
006c3104 cmp dword ptr [eax + 0x28], 1
006c3108 cmove edi, eax
006c310b cmp edx, 0x39
006c310e jne 0x6c3126
006c3110 cmp ebx, 1
006c3113 jbe 0x6c3126
006c3115 lea eax, [ebx - 1]
006c3118 mov dword ptr [esi + 0x30], eax
006c311b xor al, al
006c311d pop edi
006c311e pop esi
006c311f pop ebx
006c3120 mov esp, ebp
006c3122 pop ebp
006c3123 ret 0x14
006c3126 push edi
006c3127 mov ecx, esi
006c3129 call 0x6bd410
006c312e mov ecx, dword ptr [0xbfd65c]
006c3134 mov eax, dword ptr [ecx + 0x18190]
006c313a mov eax, dword ptr [eax + 8]
006c313d cmp eax, 0xb
006c3140 je 0x6c3147
006c3142 cmp eax, 0x11
006c3145 jne 0x6c3189
006c3147 add ecx, 0x1c31b8
006c314d call 0x7ed6e0
006c3152 xor al, al
006c3154 pop edi
006c3155 pop esi
006c3156 pop ebx
006c3157 mov esp, ebp
006c3159 pop ebp
006c315a ret 0x14
006c315d cmp dword ptr [esi + 0x2c], 0x14
006c3161 jne 0x6c3189
006c3163 cmp dword ptr [esi + 0x30], 6
006c3167 jne 0x6c3189
006c3169 push 0
006c316b push 0xb3fd8c
006c3170 lea ecx, [esi + 0x3c]
006c3173 mov dword ptr [esi + 0x30], 2
006c317a mov dword ptr [esi + 0x498], 0
006c3184 call 0x4054f0
006c3189 pop edi
006c318a pop esi
006c318b xor al, al
006c318d pop ebx
006c318e mov esp, ebp
006c3190 pop ebp
