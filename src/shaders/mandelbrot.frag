#version 330 core

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIter;
uniform float u_colorOffset;

out vec4 FragColor;

// High quality color palette function
vec3 palette(float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.00, 0.33, 0.67);
    
    return a + b * cos(6.28318 * (c * t + d + u_colorOffset));
}

void main() {
    // Convert pixel coordinates to complex plane
    vec2 uv = (gl_FragCoord.xy / u_resolution) * 2.0 - 1.0;
    uv.x *= u_resolution.x / u_resolution.y;
    
    vec2 c = u_center + uv * u_zoom;
    
    // Mandelbrot iteration
    vec2 z = vec2(0.0, 0.0);
    int iter;
    float zLen2 = 0.0;  // Store squared length for better precision
    
    for (iter = 0; iter < u_maxIter; iter++) {
        // z = z^2 + c
        float x = z.x * z.x - z.y * z.y + c.x;
        float y = 2.0 * z.x * z.y + c.y;
        z = vec2(x, y);
        
        zLen2 = z.x * z.x + z.y * z.y;
        if (zLen2 > 4.0) break;
    }
    
    // High quality coloring
    if (iter == u_maxIter) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        // Smooth iteration with better precision
        float smoothIter = float(iter) + 1.0 - log2(log2(zLen2) / 2.0);
        
        // Normalized iteration value
        float t = smoothIter / 50.0;
        
        // Apply high quality color palette
        vec3 color = palette(t);
        
        // Optional: Add subtle brightness variation for depth
        float brightness = 0.7 + 0.3 * sin(smoothIter * 0.1);
        color *= brightness;
        
        FragColor = vec4(color, 1.0);
    }
}