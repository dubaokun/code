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

enum IndexType {
    INDEX_FULL = 0x1,
    INDEX_INC_NORMAL = 0x2,
    INDEX_INC_GOOD = 0x4,
    INDEX_FULL_CACHE = 0x8,
    INDEX_ALL = INDEX_FULL | INDEX_INC_NORMAL | INDEX_INC_GOOD
};

void test() {
	IndexType t1 = INDEX_FULL;
	IndexType t2 = INDEX_INC_NORMAL;
	IndexType t3 = INDEX_INC_GOOD;
	IndexType t4 = INDEX_FULL_CACHE;
	IndexType t5 = INDEX_ALL;

	cout << t1 << endl;
	cout << t2 << endl;
	cout << t3 << endl;
	cout << t4 << endl;
	cout << t5 << endl;
	
}

int main(int argc, char ** argv)
{
	test();
	return 0;	

	PF_DATA_FLAG f1 = DT_DEFAULT;
	PF_DATA_FLAG f2 = DT_VARINT_COMPR;
	cout << f1 << endl;
	cout << f2 << endl;
	return 0;
}


