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

void main()
{
	//fs_color = vec4(vs_color, 1.f);

	//Ambient light
	vec3 ambientLight = material.ambient;

	//Difuse light
	vec3 posToLightDirVec = normalize(lightPosition - vs_position);
	vec3 diffuseColor = vec3(1.f, 1.f, 1.f);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	//Specular light
	vec3 lightToPosDirVec = normalize(vs_position - lightPosition);
	vec3 reflectVec = normalize(reflect(lightToPosDirVec , normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConst = pow(max(dot(posToViewDirVec, reflectVec), 0), 35);
	vec3 specularFinal = material.specular * specularConst;

	//Attenuation

	fs_color = texture(material.diffuseTex, vs_texcoord) * vec4(vs_color, 1.f)
	* (vec4(ambientLight, 1.f) + vec4(diffuseFinal, 1.f))
	+ vec4(specularFinal, 1.f);
}