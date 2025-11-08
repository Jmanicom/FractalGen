#version 330 core

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIter;

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
    
    // Grayscale color mapping
    if (iter == u_maxIter) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black for points in the set
    } else {
        // Smooth iteration count to avoid banding
        float smoothIter = float(iter) + 1.0 - log(log(length(z))) / log(2.0);
        float brightness = smoothIter / float(u_maxIter);
        
        // Simple grayscale
        FragColor = vec4(brightness, brightness, brightness, 1.0);
    }
}