# 测试
    - 用于测试pb的兼容性，首先用同样的pb生成pb数据，并且转成string后，写入文件中。
    - 接着，用同样格式的pb读取文件，并且解析pb；
    - 接着，增加pb的数据，不改变顺序，属于追加的形式，加入一项。
    - 接着，写入的程序，重新生成pb的cpp文件，写入数据到文件。
    - 最后，读取的程序，不重新生成pb的cpp文件，读取文件，并且进行string到pb的转换，转换成功。


# 重点
    - 本测试没有对pb进行删除操作
    - 本测试没有对pb进行修改操作（比如类型）
    - 本操作仅仅是追加项到pb，而且放在最后；


# 基础

```
message Order
{
  int32 time = 1;
  int32 userid = 2;
  float price = 3;
  string desc = 4;
  string ext = 5;
}
```
## 函数
    - 设置函数：set_time();
    - 获取函数：time();
    - pb序列化：bool SerializeToString(string* output) const;
    - pb反序列化：bool ParseFromString(const string& data);

## 参考文档
    > 序列化到字符串、文件中
    - https://blog.csdn.net/sealyao/article/details/6940245 
