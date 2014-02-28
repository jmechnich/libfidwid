libfidwid
=========

Fast Image Display library that supports drawing to X11 or OpenGL. It
was originally written for high performance camera image display in 2000.

### Installation

```bash
autoreconf -fiv
./configure
make
```

### Tests

The `src/testFidWid` contains four test programs:
- `testFidWidget` (draws using XPutImage, original version)
- `testOpenGLFBWidget` (draws to the OpenGL framebuffer)
- `testOpenGLTexWidget` (draws to an OpenGL texture)
- `testX11FidWidget` (draws using XPutImage, optimized)

### Benchmarks

On a i3-2357M CPU @ 1.30GHz with Intel HD 3000 graphics, the following
timing results were achieved (using the included `test.ppm`):

- `testFidWidget`: 116.6 FPS
- `testOpenGLFBWidget`: 53.8 FPS
- `testOpenGLTexWidget`: 161.8 FPS
- `testX11FidWidget`: 158.2 FPS
