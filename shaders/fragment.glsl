#version 330 core

in float height;
out vec4 FragColor;

void main()
{
    float h = clamp(height / 54.0, 0.0, 1.0);

    vec3 colorLow  = vec3(1.0, 0.0, 0.0);
    vec3 colorHigh = vec3(0.0, 1.0, 0.0);

    vec3 color = mix(colorLow, colorHigh, h);

    FragColor = vec4(color, 1.0);
}
