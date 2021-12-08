#version 330 core

in vec3 FragPos;
in vec3 normal;
in vec2 textCoord;

out vec4 FragColor;

uniform sampler2D textureC;
uniform sampler2D textureN;

uniform vec3 objColor;
uniform vec3 LightColor;
uniform vec3 LightPos;
uniform mat4 LightTransform;
uniform vec3 cameraPos;
uniform float ambientLight;
uniform int isTexture;


void main()
{
//ambient	
		vec3 ambient = ambientLight * LightColor;
		vec3 fragPos = FragPos;
	if(isTexture == 3){
		//diffuse
		vec3 MyLightPos = vec3(LightTransform * vec4(LightPos, 1.0f));
		vec3 normalDir = normalize(normal);
		vec3 biNormal = normalize(cross(normalDir, vec3(texture(textureN, textCoord))));
		mat3 rotation = mat3(vec3(texture(textureN, textCoord)), biNormal , normalDir);
		fragPos = rotation *FragPos;
		rotation = transpose(rotation);
		vec3 lightDir = normalize(MyLightPos - fragPos);
		lightDir = rotation * lightDir;
		float diffuseLight = max(dot(lightDir, normalDir), 0.0f);
		vec3 diffuse = diffuseLight * LightColor;
		//specular
		int shininess = 128;
		vec3 viewDir = normalize(cameraPos - fragPos);
		viewDir = rotation * viewDir;
		vec3 reflectDir = reflect(-lightDir , normalDir);//¿‘ªÁ ∫§≈Õ π›ªÁ ∫§≈Õ // -lightDir???
		float specularLight = max(dot(viewDir, reflectDir), 0.0f);
		specularLight = pow(specularLight, shininess);
		vec3 specular = specularLight * LightColor;

		vec3 re = ambient + diffuse + specular;
		vec3 result;
		
		result = vec3(re.x * texture(textureC, textCoord).x, re.y * texture(textureC, textCoord).y, re.z * texture(textureC, textCoord).z);
		FragColor = vec4(result, 1.0f);
	}
	else{
		//diffuse
		vec3 MyLightPos = vec3(LightTransform * vec4(LightPos, 1.0f));
		vec3 normalDir = normalize(normal);
		vec3 lightDir = normalize(MyLightPos - fragPos);
		float diffuseLight = max(dot(lightDir, normalDir), 0.0f);
		vec3 diffuse = diffuseLight * LightColor;
		//specular
		int shininess = 128;
		vec3 viewDir = normalize(cameraPos - fragPos);
		vec3 reflectDir = reflect(-lightDir , normalDir);//¿‘ªÁ ∫§≈Õ π›ªÁ ∫§≈Õ // -lightDir???
		float specularLight = max(dot(viewDir, reflectDir), 0.0f);
		specularLight = pow(specularLight, shininess);
		vec3 specular = specularLight * LightColor;
	
		vec3 re = ambient + diffuse + specular;
		vec3 result;

		if(isTexture == 1){
			result = vec3(re.x * texture(textureC, textCoord).x, re.y * texture(textureC, textCoord).y, re.z * texture(textureC, textCoord).z);
			FragColor = vec4(result, 1.0f);
			}
		else if(isTexture == 2){		
			result = vec3(re.x * texture(textureC, textCoord).x, re.y * texture(textureC, textCoord).y, re.z * texture(textureC, textCoord).z);
			FragColor = vec4(result, -1 * (texture(textureC, textCoord).y - 1));
		}
		else if(isTexture == 4){
			result = vec3(texture(textureC, textCoord).x, texture(textureC, textCoord).y, texture(textureC, textCoord).z);
			FragColor = vec4(result, 1.0f);
		}
		else if(isTexture == 0){
			result = vec3(re.x * objColor.x, re.y * objColor.y, re.z * objColor.z);
			FragColor = vec4(result, 1.0f);
		}
		else if(isTexture == -1){
			FragColor = vec4(objColor, 1.0f);
		}
		else {
			result = vec3(re.x * objColor.x, re.y * objColor.y, re.z * objColor.z);
			FragColor = vec4(result, 1.0f);
		}
	}
}