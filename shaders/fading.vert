#version 430

layout (location = 0) in vec4 in_Position;

uniform float alpha;

out vec4 ex_Color;

void main()
{
    gl_Position = in_Position;
    ex_Color = vec4(0.0f, 0.0f, 0.0f, alpha);
}
