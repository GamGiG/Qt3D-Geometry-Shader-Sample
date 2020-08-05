#version 330 core
in vec3 vertexPosition;
in float height;

uniform mat4 modelViewProjection;

out VS_OUT {
    float point_height;
} vs_out;

void main()
{
    vs_out.point_height = height;
    gl_Position = modelViewProjection * vec4(vertexPosition, 1.0);
}
