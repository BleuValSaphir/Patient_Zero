uniform sampler2D texture;
uniform float is_active;
uniform float time;
uniform vec2 resolution;

void main()
{
    vec4 pixel_color = texture2D(texture, gl_TexCoord[0].xy);
    
    if (is_active > 0.5) {
        vec2 center = vec2(resolution.x * 0.5, 0.0);
        float dist = distance(gl_FragCoord.xy, center);
        
        float radius = resolution.y * 0.8;
        float flicker = sin(time * 15.0) * 0.03 + cos(time * 22.0) * 0.03;
        float intensity = 1.0 - clamp(dist / (radius * (1.0 + flicker)), 0.0, 1.0);
        
        vec3 orange = vec3(1.0, 0.5, 0.1);
        pixel_color.rgb += orange * intensity * 0.8 * pixel_color.rgb;
    }
    
    gl_FragColor = pixel_color;
}
