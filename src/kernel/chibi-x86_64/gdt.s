global gdt_push
gdt_push:
    lgdt [rdi]
    mov ax, 0x10
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov rax, qword .trampoline
    push qword 0x8
    push rax
    o64 retf
.trampoline:
    ret
