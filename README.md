# RTX_Tutorial
There is my, first attempt to create the RTX. There is no any API, just image.
P.S I'm studying from the book: Ray Tracing in One Weekend. It's my first steps.

# Building
You'd get the debug build from CMake running this command: 
```cmake
cmake -B build
cmake --build build
```
On book write the next instrucion:
```cmake
build\Debug\Rethink.exe > image.ppm
```
But in my program already realize the next code:
```c++
std::ofstream ppm_file("heh.ppm");
if (!ppm_file.is_open()) {
    std::cerr << "Cannot open file!" << std::endl;
    return 1;
}

std::streambuf* original_cout = std::cout.rdbuf();
std::cout.rdbuf(ppm_file.rdbuf());

cam.render(world);

std::cout.rdbuf(original_cout);

ppm_file.close();

std::cout << "Rendering in file heh.ppm" << std::endl;
```
It's for automatically create the .ppm file, that don't render every time. 
URL: https://raytracing.github.io/books/RayTracingInOneWeekend.html

# Final result.
![image](https://github.com/tornado4444/RTX_Tutorial/blob/main/rtx.png)
