protoc student.proto --cpp_out=./; g++ --std=c++11 -o protobufTest.out -lprotobuf -lpthread test.cpp student.pb.cc
