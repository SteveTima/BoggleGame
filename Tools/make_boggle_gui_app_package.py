#!/usr/bin/python

"""This is a python script.

The purpose of this script is to filter from the visual studio project folder all files 
that the user need to create a installation package like MSI package. 

This script creates a deployement directory with the necessary Qt files and 
resources to run the \'gui\' application of Boggle Game.

For this task, the script uses a deployment tool for windows called: windeployqt.

"""

import os
import shutil
import argparse

parser = argparse.ArgumentParser(prog='make_boggle_gui_app_package', 
                                description="This script creates a deployement directory with the necessary Qt files and \
                                                resources to run the \'gui\' application of Boggle Game")
parser.add_argument('arch', choices=['x64', 'x86'],  help='Enter \'x64\' for 64 bit architectur and \'x86\' for 32 bit architectur')
parser.add_argument('--qtdir', required=True, help='Qt intsllation path that has a subdirectory \'bin\', example: C:\Qt\V5.15.2\msvc2015_64')
args = parser.parse_args()
    

class BoggleGuiPackage:

    SCRIPT_CURR_DIR = os.getcwd()
    BOGGLE_APP_FILENAME = "BoggleGuiApp.exe"
    QT_DEPLOYMNT_TOOL = "windeployqt.exe"
    BOGGLE_RES_DIR = "Resource"
    BOGGLE_APP_BUILD_MODE = "Release"
    PACKAGE_NAME = "BoggleGuiPackage"
    BOGGLE_APP_DEPENDENCIES = ["wordlist.txt"]

    def __init__(self, architecture, qt_dir):
        self.boggle_app_arch = architecture
        self.deploymnt_tool = self.make_deploymnt_tool_path(qt_dir)
        self.deploymnt_tool_src = self.make_boggle_app_path()
        self.deploymnt_tool_dest = self.make_boggle_deployemnt_dir()
        self.boggle_words_dict =  self.make_boggle_app_rsr_path(self.BOGGLE_APP_DEPENDENCIES[0])

    def make_deploymnt_tool_path(self, qt_dir):
        deploymnt_tool = os.path.join(qt_dir, "bin", self.QT_DEPLOYMNT_TOOL)
        if os.path.isfile(deploymnt_tool):
            return deploymnt_tool
        else:
            print('--error-- file ' + "\"" + deploymnt_tool + "\"" + ' does not exist or is not a file')
            return ""

    def make_boggle_app_path(self):
        boggle_app_path = os.path.join(self.SCRIPT_CURR_DIR, "..", self.boggle_app_arch, self.BOGGLE_APP_BUILD_MODE, self.BOGGLE_APP_FILENAME)
        if os.path.isfile(boggle_app_path):
            return boggle_app_path
        else:
            print('--error-- file ' + "\"" + boggle_app_path + "\"" + ' does not exist or is not a file')
            return ""

    def make_boggle_app_rsr_path(self, resource_filename):
        rsr_path = os.path.join(self.SCRIPT_CURR_DIR, "..", self.BOGGLE_RES_DIR, resource_filename)
        if os.path.isfile(rsr_path):
            return rsr_path
        else:
            print('--error-- file ' + "\"" + rsr_path + "\"" + ' does not exist or is not a file')
            return ""

    def make_boggle_deployemnt_dir(self):
        dest_path = os.path.join(self.SCRIPT_CURR_DIR, "..", "..", self.PACKAGE_NAME)
        if os.path.exists(dest_path):
            shutil.rmtree(dest_path)
        os.makedirs(dest_path)
        return dest_path
    
    def check_init_data_values(self):
        if not self.deploymnt_tool:
            return False
        elif not self.deploymnt_tool_src:
            return False
        elif not self.deploymnt_tool_dest:
            return False
        elif not self.boggle_words_dict:
            return False
        else:
            return True

    def create_boggle_package(self):
        command = self.deploymnt_tool + " --dir " + "\"" + self.deploymnt_tool_dest + "\"" + " " + "\"" + self.deploymnt_tool_src + "\""
        os.system(command)   # run windeployqtqt.exe
        shutil.copy(self.deploymnt_tool_src, self.deploymnt_tool_dest)  # copy BoggleGuiApp.exe
        shutil.copy(self.boggle_words_dict, self.deploymnt_tool_dest)   # copy wordlist.txt
    


if __name__ == "__main__":

    print('=== script starts... ===')
    myPackage = BoggleGuiPackage(args.arch, args.qtdir)
    if myPackage.check_init_data_values() == False:
        print('=== script finisched with error(s). ===')
        exit(0)
    
    myPackage.create_boggle_package()
    print('=== script finisched successfully. ===')