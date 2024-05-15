# idec
Intrinsic Discrete Exterior Calculus

Software library implementing the operations in [https://arxiv.org/abs/2201.03704](https://arxiv.org/abs/2201.03704)

## Modules
- array: functions working on integers and floating point numbers and arrays of them; importantly the **jagged1**, ..., **jagged4** structures of jagged integral arrays (of levels 1-4) are implemented
- algebra: using the structure **cs** from [CSparse library](https://github.com/DrTimothyAldenDavis/SuiteSparse/tree/master/CSparse) as a backend a wrapper structure **matrix\_sparse** is created; a simpler structure **vector\_sparse** is also created
- region: structures **simplex** and **quasi\_cube** and functions operating on them are implemented
- mesh: structure **mesh** and functions on meshes are implemented; the structure **mesh\_qc** is the same as **mesh** but is intended to be used for quasi-cubical meshes resulting from applying **forman**
- graphics: examples using [Cairo](https://www.cairographics.org) and [GTK 3](https://docs.gtk.org/gtk3/)
- shared: inputs that are dynamically loaded during execution; they contain input data for numerical examples

## Perequisites

You need the following programs and libraries installed on your system:
- git
- C compiler (GCC or Clang)
- GNU make
- pkg-config
- Cairo
- GTK+ 3

On MacOS git, Clang and GNU make should be shipped with [command line tools for XCode](https://developer.apple.com/xcode/resources/).
As a better alternative, you can install [Homebrew](https://brew.sh), and run

```
brew install git
brew install llvm
brew install make
```

(Clang is a part of LLVM).
The remaining dependencies are installed in the same manner:

```
brew install pkg-config
brew install cairo
brew install gtk+3
```

For Linux you can install the required dependencies using your preferred package manager or [Homebrew on Linux](https://docs.brew.sh/Homebrew-on-Linux).
For Windows, you should install [Windows subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install), [Homebrew on Linux](https://docs.brew.sh/Homebrew-on-Linux), and the required dependencies.


## Building on Unix-like platforms

Navigate to your preferred location on the command line. Type the following:

```
git clone https://github.com/kipiberbatov/idec
cd idec
make
```

After running **make** the result is the following:

- directory **build** is created and files from **src** are compiled into object files in **build**
- directory **lib** is created and object files from **build** are archived in **lib**
- directory **bin** is created, source files from **main** are linked against libraries in **lib** and go to **bin**
- demos are run using executables from **bin**, manually written input data from **data**, and already written files to **demo**: they go again in **demo**

This will not run graphics demos (produced by Cairo and GTK+).
To run them, after running `make`, type

```
make demo_graphics
```

Note that GTK+ windows will appear and they have to be manually closed one by one after you are finished watching them.
PDF documents are produced by Cairo and represent animations such that each page represents a snapshot at a given moment of time for that animation.
Some of the PDFs have thousands of pages and will take (uncompressed) tens of megabytes of disk space.
Note that although compilation, linking and running text demos are extremely fast (in milliseconds on average for every file), generating PDFs may take from a few seconds to a minute for the big animations.

You can run GTK+ animations and PDF animations separately, by typing

```
make demo_graphics_gtk
make demo_graphics_pdf
```
