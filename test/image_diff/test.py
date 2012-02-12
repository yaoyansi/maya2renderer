import sys
import os

def main():
    pyFile  = "testall.py";
    command = "mayapy.exe "+pyFile;

    os.system(command)
    raw_input("Press ENTER to exit.\n")

if __name__ == '__main__':
    main()