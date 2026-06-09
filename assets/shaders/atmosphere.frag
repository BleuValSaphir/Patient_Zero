uniform sampler2D window;

void main()
{
    vec4 pixelcolor = texture2D(window, vec2(gl_TexCoord[0].xy));
    vec3 shade = vec3(1.0, 0.0, 0.0);
    vec3 color = mix(pixelcolor.rgb, shade, 0.1);
    gl_FragColor = vec4(color.rgb * 0.5, pixelcolor.a);
}