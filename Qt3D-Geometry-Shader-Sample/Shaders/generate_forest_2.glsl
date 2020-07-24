#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projectionMatrix;
uniform mat4 modelView;

out vec2 TexCoords;

void main (void)
{
    vec4 center = modelView * gl_in[0].gl_Position;

    TexCoords = vec2( 0, 0 );
    gl_Position = projectionMatrix * (center + vec4(10, 10, 0, 0));
    EmitVertex();

    TexCoords = vec2( 1, 0  );
    gl_Position = projectionMatrix * (center + vec4(10, -10, 0, 0));
    EmitVertex();

    TexCoords = vec2( 0, 1 );
    gl_Position = projectionMatrix * (center + vec4(-10, 10, 0, 0));
    EmitVertex();

    TexCoords = vec2( 1, 1 );
    gl_Position = projectionMatrix * (center + vec4(-10, -10, 0, 0));
    EmitVertex();
}
