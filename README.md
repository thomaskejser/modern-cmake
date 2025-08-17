# modern-cmake

A template repo to get you going with cmake >3.x and vcpkg for C++ projects.

## Source Overview

The following source are built:

- [`paint`](src/paint/README.md) - A simple command line utility making use of libraries
- [`shapes`](src/shapes/README.md) - Allows construction and calculation of shapes
- [`renderer`](src/renderer/README.md) - renders `Shape` objects into svg

## Library Dependency Tree

- `paint` depends on both `shapes` and `renderer`.
- `renderer` depends on `shapes`



