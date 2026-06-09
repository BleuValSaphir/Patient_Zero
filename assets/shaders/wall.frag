uniform sampler2D wall_texture;

void main()
{
    vec4 pixel_color = texture2D(wall_texture, gl_TexCoord[0].xy);
    gl_FragColor = pixel_color * gl_Color;
}