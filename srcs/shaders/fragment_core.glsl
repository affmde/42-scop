#version 410

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;

uniform vec3 lightPosition;
uniform vec3 cameraPos;

uniform float fadeFactor;
uniform int showTexture;

vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 lightPosition, vec3 vs_normal)
{
	vec3 posToLightDirVec = normalize(lightPosition - vs_position);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;
	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 lightPosition, vec3 vs_normal, vec3 cameraPos)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPosition);
	vec3 reflectVec = normalize(reflect(lightToPosDirVec , normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConst = pow(max(dot(posToViewDirVec, reflectVec), 0), 35);
	vec3 specularFinal = material.specular * specularConst * texture(material.specularTex, vs_texcoord).rgb;
	return specularFinal;
}

void main()
{
	//fs_color = vec4(vs_color, 1.f);

	//Ambient light
	vec3 ambientFinal = calculateAmbient(material);

	//Difuse light
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, lightPosition, vs_normal);

	//Specular light
	vec3 specularFinal = calculateSpecular(material, vs_position, lightPosition, vs_normal, cameraPos);

	//Attenuation

	vec4 calculatedColor = texture(material.diffuseTex, vs_texcoord)
	* (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));

	vec4 colorsDisplay = vec4(vs_color, 1.f) * fadeFactor;
	vec4 texturesDisplay = fadeFactor == 0.f ? calculatedColor : calculatedColor * (1.f - fadeFactor);
	fs_color = colorsDisplay + texturesDisplay;
}