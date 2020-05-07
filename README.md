<h1>Quarantine v.0.0.1</h1>

To run the program go to bin folder where the application is located.
```bash
adna
 |-- bin
 |	 |-- app
 |   `-- app.exe
 |-- src
 |   |-- main.c 
 |   |-- util.c 
 |   |-- sort.c 
 |   |-- util.h 
 |   `-- sort.h 
 |-- ANALYSIS.docx
 `-- README.md
```
Then run command:

```bash
cd bin
./app 
```
you can also use 
```bash
cd bin 
./app.exe
```
<br>

If ever you might want to compile the program, just go to src folder where the source codes are located and run command
```bash
gcc main.c util.c sort.c -o ../bin/app
```
Then the compiled application will be saved on the bin folder.
