# 头文件
    > 头文件是algorithm.h，
    - ForwardIter lower_bound(ForwardIter first, ForwardIter last,const _Tp& val)算法返回一个非递减序列[first, last)中的第一个大于等于值val的位置。
    - ForwardIter upper_bound(ForwardIter first, ForwardIter last, const _Tp& val)算法返回一个非递减序列[first, last)中第一个大于val的位置。

# 代码实现
> 本质需要进行二分查找；
```
int lower_bound(int *array, int size, int key)
{
    int first = 0, middle;
    int half, len;
    len = size;

    while(len > 0) {
        half = len >> 1;
        middle = first + half;
        if(array[middle] < key) {     
            first = middle + 1;          
            len = len-half-1;       //在右边子序列中查找
        }
        else
            len = half;            //在左边子序列（包含middle）中查找
    }
    return first;
}

```
