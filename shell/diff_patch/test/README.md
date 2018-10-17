# diff命令

## 单独比较两个文件
> diff -uNr f1 f2，源文件f1，更改后文件f2，针对源文件f1，变成f2需要进行的改变。 u上下文相关；N 空白文件的处理，r递归处理。

# patch命令

## 步骤一
    - cd ../f1
    - diff -uNr f1 f2 > 1
    生成diff

## 步骤二
    - cd f1
    - patch -p1 < ../1
    应用diff
   
