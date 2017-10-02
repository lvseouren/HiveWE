#include "stdafx.h"

void Terrain::create() {
	vertices.resize(width * height);
	indices.resize((width - 1) * (height - 1) * 2);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			vertices[j * width + i] = { i, j, 0 };
		}
	}

	unsigned int counter = 0;
	size_t index = 0;
	for (int j = 0; j < height - 1; j++) {
		for (int i = 0; i < width - 1; i++) {
			indices[index++] = { counter, counter + 1, counter + width };
			indices[index++] = { counter + 1, counter + width + 1, counter + width};
			++counter;
		}
		++counter;
	}

	gl->glGenBuffers(1, &vertexBuffer);
	gl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	gl->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	gl->glGenBuffers(1, &indexBuffer);
	gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int) * 3, indices.data(), GL_STATIC_DRAW);

	gl->glGenTextures(1, &textureArray);
	gl->glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
	gl->glTexStorage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, textureWidth, textureHeight, textures);

	gl->glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl->glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gl->glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gl->glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void Terrain::render() {
	gl->glEnableVertexAttribArray(0);
	gl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	gl->glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, NULL);
	gl->glDisableVertexAttribArray(0);
	//std::cout << "2 " << gl->glGetError() << std::endl;
}