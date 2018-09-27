
# $language = "python"
# $interface = "1.0"

# This automatically generated script may need to be
# edited in order to work correctly.

# @author WangZongQi

import os
import sys

def Main():
    host = crt.Arguments[0] 
    password = crt.Arguments[1]
    crt.Screen.Synchronous = True
    crt.Screen.Send("ssh " + host + chr(13))
    if True == crt.Screen.WaitForString("password:", 5):
        crt.Screen.Send(password + chr(13))
Main()
