@echo off
%sort% = stable_sort
../dbg ./big_rand_10_1e4 std_sort %sort% 
../dbg ./big_rand_1e4_5e5 std_sort %sort%
../dbg ./big_rand_5e5_1e7 std_sort %sort% 
../dbg ./big_rand_1e7_1e8 std_sort %sort% 
../dbg ./big_rand_2e8 std_sort %sort% 