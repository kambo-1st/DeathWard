00506130 push ebx
00506131 mov ebx, esp
00506133 sub esp, 8
00506136 and esp, 0xfffffff8
00506139 add esp, 4
0050613c push ebp
0050613d mov ebp, dword ptr [ebx + 4]
00506140 mov dword ptr [esp + 4], ebp
00506144 mov ebp, esp
00506146 push -1
00506148 push 0x9ef3fd
0050614d mov eax, dword ptr fs:[0]
00506153 push eax
00506154 push ebx
00506155 sub esp, 0xf8
0050615b mov eax, dword ptr [0xbaa3b4]
00506160 xor eax, ebp
00506162 mov dword ptr [ebp - 0x14], eax
00506165 push esi
00506166 push edi
00506167 push eax
00506168 lea eax, [ebp - 0xc]
0050616b mov dword ptr fs:[0], eax
00506171 mov edi, ecx
00506173 mov ecx, dword ptr [edi + 0xab4]
00506179 mov eax, dword ptr [edi + 0x2c]
0050617c test ecx, ecx
0050617e jne 0x506375
00506184 test eax, eax
00506186 je 0x506191
00506188 cmp eax, 2
0050618b jne 0x506350
00506191 call 0x6c3d90
00506196 push 0
00506198 push 0xbeab70
0050619d push 0xbeab18
005061a2 push 0
005061a4 push eax
005061a5 mov eax, dword ptr [edi + 0x2c]
005061a8 lea ecx, [edi + 0x294]
005061ae push 0
005061b0 push edi
005061b1 push 0xc02fec
005061b6 push ecx
005061b7 mov ecx, dword ptr [0xbfd65c]
005061bd inc eax
005061be push eax
005061bf push 0x23
005061c1 call 0x422e20
005061c6 push eax
005061c7 call 0x9ec34c
005061cc mov esi, eax
005061ce add esp, 0x14
005061d1 mov ecx, dword ptr [esi + 0x318]
005061d7 lea eax, [esi + 0x318]
005061dd test ecx, ecx
005061df je 0x5061ff
005061e1 mov dword ptr [ebp - 0xf4], eax
005061e7 add ecx, 0x324
005061ed lea eax, [ebp - 0xf4]
005061f3 push eax
005061f4 call 0x4bc3c0
005061f9 lea eax, [esi + 0x318]
005061ff push eax
00506200 mov ecx, edi
00506202 mov dword ptr [eax], edi
00506204 call 0x4bae70
00506209 lea eax, [edi + 0x314]
0050620f mov dword ptr [esi + 0x180], 2
00506219 mov dword ptr [esi + 0x17c], 3
00506223 mov ecx, dword ptr [eax]
00506225 test ecx, ecx
00506227 je 0x506247
00506229 mov dword ptr [ebp - 0xf4], eax
0050622f add ecx, 0x324
00506235 lea eax, [ebp - 0xf4]
0050623b push eax
0050623c call 0x4bc3c0
00506241 lea eax, [edi + 0x314]
00506247 push eax
00506248 mov ecx, esi
0050624a mov dword ptr [eax], esi
0050624c call 0x4bae70
00506251 mov eax, dword ptr [esi]
00506253 mov ecx, esi
00506255 mov dword ptr [esi + 0x2b0], 0x41200000
0050625f call dword ptr [eax + 0xc]
00506262 mov dword ptr [ebp - 0xf4], 0
0050626c nop dword ptr [eax]
00506270 call 0x6c3d90
00506275 mov ecx, dword ptr [0xbfd65c]
0050627b push 0
0050627d push 0xbeab70
00506282 push 0xbeab18
00506287 push 0
00506289 push eax
0050628a push 0
0050628c push edi
0050628d push 0xc02fec
00506292 lea eax, [edi + 0x294]
00506298 push eax
00506299 push 0xa
0050629b push 0x23
0050629d call 0x422e20
005062a2 push eax
005062a3 call 0x9ec34c
005062a8 mov esi, eax
005062aa add esp, 0x14
005062ad mov ecx, dword ptr [esi + 0x314]
005062b3 lea eax, [esi + 0x314]
005062b9 test ecx, ecx
005062bb je 0x5062db
005062bd mov dword ptr [ebp - 0xf8], eax
005062c3 add ecx, 0x324
005062c9 lea eax, [ebp - 0xf8]
005062cf push eax
005062d0 call 0x4bc3c0
005062d5 lea eax, [esi + 0x314]
005062db push eax
005062dc mov ecx, edi
005062de mov dword ptr [eax], edi
005062e0 call 0x4bae70
005062e5 mov edx, dword ptr [ebp - 0xf4]
005062eb mov ecx, dword ptr [esi + 0x160]
005062f1 mov eax, dword ptr [esi + 0x164]
005062f7 and ecx, 0xfffffffb
005062fa or ecx, 0x40000
00506300 mov dword ptr [esi + 0x180], 0
0050630a movd xmm0, edx
0050630e inc edx
0050630f mov dword ptr [esi + 0x150], 0
00506319 mov dword ptr [esi + 0x2ac], 0x7d0
00506323 mov dword ptr [esi + 0x160], ecx
00506329 mov dword ptr [esi + 0x164], eax
0050632f mov byte ptr [esi + 0x169], 0
00506336 mov dword ptr [ebp - 0xf4], edx
0050633c cvtdq2ps xmm0, xmm0
0050633f movss dword ptr [esi + 0xb00], xmm0
00506347 cmp edx, 8
0050634a jl 0x506270
00506350 mov eax, dword ptr [edi + 0x164]
00506356 or dword ptr [edi + 0x160], 0x40000
00506360 mov dword ptr [edi + 0x164], eax
00506366 mov dword ptr [edi + 0xab4], 4
00506370 jmp 0x50723a
00506375 cmp eax, 1
00506378 je 0x506b6d
0050637e cmp eax, 3
00506381 je 0x506b6d
00506387 cmp eax, 0xa
0050638a jne 0x50655d
00506390 mov eax, dword ptr [edi + 0x314]
00506396 test eax, eax
00506398 je 0x506551
0050639e cmp dword ptr [eax + 0x28], 0x23
005063a2 jne 0x506551
005063a8 cmp dword ptr [eax + 0x314], 0
005063af je 0x506551
005063b5 mov ecx, edi
005063b7 call 0x4395d0
005063bc cmp dword ptr [eax + 0xab4], 8
005063c3 je 0x5063d1
005063c5 mov byte ptr [edi + 0x169], 0
005063cc jmp 0x50723a
005063d1 mov ecx, edi
005063d3 call 0x4395d0
005063d8 cmp dword ptr [eax + 0x314], 0
005063df je 0x50723a
005063e5 mov ecx, edi
005063e7 mov byte ptr [edi + 0x169], 1
005063ee call 0x4395d0
005063f3 mov ecx, eax
005063f5 call 0x4395d0
005063fa mov ecx, edi
005063fc mov esi, eax
005063fe call 0x4395d0
00506403 mov ecx, edi
00506405 movss xmm0, dword ptr [eax + 0x294]
0050640d subss xmm0, dword ptr [esi + 0x294]
00506415 movss dword ptr [ebp - 0xfc], xmm0
0050641d movss xmm0, dword ptr [eax + 0x298]
00506425 subss xmm0, dword ptr [esi + 0x298]
0050642d movss dword ptr [ebp - 0xf8], xmm0
00506435 movss xmm0, dword ptr [0xb6a928]
0050643d subss xmm0, dword ptr [edi + 0xb00]
00506445 mulss xmm0, dword ptr [0xb6a2ec]
0050644d movss dword ptr [ebp - 0xf4], xmm0
00506455 call 0x4395d0
0050645a movss xmm2, dword ptr [ebp - 0xfc]
00506462 movss xmm1, dword ptr [ebp - 0xf4]
0050646a mulss xmm1, xmm2
0050646e movss xmm0, dword ptr [eax + 0x294]
00506476 mulss xmm2, xmm2
0050647a subss xmm0, xmm1
0050647e movss dword ptr [edi + 0x294], xmm0
00506486 movss xmm0, dword ptr [edi + 0xb00]
0050648e subss xmm0, dword ptr [0xb6a8cc]
00506496 andps xmm0, xmmword ptr [0xb6c980]
0050649d movss dword ptr [ebp - 0xfc], xmm0
005064a5 movss xmm0, dword ptr [ebp - 0xf8]
005064ad movaps xmm1, xmm0
005064b0 mulss xmm0, xmm1
005064b4 addss xmm0, xmm2
005064b8 call 0x4228c0
005064bd movss xmm3, dword ptr [0xb6aafc]
005064c5 mov ecx, edi
005064c7 movss xmm2, dword ptr [ebp - 0xfc]
005064cf subss xmm3, xmm0
005064d3 movss xmm0, dword ptr [0xb6a9b0]
005064db mulss xmm2, xmm2
005064df maxss xmm3, dword ptr [0xb6a18c]
005064e7 subss xmm0, xmm2
005064eb mulss xmm3, xmm0
005064ef divss xmm3, dword ptr [0xb6aafc]
005064f7 movss dword ptr [ebp - 0xfc], xmm3
005064ff call 0x4395d0
00506504 movss xmm1, dword ptr [ebp - 0xf4]
0050650c mulss xmm1, dword ptr [ebp - 0xf8]
00506514 movss xmm0, dword ptr [eax + 0x298]
0050651c subss xmm0, xmm1
00506520 movss xmm1, dword ptr [ebp - 0xfc]
00506528 subss xmm0, dword ptr [0xb6aa14]
00506530 addss xmm1, xmm0
00506534 addss xmm1, dword ptr [edi + 0xb00]
0050653c addss xmm1, dword ptr [0xb6a8f4]
00506544 movss dword ptr [edi + 0x298], xmm1
0050654c jmp 0x50723a
00506551 mov eax, dword ptr [edi]
00506553 mov ecx, edi
00506555 call dword ptr [eax + 0x28]
00506558 jmp 0x50723a
0050655d test eax, eax
0050655f je 0x50656a
00506561 cmp eax, 2
00506564 jne 0x50723a
0050656a cmp ecx, 4
0050656d jne 0x506869
00506573 mov eax, dword ptr [0xb42f58]
00506578 movq xmm0, qword ptr [0xb42f50]
00506580 mov dword ptr [ebp - 0x3c], eax
00506583 mov al, byte ptr [0xb42f5c]
00506588 mov dword ptr [ebp - 0x30], 0xf
0050658f mov dword ptr [ebp - 0x34], 0xd
00506596 movq qword ptr [ebp - 0x44], xmm0
0050659b mov byte ptr [ebp - 0x38], al
0050659e mov byte ptr [ebp - 0x37], 0
005065a2 mov dword ptr [ebp - 4], 0
005065a9 mov eax, dword ptr [0xb42f38]
005065ae movq xmm0, qword ptr [0xb42f30]
005065b6 mov dword ptr [ebp - 0x24], eax
005065b9 mov al, byte ptr [0xb42f3c]
005065be mov dword ptr [ebp - 0x18], 0xf
005065c5 mov dword ptr [ebp - 0x1c], 0xd
005065cc movq qword ptr [ebp - 0x2c], xmm0
005065d1 mov byte ptr [ebp - 0x20], al
005065d4 mov byte ptr [ebp - 0x1f], 0
005065d8 push ecx
005065d9 mov byte ptr [ebp - 4], 1
005065dd lea eax, [ebp - 0x44]
005065e0 mov dword ptr [esp], 0x3dcccccd
005065e7 mov ecx, edi
005065e9 push eax
005065ea lea eax, [ebp - 0x2c]
005065ed push eax
005065ee call 0x6980a0
005065f3 mov byte ptr [ebp - 4], 0
005065f7 mov edx, dword ptr [ebp - 0x18]
005065fa cmp edx, 0x10
005065fd jb 0x506627
005065ff mov ecx, dword ptr [ebp - 0x2c]
00506602 inc edx
00506603 mov eax, ecx
00506605 cmp edx, 0x1000
0050660b jb 0x50661d
0050660d mov ecx, dword ptr [ecx - 4]
00506610 add edx, 0x23
00506613 sub eax, ecx
00506615 add eax, -4
00506618 cmp eax, 0x1f
0050661b ja 0x506666
0050661d push edx
0050661e push ecx
0050661f call 0x9eb08e
00506624 add esp, 8
00506627 mov dword ptr [ebp - 4], 0xffffffff
0050662e mov edx, dword ptr [ebp - 0x30]
00506631 mov dword ptr [ebp - 0x1c], 0
00506638 mov dword ptr [ebp - 0x18], 0xf
0050663f mov byte ptr [ebp - 0x2c], 0
00506643 cmp edx, 0x10
00506646 jb 0x506676
00506648 mov ecx, dword ptr [ebp - 0x44]
0050664b inc edx
0050664c mov eax, ecx
0050664e cmp edx, 0x1000
00506654 jb 0x50666c
00506656 mov ecx, dword ptr [ecx - 4]
00506659 add edx, 0x23
0050665c sub eax, ecx
0050665e add eax, -4
00506661 cmp eax, 0x1f
00506664 jbe 0x50666c
00506666 call dword ptr [0xa065ac]
0050666c push edx
0050666d push ecx
0050666e call 0x9eb08e
00506673 add esp, 8
00506676 push 0
00506678 push 0x1000800
0050667d mov ecx, edi
0050667f call 0x4122f0
00506684 test al, al
00506686 je 0x5066de
00506688 cmp dword ptr [edi + 0xe6c], -1
0050668f jne 0x5066de
00506691 mov ecx, edi
00506693 call 0x695680
00506698 push 0
0050669a mov ecx, dword ptr [eax + 0x294]
005066a0 mov eax, dword ptr [eax + 0x298]
005066a6 mov dword ptr [ebp - 0x100], eax
005066ac lea eax, [ebp - 0x104]
005066b2 mov dword ptr [ebp - 0x104], ecx
005066b8 lea ecx, [edi + 0x364]
005066be push eax
005066bf call 0x7a4830
005066c4 movss xmm0, dword ptr [edi + 0x2c4]
005066cc mulss xmm0, dword ptr [0xb6a560]
005066d4 movss dword ptr [edi + 0x2c4], xmm0
005066dc jmp 0x506727
005066de cmp dword ptr [edi + 0x2c], 2
005066e2 jne 0x5066ee
005066e4 movss xmm0, dword ptr [0xb6a560]
005066ec jmp 0x5066f6
005066ee movss xmm0, dword ptr [0xb6a4c4]
005066f6 push 1
005066f8 push 0x384
005066fd sub esp, 8
00506700 lea eax, [ebp - 0x104]
00506706 mov ecx, edi
00506708 movss dword ptr [esp + 4], xmm0
0050670e mov dword ptr [esp], 0
00506715 push eax
00506716 call 0x695a30
0050671b push eax
0050671c lea ecx, [edi + 0x364]
00506722 call 0x7a3650
00506727 cmp dword ptr [edi + 0xe6c], -1
0050672e mov ecx, edi
00506730 je 0x506742
00506732 push 0xa
00506734 call 0x6af080
00506739 movzx eax, al
0050673c test eax, eax
0050673e je 0x506794
00506740 jmp 0x506774
00506742 call 0x695680
00506747 push eax
00506748 mov ecx, edi
0050674a call 0x6aeb40
0050674f test al, al
00506751 je 0x506794
00506753 cmp byte ptr [edi + 0xa90], 0
0050675a je 0x506794
0050675c cmp dword ptr [edi + 0x2c], 0
00506760 jne 0x506794
00506762 call 0x6c3d90
00506767 xor edx, edx
00506769 mov ecx, 3
0050676e div ecx
00506770 test edx, edx
00506772 jne 0x506794
00506774 push ecx
00506775 mov dword ptr [esp], 0x3f800000
0050677c push 0
0050677e push 0x28
00506780 push ecx
00506781 mov dword ptr [esp], 0x3f800000
00506788 mov ecx, edi
0050678a push 0xa5
0050678f call 0x6ad720
00506794 cmp dword ptr [edi + 0x314], 0
0050679b je 0x506a4f
005067a1 movss xmm0, dword ptr [edi + 0x294]
005067a9 mov ecx, edi
005067ab movss dword ptr [ebp - 0xf8], xmm0
005067b3 movss xmm0, dword ptr [edi + 0x2b8]
005067bb movss dword ptr [ebp - 0xfc], xmm0
005067c3 movss xmm0, dword ptr [edi + 0x2bc]
005067cb movss dword ptr [ebp - 0x108], xmm0
005067d3 movss xmm0, dword ptr [edi + 0x298]
005067db movss dword ptr [ebp - 0xf4], xmm0
005067e3 call 0x4395d0
005067e8 movss xmm0, dword ptr [ebp - 0xf8]
005067f0 mov ecx, edi
005067f2 addss xmm0, dword ptr [ebp - 0xfc]
005067fa subss xmm0, dword ptr [eax + 0x294]
00506802 movss dword ptr [ebp - 0xf8], xmm0
0050680a movss xmm0, dword ptr [ebp - 0xf4]
00506812 addss xmm0, dword ptr [ebp - 0x108]
0050681a subss xmm0, dword ptr [eax + 0x298]
00506822 movss dword ptr [ebp - 0xf4], xmm0
0050682a call 0x4395d0
0050682f movss xmm0, dword ptr [ebp - 0xf8]
00506837 mov ecx, edi
00506839 movss dword ptr [eax + 0x2b8], xmm0
00506841 movss xmm0, dword ptr [ebp - 0xf4]
00506849 movss dword ptr [eax + 0x2bc], xmm0
00506851 call 0x4395d0
00506856 lea ecx, [eax + 0x13c]
0050685c mov al, byte ptr [edi + 0x13c]
00506862 mov byte ptr [ecx], al
00506864 jmp 0x506a4f
00506869 cmp dword ptr [edi + 0xe6c], -1
00506870 movss xmm0, dword ptr [edi + 0x2c4]
00506878 mulss xmm0, dword ptr [0xb6a50c]
00506880 movss dword ptr [edi + 0x2c4], xmm0
00506888 je 0x5069dc
0050688e mov eax, dword ptr [0xb42f58]
00506893 movq xmm0, qword ptr [0xb42f50]
0050689b mov dword ptr [ebp - 0x3c], eax
0050689e mov al, byte ptr [0xb42f5c]
005068a3 mov dword ptr [ebp - 0x30], 0xf
005068aa mov dword ptr [ebp - 0x34], 0xd
005068b1 movq qword ptr [ebp - 0x44], xmm0
005068b6 mov byte ptr [ebp - 0x38], al
005068b9 mov byte ptr [ebp - 0x37], 0
005068bd mov dword ptr [ebp - 4], 2
005068c4 mov eax, dword ptr [0xb42f38]
005068c9 movq xmm0, qword ptr [0xb42f30]
005068d1 mov dword ptr [ebp - 0x24], eax
005068d4 mov al, byte ptr [0xb42f3c]
005068d9 mov dword ptr [ebp - 0x18], 0xf
005068e0 mov dword ptr [ebp - 0x1c], 0xd
005068e7 movq qword ptr [ebp - 0x2c], xmm0
005068ec mov byte ptr [ebp - 0x20], al
005068ef mov byte ptr [ebp - 0x1f], 0
005068f3 push ecx
005068f4 mov byte ptr [ebp - 4], 3
005068f8 lea eax, [ebp - 0x44]
005068fb mov dword ptr [esp], 0x3dcccccd
00506902 mov ecx, edi
00506904 push eax
00506905 lea eax, [ebp - 0x2c]
00506908 push eax
00506909 call 0x6980a0
0050690e mov byte ptr [ebp - 4], 2
00506912 mov edx, dword ptr [ebp - 0x18]
00506915 cmp edx, 0x10
00506918 jb 0x506942
0050691a mov ecx, dword ptr [ebp - 0x2c]
0050691d inc edx
0050691e mov eax, ecx
00506920 cmp edx, 0x1000
00506926 jb 0x506938
00506928 mov ecx, dword ptr [ecx - 4]
0050692b add edx, 0x23
0050692e sub eax, ecx
00506930 add eax, -4
00506933 cmp eax, 0x1f
00506936 ja 0x506981
00506938 push edx
00506939 push ecx
0050693a call 0x9eb08e
0050693f add esp, 8
00506942 mov dword ptr [ebp - 4], 0xffffffff
00506949 mov edx, dword ptr [ebp - 0x30]
0050694c mov dword ptr [ebp - 0x1c], 0
00506953 mov dword ptr [ebp - 0x18], 0xf
0050695a mov byte ptr [ebp - 0x2c], 0
0050695e cmp edx, 0x10
00506961 jb 0x506991
00506963 mov ecx, dword ptr [ebp - 0x44]
00506966 inc edx
00506967 mov eax, ecx
00506969 cmp edx, 0x1000
0050696f jb 0x506987
00506971 mov ecx, dword ptr [ecx - 4]
00506974 add edx, 0x23
00506977 sub eax, ecx
00506979 add eax, -4
0050697c cmp eax, 0x1f
0050697f jbe 0x506987
00506981 call dword ptr [0xa065ac]
00506987 push edx
00506988 push ecx
00506989 call 0x9eb08e
0050698e add esp, 8
00506991 cmp dword ptr [edi + 0x2c], 2
00506995 jne 0x5069a1
00506997 movss xmm0, dword ptr [0xb6a434]
0050699f jmp 0x5069a9
005069a1 movss xmm0, dword ptr [0xb6a3b0]
005069a9 push 1
005069ab push 0x384
005069b0 sub esp, 8
005069b3 lea eax, [ebp - 0x104]
005069b9 mov ecx, edi
005069bb movss dword ptr [esp + 4], xmm0
005069c1 mov dword ptr [esp], 0
005069c8 push eax
005069c9 call 0x695a30
005069ce push eax
005069cf lea ecx, [edi + 0x364]
005069d5 call 0x7a3650
005069da jmp 0x506a4f
005069dc cmp dword ptr [edi + 0x70], 0
005069e0 lea ecx, [edi + 0x6c]
005069e3 je 0x506a4f
005069e5 lea eax, [ebp - 0x44]
005069e8 push eax
005069e9 call 0x444be0
005069ee push 0
005069f0 push eax
005069f1 lea ecx, [edi + 0x3c]
005069f4 mov dword ptr [ebp - 4], 4
005069fb call 0x405800
00506a00 mov dword ptr [ebp - 4], 0xffffffff
00506a07 mov edx, dword ptr [ebp - 0x30]
00506a0a cmp edx, 0x10
00506a0d jb 0x506a3d
00506a0f mov ecx, dword ptr [ebp - 0x44]
00506a12 inc edx
00506a13 mov eax, ecx
00506a15 cmp edx, 0x1000
00506a1b jb 0x506a33
00506a1d mov ecx, dword ptr [ecx - 4]
00506a20 add edx, 0x23
00506a23 sub eax, ecx
00506a25 add eax, -4
00506a28 cmp eax, 0x1f
00506a2b jbe 0x506a33
00506a2d call dword ptr [0xa065ac]
00506a33 push edx
00506a34 push ecx
00506a35 call 0x9eb08e
00506a3a add esp, 8
00506a3d mov dword ptr [ebp - 0x34], 0
00506a44 mov dword ptr [ebp - 0x30], 0xf
00506a4b mov byte ptr [ebp - 0x44], 0
00506a4f cmp byte ptr [edi + 0x16b], 0
00506a56 mov eax, dword ptr [edi + 0x314]
00506a5c je 0x506aa4
00506a5e test eax, eax
00506a60 je 0x50723a
00506a66 mov ecx, edi
00506a68 call 0x4395d0
00506a6d push dword ptr [edi + 0xbb4]
00506a73 xor ecx, ecx
00506a75 mov esi, eax
00506a77 cmp dword ptr [edi + 0x2c], ecx
00506a7a push 0
00506a7c setne cl
00506a7f push ecx
00506a80 push 0x1a
00506a82 mov ecx, esi
00506a84 call 0x697c60
00506a89 mov eax, dword ptr [esi + 0x2dc]
00506a8f mov dword ptr [esi + 0x180], 4
00506a99 mov dword ptr [esi + 0x2d8], eax
00506a9f jmp 0x50723a
00506aa4 test eax, eax
00506aa6 jne 0x50723a
00506aac push dword ptr [edi + 0xbb4]
00506ab2 mov esi, dword ptr [edi + 0x2c]
00506ab5 mov ecx, edi
00506ab7 push eax
00506ab8 push eax
00506ab9 push 0xb
00506abb call 0x697c60
00506ac0 mov eax, dword ptr [edi + 0x2dc]
00506ac6 mov dword ptr [edi + 0x2d8], eax
00506acc cmp esi, 3
00506acf jne 0x506b1f
00506ad1 cmp dword ptr [edi + 0xbc], 0
00506ad8 jg 0x506af8
00506ada cmp dword ptr [edi + 0x50], 0x10
00506ade lea eax, [edi + 0x3c]
00506ae1 jb 0x506ae6
00506ae3 mov eax, dword ptr [edi + 0x3c]
00506ae6 push 0
00506ae8 push eax
00506ae9 push 0xa0830c
00506aee push 3
00506af0 call 0x95e330
00506af5 add esp, 0x10
00506af8 mov eax, dword ptr [edi + 0xb8]
00506afe mov dword ptr [eax + 0x48], 0x3f8a0a0b
00506b05 mov dword ptr [eax + 0x4c], 0x3f61e1e3
00506b0c mov dword ptr [eax + 0x50], 0x3f61e1e3
00506b13 mov dword ptr [eax + 0x54], 0x3f800000
00506b1a jmp 0x50723a
00506b1f cmp dword ptr [edi + 0xbc], 0
00506b26 jg 0x506b46
00506b28 cmp dword ptr [edi + 0x50], 0x10
00506b2c lea eax, [edi + 0x3c]
00506b2f jb 0x506b34
00506b31 mov eax, dword ptr [edi + 0x3c]
00506b34 push 0
00506b36 push eax
00506b37 push 0xa0830c
00506b3c push 3
00506b3e call 0x95e330
00506b43 add esp, 0x10
00506b46 mov eax, dword ptr [edi + 0xb8]
00506b4c mov dword ptr [eax + 0x48], 0x3fb1b1b2
00506b53 mov dword ptr [eax + 0x4c], 0x3fb1b1b2
00506b5a mov dword ptr [eax + 0x50], 0x3fb1b1b2
00506b61 mov dword ptr [eax + 0x54], 0x3f800000
00506b68 jmp 0x50723a
00506b6d call 0x6c3d90
00506b72 xor edx, edx
00506b74 mov ecx, 0xa
00506b79 div ecx
00506b7b test edx, edx
00506b7d jne 0x506bc1
00506b7f call 0x6c3d90
00506b84 push ecx
00506b85 mov ecx, edi
00506b87 movd xmm0, eax
00506b8b cvtdq2pd xmm0, xmm0
00506b8f shr eax, 0x1f
00506b92 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00506b9b cvtpd2ps xmm0, xmm0
00506b9f mulss xmm0, dword ptr [0xb6a19c]
00506ba7 mulss xmm0, dword ptr [0xb6a480]
00506baf addss xmm0, dword ptr [0xb6a350]
00506bb7 movss dword ptr [esp], xmm0
00506bbc call 0x68d7b0
00506bc1 cmp byte ptr [edi + 0x16b], 0
00506bc8 jne 0x5070bb
00506bce call 0x6c3d90
00506bd3 xor edx, edx
00506bd5 mov ecx, 0x3e8
00506bda div ecx
00506bdc test edx, edx
00506bde jne 0x506c03
00506be0 mov ecx, edi
00506be2 call 0x448120
00506be7 test eax, eax
00506be9 je 0x5070bb
00506bef mov ecx, edi
00506bf1 call 0x448120
00506bf6 cmp dword ptr [eax + 0xe6c], -1
00506bfd je 0x5070bb
00506c03 cmp dword ptr [edi + 0x318], 0
00506c0a je 0x50718d
00506c10 cvttss2si esi, dword ptr [edi + 0x2fc]
00506c18 mov ecx, edi
00506c1a cvttss2si eax, dword ptr [edi + 0x2f8]
00506c22 sub esi, eax
00506c24 call 0x448120
00506c29 mov ecx, edi
00506c2b mov eax, dword ptr [eax + 0xaf0]
00506c31 sub eax, esi
00506c33 mov esi, 0xffffffe2
00506c38 cmp eax, esi
00506c3a cmovg esi, eax
00506c3d call 0x448120
00506c42 mov ecx, edi
00506c44 mov dword ptr [eax + 0xaf0], esi
00506c4a call 0x448120
00506c4f mov ecx, edi
00506c51 cmp dword ptr [eax + 0xab4], 4
00506c58 jne 0x506ef4
00506c5e call 0x448120
00506c63 cmp dword ptr [eax + 0xe6c], -1
00506c6a je 0x506d2a
00506c70 mov eax, dword ptr [edi + 0x160]
00506c76 and eax, 0x1000a00
00506c7b or eax, 0
00506c7e jne 0x50723a
00506c84 push 1
00506c86 push ecx
00506c87 mov ecx, edi
00506c89 call 0x448120
00506c8e add esp, 4
00506c91 mov ecx, eax
00506c93 call 0x6afe20
00506c98 push 0xc02fec
00506c9d push ecx
00506c9e mov ecx, edi
00506ca0 call 0x448120
00506ca5 add esp, 4
00506ca8 lea ecx, [eax + 0xe70]
00506cae call 0x962ca0
00506cb3 test al, al
00506cb5 je 0x50723a
00506cbb push ecx
00506cbc mov dword ptr [esp], 0x3f800000
00506cc3 push 0
00506cc5 push 2
00506cc7 push ecx
00506cc8 mov dword ptr [esp], 0x3f800000
00506ccf mov ecx, edi
00506cd1 push 0xe2
00506cd6 call 0x6ad720
00506cdb push ecx
00506cdc lea eax, [ebp - 0x104]
00506ce2 mov dword ptr [esp], 0x41600000
00506ce9 push eax
00506cea mov ecx, edi
00506cec call 0x448120
00506cf1 lea ecx, [eax + 0xe70]
00506cf7 call 0x9628d0
00506cfc movss xmm0, dword ptr [edi + 0x2c4]
00506d04 movss xmm2, dword ptr [eax]
00506d08 movss xmm1, dword ptr [eax + 4]
00506d0d divss xmm2, xmm0
00506d11 divss xmm1, xmm0
00506d15 movss dword ptr [edi + 0x2b8], xmm2
00506d1d movss dword ptr [edi + 0x2bc], xmm1
00506d25 jmp 0x506ecd
00506d2a push 0
00506d2c push 4
00506d2e mov ecx, edi
00506d30 call 0x684790
00506d35 test al, al
00506d37 je 0x50723a
00506d3d mov eax, dword ptr [edi + 0x160]
00506d43 and eax, 0x1000a00
00506d48 or eax, 0
00506d4b jne 0x50723a
00506d51 mov ecx, edi
00506d53 call 0x695680
00506d58 mov ecx, edi
00506d5a movss xmm3, dword ptr [eax + 0x2b8]
00506d62 movss dword ptr [ebp - 0xf4], xmm3
00506d6a movss xmm3, dword ptr [eax + 0x2bc]
00506d72 movss dword ptr [ebp - 0xf8], xmm3
00506d7a call 0x695680
00506d7f movss xmm2, dword ptr [ebp - 0xf4]
00506d87 lea esi, [edi + 0x294]
00506d8d movss xmm1, dword ptr [ebp - 0xf8]
00506d95 mulss xmm2, dword ptr [0xb6a864]
00506d9d mulss xmm1, dword ptr [0xb6a864]
00506da5 addss xmm2, dword ptr [eax + 0x294]
00506dad addss xmm1, dword ptr [eax + 0x298]
00506db5 subss xmm2, dword ptr [esi]
00506db9 subss xmm1, dword ptr [esi + 4]
00506dbe movaps xmm0, xmm2
00506dc1 movss dword ptr [ebp - 0xf4], xmm2
00506dc9 mulss xmm0, xmm2
00506dcd movaps xmm3, xmm1
00506dd0 movss dword ptr [ebp - 0xf8], xmm1
00506dd8 mulss xmm3, xmm1
00506ddc addss xmm3, xmm0
00506de0 movss xmm0, dword ptr [0xb6ad48]
00506de8 comiss xmm0, xmm3
00506deb movss dword ptr [ebp - 0x108], xmm3
00506df3 jbe 0x50723a
00506df9 ucomiss xmm2, dword ptr [0xc02fec]
00506e00 lahf 
00506e01 test ah, 0x44
00506e04 jp 0x506e17
00506e06 ucomiss xmm1, dword ptr [0xc02ff0]
00506e0d lahf 
00506e0e test ah, 0x44
00506e11 jnp 0x50723a
00506e17 mov ecx, edi
00506e19 call 0x695680
00506e1e push 0
00506e20 push 0
00506e22 push 0
00506e24 mov ecx, dword ptr [eax + 0x294]
00506e2a mov eax, dword ptr [eax + 0x298]
00506e30 push 0
00506e32 mov dword ptr [ebp - 0x104], ecx
00506e38 mov ecx, dword ptr [0xbfd65c]
00506e3e mov dword ptr [ebp - 0x100], eax
00506e44 lea eax, [ebp - 0x104]
00506e4a push 2
00506e4c push eax
00506e4d mov ecx, dword ptr [ecx + 0x18190]
00506e53 push esi
00506e54 call 0x7af4b0
00506e59 test al, al
00506e5b je 0x50723a
00506e61 push ecx
00506e62 mov dword ptr [esp], 0x3f800000
00506e69 push 0
00506e6b push 2
00506e6d push ecx
00506e6e mov dword ptr [esp], 0x3f800000
00506e75 mov ecx, edi
00506e77 push 0xe2
00506e7c call 0x6ad720
00506e81 movss xmm0, dword ptr [ebp - 0x108]
00506e89 call 0x4228c0
00506e8e movss xmm2, dword ptr [0xb6a9a0]
00506e96 divss xmm2, xmm0
00506e9a movss xmm0, dword ptr [edi + 0x2c4]
00506ea2 movaps xmm1, xmm2
00506ea5 mulss xmm2, dword ptr [ebp - 0xf8]
00506ead mulss xmm1, dword ptr [ebp - 0xf4]
00506eb5 divss xmm2, xmm0
00506eb9 divss xmm1, xmm0
00506ebd movss dword ptr [edi + 0x2bc], xmm2
00506ec5 movss dword ptr [edi + 0x2b8], xmm1
00506ecd mov ecx, edi
00506ecf call 0x448120
00506ed4 mov ecx, edi
00506ed6 mov dword ptr [eax + 0xaf0], 0x1e
00506ee0 call 0x448120
00506ee5 mov dword ptr [eax + 0xab4], 8
00506eef jmp 0x50723a
00506ef4 call 0x448120
00506ef9 cmp dword ptr [eax + 0xab4], 8
00506f00 jne 0x50723a
00506f06 mov ecx, edi
00506f08 call 0x448120
00506f0d movss xmm1, dword ptr [eax + 0x298]
00506f15 subss xmm1, dword ptr [edi + 0x298]
00506f1d movss xmm2, dword ptr [eax + 0x294]
00506f25 subss xmm2, dword ptr [edi + 0x294]
00506f2d movaps xmm0, xmm1
00506f30 movss dword ptr [ebp - 0x100], xmm1
00506f38 mulss xmm0, xmm1
00506f3c movaps xmm1, xmm2
00506f3f movss dword ptr [ebp - 0xf8], xmm2
00506f47 mulss xmm1, xmm2
00506f4b addss xmm0, xmm1
00506f4f call 0x4228c0
00506f54 movss xmm1, dword ptr [0xb6a8f4]
00506f5c comiss xmm1, xmm0
00506f5f movss dword ptr [ebp - 0xf4], xmm0
00506f67 jbe 0x506f97
00506f69 mov ecx, edi
00506f6b call 0x448120
00506f70 cmp dword ptr [eax + 0xaf0], 0xf
00506f77 jge 0x506f8f
00506f79 mov ecx, edi
00506f7b call 0x448120
00506f80 mov dword ptr [eax + 0xab4], 4
00506f8a jmp 0x50723a
00506f8f movss xmm0, dword ptr [ebp - 0xf4]
00506f97 comiss xmm0, dword ptr [0xb6a18c]
00506f9e jbe 0x50723a
00506fa4 mov ecx, edi
00506fa6 call 0x448120
00506fab xorps xmm4, xmm4
00506fae mov dword ptr [ebp - 0x108], 0
00506fb8 lea ecx, [ebp - 0xfc]
00506fbe movd xmm0, dword ptr [eax + 0xaf0]
00506fc6 lea eax, [ebp - 0x108]
00506fcc cvtdq2ps xmm0, xmm0
00506fcf subss xmm0, dword ptr [0xb6af0c]
00506fd7 divss xmm0, dword ptr [0xb6aa4c]
00506fdf comiss xmm4, xmm0
00506fe2 movss dword ptr [ebp - 0xfc], xmm0
00506fea movss xmm0, dword ptr [0xb6a614]
00506ff2 cmovbe eax, ecx
00506ff5 movss xmm1, dword ptr [eax]
00506ff9 comiss xmm1, xmm0
00506ffc ja 0x507004
00506ffe movss xmm0, xmm1
00507002 jmp 0x507008
00507004 movss xmm0, xmm0
00507008 mulss xmm0, dword ptr [0xb6a50c]
00507010 movss xmm3, dword ptr [0xb6a6c8]
00507018 movss xmm5, dword ptr [edi + 0x2c4]
00507020 subss xmm3, xmm0
00507024 movss xmm2, dword ptr [ebp - 0xf8]
0050702c ucomiss xmm5, xmm4
0050702f divss xmm3, dword ptr [ebp - 0xf4]
00507037 lahf 
00507038 mulss xmm2, xmm3
0050703c mulss xmm3, dword ptr [ebp - 0x100]
00507044 test ah, 0x44
00507047 jnp 0x507084
00507049 movss xmm1, dword ptr [edi + 0x2f4]
00507051 movaps xmm0, xmm1
00507054 mulss xmm1, xmm3
00507058 mulss xmm0, xmm2
0050705c divss xmm1, xmm5
00507060 divss xmm0, xmm5
00507064 addss xmm1, dword ptr [edi + 0x2bc]
0050706c addss xmm0, dword ptr [edi + 0x2b8]
00507074 movss dword ptr [edi + 0x2bc], xmm1
0050707c movss dword ptr [edi + 0x2b8], xmm0
00507084 mov ecx, edi
00507086 call 0x448120
0050708b movd xmm0, dword ptr [eax + 0xaf0]
00507093 cvtdq2ps xmm0, xmm0
00507096 mulss xmm0, dword ptr [0xb6a1e4]
0050709e addss xmm0, dword ptr [0xb6a5a4]
005070a6 mulss xmm0, dword ptr [edi + 0x2c4]
005070ae movss dword ptr [edi + 0x2c4], xmm0
005070b6 jmp 0x50723a
005070bb cmp dword ptr [edi + 0x318], 0
005070c2 je 0x50718d
005070c8 mov ecx, edi
005070ca call 0x448120
005070cf push dword ptr [edi + 0xbb4]
005070d5 mov esi, eax
005070d7 push 0
005070d9 push 0
005070db push 0xb
005070dd mov ecx, esi
005070df call 0x697c60
005070e4 mov ecx, dword ptr [esi + 0x2dc]
005070ea mov dword ptr [esi + 0x180], 4
005070f4 mov dword ptr [esi + 0x2d8], ecx
005070fa cmp dword ptr [edi + 0x2c], 3
005070fe jne 0x507144
00507100 cmp dword ptr [esi + 0xbc], 0
00507107 jg 0x507127
00507109 cmp dword ptr [esi + 0x50], 0x10
0050710d lea eax, [esi + 0x3c]
00507110 jb 0x507115
00507112 mov eax, dword ptr [esi + 0x3c]
00507115 push 0
00507117 push eax
00507118 push 0xa0830c
0050711d push 3
0050711f call 0x95e330
00507124 add esp, 0x10
00507127 mov eax, dword ptr [esi + 0xb8]
0050712d mov dword ptr [eax + 0x48], 0x3f8a0a0b
00507134 mov dword ptr [eax + 0x4c], 0x3f61e1e3
0050713b mov dword ptr [eax + 0x50], 0x3f61e1e3
00507142 jmp 0x507186
00507144 cmp dword ptr [esi + 0xbc], 0
0050714b jg 0x50716b
0050714d cmp dword ptr [esi + 0x50], 0x10
00507151 lea eax, [esi + 0x3c]
00507154 jb 0x507159
00507156 mov eax, dword ptr [esi + 0x3c]
00507159 push 0
0050715b push eax
0050715c push 0xa0830c
00507161 push 3
00507163 call 0x95e330
00507168 add esp, 0x10
0050716b mov eax, dword ptr [esi + 0xb8]
00507171 mov dword ptr [eax + 0x48], 0x3fb1b1b2
00507178 mov dword ptr [eax + 0x4c], 0x3fb1b1b2
0050717f mov dword ptr [eax + 0x50], 0x3fb1b1b2
00507186 mov dword ptr [eax + 0x54], 0x3f800000
0050718d cmp byte ptr [edi + 0x16b], 0
00507194 je 0x5071f3
00507196 cmp dword ptr [edi + 0x2c], 3
0050719a jne 0x5071f3
0050719c lea ecx, [ebp - 0xf0]
005071a2 mov dword ptr [ebp - 0x104], 0x41000000
005071ac mov dword ptr [ebp - 0x100], 0
005071b6 call 0x430d70
005071bb push eax
005071bc push 6
005071be lea eax, [ebp - 0x104]
005071c4 mov ecx, edi
005071c6 push eax
005071c7 lea eax, [edi + 0x294]
005071cd push eax
005071ce call 0x6a1a20
005071d3 push ecx
005071d4 mov dword ptr [esp], 0x3f800000
005071db push 0
005071dd push 2
005071df push ecx
005071e0 mov dword ptr [esp], 0x3f800000
005071e7 mov ecx, edi
005071e9 push 0x92
005071ee call 0x6ad720
005071f3 mov eax, dword ptr [edi + 0x164]
005071f9 mov ecx, edi
005071fb push dword ptr [edi + 0xbb4]
00507201 and dword ptr [edi + 0x160], 0xfffbffff
0050720b mov dword ptr [edi + 0x164], eax
00507211 xor eax, eax
00507213 cmp dword ptr [edi + 0x2c], 1
00507217 push 0
00507219 setne al
0050721c push eax
0050721d push 0x1a
0050721f call 0x697c60
00507224 mov eax, dword ptr [edi + 0x2dc]
0050722a mov dword ptr [edi + 0x180], 4
00507234 mov dword ptr [edi + 0x2d8], eax
0050723a mov ecx, dword ptr [ebp - 0xc]
0050723d mov dword ptr fs:[0], ecx
00507244 pop ecx
00507245 pop edi
00507246 pop esi
00507247 mov ecx, dword ptr [ebp - 0x14]
0050724a xor ecx, ebp
0050724c call 0x9eacd7
00507251 mov esp, ebp
00507253 pop ebp
00507254 mov esp, ebx
00507256 pop ebx
00507257 ret 
