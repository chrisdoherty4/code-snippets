import subprocess

args1=["python", "--help -h"]
args2=["python", "--help", "-h"]
args3=[]
args3.extend("python --help -h".split(" "))
subprocess.check_call(args3)
