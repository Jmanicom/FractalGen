#version 330 core

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIter;
uniform float u_colorOffset;

out vec4 FragColor;

void main() {
    // Convert pixel coordinates to complex plane
    vec2 uv = (gl_FragCoord.xy / u_resolution) * 2.0 - 1.0;
    uv.x *= u_resolution.x / u_resolution.y; // aspect ratio correction
    
    vec2 c = u_center + uv * u_zoom;
    
    // Mandelbrot iteration
    vec2 z = vec2(0.0, 0.0);
    int iter;
    
    for (iter = 0; iter < u_maxIter; iter++) {
        // z = z^2 + c
        float x = z.x * z.x - z.y * z.y + c.x;
        float y = 2.0 * z.x * z.y + c.y;
        z = vec2(x, y);
        
        if (length(z) > 2.0) break;
    }
    
    // Color mapping
    if (iter == u_maxIter) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black for points in the set
    } else {
        // Smooth iteration count to avoid color banding
        float smoothIter = float(iter) + 1.0 - log(log(length(z))) / log(2.0);
        float t = smoothIter / 50.0 + u_colorOffset; // Add color offset for animation
        
        // Define vibrant color palette
        vec3 color1 = vec3(0.0, 0.02, 0.2);   // Dark blue
        vec3 color2 = vec3(0.5, 0.0, 0.5);     // Purple
        vec3 color3 = vec3(1.0, 0.5, 0.0);     // Orange
        vec3 color4 = vec3(1.0, 1.0, 0.5);     // Yellow
        
        float m = mod(t, 4.0);
        vec3 color;
        
        if (m < 1.0) {
            color = mix(color1, color2, m);
        } else if (m < 2.0) {
            color = mix(color2, color3, m - 1.0);
        } else if (m < 3.0) {
            color = mix(color3, color4, m - 2.0);
        } else {
            color = mix(color4, color1, m - 3.0);
        }
        
        FragColor = vec4(color, 1.0);
    }
}