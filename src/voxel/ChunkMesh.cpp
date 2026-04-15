#include "ChunkMesh.h"

#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Renderer.h"
#include "renderer/Texture.h"
#include "core/Camera.h"

ChunkMesh::ChunkMesh(const ChunkContext& ctx) {
    m_chunkContext = std::make_unique<ChunkContext>(ctx);
}

ChunkMesh::~ChunkMesh() = default;

void ChunkMesh::Build() {
    ClearCPU();
    GenerateGeometry();
}

void ChunkMesh::Update() {
    ClearCPU();
    GenerateGeometry();
}

void ChunkMesh::ClearCPU() {
    m_vertices.clear();
    m_indices.clear();
    m_offset = 0;
}

void ChunkMesh::GenerateGeometry() {
    Chunk chunk = m_chunkContext->Center;

    float cordX = chunk.GetPosition().x;
    float cordY = chunk.GetPosition().y;
    float cordZ = chunk.GetPosition().z;

    for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x) 
    for (uint32_t y = 0; y < CHUNK_SIZE_Y; ++y)
    for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {
        Block block = chunk.GetBlock(x, y, z);

        if (!block.IsSolid())
            continue;

        for(auto& dir : { 
                    Direction::Right, Direction::Left,
                    Direction::Top, Direction::Bottom,
                    Direction::Front, Direction::Back
                }) {
            if (ShouldRenderFace(x, y, z, dir))
                AddFace(x+cordX, y+cordY, z+cordZ, dir, block);
        }

    }
}

bool ChunkMesh::ShouldRenderFace(int32_t x, int32_t y, int32_t z, Direction direction) {
    const Chunk& chunk = m_chunkContext->Center;
    const Chunk* adj = nullptr;

    auto isAir = [&](int nx, int ny, int nz, const Chunk* adjacent) {
        if (adjacent != nullptr) {
            return !adjacent->GetBlock(nx, ny, nz).IsSolid();
        }
        return true;
    };

    switch (direction) {
        case Direction::Right : { 
            if (x + 1 >= CHUNK_SIZE_X) {
                return isAir(0, y, z, m_chunkContext->Right);
            }
            return !chunk.GetBlock(x + 1, y, z).IsSolid();
        }
        case Direction::Left : { 
            if (x == 0) {
                return isAir(CHUNK_SIZE_X-1, y, z, m_chunkContext->Left);
            }
            return !chunk.GetBlock(x - 1, y, z).IsSolid();
        }
        case Direction::Top : { 
            if (y + 1 >= CHUNK_SIZE_Y) {
                return isAir(x, 0, z, m_chunkContext->Top);
            }
            return !chunk.GetBlock(x, y + 1, z).IsSolid();
        }
        case Direction::Bottom : { 
            if (y == 0) {
                return isAir(x, CHUNK_SIZE_Y-1, z, m_chunkContext->Bottom);
            }
            return !chunk.GetBlock(x, y - 1, z).IsSolid();
        }
        case Direction::Front : { 
            if (z + 1 >= CHUNK_SIZE_Z) {
                return isAir(x, y, 0, m_chunkContext->Front);
            }
            return !chunk.GetBlock(x, y, z + 1).IsSolid();
        }
        case Direction::Back : { 
            if (z == 0) {
                return isAir(x, y, CHUNK_SIZE_Z-1, m_chunkContext->Back);
            }
            return !chunk.GetBlock(x, y, z - 1).IsSolid();
        }
    }

    return false;
}

void ChunkMesh::AddFace(float x, float y, float z, Direction direction, Block block) {
    BlockTextures textures = GetBlockTextures(block.GetType());

    switch (direction) {

    case Direction::Right: {
        m_vertices.insert(m_vertices.end(), {
            Vertex{ glm::vec3(x+1, y,   z  ) },
            Vertex{ glm::vec3(x+1, y,   z+1) },
            Vertex{ glm::vec3(x+1, y+1, z+1) },
            Vertex{ glm::vec3(x+1, y+1, z  ) }
        });
        break;
    }

    case Direction::Left: {
        m_vertices.insert(m_vertices.end(), {
            Vertex{ glm::vec3(x, y,   z  ) },
            Vertex{ glm::vec3(x, y,   z+1) },
            Vertex{ glm::vec3(x, y+1, z+1) },
            Vertex{ glm::vec3(x, y+1, z  ) }
        });
        break;
    }

    case Direction::Top: {
        m_vertices.insert(m_vertices.end(), {
            Vertex{ glm::vec3(x,   y+1, z  ) },
            Vertex{ glm::vec3(x+1, y+1, z  ) },
            Vertex{ glm::vec3(x+1, y+1, z+1) },
            Vertex{ glm::vec3(x,   y+1, z+1) }
        });
        break;
    }

    case Direction::Bottom: {
        m_vertices.insert(m_vertices.end(), {
            Vertex{ glm::vec3(x,   y, z  ) },
            Vertex{ glm::vec3(x,   y, z+1) },
            Vertex{ glm::vec3(x+1, y, z+1) },
            Vertex{ glm::vec3(x+1, y, z  ) }
        });
        break;
    }

    case Direction::Front: {
        m_vertices.insert(m_vertices.end(), {
            Vertex{ glm::vec3(x,   y,   z+1) },
            Vertex{ glm::vec3(x+1, y,   z+1) },
            Vertex{ glm::vec3(x+1, y+1, z+1) },
            Vertex{ glm::vec3(x,   y+1, z+1) }
        });
        break;
    }

    case Direction::Back: {
        m_vertices.insert(m_vertices.end(), {
            Vertex{ glm::vec3(x,   y,   z) },
            Vertex{ glm::vec3(x,   y+1, z) },
            Vertex{ glm::vec3(x+1, y+1, z) },
            Vertex{ glm::vec3(x+1, y,   z) }
        });
        break;
    }

    }

    m_indices.insert(m_indices.end(), {
        m_offset, m_offset+1, m_offset+2,
        m_offset+2, m_offset+3, m_offset
    });
    m_offset += 4;
}

