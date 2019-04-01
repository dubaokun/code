# 为python安装matplotlib模块
- matplotlib是python中强大的画图模块。

- 首先确保已经安装python，然后用pip来安装matplotlib模块。

- 进入到cmd窗口下，执行python -m pip install -U pip setuptools进行升级。

- 接着键入python -m pip install matplotlib进行自动的安装，系统会自动下载安装包。

- 安装完成后，可以用python -m pip list查看本机的安装的所有模块，确保matplotlib已经安装成功。

# python开发包
sudo yum install python-devel

sudo pip install -I pyparsing==2.2.0

sudo yum install -y tkinter 
sudo yum install -y tk-devel


# 显示图片
Linux中，创建文件 ~/.config/matplotlib/matplotlibrc， 
（其中，~/.config/matplotlib/是配置文件matplotlibrc的路径）

添加如下一行：

backend : Agg
