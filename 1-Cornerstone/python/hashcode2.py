def convert_n_bytes(n, b):
    bits = b * 8
    return (int)(((n + 2 ** (bits - 1)) % (2 ** bits) - 2 ** (bits - 1)) & 0xfffffff)

def convert_4_bytes(n):
    return convert_n_bytes(n, 4)

def getHashCode(s):
    h = 0
    n = len(s)
    for i, c in enumerate(s):
        h = h + ord(c) * 31 ** (n - 1 - i)
    return convert_4_bytes(h)

if __name__ == '__main__':
    print("www.runoob.com hashcode= ", getHashCode("www.runoob.com"))
    print("202001020031390101290230832DD8BA11 hashcode=  " , getHashCode("202001020031390101290230832DD8BA11"))
    print("202001020041330100120351982379A3A5 hashcode=  " , getHashCode("202001020041330100120351982379A3A5"))
