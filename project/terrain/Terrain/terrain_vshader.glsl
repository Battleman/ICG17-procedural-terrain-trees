#version 330

in vec2 position;
in float shift;

out vec2 uv;
out vec3 normal_mv;
out vec3 view_dir;
out vec3 light_dir;
out float base_color;

uniform sampler2D height_map;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 M;
uniform float res;

const vec3 light_world = vec3(1,1,1);

float height(vec2 p) {
    p*=1-(2/res); //Align with texture margin
    p+=(1/res);
    return texture(height_map,p).r*1;
}

vec3 fdiff(vec2 p) {
    float d = 0.5f/res;
    float hL = height(p - vec2(d,0));
    float hR = height(p + vec2(d,0));
    float hD = height(p - vec2(0,d));
    float hU = height(p + vec2(0,d));

    vec3 norm;
    // deduce terrain normal
    norm.x = hL - hR;
    norm.y = hD - hU;
    norm.z = 500*d;
    return normalize(norm);
}

void main() {
    uv = (position + vec2(1.0, 1.0)) * 0.5;
    float value = height(uv);
    base_color = value*0.09;

    vec3 pos_3d = vec3(position.x,position.y,value*0.1+shift);
    normal_mv = normalize((MV*vec4(fdiff(uv),0)).xyz);
    view_dir = normalize((MV*vec4(pos_3d,1.0)).xyz);
    light_dir = (MV*vec4(light_world,0)).xyz;
    gl_Position = MVP* vec4(pos_3d,1.0);
}
