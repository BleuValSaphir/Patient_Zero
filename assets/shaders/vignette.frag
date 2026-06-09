uniform sampler2D window;
uniform float radius;
uniform float vignette_var;
uniform vec3 color;

void main()
{
    vec4 pixelcolor = texture2D(window, vec2(gl_TexCoord[0].xy));
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(gl_TexCoord[0].xy, center);
    float darkening = smoothstep(radius - vignette_var, radius, dist);
    vec3 new_color = mix(pixelcolor.rgb, color, darkening);
    gl_FragColor = vec4(new_color.rgb, pixelcolor.a);

}