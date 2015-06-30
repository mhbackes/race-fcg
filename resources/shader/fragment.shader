#version 330

uniform sampler2D tex;
uniform mat4 model;

uniform vec3 light_position;
uniform vec3 light_intensities;
// coeficiente de iluminacao ambiente
uniform float light_ambient_coefficient;
// BRILHO ESPECULAR
uniform float material_shininess;
// COR DA LUZ ESPECULAR (MATERIAL)
uniform vec3 COR_ESPECULAR_MAT;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

void main() {
    //calculate normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * fragNormal);

    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = vec3(model * vec4(fragVert, 1));

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light_intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = texture(tex, fragTexCoord);

    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = light_position - fragPosition;

    //calculate the cosine of the angle of incidence -> COMPONENTE DIFUSA
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);
    vec3 DIFUSA = brightness * light_intensities * surfaceColor.rgb;

    // ILUMINACAO AMBIENTE
    vec3 AMBIENTE = light_ambient_coefficient * surfaceColor.rgb * light_intensities;

    // ILUMINACAO ESPECULAR
    vec3 VETOR_INCIDENCIA = -surfaceToLight;
    vec3 VETOR_REFLEXAO = reflect(VETOR_INCIDENCIA, normal);
    float CEF = dot(normal, VETOR_REFLEXAO) / (length(surfaceToLight) * length(normal));
    CEF = clamp(CEF, 0, 1);
    float COEFICIENTE_ESPECULAR = 0.0;
    // se componente difusa é 0 (a parte do objeto que não está iluminada)
    // componente especular também vai ser 0 (evita comportamentos estranhos)
    // para partes não iluminadas
    if(brightness > 0.0)
        COEFICIENTE_ESPECULAR = pow(CEF, material_shininess);

    vec3 ESPECULAR = COEFICIENTE_ESPECULAR * COR_ESPECULAR_MAT * light_intensities;

	finalColor = vec4(AMBIENTE + ESPECULAR + DIFUSA, surfaceColor.a);
}