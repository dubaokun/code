// 跳台阶问题的解法：
// 动态规划思想：
//   静态元素：
//      人：一步 and 二步
//      台阶：10阶
// 多少种走法
// 思路：首先，所有的问题到手之后都不着急解决，
// 这个题乍看非常难以处理，枚举是枚举不完的，
// 这个时候不要慌乱，需要仔细思考，思考是要如何
// 处理，很多时候只要仔细想想还是可以解决的，大部分的问题都是
// 分而治之，大事化小，小事化了，仔细考虑一个基本单元
// 是如何处理的，比如第10阶的走法。
// https://juejin.im/post/5a29d52cf265da43333e4da7

#include <iostream>

using namespace std;

// using base-recursion algorithm, O(2^n) 复杂度
int jump_step_1(int step_count) { 
    if (3 > step_count) {
        return step_count;
    }

    return jump_step_1(step_count - 1) + jump_step_1(step_count - 2);
}

// 备忘录算法，空间换时间，存储需要重复计算的节点
// 时间复杂度和空间复杂度都是 O(N)
int jump_step_2(int step_count, std::map<int, int>& step_map) {
    if (3 > step_count) {
        return step_count;
    }

    if(!step_map.find(step_count)) {
        step_map[step_count] = jump_step_2(step_count - 1) + jump_step_2(step_count - 2);
    }
        
    return step_map[step_count];
}

// using no-recursion algorithm
// 时间复杂度 O(N)
int jump_step_3(int step_count) {
    if (0 == step_count || 1 == step_count || 2 == step_count) {
        return step_count;
    }
    
    int first = 1;
    int second = 2;
    int total_count = 0;
    for (int i = 3; i <= step_count; ++i) {
        total_count = first + second;
        first = second;
        second = total_count;
    } 

    return total_count;
}
