import sys
import os
from os.path import abspath, realpath, dirname, join


def getVsFiles(folder):
    out = []
    for entry in os.scandir(folder):
        if entry.is_file():
            # .sln and .vcxproj
            if ".sln" in entry.name or ".vcxproj" in entry.name:
                out.append(entry)
    return out

if __name__ == '__main__':
    # delete old vs files
    root = dirname(dirname(realpath(__file__)))
    print('root: "%s"' % root)
    vs_files = getVsFiles(root)
    for entry in os.scandir(root):
        if entry.is_dir():
            vs_files += getVsFiles(entry.path)

    for f in vs_files:
        print("Deleting " + f.path)
        os.remove(f.path)

    # generate new files
    os.chdir(root)
    print('curdir: "%s"' % os.curdir)
    
    premake_path = root + '\\premake\\premake5.exe'
    print(premake_path)
    
    os.system("%s %s" % (premake_path, 'vs2017'))
    input("Press enter to exit...")
