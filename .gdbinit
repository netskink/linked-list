set print pretty on
# set args writer
break main

# In one xterm, do tty and get the result
# $ tty
# /dev/pts/3
# Then in gdb, do
# (gdb) set inferior-tty /dev/pts/3
# and now all prints/couts/warning messages will go to the /dev/pts/3 tty.
set inferior-tty /dev/pts/3


