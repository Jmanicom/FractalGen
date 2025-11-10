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
    
   // --- Color calculation ---
    if (iter == u_maxIter) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        float smoothIter = float(iter) + 1.0 - log2(log2(zLen2));
        float t = smoothIter / float(u_maxIter);

        // Tuned palette
        vec3 color1 = vec3(0.0, 0.0, 0.05);   // almost black navy deepBlue
        vec3 color2  = vec3(0.02, 0.05, 0.25);   // darker indigo midBlue
        vec3 color3 = vec3(0.15, 0.25, 0.9);  // vivid electric blue brightBlue
        vec3 color4 = vec3(0.9, 0.95, 1.0);    // outer glow white-blue whiteGlow

        // smoother gradient blending
        float shade = pow(t, 0.4);
        vec3 color = mix(color1, color2, smoothstep(0.0, 0.2, shade));
        color = mix(color, color3, smoothstep(0.2, 0.8, shade));
        color = mix(color, color4, smoothstep(0.8, 1.0, shade));

        // contrast boost & gamma correction
        color = pow(color, vec3(0.9));
        color *= 1.0;

        // optional subtle shimmer
        color *= 0.9 + 0.1 * sin(t * 30.0 + u_colorOffset * 10.0);

        FragColor = vec4(color, 1.0);
    }

}