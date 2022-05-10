# idec
Intrinsic Discrete Exterior Calculus

Software library implementing the operations in [https://arxiv.org/abs/2201.03704](https://arxiv.org/abs/2201.03704)

## Modules
- array: functions working on integers and floating point numbers and arrays of them; importantly the **jagged1**, ..., **jagged4** structures of jagged integral arrays (of levels 1-4) are implemented
- algebra: using the structure **cs** from [CSparse library](https://github.com/DrTimothyAldenDavis/SuiteSparse/tree/master/CSparse) as a backend a wrapper structure **matrix\_sparse** is created; a simpler structure **vector\_sparse** is also created
- region: structures **simplex** and **quasi\_cube** and functions operating on them are implemented
- mesh: structure **mesh** and functions on meshes are implemented; the structure **mesh\_qc** is the same as **mesh** but is intended to be used for quasi-cubical meshes resulting from applying **forman**

## Building on Unix-like platforms
- Go to installation directory 
- Type make
  * directory **build** is created and files from **src** are compiled into object files in **build**
  * directory **lib** is created and object files from **build** are archived in **lib**
  * directory **bin** is created, source files from **main** are linked against libraries in **lib** and go to **bin**
  * demos are run using executables from **bin** and already existing files in **demo** and go in **demo**
