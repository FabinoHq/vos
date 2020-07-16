#!/bin/sh
valgrind --tool=helgrind --gen-suppressions=all --log-file=valgrind_log ../VOS
