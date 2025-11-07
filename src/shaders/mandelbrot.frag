#version 330 core
out vec4 fragColor;

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIter;

void main()
{
    // Map pixel to world space
    vec2 uv = (gl_FragCoord.xy / u_resolution - 0.5) * 2.0;
    float aspect = u_resolution.x / u_resolution.y;
    uv.x *= aspect;
    vec2 c = u_center + uv * u_zoom;

    // Mandelbrot iteration
    vec2 z = vec2(0.0);
    int i;
    for (i = 0; i < u_maxIter; ++i) {
        if (dot(z, z) > 4.0) break;
        z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c;
    }

    float t = float(i) / float(u_maxIter);
    fragColor = vec4(vec3(t, t*t, t*t*t), 1.0);
}