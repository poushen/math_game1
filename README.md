# math_game1
test2.c is for </br>
   1  ?  ? 11  | 31 </br>
   ?  ?  ?  ?  | 27 </br>
   ?  ?  ?  ?  | 29 </br>
  15  ?  ? 10  | 49 </br>
  -------------+ </br>
  43 37 23 33
  
  
test3.c is for </br>
   1  ?  ? 12  | 31  , ? + ? = 18 </br>
   ?  ?  ?  ?  | 27 </br>
   ?  ?  ?  ?  | 29 </br>
  16  ?  ? 10  | 49  , ? + ? = 23 </br>
  -------------+ </br>
  43 37 23 33 </br>
  </br>
  26       11  <=  ? + ? </br>
  
# How to execute and see the result
ops@ops-win81:/mnt/c/Users/Phou-shen$ gcc -o test2 test2.c </br>
ops@ops-win81:/mnt/c/Users/Phou-shen$ ./test2 </br>
 1 12  7 11 </br>
13  5  6  3 </br>
14  4  2  9 </br>
15 16  8 10 </br>
------------ </br>
</br>
 1 12  7 11 </br>
14  4  6  3 </br>
13  5  2  9 </br>
15 16  8 10 </br>
------------ </br>
</br>
It took 47.53 seconds, find 2 matchs </br>

the same method apply to test3.c </br>

# How to compile pthread version
$ gcc -o test4 test4.c -lpthread

