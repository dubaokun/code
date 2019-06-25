g++ -g main.cpp  
addr2line -e a.out -ifC 40054b
readelf -w a.out   // 查看源代码对应的行数信息 

1）背景介绍：
	生产环境没打开coredump,运维监控到一个进程退出
2）排查手法
	pkgdeal[6362]: segfault at 1d ip 0031f8ba sp bff14fe0 error 4 in libtrsies.so[30f000+35000]

	0x31f8ba - 0x30f000 = 0x108BA
	addr2line -e libtrsies.so 0x108ba -fiC
	
	s_locxmlnode
	forxml.c:430
