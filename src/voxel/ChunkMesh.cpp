#include "ChunkMesh.h"

#include <iostream>

void ChunkMesh::Build(const Chunk& chunk) {
    vertices.clear();
    indices.clear();
    offset = 0;

    for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x) 
    for (uint32_t y = 0; y < CHUNK_SIZE_Y; ++y)
    for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {
        Block block = chunk.GetBlock(x, y, z);

        if (!block.IsSolid())
            continue;
        
        // Add right face
        if (x + 1 >= CHUNK_SIZE_X || !chunk.GetBlock(x + 1, y, z).IsSolid())
            AddFaceRight(x, y, z);

        // Add left face
        if (x == 0 || !chunk.GetBlock(x - 1, y, z).IsSolid())
            AddFaceLeft(x, y, z);

        // Add up face
        if (y + 1 >= CHUNK_SIZE_Y || !chunk.GetBlock(x, y + 1, z).IsSolid())
            AddFaceTop(x, y, z);

        // Add down face
        if (y == 0 || !chunk.GetBlock(x, y - 1, z).IsSolid())
            AddFaceBottom(x, y, z);

        // Add front face
        if (z + 1 >= CHUNK_SIZE_Z || !chunk.GetBlock(x, y, z + 1).IsSolid())
            AddFaceFront(x, y, z);

        // Add back face
        if (z == 0 || !chunk.GetBlock(x, y, z - 1).IsSolid())
            AddFaceBack(x, y, z);

    }
}

void ChunkMesh::AddFaceRight(float x, float y, float z)
{
    vertices.insert(vertices.end(), {
        x+1, y,   z,
        x+1, y,   z+1,
        x+1, y+1, z+1,
        x+1, y+1, z
    });

    indices.insert(indices.end(), {
        offset, offset+1, offset+2,
        offset+2, offset+3, offset
    });

    offset += 4;
}

void ChunkMesh::AddFaceLeft(float x, float y, float z)
{
    vertices.insert(vertices.end(), {
        x, y,   z,
        x, y+1, z,
        x, y+1, z+1,
        x, y,   z+1
    });

    indices.insert(indices.end(), {
        offset, offset+1, offset+2,
        offset+2, offset+3, offset
    });

    offset += 4;
}

void ChunkMesh::AddFaceTop(float x, float y, float z)
{
    vertices.insert(vertices.end(), {
        x,   y+1, z,
        x+1, y+1, z,
        x+1, y+1, z+1,
        x,   y+1, z+1
    });

    indices.insert(indices.end(), {
        offset, offset+1, offset+2,
        offset+2, offset+3, offset
    });

    offset += 4;
}

void ChunkMesh::AddFaceBottom(float x, float y, float z)
{
    vertices.insert(vertices.end(), {
        x,   y, z,
        x+1, y, z,
        x+1, y, z+1,
        x,   y, z+1
    });

    indices.insert(indices.end(), {
        offset, offset+1, offset+2,
        offset+2, offset+3, offset
    });

    offset += 4;
}

void ChunkMesh::AddFaceFront(float x, float y, float z)
{
    vertices.insert(vertices.end(), {
        x,   y,   z+1,
        x+1, y,   z+1,
        x+1, y+1, z+1,
        x,   y+1, z+1
    });

    indices.insert(indices.end(), {
        offset, offset+1, offset+2,
        offset+2, offset+3, offset
    });

    offset += 4;
}

void ChunkMesh::AddFaceBack(float x, float y, float z)
{
    vertices.insert(vertices.end(), {
        x,   y,   z,
        x,   y+1, z,
        x+1, y+1, z,
        x+1, y,   z
    });

    indices.insert(indices.end(), {
        offset, offset+1, offset+2,
        offset+2, offset+3, offset
    });

    offset += 4;
}

