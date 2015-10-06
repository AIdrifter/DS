#!/bin/sh
find ./  -name "*.c" -o -name "*.h" -o -name "*.cpp" > cscope.files
cscope -Rbq -i cscope.files
ctags -R --exclude=.svn



