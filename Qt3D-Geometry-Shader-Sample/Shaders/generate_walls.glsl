#version 330 core
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 TexCoords;

in VS_OUT {
    float point_height;
} gs_in[];

void main() {
    gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0);
    TexCoords = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4(0.0, 0.0, 0.0, 0.0);
    TexCoords = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.0, gs_in[0].point_height, 0.0, 0.0);
    TexCoords = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4(0.0, gs_in[1].point_height, 0.0, 0.0);
    TexCoords = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}
