from distutils.dir_util import copy_tree
from shutil import copyfile
import os

command = '"' + 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/MSBuild/Current/Bin/MSBuild.exe' + '"'
command += " /p:Configuration=Release"
command += " /p:OutDir=../BuildOutput/"

os.system(command)

copy_tree("./Project/Resources", "./BuildOutput/Resources")
copyfile("./Project/glew32.dll", "./BuildOutput/glew32.dll")