import os
import shutil
filelist=[]
rootdir="./data"
filelist=os.listdir(rootdir)
for f in filelist:
  filepath = os.path.join( rootdir, f)
  if os.path.isfile(filepath):
    os.remove(filepath)
    print(filepath+" removed!")
  elif os.path.isdir(filepath):
    filelist1 = os.listdir(filepath)
    for f1 in filelist1:
        filepath1 = os.path.join(filepath, f1)
        os.remove(filepath1)
        print(filepath1 + " removed!")