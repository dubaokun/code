# 

(gdb) disas main
Dump of assembler code for function main(int, char**):
   0x0000000000400564 <+0>:     push   %rbp                 // 寄存器rbp指向调用函数栈的栈底，压入新函数栈的栈底
   0x0000000000400565 <+1>:     mov    %rsp,%rbp            // 寄存器rsp指向调用函数栈的栈顶，赋值给rbp
   0x0000000000400568 <+4>:     sub    $0x20,%rsp           //将rsp栈顶指针向下移动32个字节，即用于开辟内存，存储该函数的局部变量
   0x000000000040056c <+8>:     mov    %edi,-0x14(%rbp)
   0x000000000040056f <+11>:    mov    %rsi,-0x20(%rbp)
   0x0000000000400573 <+15>:    movl   $0x1,-0x4(%rbp)      //将1存储在rbp位置-12偏移量的位置，即x的值
   0x000000000040057a <+22>:    movl   $0x2,-0x8(%rbp)      //将2存储在rbp位置-8偏移量的位置，即y的值
   0x0000000000400581 <+29>:    mov    -0x8(%rbp),%edx
   0x0000000000400584 <+32>:    mov    -0x4(%rbp),%eax
   0x0000000000400587 <+35>:    mov    %edx,%esi
   0x0000000000400589 <+37>:    mov    %eax,%edi
   0x000000000040058b <+39>:    callq  0x40053d <sum(int, int)>
   0x0000000000400590 <+44>:    mov    %eax,-0xc(%rbp)
   0x0000000000400593 <+47>:    mov    -0xc(%rbp),%eax
   0x0000000000400596 <+50>:    mov    %eax,%esi
   0x0000000000400598 <+52>:    mov    $0x400640,%edi
   0x000000000040059d <+57>:    mov    $0x0,%eax
   0x00000000004005a2 <+62>:    callq  0x400420 <printf@plt>
   0x00000000004005a7 <+67>:    mov    $0x0,%eax
   0x00000000004005ac <+72>:    leaveq 
   0x00000000004005ad <+73>:    retq   
End of assembler dump.
