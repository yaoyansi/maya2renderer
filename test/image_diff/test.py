import sys
import os
import liqTestLog as mLiqlog

HTMLViewerPath="D:/Program Files/Mozilla Firefox/firefox.exe";
pyFile  = "testall.py";

def main():

    command = "mayapy.exe "+pyFile;
    os.system(command)

    # open the log file
    if HTMLViewerPath=="":
        os.system("explorer.exe .\\_liqTestLog.htm")
    else:
        os.system("\""+HTMLViewerPath+"\" ./_liqTestLog.htm")
    raw_input("main() done. Press ENTER to exit.")

if __name__ == '__main__':
    main()