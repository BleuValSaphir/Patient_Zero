uniform sampler2D floor_tex;
uniform sampler2D ceil_tex;
uniform vec2 resolution;
uniform vec2 player_pos;
uniform float player_angle;
uniform float player_pitch;

void main()
{
    float y = resolution.y - gl_FragCoord.y;
    float x = gl_FragCoord.x;

    float p = y - (resolution.y / 2.0) - player_pitch;
    
    if (p == 0.0) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    float is_floor = p > 0.0 ? 1.0 : 0.0;
    float abs_p = abs(p);
    
    float r_d = 960.0 / abs_p;
    float fov = 1.0471975512; // PI / 3
    
    vec2 dir = vec2(cos(player_angle), sin(player_angle));
    vec2 plane = vec2(-sin(player_angle) * tan(fov / 2.0), cos(player_angle) * tan(fov / 2.0));
    
    vec2 floorPos = (player_pos + r_d * (dir - plane)) + ((r_d * 2.0 * plane) / resolution.x) * x;
    vec2 texCoord = fract(floorPos);
    
    float ratio = clamp(1.0 - (r_d * 35.0 / 255.0), 0.0, 1.0);
    
    vec4 color = mix(texture2D(ceil_tex, texCoord), texture2D(floor_tex, texCoord), is_floor);
    gl_FragColor = vec4(color.rgb * ratio, 1.0);
}
