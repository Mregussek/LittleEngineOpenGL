
#ifndef BUFFER_H
#define BUFFER_H


#include "includes.h"
#include "defines.h"


namespace le
{

struct BufferSpecification {

	f32* pVertices{ nullptr };
	u32 countVertices{ 0 };
	u32 sizeofVertices{ 0 };
	u32* pIndices{ nullptr };
	u32 countIndices{ 0 };
	u32 sizeofIndices{ 0 };

};


class Buffer {
public:

	b8 init(BufferSpecification _bufferSpecs);
	void close();

	void use() const;

	const BufferSpecification& getSpecs() const;

private:

	BufferSpecification mBufferSpecs;
	u32 mVAO{};
	u32 mVBO{};
	u32 mEBO{};

};

}


#endif
