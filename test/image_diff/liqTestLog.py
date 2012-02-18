import sys
import os

gLiqTestLogFile = './_liqTestLog.htm'

class LiqTestLog:
    def __init__(self, logfileFullPath):
        LiqTestLog.__logFile = open(logfileFullPath, 'w')
        LiqTestLog.__logFile.write("<html>")
        LiqTestLog.__logFile.write("<head><META HTTP-EQUIV=\"Content-Type\" content=\"text/html; charset=utf-16\"></head>")
        LiqTestLog.__logFile.write("<body>")

    def __del__(self):
        LiqTestLog.__logFile.write("</body>")
        LiqTestLog.__logFile.write("</html>")
        LiqTestLog.__logFile.close()


    def writeLocalFile(self, fileFullPath):
        if True:
            LiqTestLog.__logFile.write("<a href=\"file:///"+fileFullPath+"\">"+fileFullPath+"</a><br>")
        else:
            LiqTestLog.__logFile.write(fileFullPath)
        LiqTestLog.__logFile.write("\n")

    def write(self, data):
        LiqTestLog.__logFile.write(data)
        LiqTestLog.__logFile.write("\n")

    def write2(self, data):
        LiqTestLog.__logFile.write(data)


# instance of class LiqTestLog
gLiqTestLog = LiqTestLog( gLiqTestLogFile )


# scene ----------------------------------------------
def scene_beg(sceneName):
    gLiqTestLog.write("<blockquote>")
    gLiqTestLog.write("<table width=100% bgcolor=#DFDFE5><tr><td><font face=arial size=4>")
    gLiqTestLog.writeLocalFile(sceneName)
    gLiqTestLog.write("</font></table>")

def scene_end():
    gLiqTestLog.write("</blockquote>")

# renderer ----------------------------------------------
def renderer_beg(rendererName):
    gLiqTestLog.write("<blockquote>")
    msg=""
    if(rendererName=="renderman"):
        msg="(for now, the image which rendered by renderman cann't be displayed in IE/firefox, you have to view the image with mspaint.exe)"

    gLiqTestLog.write("<li>"+rendererName+"<font size=\"+1\" color=\"red\">"+msg+"</font>"+"</li>")

def renderer_end():
    gLiqTestLog.write("</blockquote>")

# output_img ----------------------------------------------
def output_img_beg(imgFullPath):
    gLiqTestLog.write("<blockquote>")
    gLiqTestLog.write("<pre>out put image</pre>")
    gLiqTestLog.write("<table>")
    gLiqTestLog.writeLocalFile(imgFullPath)
    gLiqTestLog.write("<img src=\"file:///"+imgFullPath+"\" WIDTH=\"200\" HEIGHT=\"200\" BORDER=\"0\" ALT=\"\"/>")
    gLiqTestLog.write("</table>")

def output_img_end():
    gLiqTestLog.write("</blockquote>")

# imgdiff_begin ----------------------------------------------
def imgdiff_beg(msg, imgdiffFullPath):
    gLiqTestLog.write("<pre><font size=\"+1\" color=\"red\">"+msg+"</font></pre>")
    gLiqTestLog.writeLocalFile(imgdiffFullPath)
    gLiqTestLog.write("<img src=\"file:///"+imgdiffFullPath+"\" WIDTH=\"200\" HEIGHT=\"200\" BORDER=\"0\" ALT=\"\"/>")

def imgdiff_end():
    gLiqTestLog.write("")



def flog(data):
    gLiqTestLog.write("<pre>"+data+"</pre>")

def unit_test():
    #gLiqTestLog.write("hello liqTestlog00!")
    flog("aaa")

if __name__ == '__main__':
    unit_test()
    raw_input("Press ENTER to exit.\n")