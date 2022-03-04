import numpy as np
import tensorflow as tf

from utils import layers
from models.base_gattn import BaseGAttN

class GAT(BaseGAttN):
    def inference(inputs, nb_classes, nb_nodes, training, attn_drop, ffd_drop,
            bias_mat, hid_units, n_heads, activation=tf.nn.elu, residual=False):
        '''
        第一层，有H1个注意力头，每个头的输入都是(B,N,D)，每头注意力输出(B,N,F1)；
        将所有注意力头的输出聚合，聚合为(B,N,F1*H1)
        '''
        attns = []
        # n_heads[0]=第一层注意力的头数，设为H1
        for _ in range(n_heads[0]):
            attns.append(layers.attn_head(inputs, bias_mat=bias_mat,
                out_sz=hid_units[0], activation=activation,
                in_drop=ffd_drop, coef_drop=attn_drop, residual=False))
        h_1 = tf.concat(attns, axis=-1)
        # 第二层    
        for i in range(1, len(hid_units)):
            h_old = h_1
            attns = []
            for _ in range(n_heads[i]):
                attns.append(layers.attn_head(h_1, bias_mat=bias_mat,
                    out_sz=hid_units[i], activation=activation,
                    in_drop=ffd_drop, coef_drop=attn_drop, residual=residual))
            h_1 = tf.concat(attns, axis=-1)
        # 第三层
        out = []
        for i in range(n_heads[-1]):
            out.append(layers.attn_head(h_1, bias_mat=bias_mat,
                out_sz=nb_classes, activation=lambda x: x,
                in_drop=ffd_drop, coef_drop=attn_drop, residual=False))
        logits = tf.add_n(out) / n_heads[-1]
    
        return logits
