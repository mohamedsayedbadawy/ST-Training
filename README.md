 readelf -s app.o -o app_ST.txt
   63  readelf -S  app.o -o app_ST.txt
   64  ls
   65  readelf -S  app.o 
   66  readelf -S  app.o>app.txt
   67  ls
   68  app.txt
   69  cat app.txt
   70  readelf -S app.o
   71  readelf -s app.o
   72  readelf -s app.o>app.txt
   73  ls
   74  cat app.txt
   75  readelf -s function1.o>function.txt
   76  cat function1.txt
   77  rm function.txt
   78  readelf -s function1.o>function1.txt
   79  cat function.txt
   80  ls
   81  cat function1.txt
   82  gcc app.c function.c function.h>output.o
   83  ls
   84  readelf -s app.o
   85  readelf -s output.o
   86  rm a.out
   87  gcc app.c function.c function.h
   88  ls
   89  rm a.out
   90  gcc-c app.c function.c function.h>output.o
   91  gcc -c app.c function.c function.h>output.o
   92  gcc output.o
   93* gcc 
   94  gcc  app.c function.c function.h -o output.exe
   95  ls
   96  rm output.o
   97  ls 
   98  readelf -s output.exe>output.txt
   99  cat output.txt
  100  size output.o
  101  readelf -S output.exe |grep ".text"
  102  size output.exe
  103  readelf -S output.exe 
  104  readelf -S output.exe |grep ".text"
  105  size output.exe
  106  size output.exe>output_size.txt
  107  cat output_size.txt 
  108  readelf -S output.exe 
  109  size output.exe>output_size.txt
  110  cat output_size.txt 
  111  size app.o>app_size.txt
  112  cat app_size.txt 
  113  size function1.o>function_size.txt
  114  cat function_size.txte
  115  size function1.o>function1_size.txt
  116  cat function1_size.txt 

