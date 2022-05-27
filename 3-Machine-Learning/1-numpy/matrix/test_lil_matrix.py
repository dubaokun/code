import scipy.sparse as sp
data = [1, 1, 2]
row = [0, 1, 1]
col = [0, 1, 2]
matrix = sp.coo_matrix((data, (row, col)), shape=(3, 3))
# 输出
    [[1, 0, 0],
     [0, 1, 2],
     [0, 0, 0]]
       
# 转化为lil_matrix
matrix = matrix.tolil()
# 改变某个元素，第0行第2个位置更新为第1行第1个位置
matrix[0, 2] = matrix[1, 1] 
matrix.todense()
# 输出
    [[1, 0, 1],
     [0, 1, 2],
     [0, 0, 0]]
                
# 更新指定的多个行
matrix[[0, 2]] = matrix[1]
matrix.todense()

# 输出
    [[0, 1, 2],
     [0, 1, 2],
     [0, 1, 2]]
