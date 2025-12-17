#!/bin/bash
set -x
sdcc -mz80 --std c99 -V --Werror -S baremetal_binary_test.c

set +x
printf "Press Enter to see result..."
read _
less baremetal_binary_test.asm
