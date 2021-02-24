# Raytracer
3D scenes generation using ray tracing method

[![Build Status](https://travis-ci.org/radx64/raytracer.svg)](https://travis-ci.org/radx64/raytracer)


## Render example ##
![](https://raw.githubusercontent.com/radx64/raytracer/master/render.png)


### TODO:
* [ ] Color clamping
* [ ] Recursive tracing (~~reflections~~, ~~refractions~~)
* [ ] Antialiasing 
* [ ] More shapes (triangle, real plane, torus, cone, etc...)
* [ ] Obj files parsing
* [ ] Texture materials (UV mapping)
* [ ] Implement a thread pool and image slicer, like in proper renderers

### Known issues:
* Light refraction is not implemented properly (internal refractions are a mess)
* Threads are running in equal parts of image which is not efficient. Need more parts to load balance threads.
* UV mapping is not using real textures yet