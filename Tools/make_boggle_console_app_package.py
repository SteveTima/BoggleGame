#!/usr/bin/python

"""This is a python script.

The purpose of this script is to filter from the visual studio project folder all files 
that the user need to create a installation package like MSI package. 

This script creates a deployement directory with the necessary files and 
resources to run the \'console\' application of Boggle Game.

"""

import sys
import os
import shutil

def parse_script_arguments(script_args):
    SCRIPT_OPTIONS = ["x64", "x86"]
    NBR_OF_ARGS_NEEDED = 2
    help_opt = False
    parsing_successfull = True
    prog_architectur = ""
    if (len(script_args) == 1) or ((len(script_args) == NBR_OF_ARGS_NEEDED) and (script_args[1] == "-h" or script_args[1] == "-help")):
        help_opt = True
    elif len(script_args) == NBR_OF_ARGS_NEEDED:
        for i in range(NBR_OF_ARGS_NEEDED):
            if i == 0:
                pass # script_args[0]: ignore script programm name
            elif script_args[i] in SCRIPT_OPTIONS:
                prog_architectur = script_args[i]
            else:
                print('--error-- wrong argument')
                parsing_successfull = False
                break
    else:
        print('--error-- bad use of the script')
        parsing_successfull = False
    return [help_opt, parsing_successfull, prog_architectur]

def display_script_help():
    print('usage: make_boggle_console_app_package.py [-h] \'ARCHITECTURE\'\n')
    print('-h, -help             show this help message and exit')
    print('ARCHITECTURE          \'x64\' for 64 bit architecture or \'x86\' for 32 bit architecture')
    

class BoggleConsolePackage:

    SCRIPT_CURR_DIR = os.getcwd()
    BOGGLE_APP_FILENAME = "BoggleConsoleApp.exe"
    BOGGLE_RES_DIR = "Resource"
    BOGGLE_APP_BUILD_MODE = "Release"
    PACKAGE_NAME = "BoggleConsolePackage"
    BOGGLE_APP_DEPENDENCIES = ["wordlist.txt"]

    def __init__(self, architecture):
        self.boggle_app_arch = architecture
        self.boggle_app_executable = self.make_boggle_app_path()
        self.deploymnt_dest = self.make_boggle_deployemnt_dir()
        self.boggle_words_dict =  self.make_boggle_app_rsr_path(self.BOGGLE_APP_DEPENDENCIES[0])

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
        if not self.boggle_app_executable:
            return False
        elif not self.deploymnt_dest:
            return False
        elif not self.boggle_words_dict:
            return False
        else:
            return True

    def create_boggle_package(self):
        shutil.copy(self.boggle_app_executable, self.deploymnt_dest)  # copy BoggleConsoleApp.exe
        shutil.copy(self.boggle_words_dict, self.deploymnt_dest)   # copy wordlist.txt
    


if __name__ == "__main__":

    print('=== script starts... ===')

    help, parse_succeeded, arch = parse_script_arguments(sys.argv)
    if help == True:
        display_script_help()
        print('=== script finisched successfully. ===')
        exit(0)
    if not parse_succeeded:
        print('--message-- Type "-h" or "-help" for more information.')
        print('=== script finisched with error(s). ===')
        exit(0)

    myPackage = BoggleConsolePackage(arch)
    if myPackage.check_init_data_values() == False:
        print('=== script finisched with error(s). ===')
        exit(0)
    
    myPackage.create_boggle_package()
    print('=== script finisched successfully. ===')