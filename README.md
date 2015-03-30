# Directionality Indicator

Visualization of directional information on anatomical surfaces. The project is work-in-progress. More information and functionality will follow soon.

## License

The software is licensed under the terms and conditions of the LGPL v3 license.
As such, you are allowed to use the software and its source according to the GPLv3, LGPLv3, or any newer version of these licenses.

## Authors

* Sebastian Eichelbaum: [www.nemtics.com](http://www.nemtics.com)

## Installation

### Dependencies

To compile, you will need the following libraries and software installed on your system. The packages are available via your Linux distribution's
repository, MacPorts, and MSYS2.

* Qt >= 4.8, including Qt5
* CMake >= 2.8
* CLang or GCC <= 4.7, supporting basic C++11 functionality.

### Runtime Dependencies

* OpenGL 3.3 Core.

### Building

The software uses CMake to create Makefiles. So, once you downloaded the source, you need to follow these steps:

```shell
$ cd /path/to/DirectionalityIndicator
# As we use out-of-source builds: Change to the build sub-directory
$ cd build
# Allow CMake to build and update the Makefiles. 
# -> Use this command everytime you do a git pull.
# -> CMake will complain about missing depenencies.
$ cmake ../src
# -> CMake does not find Qt5 although you have it installed? Help Cmake to find it by defining the QTDIR variable:
$ DI_QTDIR=/path/to/Qt cmake ../src
# -> You want to force CMake to use Qt4?
$ cmake -DDI_FORCE_QT4=ON ../src
# Build using make
$ make
# Run the software
$ ./DirectionalityIndicator
```

## Usage

To start, simply start the binary.

```shell
$ DirectionalityIndicator
```

It is planned to allow specification of data files on the command line. Right now, this is not supported. More options will follow.

## Support

### Build GCC 4.9

This is needed if your system does not provide a modern GCC, or you are not allowed to install one from a repository. There are some prerequisites
that need to be available on the build system:

* _some_ GCC


```shell
$ cd ~
$ mkdir -p .local/toolchains
$ cd .local/toolchains
# Now, download GCC source:
$ wget ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-4.9.2/gcc-4.9.2.tar.bz2
# Extract archive
$ tar xjf gcc-4.9.2.tar.bz2
$ cd gcc-4.9.2
# Building GCC requires some dependencies. GCC provides a script to download them for us:
$ ./contrib/download_prerequisites
# Now configure the build. The environment variables CC and CXX should be set to ensure they point to GCC (and not clang for example):
$ CC=/usr/bin/gcc CXX=/usr/bin/g++ ./configure --prefix=$HOME/.local/toolchains/gcc/ --disable-multilib --enable-languages=c,c++ --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
# Start building. You can build in parallel by specifying the number of cores to use with the -j parameter:
$ make -j4
# After this is done, install to the prefiously defined set prefix (.local/toolchains/gcc in this case)
$ make install
```

Now, you need to tell CMake to use the alternative toolchain to build DirectionalityIndicator. Follow the above instructions but replace the CMake
call by this one:

```shell
DI_FORCE_LIBDIR=~/.local/toolchains/gcc/lib64 CC=~/.local/toolchains/gcc/bin/ CXX=~/.local/toolchains/gcc/bin/g++ cmake ../src
```

