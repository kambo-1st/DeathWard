; Repentance1.7.9b bounded native evidence. Candidate names are interpretations, not exported symbols.
004bc1e0 push ebp
004bc1e1 mov ebp, esp
004bc1e3 movss xmm1, dword ptr [0xb6aa3c] ; f32=40
004bc1eb push ebx
004bc1ec mov ebx, dword ptr [ebp + 8]
004bc1ef push esi
004bc1f0 mov esi, ecx
004bc1f2 movss xmm2, dword ptr [0xb6a480] ; f32=0.5
004bc1fa push edi
004bc1fb mov eax, dword ptr [ebx]
004bc1fd mov dword ptr [esi + 0x294], eax
004bc203 mov eax, dword ptr [ebx + 4]
004bc206 mov dword ptr [esi + 0x298], eax
004bc20c movss xmm0, dword ptr [ebx]
004bc210 subss xmm0, xmm1
004bc214 mov eax, dword ptr [0xbfd65c]
004bc219 mov edi, dword ptr [eax + 0x18190]
004bc21f divss xmm0, xmm1
004bc223 addss xmm0, xmm2
004bc227 cvttss2si ecx, xmm0
004bc22b test ecx, ecx
004bc22d js 0x4bc25f
004bc22f mov edx, dword ptr [edi + 0xc]
004bc232 cmp ecx, edx
004bc234 jge 0x4bc25f
004bc236 movss xmm0, dword ptr [ebx + 4]
004bc23b subss xmm0, dword ptr [0xb6ab20] ; f32=120
004bc243 divss xmm0, xmm1
004bc247 addss xmm0, xmm2
004bc24b cvttss2si eax, xmm0
004bc24f test eax, eax
004bc251 js 0x4bc25f
004bc253 cmp eax, dword ptr [edi + 0x10]
004bc256 jge 0x4bc25f
004bc258 imul edx, eax
004bc25b add edx, ecx
004bc25d jmp 0x4bc262
004bc25f or edx, 0xffffffff
004bc262 mov ecx, dword ptr [ebp + 0xc]
004bc265 mov dword ptr [esi + 0xb14], edx
004bc26b pop edi
004bc26c mov eax, dword ptr [ecx]
004bc26e mov dword ptr [esi + 0x2b8], eax
004bc274 mov eax, dword ptr [ecx + 4]
004bc277 mov dword ptr [esi + 0x2bc], eax
004bc27d mov eax, dword ptr [ecx]
004bc27f mov dword ptr [esi + 0xb00], eax
004bc285 mov eax, dword ptr [ecx + 4]
004bc288 mov dword ptr [esi + 0xb04], eax
004bc28e mov dword ptr [esi + 0x284], edx
004bc294 pop esi
004bc295 pop ebx
004bc296 pop ebp
004bc297 ret 8
