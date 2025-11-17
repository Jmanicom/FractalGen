#version 400 compatibility
#extension GL_ARB_gpu_shader_fp64 : enable

// Modifiable if double's are wanted later
#define FLOAT float
#define VEC2 vec2
#define VEC3 vec3 

uniform int u_fType;
uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIter;
uniform vec2 u_mousePos;
uniform bool u_drawMandelbrot;
uniform bool u_drawJulia;

out vec4 FragColor;

// Hash function for dithering
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453);
}

VEC2 cx_sqr(VEC2 a) {
    FLOAT x2 = a.x * a.x;
    FLOAT y2 = a.y * a.y;
    FLOAT xy = a.x * a.y;
    return VEC2(x2 - y2, xy + xy);
}

VEC2 cx_cube(VEC2 a) {
    FLOAT x2 = a.x * a.x;
    FLOAT y2 = a.y * a.y;
    FLOAT d = x2 - y2;
    return VEC2(a.x * (d - y2 - y2), a.y * (x2 + x2 + d));
}

VEC2 cx_mul(VEC2 a, VEC2 b) {
    return VEC2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

VEC2 cx_div(VEC2 a, VEC2 b) {
    FLOAT denom = 1.0 / (b.x * b.x + b.y * b.y);
    return VEC2(a.x * b.x + a.y * b.y, a.y * b.x - a.x * b.y) * denom;
}

vec2 mandelbrot(vec2 z, vec2 c) {
    return cx_sqr(z) + c;
}

vec2 burningShip(VEC2 z, VEC2 c) {
    return VEC2(z.x * z.x - z.y * z.y, -2.0 * abs(z.x * z.y)) + c;
}

vec2 feather(VEC2 z, VEC2 c) {
    return cx_div(cx_cube(z), VEC2(1.0, 0.0) + z * z) + c;
}

vec2 tricorn(VEC2 z, VEC2 c) {
    return VEC2(z.x * z.x - z.y * z.y, -2.0 * z.x * z.y) + c;
}

vec3 computeFractal(VEC2 zInit, VEC2 c) {
    VEC2 z = zInit;
    int iter;
    float zlen2 = 0.0;

    for (iter = 0; iter < u_maxIter; iter++) {
        switch (u_fType) {
            case 0: z = mandelbrot(z, c); break;
            case 1: z = burningShip(z, c); break;
            case 2: z = feather(z, c); break;
            case 3: z = tricorn(z, c); break;
        }
    
        zlen2 = dot(z, z);
        if (zlen2 > 4.0) break;
    }

    if (iter == u_maxIter) {
        return vec3(0.0, 0.0, 0.0);
    } else {
        float smoothIter = float(iter) + 1.0 - log2(log2(zlen2));

        // Dynamic threshold to eliminate halo
        float iterThreshold = mix(15.0, 5.0, clamp(u_zoom / 2.0, 0.0, 1.0));
        if (smoothIter < iterThreshold) {
            return vec3(0.05, 0.05, 0.15);
        }

        float t = sqrt(smoothIter / 50.0);
        t = mod(t, 1.0);

        vec3 color1 = vec3(1.0, 0.8, 0.4);     // Light yellow-orange
        vec3 color2 = vec3(1.0, 0.5, 0.0);     // Bright orange
        vec3 color3 = vec3(0.5, 0.2, 0.6);     // Deep purple
        vec3 color4 = vec3(0.1, 0.3, 0.7);     // Deep blue
        vec3 color5 = vec3(0.3, 0.6, 0.9);     // Light blue
        vec3 color6 = vec3(0.7, 0.85, 0.95);   // Cyan-white

        vec3 color;
        float stage = t * 5.0;

        if (stage < 1.0) {
            color = mix(color1, color2, smoothstep(0.0, 1.0, stage));
        } else if (stage < 2.0) {
            color = mix(color2, color3, smoothstep(0.0, 1.0, stage - 1.0));
        } else if (stage < 3.0) {
            color = mix(color3, color4, smoothstep(0.0, 1.0, stage - 2.0));
        } else if (stage < 4.0) {
            color = mix(color4, color5, smoothstep(0.0, 1.0, stage - 3.0));
        } else {
            color = mix(color5, color6, smoothstep(0.0, 1.0, stage - 4.0));
        }

        // Subtle brightness variation for texture
        float detail = sin(smoothIter * 0.3) * 0.08 + 1.0;
        color *= detail;
        
        // Contrast boost
        color = pow(color, vec3(0.85));
        
        // Slight saturation boost
        float gray = dot(color, vec3(0.299, 0.587, 0.114));
        color = mix(vec3(gray), color, 1.15);
        
        color = clamp(color, 0.0, 1.0);
        
        return color;
    }
}

void main() {
    // Convert pixel coordinates to complex plane
    vec2 uv = (gl_FragCoord.xy / u_resolution) * 2.0 - 1.0;
    uv.x *= u_resolution.x / u_resolution.y;
    
    vec2 px = u_center + uv * u_zoom;

    VEC3 col = VEC3(0.0);

    if (u_drawMandelbrot) {
        vec3 mandelbrotColor = computeFractal(vec2(0.0), px);
        col += mandelbrotColor;
    }
    if (u_drawJulia) {
        VEC3 juliaColor = computeFractal(px, u_mousePos);
        col += juliaColor;
    }
    if (u_drawMandelbrot && u_drawJulia) {
        col *= 0.5;
    }

    // Add dithering
    float dither = (hash(gl_FragCoord.xy) - 0.5) / 255.0;
    col += vec3(dither);
    col = clamp(col, 0.0, 1.0);

    FragColor = vec4(col, 1.0);
}