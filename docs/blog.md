Today's blog is written in collaboration with my friend \[Martin Broholm Anderson](https://github.com/MBroholmA).

Martin and I are both C++ programmers - but we come from different programming traditions. This always provides us with
a rich source of subjects to

argue about. I have been working for years on old Cmake projects (from the 2.x) and Martin has been busy reorganizing
Cmake projects at his workplace

to match a modern, CMake 3.x style. Martin is a Visual Studio user, I use CLion - so we hope our mixed experience will
give you a good experience no matter

what IDE you prefer.

This blog contains the result of our discussions and our final agreement on best practices for creating modern style
repos that use Cmake 3.x. We expect that

this blog will be regularly updated to serve as a reference for both experienced developers and new users who are just
getting started with Cmake and C++.

The repo containing our template CMake project can be found on GitHub : \[modern
Cmake](https://github.com/thomaskejser/modern-cmake).

As is the tradition on Database Doctor - I encourage disagreement and discussions.

# Step 1: Pick a namespace

To play nice with other libraries, your own code should live in a namespace that is unique to you.

The namespace could be the name of the company you work for - or it could be something else that is likely
unique. Think of it the same way you think of a domain name - it's is the unique name of you little piece of code
on the Internet.

## Why Pick a namespace?

When your code is consumed, particularly if that code is a library, you don't know what other libraries
you might co-exist with. Instead of polluting the global namespace with your classes and functions - you make it clear
to the consumer of your library how to find your code.

Even the C++ standard library lives by this rule - putting all their code in the `std` namespace. Note that consumers
don't need to type your namespace prefix over and over again (at least not in internal files) - they can always do:

The namespace will be used throughout your repo, so pick wisely.

## Our namespace and libraries

For our example repo, we use the namespace: `demo`.

As you can read in our [`README.md`](https://github.com/thomaskejser/modern-cmake/blob/main/README.md) we offer
two libraries:

- `shapes` - in namespace `demo::shapes`
- `svg_renderer` - in namespace `demo::svg_renderer`

Note that when you consume libraries, you do not need to prefix the namespace in your implementation files. You can do
this instead:

```c++
using namespace demo::shapes;

std::vector<Shape> make_snow_man() {
    head = Circle{5, Point{0, 2.5}}   
    body = Circle{7, Point{0, 9}}
    return {head, body}
}
```

## The Rule you should never break about Namespace

There is a rule about `using namespace` that you should always follow:

> You shall *not*  put `using namspace` into public headers

Why? Because if you do this, then a person including your public header may end up with a `using` declaration that
they did not intend. And this can be very hard to track down. Consider this example:

The Martin's public header `shapes.h` contains:

```c++
#pragma once

namepace demo::shapes  {
using Shape = std::variant<Circle, Rectangle, Triangle>;  
}

using namespace demo::shapes
```

The poor Doctor is writing a library that can draw funny caricatures of people. The Doctor includes Martin's header
and does this:

```c++
#include <demo/shapes/shapes.h>
// Shape is not defined in the global namespace

enum class Shape { UNDERWEIGHT, NORMAL, OVERWEIGHT, AMERICAN };

Shape classify_body(double weight, double height ) {
    auto v = weight / (height * height)
    if (v < 18.5) {
        return Shape::UNDERWEIGHT;
    }
    if (v >= 18.5 && v < 25) {
        return Shape::NORMAL;
    }
    // ... etc...
}

demo::Shape draw_carricature(Shape body_classification) { 
    // ...
}
```

Doctor is now going to get some very odd compile errors, because his definition of `Shape` does not match what Martin
did.

Summary: don't put `using namespace` in headers.

# Repo High Level Overview

Our repo root looks like this:

- `src` - All source files except the root level `CMakeList` lives here. Each library or executable has its own
  directory
- `docs` - Generic docs about the repo and usage examples for consumers. Individual projects under `src` contain docs
  and `README` targeted towards maintainers
- `extern` - any libraries not in the repo that we depend on are in here.
- `cmake` - Custom functions live here. We provide a few basic ones that you might find useful
- `.vscode` - Visual Studio specific configuration

# Root Level files

In the root of every repo, the following files are present

- [`README.md`](#the-root-level-readmemd)
- [`LICENCE`](#the-license-file)
- [`.gitignore`](#gitignore)
- `.clang-tidy` and `.clang-format`
- `CMakePresents.json`
- `CMakeList.txt`

## The Root level `README.md`

If you don't already know how to write `.md` files, now is a good time to start. It should take you no more than an hour
or two to learn.

The root level `README.md` file tell the read what this repo is **for**. It provides an overview of what binaries are
build and a single line about each binary

and what it does. For detailed information about each binary - you can link to the `README.md` file inside the directory
of the binary - located in `[root]/src/[binary]/README.md`

**Resources**

- [Getting Started with MarkDown](https://www.markdownguide.org/getting-started/)

## The `LICENSE` file

If you are using Github, you will be offered the option to create this file when the repo is first made. You should
pick a licensing model for everything in this repo and the `LICENSE` file should contain a standard text pertaining
to that license.

A detailed discussion about which license works for your situation is out of scope for this document. Be nice to
lawyer if you need the advice. At the rate LLMs are going - they will need your money soon.

## `.gitignore`

Files listed here will be ignored by git and not be commited to the repo. Our demo repo contains a standard one
you can use for your C++ project.

**Resources**

- [.gitignore documentation](https://git-scm.com/docs/gitignore)

## `.clang-tidy` and `.clang-format`

These files control your coding convention and how you code is formatted. Most IDEs will be able to consume these
files directly and automatically format code as you type.

Don't argue endlessly in your project about what coding convention to use and spending time formatting your code.
Instead, put these two files in the root of your repo and everyone's code will look the same.

`.clang-tidy` will also help you find common issue with your C++ code - it is a good idea to always run with one.

The Doctor likes the Google formatting guide (but with 120 character long lines - because it isn't 1980 anymore).
You might have other preferences. The important part is to set the rule early - ideally when the repo is created.

**Resources**

- [Clang format style options](https://clang.llvm.org/docs/ClangFormatStyleOptions.html) - Here, you find the list
  of various styles. Search for "BasedOnStyle"

## `CMakePresets.json` - Configuration options for your build

The files is important for all modern CMake lists. It provides a series of "presents" which allow various IDE and
toolchains to build what is in your repo.

Presents contain:

- Options (under `cacheVariables`) - these control things like your toolchain and platform specific build settings
- Various directories - where does your build and install files go?

### Clion and `CMakePresets.json`

If you are using CLion, you enable the build configurations from `CMakePresets.json` by going here:

- **Settings → Build, Execution, Deployment → CMake**

From here, check the box for the present you want to use.

## The Root level `CmakeLists.txt`

We want to avoid doing too much work in this file. While it is *possible* to make a single, gigantic, `CMakeLists.txt`
that control how everything in the repo is build - it is bad idea. For the same reason it is bad idea to have
gigantic "do it all" functions in your code.

When you do `add_subdirectory` in CMake, you are saying to that subdirectory: "Everything I have defined is also
defined for you - and you can add more as you wish". You can think of this almost as inheritance.

It is perhaps easier to see this in act. In the repo, we have this:

```cmake
cmake_minimum_required(VERSION 3.24)
project(demo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(cmake/EmbedStrings.cmake)
```

This sets the basic rules of the repo:

- You need at least version 3.24 of CMake to build this
- The project (which matches the namespace you picked earlier) is called `demo`
- We are using C++ version 23
- The Cmake modules we allow you to use are in the root. Note that we are appending to the path here, in case our
  caller already has some clever modules they want to access.
- We introduce a handy function called `EmbedStrings` - which we can use to embed strings from files directly into C++
  code (which means we can compile them into our binaries)

Everyone under this root level CMakeLists.txt follow the above rules - unless they explicitly tell us otherwise.

### Building tests only when you need to: `DEMO_ENABLE_TESTING`

We proceed to set:

```cmake
option(DEMO_ENABLE_TESTING "Enable testing" ${PROJECT_IS_TOP_LEVEL})
```

Again, we use the namespace prefix we picked earlier to avoid conflicts with people consuming our project. We also
introduce an interesting default here: `PROJECT_IS_TOP_LEVEL`. This says: "If you called `cmake` directly on me
(as opposed to me being a sub-repo of something else) then `DEMO_ENABLE_TESTING` should be `TRUE`". This has the
effect of detecting if we should be building our test code or not.

### Various Flags and Settings

Our root `CMakeLists.txt` proceeds to set various configuration options. If you need to detect what platform you are
on and act accordingly, this is where you do it.

Martin plays a particularly cool trick here:

```cmake
foreach (lang IN ITEMS C CXX)
    add_compile_definitions(
            #Exclude rarely-used stuff from Windows headers
            "$<$<COMPILE_LANGUAGE:${lang}>:WIN32_LEAN_AND_MEAN;NOMINMAX;VC_EXTRALEAN>"
    )
endforeach ()
```

Unpacking this from outer to inner:

- For the languages C and CXX (c++ in CMake language)
- Loop over all targets with: `$<...>`
- Then: `$<COMPILE_LANGUAGE:${lang} ... >` - This is conditional, it says: "If the compiled language is C or CXX".
  If it is, the value is 1 and the next bit gets evaluated. If 0, the entire thing evaluates to nothing and
  `add_compile_definitions` just does nothing.

Basically, this allows us to force all targets that are under our `CMakeLists.txt` and which are C or C++ to have the
Windows specific compile flags set. Clever indeed.

### One Global Library `plog`

We finally add a single library that should be available to everyone - namely our logger:

```cmake
find_package(plog CONFIG REQUIRED)
```

Here, we pick `plog`, but other could be chosen too. It's generally a good idea to agree on a single log library, it
just makes things easier for everyone.

### The rest of the source and `src/CMakeLists.txt`

We have now done all our global config and we can finally add the actual source we want to compile with:

```cmake
add_directory(src)
```

This points as the next level down our tree, the `src` directory. In here, we have one directory per target we expose
to the outside world.

The file `src/CMakeList.txt` is the only file in `src` and it just contains:

```cmake
add_subdirectory(paint)
add_subdirectory(shapes)
add_subdirectory(renderer)
```

This is a nice way to arrange things, because it allows us to quickly comment source and an out if we are experimenting
with various builds.

# Third party sources (in `extern`) and `vcpkg`

Before we move on to our actual source code, let us sit down and talk about third party dependencies.

Martin and I have vastly different opinions. And for your reading pleasure, we will present both.

I come from a background of strictly controlling the binary you build - down to what exactly is compiled for each third
party dependency you take. I don't want to link or include *anything* that I not 100% in control of. I try not to take
dependencies - unless I  *absolutely* need them. I hate watching my build download half the internet just to lowercase
a string. If you pull in big libraries to do small things - I get grumpy. I prefer to keep linkage strictly private
whenever I can - making extensive use of [Pimpl idioms](https://en.cppreference.com/w/cpp/language/pimpl.html) and
generally avoiding headers from anything except `std` being pulled into my public headers.

Martin, on the other hand, deals with a lot of code that must be flexibly integrated in ways that is a-priory unknown
to the creator of the original code. For example, in a setup like Martin's - repositories from all over his
organisation will be build and linked up in many different build environments. When you borrow and link a third party
dependency to a library from one corner of the organisation - you might want externally control that this linkage is the
same as for the library you are currently building. This of course makes a lot of sense when headers have to be binary
compatible and you need a lot of "generic" usability without strict control of each binary.

Our preferences influence how we deal with integrating `vcpkg` and we have provided both methods for you to choose from
in our repo template.

## Martin's Choice: Using `vcpkg` from the environment

Martin generally prefers to have a `vcpkg` on his build machines that serves up libraries to anyone building on it.
This method is great when you have repositories that frequently use the same packages and if you want to save space on
your machine. In this setup, there is only one copy of each required library version on the machine. The `vcpkg`
package manager becomes part of the same subsystem that makes up the compiler toolchain.

In Martin's setup - you install `vcpkg` on the machine itself, point the environment variable `VCPKG_ROOT` at your
installation and off you go. Any repo you compile on that machine will now use the same binaries.

## `CMakePresets.json` for environment supplied `vcpkg`

Your present, i fyou used Martin's solution, will look something like this:

```json
{
  "name": "msvc_x64",
  "displayName": "MSVC with vcpkg external",
  "generator": "Visual Studio 17 2022",
  "binaryDir": "${sourceDir}/build/${presetName}",
  "cacheVariables": {
    "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake",
    "VCPKG_TARGET_TRIPLET": "x64-windows",
    "VCPKG_OVERLAY_PORTS": "${sourceDir}/extern/vcpkg-overlays"
  }
}
```

Notice how we will pull in ports from the local `extern` directory - but we take our `vcpkg` binary and its installed
package from the environment.

## The Doctor's Choice: Vendoring `vcpkg`

If you want complete control over your binaries (for example, when building highly optimised and/or embedded systems)
you have the option of vendoring `vcpkg`. What this means, is that your package manager itself is part of your repo.

This allows you to pin every single build script and be in complete control over what your external libraries
look like.

Here is how you do it:

### Submodule `vcpkg` into `externn/vcpkg`

Easiest done with a raw `git` command like this:

```shell
git submodule add https://github.com/microsoft/vcpkg.git extern/vcpkg
```

You can now pin a specific commit of `vcpkg` with:

```shell
git -C extern/vcpkg checkout <known-good-commit>   # pin vcpkg version
git commit -m "Vendor vcpkg at pinned commit"
```

### Install `vcpkg` into your repo

Next, you need to bootstrap `vcpkg`. You only need to do this once and the invocation is:

```shell
cd extern/vcpkg
./bootstrap-vcpkg.bat
```

If you are on Linux or OSX, replace `.bat` with `.sh`

You now have a completely pinned and private version of the external package manager.

### Create the initial `vcpkg.json` manifest file and pin it

In the root of the demo repo, you will find the file `vcpkg.json`. This file locks down all version of packages that are
supplied by `vcpkg`. You can also specify that you just need the dependency, but that you don't care what version it is.

You can use this file as a starting point for your own repos.

Once your file is updated with the external dependencies you need, you can now do this:

```shell
./extern/vcpkg/vcpkg x-update-baseline --add-initial-baseline
```

This will pin the `vcpkg` SHA to your manifest file locking the configuration down.

Note that even with Martin's solution you can still lock down individual versions with the manifest - but you are
now relying on the environments `vcpkg` to supply you those versions.

### Use `CMakePresents.json` to use your vendored `vcpkg`

In our repo, we supply a vendored `vcpkg` preset, it looks like this:

```json
{
  "name": "msvc_vendor_x64",
  "displayName": "MSVC with vcpkg vendored",
  "generator": "Visual Studio 17 2022",
  "binaryDir": "${sourceDir}/build/${presetName}",
  "cacheVariables": {
    "CMAKE_BUILD_TYPE": "Debug",
    "CMAKE_TOOLCHAIN_FILE": "${sourceDir}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake",
    "VCPKG_TARGET_TRIPLET": "x64-windows",
    "VCPKG_FEATURE_FLAGS": "manifests",
    "VCPKG_OVERLAY_PORTS": "${sourceDir}/extern/vcpkg-overlays",
    "VCPKG_INSTALLED_DIR": "${sourceDir}/extern/vcpkg/installed"
  },
  "environment": {
    "VCPKG_ROOT": "${sourceDir}/extern/vcpkg"
  }
}
```

### A warning about vendored `vcpkg`

Vendoring allows you to be full control of every package and its binaries.

However, it comes with a downside: You will get one copy of all the build binaries per repo on your machine. This can
be a substantial amount of space on you disk.

# TODO: Structuring Libraries

# TODO: Structuring Executables

# TODO: Include order

## Correctly including your libraries


