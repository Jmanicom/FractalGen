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
    
   // --- Color mapping ---
    if (iter == u_maxIter) {
        // Inside set = pure black
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        // Smooth coloring
        float smoothIter = float(iter) + 1.0 - log2(log2(abs(zLen2)));
        float t = smoothIter / float(u_maxIter) + u_colorOffset;

        // Deep, moody dark-blue palette
        vec3 color1 = vec3(0.02, 0.05, 0.25);   // almost black navy deepBlue
        vec3 color2  = vec3(0.05, 0.10, 0.45);   // darker indigo midBlue
        vec3 color3 = vec3(0.25, 0.35, 1.0);  // vivid electric blue brightBlue
        vec3 color4 = vec3(0.9, 0.95, 1.0);    // outer glow white-blue whiteGlow

        // Gradient blending
        float shade = pow(t, 0.45);
        vec3 color = mix(color1, color2, smoothstep(0.0, 0.2, shade));
        color = mix(color, color3, smoothstep(0.2, 0.8, shade));
        color = mix(color, color4, smoothstep(0.8, 1.0, shade));

        // Subtle brightness & gamma correction
        color *= 0.85 + 0.15 * sin(t * 25.0 + u_colorOffset * 10.0);
        color = pow(color, vec3(0.9));

        FragColor = vec4(color, 1.0);
    }
}