#version 330

uniform sampler2D tex;
uniform mat4 model;
uniform vec3 camera_position;

uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;
uniform vec3 light_position;
uniform float material_shininess;

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

    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = normalize(light_position - fragPosition);

    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLight);
    brightness = clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light_intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = texture(tex, fragTexCoord);

    vec3 surfaceToView = normalize(camera_position - fragPosition);
    vec3 reflection = -normalize(reflect(surfaceToLight, normal));
    float specular_brightness = dot(reflection, surfaceToView);
	specular_brightness = clamp(specular_brightness, 0, 1);
	if(brightness <= 0){
		specular_brightness = 0.0;
	}
	
    vec3 diffuse_shading = brightness * light_diffuse * surfaceColor.rgb;

    vec3 ambient_shading = light_ambient * surfaceColor.rgb;

    vec3 specular_shading = light_specular * surfaceColor.rgb * pow(specular_brightness, material_shininess);

	finalColor = vec4(diffuse_shading + ambient_shading  + specular_shading, surfaceColor.a);
}
