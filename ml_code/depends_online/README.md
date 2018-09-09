# md
	各个安装包版本：
	nose-1.3.1
	lapack-3.5.0
	atlas-3.10.1
	scipy-0.11.0
	numpy-1.6.2

	依赖关系：scipy的安装需要依赖于numpy、lapack、atlas（后两者都是线性代数工具包，不清楚的自行google），
	而numpy和sci的测试程序的运行又依赖于nose，因此，整个安装过程必须要按顺序执行的，否则是无法执行下去的。

# depends
  - setuptools
	-- https://files.pythonhosted.org/packages/ef/1d/201c13e353956a1c840f5d0fbf0461bd45bbd678ea4843ebf25924e8984c/setuptools-40.2.0.zip
	-- step
		wget http://pypi.python.org/packages/source/s/setuptools/setuptools-0.6c11.tar.gz
		tar zxvf setuptools-0.6c11.tar.gz
		cd setuptools-0.6c11
		python setup.py install

  - pip
	-- https://files.pythonhosted.org/packages/69/81/52b68d0a4de760a2f1979b0931ba7889202f302072cc7a0d614211bc7579/pip-18.0.tar.gz
	-- step
		参考上面的。

  -- other
	- sudo yum install python-dev python-devel
	- 

  - numpy: 1.11.2 
	-- version: numpy-1.11.2.tar.gz
	-- link: https://sourceforge.net/projects/numpy/files/NumPy/1.11.2/numpy-1.11.2.tar.gz/download
	-- test
		[yqtao@localhost ~]$ python
		Python 2.7.5 (default, Sep 15 2016, 22:37:39) 
		[GCC 4.8.5 20150623 (Red Hat 4.8.5-4)] on linux2
		Type "help", "copyright", "credits" or "license" for more information.
		>>> from numpy import *            //导入函数库
		>>> eye(4)                         //生成单位矩阵
		array([[ 1.,  0.,  0.,  0.],
			[ 0.,  1.,  0.,  0.],
			[ 0.,  0.,  1.,  0.],
			[ 0.,  0.,  0.,  1.]])

  - no lapack/blas resources found
    -- blas
		--- http://www.netlib.org/blas/blas-3.8.0.tgz; 
		gfortran -c -O3 -fPIC *.f  # 编译所有的 .f 文件，生成 .o文件 
		ar rv libblas.a *.o  # 链接所有的 .o文件，生成.a 文件  
		sudo cp libblas.a /usr/local/lib  #将库文件复制到系统库目录  

	-- cblas 
		--- http://www.netlib.org/blas/blast-forum/cblas.tgz
		编译cblas， 进入CBLAS文件夹，首先根据你自己的计算机平台，将目录下某个 Makefile.XXX复制为 Makefile.in , XXX表示计算机的平台，如果是Linux，那么就将Makefile.LINUX 复制为Makefile.in，然后执行以下命令

		 cp ../BLAS-3.8.0/libblas.a testing/ # 将上一步编译成功的 libblas.a复制到 CBLAS目录下的testing子目录  
		make # 编译所有的目录  
		sudo cp lib/cblas_LINUX.a /usr/local/lib/libcblas.a #将库文件复制到系统库目录下  


	-- lpack 
		--- http://www.netlib.org/lapack/lapack-3.8.0.tar.gzi; cp make.inc.example make.inc
		3）编译lapack以及lapacke，这一步比较麻烦，首先当然是进入lapack-3.4.2文件夹，然后根据平台的特点，将INSTALL目录下对应的make.inc.XXX复制一份到 lapack-3.4.2目录下，
		并命名为make.inc, 这里我复制的是INSTALL/make.inc.gfortran，因为我这里用的是gfortran编译器。修改lapack-3.4.2/Makefile,因为lapack以来于blas库，所以需要做如下修改

		#lib: lapacklib tmglib

		lib: blaslib variants lapacklig tmglib

		make # 编译所有的lapack文件 

		ulimit -s 65000

		cd lapacke # 进入lapacke 文件夹，这个文件夹包含lapack的C语言接口文件 

		make # 编译lapacke  

		cp include/*.h /usr/local/include#将lapacke的头文件复制到系统头文件目录  

		cd .. #返回到 lapack-3.4.2 目录 

		cp *.a /usr/local/lib # 将生成的所有库文件复制到系统库目录 

		修改make.inc CFLAGS OPTS -fPIC

	-- 


  - scipy 1.1.0
	-- https://files.pythonhosted.org/packages/07/76/7e844757b9f3bf5ab9f951ccd3e4a8eed91ab8720b0aac8c2adcc2fdae9f/scipy-1.1.0.tar.gz
	-- python setup.py install 


