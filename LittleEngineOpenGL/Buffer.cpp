
#include "Buffer.h"


namespace le
{

static void displayBufferSpecs(const BufferSpecification& bufferSpecs) {
    std::cout << "Vertices Size: " << bufferSpecs.countVertices << " Vertices Capacity: " << bufferSpecs.sizeofVertices << "\n";
    std::cout << "Indices Size: " << bufferSpecs.countIndices << " Indices Capacity: " << bufferSpecs.sizeofIndices << "\n";
}
    

b8 Buffer::init(BufferSpecification _bufferSpecs) {
    bufferSpecs = _bufferSpecs;
    displayBufferSpecs(bufferSpecs);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, bufferSpecs.sizeofVertices, bufferSpecs.pVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSpecs.sizeofIndices, bufferSpecs.pIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    std::cout << "Buffer initialized!\n";
    return LTRUE;
}


void Buffer::close() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    std::cout << "Buffer closed!\n";
}


void Buffer::use() const {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}


const BufferSpecification& Buffer::getSpecs() const {
    return bufferSpecs;
}


}
