#include <iostream>

using namespace std;

enum PF_DATA_FLAG
{
    DT_DEFAULT = 0x03,      //默认, 原值
    DT_VARINT_COMPR,        //varint压缩
	DT_STR_COMPR,           //字符串压缩
	DT_STR_ENCODE,          //字符串编码排重
	DT_BIT_RECORD,           //适用于非基础整数类型的数值，比如10bit的整数
};


int main(int argc, char ** argv)
{
	PF_DATA_FLAG f1 = DT_DEFAULT;
	PF_DATA_FLAG f2 = DT_VARINT_COMPR;
	cout << f1 << endl;
	cout << f2 << endl;
	return 0;
}
