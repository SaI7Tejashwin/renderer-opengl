#include "Renderer.h"

#include <iostream>


void Renderer:: Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	/*glUseProgram(shader); */
	shader.Bind();


	/*glUniform4f(location, r, 0.3f, 0.8f, 1.0f);*/
	//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

	//glBindVertexArray(vao);
	va.Bind();
	ib.Bind();
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr); //this is used to render when we have index arrays
													//used most of the time
}