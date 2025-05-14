# CMC
Combinatorial Mesh Calculus

Software library implementing the operations in
<https://arxiv.org/abs/2201.03704> and (new paper here).
At the moment diffusion in strong and weak formulations is being implemented.

The project is hosted on GitHub at <https://github.com/kipiberbatov/cmc>.

The project produces its own website, hosted at
<https://kipiberbatov.github.io/cmc>.

## Modules
- array: functions working on integers and floating point numbers and
arrays structures of those types;
importantly the **jagged1**, ..., **jagged4** structures of jagged integer
arrays (of levels 1-4) are implemented;
- algebra: using the structure **cs** from
[CSparse library](https://github.com/DrTimothyAldenDavis/SuiteSparse/tree/stable/CSparse)
as a backend, a wrapper structure **matrix\_sparse** is created;
a simpler structure **vector\_sparse** is also created;
- region: structures **simplex** and **quasi\_cube**
and functions operating on them are implemented;
- mesh: structure **mesh** and functions on meshes are implemented;
the structure **mesh\_qc** is the same as **mesh** but is intended to be used
for quasi-cubical meshes resulting from applying **forman**;
- diffusion: includes various structures for encoding the input data for
diffusion problems (in particular, heat equation), as well as implementations
of solution methods for those problems;
- graphics: structures and functions for drawing images and animations on a
canvas in a backend-independent way (the canvas and animation backend are
selected at runtime according to the command line arguments);

## Plugins
- diffusion: problem data and exact solutions to transient and steady-state
continuous diffusion problems;
- canvas: procedures for drawing shapes on a canvas, currently with Cairo;
- animation: procedures for producing animations based on the canvas data;
PDF, SVG and GTK animation backends are supported via the Cairo canvas backend.

## Dependencies

You need the following programs and installed on your system in order to clone,
build the project and run the text-outputting demos:
- git
- C compiler (GCC or Clang)
- GNU make

In order to build the canvas and animation plugins, run PDF- and SVG-outputting
demos and GTK animations, you need the following software
- pkg-config
- Cairo
- GTK+ 3

To build the documentation, you need the LaTeX compiler **pdflatex**. 

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
brew install texlive
```

For Linux you can install the required dependencies using your preferred
package manager or [Homebrew on Linux](https://docs.brew.sh/Homebrew-on-Linux).
(Cairo and GTK+ may already be installed by your distribution.)

For Windows, you should install
[Windows subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install),
[Homebrew on Linux](https://docs.brew.sh/Homebrew-on-Linux),
and the required dependencies.


## Building on Unix-like platforms

Make sure you have all the dependencies installed.
Via the command line vavigate to your preferred location on your computer.
Type the following:

```
git clone https://github.com/kipiberbatov/cmc
cd cmc
make -j
```

(`make -j` will speed the build process by executing in parallel)
After running `make -j` the result is a directory **build/release**
(if you want a debug build, type `make -j MODE=debug CFLAGS='-g -O0'`).
Inside **build/release** (substitute **release** with **debug** in debug mode)
the following directories are created:
- **build/release/obj** where source files from
[code/c/src](https://github.com/kipiberbatov/cmc/tree/main/code/c/src)
are compiled into object files;
- **build/release/lib** where object files from **build/release/obj**
are archived;
- **build/release/bin** where source files from
[code/c/main](https://github.com/kipiberbatov/cmc/tree/main/code/c/main)
are compiled and linked against libraries in **build/release/lib**;
- **build/release/txt** where text-outputting demos are run using
executables from **build/release/bin**,
manually written input data from
[data](https://github.com/kipiberbatov/cmc/tree/main/data),
and already generated files from **build/release/txt**.

You can generate PDFs of various images and animations (e.g., meshes, cochains)
in a freshly created directory **build/release/pdf** by typing
```
make -j pdf
```
PDF documents are produced by Cairo and represent animations such that
each page is a snapshot of that animation at a given moment of time.
Some of the PDFs have thousands of pages
and will take (uncompressed) tens of megabytes of disk space.
Note that although compilation, linking and running text-outputting demos are
extremely fast (in milliseconds on average for every file),
generating PDFs may take from a few seconds to a minute for the big animations.

Similarly, you can generate SVGs of various images in a freshly created
directory **build/release/svg** by typing
```
make -j svg
```
Unfortunately, SVG animations, although being generated, cannot be read by most
browsers as they use the unsupported pageSet element for multiple pages.
(One SVG animation of window with changing colors is generated as an example.)

You can run GTK animations in pop-up windows by typing
```
make gtk
```
(Log files documenting animation runs will be saved in a freshly created
directory **build/release/gtk**.)
Note that GTK+ windows will appear and they have to be manually closed after
you are finished watching them.
If you want to close them automatically after finishing, type
```
make CLOSE_AUTOMATICALLY=1 gtk
```

You can build the LaTeX documentation in a freshly created **build/docs**
directory by typing
```
make docs
```

You can combine the documentation with web assets to create a static website by
typing
```
make website
```
This will create a **build/website** directory with all the web assets.
In fact this is the way the website
<https://kipiberbatov.github.io/cmc>
is deployed as is evident by the file
[.github/workflows/github-pages.yaml](https://github.com/kipiberbatov/cmc/blob/main/.github/workflows/github-pages.yaml).

You can clean the generated files (the build directory) using
```
make distclean
```

There are various smaller cleans that will delete certain types of files.
For instance `make clean` will clean the object files.
You can look the files in
[code/make](https://github.com/kipiberbatov/cmc/tree/main/code/make)
to see all the cleaning options (they end with **_clean** or **_distclean**).
