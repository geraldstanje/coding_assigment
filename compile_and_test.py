#!/usr/bin/python

import os
from struct import *
import subprocess
import shlex

def run_sub_process(mylist):
  pipe = subprocess.Popen(mylist, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  stdout, stderr = pipe.communicate()
  stdout_test = stdout.decode('utf-8')
  stderr_res = stderr.decode('utf-8')
  return stdout, stderr_res

def main():
  # compile unit test
  run_sub_process(['make', 'clean'])
  run_sub_process(['make', 'BUILD=test'])

  # run unit test to check for memory leaks
  stdout_res, stderr_res = run_sub_process(['valgrind', '--tool=memcheck', '--leak-check=full', './main', '-t'])

  if stderr_res.find("ERROR SUMMARY: 0 errors") == -1:
    print "valigrind check...failed"
  else:
    print "valigrind check...passed"

  # compile benchmark test
  run_sub_process(['make', 'clean'])
  run_sub_process(['make', 'BUILD=benchmark'])

  # run benchmark to benchmark the app
  stdout_res, stderr_res = run_sub_process(['./main', '-t'])
  
  print "benchmark in ms:\n" + stderr_res

if __name__ == "__main__":
  main()