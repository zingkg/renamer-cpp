# renamer-cpp
A batch renamer command-line tool written in C++.

## Commands

### rename
```
--rename
./renamer.out --rename <find name> <replace name> <file>+
```
Finds the input name within the file's name and replaces it.
```
./renamer.out --rename chocolate cacao chocolate_1.jpg chocolate_2.jpg
results in:
cacao_1.jpg cacao_2.jpg
```

### wipe file name, rename, and number
```
--wipe-rename-number
./renamer.out --wipe-rename-number <input string> <file>+
```
Wipes the file's name, uses the input name, and numbers the file(s) starting at 1.
```
./renamer.out --wipe-rename-number clockwork chocolate_1.jpg chocolate_2.jpg
results in:
clockwork1.jpg clockwork2.jpg
```

### prepend a number
```
--num-prepend
./renamer.out --num-prepend <input string> <starting number> <file>+
```
Prepends a string and a number to the file(s).
```
./renamer.out --num-prepend sky 5 ground_1.jpg ground_2.jpg ground_3.jpg
results in:
5sky.jpg 6sky.jpg 7sky.jpg
```

### appends a number
```
--num-append
./renamer.out --num-append <input string> <starting number> <file>+
```
Appends a string and a number to the file(s).
```
./renamer.out --num-append sky 10 ground_1.jpg ground_2.jpg ground_3.jpg
results in:
sky10.jpg sky11.jpg sky12.jpg
```

### delete a preceding number and prepend a number
```
--del-prec-num-prep
./renamer.out --del-prec-num-prep <input string> <starting number> <file>+
```
Deletes a preceding number and prepends a number to the file(s).
```
./renamer.out --del-prec-num-prep -pool- 1 1mountain.jpg 2mountain.jpg
results in:
1-pool-mountain.jpg 2-pool-mountain.jpg
```

### delete an ending number and append a number
```
--del-end-num-app
./renamer.out --del-end-num-app <input string> <starting number> <file>+
```
Deletes an ending number and appends a number to the file(s).
```
./renamer.out --del-end-num-app -yard- 1 joe5.jpg joe6.jpg
results in:
joe-yard-1.jpg joe-yard-2.jpg
```

### prepend a string
```
--pre-str
./renamer.out --pre-str <input string> <file>+
```
Prepends a string to the file(s).
```
./renamer.out --pre-str 2010- pic1.jpg pic2.jpg pic3.jpg
results in:
2010-pic1.jpg 2010-pic2.jpg 2010-pic3.jpg
```

### append a string
```
--app-str
./renamer.out --app-str <input string> <file>+
```
Appends a string to the file(s).
```
./renamer.out --app-str -Q2 2016-pic1.jpg 2016-pic2.jpg 2016-pic3.jpg
results in:
2016-pic1-Q2.jpg 2016-pic2-Q2.jpg 2016-pic3-Q2.jpg
```