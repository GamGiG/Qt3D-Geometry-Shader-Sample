#version 330 core
uniform sampler2D texture_diffuse1;
in vec2 TexCoords;
out vec4 FragColor;

void main (void)
{
    vec4 color = texture(texture_diffuse1, TexCoords);
    if (color.a == 0)
        discard;

    FragColor = color;
}
