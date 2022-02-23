import tensorflow as tf
sess=tf.Session()
#特征数据
features = {
            'department': ['sport', 'sport', 'drawing', 'gardening', 'travelling'],
            }
#特征列
department = tf.feature_column.categorical_column_with_hash_bucket('department',
        10, dtype=tf.string)
print("—————1—————")
# print columns
columns = tf.feature_column.embedding_column(department, dimension=10)
#输入层（数据，特征列）
inputs = tf.feature_column.input_layer(features, columns)
print("======2======")
print(inputs)
print("======2======")
#初始化并运行
init = tf.global_variables_initializer()
sess.run(tf.tables_initializer())
sess.run(init)
 
v=sess.run(inputs)
print(v)
