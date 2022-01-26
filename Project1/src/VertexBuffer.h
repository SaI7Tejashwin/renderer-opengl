#pragma once


class VertexBuffer
{
private:
	unsigned int m_RendererID; //The internal ID of the openGL renderer
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};
