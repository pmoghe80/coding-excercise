#Import Module
import subprocess
import os
import sys

dir = raw_input("Enter Source Directory for cscope: ");

#p = subprocess.Popen(["find", dir , "-name", "*.[c|h]"], stdout=subprocess.PIPE);
#print p.communicate();
cscope_file = dir + "/cscope.files"
subprocess.call(['rm', '-rf', cscope_file])
subprocess.call(['touch',cscope_file])
#print cscope_file
sys.stdout = open(cscope_file, 'a+')
subprocess.call(['cat',cscope_file])
#subprocess.call(['cd', dir])
os.chdir(dir)
subprocess.call(['find', dir , '-name', '*.[c|h]'], stdout=sys.stdout)
subprocess.call(['find', dir , '-name', '*.cc'],stdout=sys.stdout) 
subprocess.call(['find', dir , '-name', '*.cpp'],stdout=sys.stdout)
subprocess.call(['find', dir , '-name', '*.py'],stdout=sys.stdout)
subprocess.call(['cscope', '-b'])
subprocess.call(['cscope', '-d'])




