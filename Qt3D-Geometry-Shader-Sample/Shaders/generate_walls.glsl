#version 330 core
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 TexCoords;

void main() {
    gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0);
    TexCoords = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4(0.0, 0.0, 0.0, 0.0);
    TexCoords = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.8, 0.0, 0.0);
    TexCoords = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4(0.0, 0.8, 0.0, 0.0);
    TexCoords = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}
