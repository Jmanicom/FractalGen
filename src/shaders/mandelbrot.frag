#version 400 core

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIter;
uniform float u_colorOffset;

out vec4 FragColor;

void main() {
    // Convert pixel coordinates to complex plane
    vec2 uv = (gl_FragCoord.xy / u_resolution) * 2.0 - 1.0;
    uv.x *= u_resolution.x / u_resolution.y;
    
    vec2 c = u_center + uv * u_zoom;
    
    // Mandelbrot iteration with better precision
    vec2 z = vec2(0.0, 0.0);
    int iter;
    float zLen2 = 0.0;
    
    for (iter = 0; iter < u_maxIter; iter++) {
        // z = z^2 + c
        float x = z.x * z.x - z.y * z.y + c.x;
        float y = 2.0 * z.x * z.y + c.y;
        z = vec2(x, y);
        
        zLen2 = z.x * z.x + z.y * z.y;
        if (zLen2 > 4.0) break;
    }
    
   // Color Mapping
    if (iter == u_maxIter) {
        // Inside set = pure black
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        // Smooth coloring
        float smoothIter = float(iter) + 1.0 - log2(log2(abs(zLen2)));
        float t = smoothIter / float(u_maxIter) + u_colorOffset;

        // Dark Blue Color Palette
        vec3 color1 = vec3(0.0, 0.0, 0.0);      // Very Dark Blue
        vec3 color2 = vec3(0.0, 0.05, 0.1);     // darker indigo midBlue
        vec3 color3 = vec3(0.25, 0.35, 1.0);    // Bright Blue
        vec3 color4 = vec3(0.03, 0.5, 1.0);     // Electric Blue
        vec3 color5 = vec3(0.9, 0.95, 1.0);     // outer glow white-blue whiteGlow

        // Gradient blending
        float shade = pow(t, 0.30);
        vec3 color = mix(color2, color3, smoothstep(0.0, 0.5, shade));
        color = mix(color, color4, smoothstep(0.2, 0.8, shade));
        color = mix(color, color5, smoothstep(0.8, 1.0, shade));

        FragColor = vec4(color, 1.0);
    }
}