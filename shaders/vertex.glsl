#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;
layout(location = 2) in vec2 aTextCoord;

out vec3 VertexColor;
out vec2 TexCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform vec3 uCol;

void main() {
    gl_Position = uProjection * uView * vec4(aPos, 1.0);
    VertexColor = uCol;
    TexCoord = aTextCoord;
}
