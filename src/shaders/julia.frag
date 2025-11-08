#version 330 core

uniform vec2 u_resolution;
uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIter;
uniform float u_colorOffset;
uniform vec2 u_juliaC;  // The Julia set constant

out vec4 FragColor;

void main() {
    // Convert pixel coordinates to complex plane
    vec2 uv = (gl_FragCoord.xy / u_resolution) * 2.0 - 1.0;
    uv.x *= u_resolution.x / u_resolution.y;
    
    // For Julia set, the initial z is the pixel position
    vec2 z = u_center + uv * u_zoom;
    
    // Julia set iteration: z = z^2 + c (where c is constant)
    int iter;
    float zLen2 = 0.0;
    
    for (iter = 0; iter < u_maxIter; iter++) {
        // z = z^2 + c
        float x = z.x * z.x - z.y * z.y + u_juliaC.x;
        float y = 2.0 * z.x * z.y + u_juliaC.y;
        z = vec2(x, y);
        
        zLen2 = z.x * z.x + z.y * z.y;
        if (zLen2 > 4.0) break;
    }
    
    // High quality dark color palette
    if (iter == u_maxIter) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        // Improved smooth iteration count
        float smoothIter = float(iter) + 1.0 - log2(log2(zLen2) / 2.0);
        float t = smoothIter / 50.0 + u_colorOffset;
        
        // Darker, richer color palette
        vec3 color1 = vec3(0.0, 0.01, 0.1);
        vec3 color2 = vec3(0.2, 0.0, 0.3);
        vec3 color3 = vec3(0.6, 0.2, 0.0);
        vec3 color4 = vec3(0.8, 0.6, 0.1);
        
        float m = mod(t, 4.0);
        vec3 color;
        
        if (m < 1.0) {
            color = mix(color1, color2, smoothstep(0.0, 1.0, m));
        } else if (m < 2.0) {
            color = mix(color2, color3, smoothstep(0.0, 1.0, m - 1.0));
        } else if (m < 3.0) {
            color = mix(color3, color4, smoothstep(0.0, 1.0, m - 2.0));
        } else {
            color = mix(color4, color1, smoothstep(0.0, 1.0, m - 3.0));
        }
        
        float brightness = 0.85 + 0.15 * sin(smoothIter * 0.05);
        color *= brightness;
        color = pow(color, vec3(1.1));
        
        FragColor = vec4(color, 1.0);
    }
}