# a.out
    - 0x401049

# objdump -d -C a.out
    - 401049

# gdb
    1. gdb a.out
    2. disassemble /m main | /m 源码和汇编一起排列 | /r 还可以看到16进制代码/r 还可以看到16进制代码
    3. x/15i main

# 
- 476   401044:   e8 d2 ff ff ff          callq  40101b <test1()>
- 477   401049:   b8 00 00 00 00          mov    $0x0,%eax


- https://blog.csdn.net/xuleilx/article/details/7365424
- https://wangchujiang.com/linux-command/c/objdump.html
