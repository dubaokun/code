#/bin/sh
protoc -I=../protos/ --cpp_out=./ ../protos/helloworld.proto
