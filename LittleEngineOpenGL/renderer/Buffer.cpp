
#include "Buffer.h"


namespace le
{

static void displayBufferSpecs(const BufferSpecification& bufferSpecs) {
    std::cout << "Vertices Size: " << bufferSpecs.countVertices << " Vertices Capacity: " << bufferSpecs.sizeofVertices << "\n";
    std::cout << "Indices Size: " << bufferSpecs.countIndices << " Indices Capacity: " << bufferSpecs.sizeofIndices << "\n";
}
    

b8 Buffer::init(BufferSpecification _bufferSpecs) {
    mBufferSpecs = _bufferSpecs;
    displayBufferSpecs(mBufferSpecs);

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mBufferSpecs.sizeofVertices, mBufferSpecs.pVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mBufferSpecs.sizeofIndices, mBufferSpecs.pIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    LLOG("Buffer initialized!");
    return LTRUE;
}


void Buffer::close() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
    LLOG("Buffer closed!");
}


void Buffer::use() const {
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
}


const BufferSpecification& Buffer::getSpecs() const {
    return mBufferSpecs;
}


}
