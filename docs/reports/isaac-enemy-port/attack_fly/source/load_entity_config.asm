00681ea0 push ebp
00681ea1 mov ebp, esp
00681ea3 and esp, 0xfffffff8
00681ea6 push ecx
00681ea7 mov eax, dword ptr [0xbfd680]
00681eac push ebx
00681ead push esi
00681eae mov esi, ecx
00681eb0 add eax, 0x29f88
00681eb5 push edi
00681eb6 mov ecx, eax
00681eb8 mov dword ptr [esp + 0xc], eax
00681ebc push dword ptr [esi + 0x30]
00681ebf mov edi, dword ptr [esi + 0x2c]
00681ec2 mov ebx, dword ptr [esi + 0x28]
00681ec5 push edi
00681ec6 push ebx
00681ec7 call 0x66d910
00681ecc test eax, eax
00681ece je 0x681ee0
00681ed0 mov ecx, dword ptr [esp + 0xc]
00681ed4 push eax
00681ed5 call 0x6744f0
00681eda mov edi, dword ptr [esi + 0x2c]
00681edd mov ebx, dword ptr [esi + 0x28]
00681ee0 mov eax, dword ptr [esi + 0x30]
00681ee3 mov ecx, dword ptr [0xbfd680]
00681ee9 push eax
00681eea push edi
00681eeb push ebx
00681eec lea ecx, [ecx + 0x29f88]
00681ef2 call 0x66d910
00681ef7 mov edx, eax
00681ef9 mov dword ptr [esi + 0x288], edx
00681eff test edx, edx
00681f01 je 0x682106
00681f07 mov ecx, dword ptr [edx + 0x24]
00681f0a mov dword ptr [esi + 0x150], ecx
00681f10 mov eax, dword ptr [edx + 0x28]
00681f13 mov dword ptr [esi + 0x2e0], eax
00681f19 mov eax, dword ptr [edx + 0x44]
00681f1c mov dword ptr [esi + 0x2d4], eax
00681f22 mov eax, dword ptr [0xbfd65c]
00681f27 movss xmm3, dword ptr [edx + 0x54]
00681f2c comiss xmm3, dword ptr [0xb6a1c8]
00681f33 mov eax, dword ptr [eax]
00681f35 movss xmm2, dword ptr [edx + 0x50]
00681f3a jbe 0x681f7c
00681f3c movd xmm1, eax
00681f40 cvtdq2ps xmm1, xmm1
00681f43 minss xmm1, dword ptr [0xb6a974]
00681f4b cmp eax, 5
00681f4e jge 0x681f66
00681f50 movss xmm0, dword ptr [0xb6a614]
00681f58 mulss xmm0, xmm1
00681f5c mulss xmm0, xmm3
00681f60 addss xmm0, xmm2
00681f64 jmp 0x681f7f
00681f66 movss xmm0, dword ptr [0xb6a560]
00681f6e mulss xmm0, xmm1
00681f72 mulss xmm0, xmm3
00681f76 addss xmm0, xmm2
00681f7a jmp 0x681f7f
00681f7c movaps xmm0, xmm2
00681f7f movss dword ptr [esi + 0x2dc], xmm0
00681f87 mov eax, edx
00681f89 mov dword ptr [esi + 0x2c8], 0
00681f93 movss xmm0, dword ptr [0xc02fec]
00681f9b movss dword ptr [esi + 0x2cc], xmm0
00681fa3 movss xmm0, dword ptr [0xc02ff0]
00681fab movss dword ptr [esi + 0x2d0], xmm0
00681fb3 push dword ptr [eax + 0x48]
00681fb6 movss xmm0, dword ptr [eax + 0x38]
00681fbb push dword ptr [eax + 0x40]
00681fbe push dword ptr [eax + 0x3c]
00681fc1 push ecx
00681fc2 mov ecx, esi
00681fc4 movss dword ptr [esp], xmm0
00681fc9 call 0x6843a0
00681fce mov edi, dword ptr [esi + 0x288]
00681fd4 mov eax, dword ptr [edi + 0x4c]
00681fd7 mov dword ptr [esi + 0x2c0], eax
00681fdd cmp dword ptr [edi + 0xc4], 0
00681fe4 je 0x6820de
00681fea mov ebx, dword ptr [edi + 0xc8]
00681ff0 add edi, 0xb4
00681ff6 mov ecx, edi
00681ff8 cmp ebx, 0x10
00681ffb jb 0x681fff
00681ffd mov ecx, dword ptr [edi]
00681fff mov eax, dword ptr [edi + 0x10]
00682002 mov edx, eax
00682004 push 4
00682006 push 0xb48e60
0068200b mov dword ptr [esp + 0x14], eax
0068200f call 0x408190
00682014 add esp, 8
00682017 test al, al
00682019 je 0x68202c
0068201b mov dword ptr [esi + 0x17c], 0
00682025 pop edi
00682026 pop esi
00682027 pop ebx
00682028 mov esp, ebp
0068202a pop ebp
0068202b ret 
0068202c mov ecx, edi
0068202e cmp ebx, 0x10
00682031 jb 0x682035
00682033 mov ecx, dword ptr [edi]
00682035 mov edx, dword ptr [esp + 0xc]
00682039 push 5
0068203b push 0xb48e68
00682040 call 0x408190
00682045 add esp, 8
00682048 test al, al
0068204a je 0x68205d
0068204c mov dword ptr [esi + 0x17c], 3
00682056 pop edi
00682057 pop esi
00682058 pop ebx
00682059 mov esp, ebp
0068205b pop ebp
0068205c ret 
0068205d mov ecx, edi
0068205f cmp ebx, 0x10
00682062 jb 0x682066
00682064 mov ecx, dword ptr [edi]
00682066 mov edx, dword ptr [esp + 0xc]
0068206a push 6
0068206c push 0xb44acc
00682071 call 0x408190
00682076 add esp, 8
00682079 test al, al
0068207b je 0x68208e
0068207d mov dword ptr [esi + 0x17c], 5
00682087 pop edi
00682088 pop esi
00682089 pop ebx
0068208a mov esp, ebp
0068208c pop ebp
0068208d ret 
0068208e cmp ebx, 0x10
00682091 jb 0x682095
00682093 mov edi, dword ptr [edi]
00682095 mov edx, dword ptr [esp + 0xc]
00682099 mov ecx, edi
0068209b push 6
0068209d push 0xb48dbc
006820a2 call 0x408190
006820a7 add esp, 8
006820aa test al, al
006820ac je 0x6820bf
006820ae mov dword ptr [esi + 0x17c], 6
006820b8 pop edi
006820b9 pop esi
006820ba pop ebx
006820bb mov esp, ebp
006820bd pop ebp
006820be ret 
006820bf push dword ptr [esi + 0x30]
006820c2 push dword ptr [esi + 0x2c]
006820c5 push dword ptr [esi + 0x28]
006820c8 push 0xb48dc4
006820cd push 3
006820cf call 0x95e330
006820d4 add esp, 0x14
006820d7 pop edi
006820d8 pop esi
006820d9 pop ebx
006820da mov esp, ebp
006820dc pop ebp
006820dd ret 
006820de mov eax, dword ptr [esi + 0x174]
006820e4 xor ecx, ecx
006820e6 sub eax, dword ptr [esi + 0x170]
006820ec sar eax, 3
006820ef cmp ecx, eax
006820f1 sbb eax, eax
006820f3 and eax, 2
006820f6 add eax, 3
006820f9 mov dword ptr [esi + 0x17c], eax
006820ff pop edi
00682100 pop esi
00682101 pop ebx
00682102 mov esp, ebp
00682104 pop ebp
00682105 ret 
00682106 mov eax, dword ptr [esi + 0x170]
0068210c push edi
0068210d mov dword ptr [esi + 0x2c8], 0x3f800000
00682117 movss xmm0, dword ptr [0xbc7a28]
0068211f push ebx
00682120 movss dword ptr [esi + 0x2cc], xmm0
00682128 movss xmm0, dword ptr [0xbc7a2c]
00682130 push 0xb48dfc
00682135 push 0
00682137 movss dword ptr [esi + 0x2d0], xmm0
0068213f mov dword ptr [esi + 0x150], 0x3c800000
00682149 mov dword ptr [esi + 0x2e0], 0
00682153 mov dword ptr [esi + 0x2dc], 0
0068215d mov dword ptr [esi + 0x2d4], 0
00682167 mov dword ptr [esi + 0x174], eax
0068216d mov dword ptr [esi + 0x17c], 3
00682177 mov dword ptr [esi + 0x2c0], 0x3f800000
00682181 call 0x95e330
00682186 add esp, 0x10
00682189 pop edi
0068218a pop esi
0068218b pop ebx
0068218c mov esp, ebp
0068218e pop ebp
0068218f ret 
