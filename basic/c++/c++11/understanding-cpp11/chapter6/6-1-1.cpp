const int GetConst() { return 1; }

void Constless(int cond) {
     int arr[GetConst()] = {0};     // 无法通过编译

     enum { e1 = GetConst(), e2 };  // 无法通过编译

     switch (cond) {
         case GetConst():           // 无法通过编译
             break;
         default:
             break;
     }
}
