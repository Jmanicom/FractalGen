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
    
    // Mandelbrot iteration
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
        float smoothIter = float(iter) + 1.0 - log2(log2(zLen2));
        
        // Normalize with smooth cycling
        float t = sqrt(smoothIter / 50.0) + u_colorOffset * 0.1;
        t = mod(t, 1);
        
        // Exact color palette from the reference image
        vec3 color1 = vec3(1.0, 0.8, 0.4);     // Light yellow-orange
        vec3 color2 = vec3(1.0, 0.5, 0.0);     // Bright orange
        vec3 color3 = vec3(0.5, 0.2, 0.6);     // Deep purple
        vec3 color4 = vec3(0.1, 0.3, 0.7);     // Deep blue
        vec3 color5 = vec3(0.3, 0.6, 0.9);     // Light blue
        vec3 color6 = vec3(0.7, 0.85, 0.95);   // Cyan-white
        
        // Multi-stage gradient matching the image
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
        
        // Contrast boost to match the image
        color = pow(color, vec3(0.85));
        
        // Slight saturation boost
        float gray = dot(color, vec3(0.299, 0.587, 0.114));
        color = mix(vec3(gray), color, 1.15);
        
        color = clamp(color, 0.0, 1.0);
        
        FragColor = vec4(color, 1.0);
    }
}