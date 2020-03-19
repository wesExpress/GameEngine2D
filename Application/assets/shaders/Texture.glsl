#type vertex
#version 330

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

out vec2 v_texCoord;

void main()
{
    v_texCoord = a_TexCoord;
    gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform float u_scale;

void main()
{
    color = texture(u_texture, v_texCoord * u_scale) * u_color;
}