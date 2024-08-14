# IDEC
Intrinsic Discrete Exterior Calculus

Software library implementing the operations in
[https://arxiv.org/abs/2201.03704](https://arxiv.org/abs/2201.03704)

The project is hosted at GitHub at
[https://github.com/kipiberbatov/idec](https://github.com/kipiberbatov/idec).

## Modules
- array: functions working on integers and floating point numbers and
arrays structures of those types;
importantly the **jagged1**, ..., **jagged4** structures of jagged integral
arrays (of levels 1-4) are implemented;
- algebra: using the structure **cs** from
[CSparse library](https://github.com/DrTimothyAldenDavis/SuiteSparse/tree/master/CSparse)
as a backend, a wrapper structure **matrix\_sparse** is created;
a simpler structure **vector\_sparse** is also created;
- region: structures **simplex** and **quasi\_cube**
and functions operating on them are implemented;
- mesh: structure **mesh** and functions on meshes are implemented;
the structure **mesh\_qc** is the same as **mesh** but is intended to be used
for quasi-cubical meshes resulting from applying **forman**;
- graphics: examples using [Cairo](https://www.cairographics.org) and
[GTK 3](https://docs.gtk.org/gtk3/)
- shared: inputs that are dynamically loaded during execution:
they contain input data for numerical examples.

## Prerequisites

You need the following programs and libraries installed on your system:
- git
- C compiler (GCC or Clang)
- GNU make
- pkg-config
- Cairo
- GTK+ 3

On MacOS git, Clang and GNU make should be shipped with
[command line tools for XCode](https://developer.apple.com/xcode/resources/).
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

For Linux you can install the required dependencies using your preferred
package manager or [Homebrew on Linux](https://docs.brew.sh/Homebrew-on-Linux).
For Windows, you should install
[Windows subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install),
[Homebrew on Linux](https://docs.brew.sh/Homebrew-on-Linux),
and the required dependencies.


## Building on Unix-like platforms

Navigate to your preferred location on the command line. Type the following:

```
git clone https://github.com/kipiberbatov/idec
cd idec
make -j
```

(`make -j` will speed the build process by executing in parallel)
After running `make -j` the result is a directory **build/release**
(if you want a debug build, type `make -j BUILD_MODE=debug CFLAGS='-g -O0'`).
Inside **build/release** (substitute **release** with **debug** in debug mode)
the following directories are created:
- **build/release/obj** where source files from **code/c/src**
are compiled into object files;
- **build/release/lib** where object files from **build/release/obj**
are archived;
- **build/release/bin** where source files from **code/c/main** are compiled
and linked against libraries in **build/release/lib**;
- **build/release/demo** where demos are run using
executables from **build/release/bin**,
manually written input data from **data**,
and already generated files from **build/release/demo**.

This will not run graphics demos (produced by Cairo and GTK+).
To run them, after running `make`, type

```
make demo_graphics
```

Note that GTK+ windows will appear
and they have to be manually closed one by one
after you are finished watching them.

PDF documents are produced by Cairo
and represent animations such that
each page represents a snapshot at a given moment of time for that animation.
Some of the PDFs have thousands of pages
and will take (uncompressed) tens of megabytes of disk space.
Note that although compilation,
linking and running text demos are extremely fast
(in milliseconds on average for every file),
generating PDFs may take from a few seconds to a minute for the big animations.

You can run GTK+ animations and PDF animations separately, by typing

```
make demo_graphics_gtk
make demo_graphics_pdf
```

You can build the latex documentation by typing
```
make docs
```
(it will go to a freshly created **build/docs** directory).

You can combine the documentation with web assets to create a static website by
typing
```
make website
```
This will create a **build/website** directory with all the web assets.
In fact this is the way the website
[https://kipiberbatov.github.io/idec](https://kipiberbatov.github.io/idec)
is deployed as is evident by the **.github/workflows/github-pages.yaml** file.

You can clean the generated files (the build directory) using
```
make distclean
```

There are various smaller cleans that will delete certain types of files.
For instance `make clean` will clean the object files.
You can look in **Makefile** or the files in **code/make**
to see all the cleaning options (they all end with **_clean**).
