#pragma once

#include<GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void Clear() const; //we use const just in case we have a const rendererID
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};