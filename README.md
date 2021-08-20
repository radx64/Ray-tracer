# Raytracer
3D scenes generation using ray tracing method.

[![Build Status](https://travis-ci.org/radx64/raytracer.svg)](https://travis-ci.org/radx64/raytracer)

## Render example ##
![](https://raw.githubusercontent.com/radx64/raytracer/master/render.png)

![](https://raw.githubusercontent.com/radx64/raytracer/master/planets.png)

### TODO:
* [ ] Color clamping
* [ ] Recursive tracing (~~reflections~~, ~~refractions~~)
* [ ] Antialiasing 
* [ ] More shapes (triangle, real plane, torus, cone, etc...)
* [ ] Obj files parsing
* [ ] Implement a thread pool and image slicer, like in proper renderers
* [ ] Add different channels of texture mapping (eg. normals, specular etc)
### Known issues:
* Light refraction is not implemented properly (internal refractions are a mess)
* Threads are running in equal parts of image which is not efficient. Need more parts to load balance threads.
