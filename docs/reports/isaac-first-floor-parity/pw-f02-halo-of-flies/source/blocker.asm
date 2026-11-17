005efae0 push ebp
005efae1 mov ebp, esp
005efae3 and esp, 0xfffffff8
005efae6 mov eax, dword ptr [ecx + 0x2c]
005efae9 sub esp, 0x10
005efaec cmp eax, 0x23
005efaef je 0x5efb61
005efaf1 cmp eax, 0x2c
005efaf4 je 0x5efb61
005efaf6 cmp eax, 0x2d
005efaf9 je 0x5efb61
005efafb cmp eax, 0x21
005efafe je 0x5efb61
005efb00 cmp eax, 0x41
005efb03 je 0x5efb61
005efb05 cmp eax, 0x20
005efb08 je 0x5efb61
005efb0a cmp eax, 0x2a
005efb0d je 0x5efb61
005efb0f cmp eax, 0x11
005efb12 je 0x5efb61
005efb14 cmp eax, 0x33
005efb17 je 0x5efb61
005efb19 cmp eax, 0x4b
005efb1c je 0x5efb61
005efb1e cmp eax, 0x32
005efb21 jne 0x5efb2c
005efb23 cmp dword ptr [ecx + 0x30], 0
005efb27 jmp 0x5efc8c
005efb2c cmp eax, 0x44
005efb2f je 0x5efb61
005efb31 cmp eax, 0x43
005efb34 je 0x5efb61
005efb36 cmp eax, 0x53
005efb39 je 0x5efb61
005efb3b cmp eax, 0x5f
005efb3e je 0x5efb61
005efb40 cmp eax, 0x45
005efb43 je 0x5efb61
005efb45 cmp eax, 0x46
005efb48 je 0x5efb61
005efb4a cmp eax, 0x67
005efb4d je 0x5efb61
005efb4f cmp eax, 0x68
005efb52 jne 0x5efb67
005efb54 cmp dword ptr [ecx + 0xc9c], 0
005efb5b jge 0x5efc92
005efb61 mov al, 1
005efb63 mov esp, ebp
005efb65 pop ebp
005efb66 ret
