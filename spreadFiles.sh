#!/usr/bin/expect -f
set arg1 [lindex $argv 0]

spawn scp /tmp/file_* $arg1:/home/umkc_yjang
expect {
#  -re ".*es.*o.*" {
#    exp_send "yes\r"
#    exp_continue
#  }
  -re ".*sphrase.*" {
      exp_send "dbms2015\r"
  }
}
interact
