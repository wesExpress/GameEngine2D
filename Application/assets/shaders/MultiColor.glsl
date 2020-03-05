#type vertex
#version 330

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

out vec3 v_position;
out vec4 v_color;

void main()
{
    v_position = vec3(a_Position);
    v_color = a_Color;
    gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330

layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;

void main()
{
    color = vec4(v_position*0.5 + 0.5, 1.0);
    color = v_color;
}