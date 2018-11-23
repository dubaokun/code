g++ -g main.cpp  
addr2line -e a.out -ifC 40054b
readelf -w a.out   // 查看源代码对应的行数信息 
