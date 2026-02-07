glad
====

Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specifications
for multiple languages.

<<<<<<< HEAD
**Use the [webservice](https://glad.dav1d.de) to generate the files you need!**
=======
Check out the [webservice for glad2](https://glad.sh) to generate the files you need!
>>>>>>> glad2


**NOTE:** This is the 2.0 branch, which adds more functionality but changes the API.

Some languages are only available in the [glad1 generator](https://glad.dav1d.de).

## Examples

```c
<<<<<<< HEAD
#include <glad/glad.h>

int main()
{
=======
#include <glad/gl.h>
// GLFW (include after glad)
#include <GLFW/glfw3.h>


int main() {
>>>>>>> glad2
    // -- snip --

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

<<<<<<< HEAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    // -- snip --
```

The full code: [hellowindow2.cpp](https://github.com/Dav1dde/glad/blob/master/example/c%2B%2B/hellowindow2.cpp).

### Glad 2
=======
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }

    // Successfully loaded OpenGL
    printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    // -- snip --
}
```

The full code: [hellowindow2.cpp](example/c++/hellowindow2.cpp)

More examples in the [examples directory](example/) of this repository.

## Plugins

Glad [plugins](https://github.com/Dav1dde/glad/wiki/Extending-Glad)
maintained by the community to add support for more languages:

- [Fortran](https://github.com/AarnoldGad/glad-fortran).

## Documentation

The documentation can be found in the [wiki](https://github.com/Dav1dde/glad/wiki).
>>>>>>> glad2

Glad 2 is becoming mature and is pretty stable now, consider using the
[glad2 branch](https://github.com/Dav1dde/glad/tree/glad2) or its [webservice](https://glad.sh).

**There is no need to switch, if you don't want to. I will support both versions.**

Glad2 brings several improvements and new features:

* Better EGL, GLX, WGL support
* **Vulkan** Support
* Rust Support
* More Generator Features (e.g. header only)
* Better XML-Specification parsing
* Better Web-Generator
* Better Cmake support
* Better Examples
* Better CLI
* Better Loader
* Better API

If you're using glad for more than GL, I highly recommend checking out glad2.

Examples can be found [in the example directory](/example). Some examples:

<<<<<<< HEAD

**If you don't want to install glad you can use the [webservice](https://glad.dav1d.de)**


Otherwise either install glad via pip:

    # Windows
    pip install glad

    # Linux
    pip install --user glad
    # Linux global (root)
    pip install glad

To install the most recent version from Github:

    pip install --upgrade git+https://github.com/dav1dde/glad.git#egg=glad

Or launch glad directly (after cloning the repository):

    python -m glad --help

Installing and building glad via vcpkg

You can download and install glad using the [vcpkg](https://github.com/Microsoft/vcpkg) dependency manager:

    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
    ./vcpkg integrate install
    vcpkg install glad

The glad port in vcpkg is kept up to date by Microsoft team members and community contributors. If the version is out of date, please [create an issue or pull request](https://github.com/Microsoft/vcpkg) on the vcpkg repository.

When integrating glad into your build system the `--reproducible` option is highly recommended.

## Generators ##

### C/C++ ###

```c
struct gladGLversionStruct {
    int major;
    int minor;
};

extern struct gladGLversionStruct GLVersion;

typedef void* (* GLADloadproc)(const char *name);

/*
 * Load OpenGL using the internal loader.
 * Returns the true/1 if loading succeeded.
 *
 */
int gladLoadGL(void);

/*
 * Load OpenGL using an external loader like SDL_GL_GetProcAddress.
 *
 * Substitute GL with the API you generated
 *
 */
int gladLoadGLLoader(GLADloadproc);

/**
 * WGL and GLX have an unload function to free the module handle.
 * Call the unload function after your last GLX or WGL API call.
 */
void gladUnloadGLX(void);
void gladUnloadWGL(void);
```

`glad.h` completely replaces any `gl.h` or `gl3.h` only include `glad.h`.

```c
    if(!gladLoadGL()) { exit(-1); }
    printf("OpenGL Version %d.%d loaded", GLVersion.major, GLVersion.minor);

    if(GLAD_GL_EXT_framebuffer_multisample) {
        /* GL_EXT_framebuffer_multisample is supported */
    }

    if(GLAD_GL_VERSION_3_0) {
        /* We support at least OpenGL version 3 */
    }
```

On non-Windows platforms glad requires `libdl`, make sure to link with it (`-ldl`).

Note, there are two kinds of extension/version symbols, e.g. `GL_VERSION_3_0` and
`GLAD_VERSION_3_0`. Latter is a runtime boolean (represented as integer), whereas
the first (not prefixed with `GLAD_`) is a compiletime-constant, indicating that this
header supports this version (the official headers define these symbols as well).
The runtime booleans are only valid *after* a successful call to `gladLoadGL` or `gladLoadGLLoader`.


### C/C++ Debug ###

The C-Debug generator extends the API by these two functions:

```c
// this symbol only exists if generated with the c-debug generator
#define GLAD_DEBUG
typedef void (* GLADcallback)(const char *name, void *funcptr, int len_args, ...);

/*
 * Sets a callback which will be called before every function call
 * to a function loaded by glad.
 *
 */
GLAPI void glad_set_pre_callback(GLADcallback cb);

/*
 * Sets a callback which will be called after every function call
 * to a function loaded by glad.
 *
 */
GLAPI void glad_set_post_callback(GLADcallback cb);
```

To call a function like `glGetError` in a callback prefix it with `glad_`, e.g.
the default post callback looks like this:

```c
void _post_call_callback_default(const char *name, void *funcptr, int len_args, ...) {
    GLenum error_code;
    error_code = glad_glGetError();

    if (error_code != GL_NO_ERROR) {
        fprintf(stderr, "ERROR %d in %s\n", error_code, name);
    }
}
```

You can also submit own implementations for every call made by overwriting
the function pointer with the name of the function prefixed by `glad_debug_`.

E.g. you could disable the callbacks for glClear with `glad_debug_glClear = glad_glClear`, where
`glad_glClear` is the function pointer loaded by glad.

The `glClear` macro is defined as `#define glClear glad_debug_glClear`,
`glad_debug_glClear` is initialized with a default implementation, which calls
the two callbacks and the real function, in this case `glad_glClear`.


## FAQ ##

### How do I build glad or how do I integrate glad?

Easiest way of using glad is through the [webservice](https://glad.dav1d.de).

Alternatively glad integrates with:

* `CMake`
* [Conan](https://conan.io/center/glad)
* [VCPKG](https://github.com/Microsoft/vcpkg)

Thanks for all the help and support maintaining those!

### glad includes windows.h [#42](https://github.com/Dav1dde/glad/issues/42)

**Since 0.1.30:** glad does not include `windows.h` anymore.

**Before 0.1.30:**
Defining `APIENTRY` before including `glad.h` solves this problem:

```c
#ifdef _WIN32
    #define APIENTRY __stdcall
#endif

#include <glad/glad.h>
```

But make sure you have the correct definition of `APIENTRY` for platforms which define `_WIN32` but don't use `__stdcall`

### What's the license of glad generated code?
[#101](https://github.com/Dav1dde/glad/issues/101)
[#253](https://github.com/Dav1dde/glad/issues/253)
=======
* C/C++
    * [GL GLFW](example/c/gl_glfw.c)
    * [GL GLFW On-Demand loading](example/c/gl_glfw_on_demand.c)
    * [GL GLFW Multiple Windows/Contexts](example/c++/multiwin_mx/)
    * [GL SDL3 Callbacks](example/c/gl_sdl3_callbacks.c)
    * [GL SDL3](example/c/gl_sdl3.c)
    * [GL SDL2](example/c/gl_sdl2.c)
    * [Vulkan GLFW](example/c/vulkan_tri_glfw/)
    * [GLX](example/c/glx.c)
    * [GLX Modern](example/c/glx_modern.c)
    * [WGL](example/c/wgl.c)
    * [EGL X11](example/c/egl_x11/)
* Rust
    * [GL GLFW](example/rust/gl-glfw/)
    * [GL GLFW Multiple Windows/Contexts](example/rust/gl-glfw-mx/)
>>>>>>> glad2

The glad generated code itself is any of Public Domain, WTFPL or CC0,
the source files for the generated code are under various licenses
from Khronos.

* EGL: See [egl.xml](https://github.com/KhronosGroup/EGL-Registry/blob/main/api/egl.xml#L4)
* GL: Apache Version 2.0
* GLX: Apache Version 2.0
* WGL: Apache Version 2.0
* Vulkan: Apache Version 2.0 [with exceptions for generated code](https://raw.githubusercontent.com/KhronosGroup/Vulkan-Docs/main/xml/vk.xml)

Now the Apache License may apply to the generated code (not a lawyer),
but see [this clarifying comment](https://github.com/KhronosGroup/OpenGL-Registry/issues/376#issuecomment-596187053).

Glad also adds header files form Khronos,
these have separated licenses in their header.

## License

For the source code and various Khronos files see [LICENSE](/LICENSE).

The generated code from glad is any of Public Domain, WTFPL or CC0.
Now Khronos has some of their specifications under Apache Version 2.0
license which may have an impact on the generated code,
[see this clarifying comment](https://github.com/KhronosGroup/OpenGL-Registry/issues/376#issuecomment-596187053)
on the Khronos / OpenGL-Specification issue tracker.
