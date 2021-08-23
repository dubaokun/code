#include <iostream>
#include <string>
#include "student.pb.h"
using namespace std;

int main(int argc, char* argv[]){
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::Student student;
    
    //给消息类Student对象student赋值
    student.set_id(201421031059);
    *student.mutable_name()="dablelv";
    student.set_email("dablelv@tencent.com");
    //增加一个号码对象
    tutorial::Student::PhoneNumber* phone_number = student.add_phone();
    phone_number->set_number("15813354925");
    phone_number->set_type(tutorial::Student::MOBILE);
    
    //再增加一个号码对象
    tutorial::Student::PhoneNumber* phone_number1 = student.add_phone();
    phone_number1->set_number("0564-4762652");
    phone_number1->set_type(tutorial::Student::HOME);

    //对消息对象student序列化到string容器
    string serializedStr;
    student.SerializeToString(&serializedStr);
    cout<<"-------------序列化输出，二进制---------------"<<endl;
    cout<<"serialization result:"<<serializedStr<<endl; //序列化后的字符串内容是二进制内容，非可打印字符，预计输出乱码
    cout<<endl<<"debugString:"<<student.DebugString();
    
/*----------------上面是序列化，下面是反序列化-----------------------*/
    //解析序列化后的消息对象，即反序列化
    tutorial::Student deserializedStudent;
    if(!deserializedStudent.ParseFromString(serializedStr)){
      cerr << "Failed to parse student." << endl;
      return -1;
    }
    
    cout<<"-------------反序列化输出，字符串---------------"<<endl;
    //打印解析后的student消息对象 
    cout<<"deserializedStudent debugString:"<<deserializedStudent.DebugString();
    cout <<endl<<"Student ID: " << deserializedStudent.id() << endl;
    cout <<"Name: " << deserializedStudent.name() << endl;
    if (deserializedStudent.has_email()){
    	cout << "E-mail address: " << deserializedStudent.email() << endl;
    }
    for (int j = 0; j < deserializedStudent.phone_size(); j++){
    	const tutorial::Student::PhoneNumber& phone_number = deserializedStudent.phone(j);

      	switch (phone_number.type()) {
            case tutorial::Student::MOBILE:
          	cout << "Mobile phone #: ";
          	break;
            case tutorial::Student::HOME:
                cout << "Home phone #: ";
          	break;
        }
        cout <<phone_number.number()<<endl;
    }

    google::protobuf::ShutdownProtobufLibrary();
}
