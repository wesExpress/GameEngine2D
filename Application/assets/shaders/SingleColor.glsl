#type vertex
#version 330

layout(location = 0) in vec3 a_Position;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

out vec3 v_position;

void main()
{
    v_position = vec3(a_Position);
    gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330

layout(location = 0) out vec4 color;

in vec3 v_position;

uniform vec3 u_color;

void main()
{
    color = vec4(u_color, 1.0);
}