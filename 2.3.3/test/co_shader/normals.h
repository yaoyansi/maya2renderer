//
// normals.h
//
// Compute normalized shading normal with appropriate orientation.
// We ensure that the normal faces forward if Sides is 2 or if the
// shader evaluation is caused by a ray hit.
//
normal
shadingnormal(normal N)
{
    normal Ns = normalize(N);
    uniform float sides = 2;
    uniform float raydepth;
    attribute("Sides", sides);
    rayinfo("depth", raydepth);
    if (sides == 2 || raydepth > 0)
        Ns = faceforward(Ns, I, Ns);
    return Ns;
}
