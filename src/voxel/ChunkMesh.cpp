#include "ChunkMesh.h"

#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Renderer.h"
#include "core/Camera.h"

ChunkMesh::ChunkMesh() {
    m_vao = std::make_unique<VertexArray>();
}

ChunkMesh::~ChunkMesh() = default;

void ChunkMesh::Draw(Renderer& renderer, Camera& camera) {
    renderer.Draw(*m_vao, camera);
}

void ChunkMesh::Build(const ChunkContext& chunkContext) {
    m_vertices.clear();
    m_indices.clear();
    offset = 0;

    GenerateGeometry(chunkContext);
    
    auto vbo = std::make_unique<VertexBuffer>(m_vertices.data(), m_vertices.size() * sizeof(float));
    auto ibo = std::make_unique<IndexBuffer>(m_indices.data(), m_indices.size());

    m_ref_vbo = vbo.get();
    m_ref_ibo = ibo.get();

    BufferLayout layout;
    layout.Push<glm::vec3>("aPos");

    m_vao = std::make_unique<VertexArray>();
    m_vao->AddVertexBuffer(std::move(vbo), layout);
    m_vao->SetIndexBuffer(std::move(ibo));
}

void ChunkMesh::Update(const ChunkContext& chunkContext) {
    m_vertices.clear();
    m_indices.clear();
    offset = 0;
    
    GenerateGeometry(chunkContext);

    // Update
    m_ref_vbo->SetData(m_vertices.data(), m_vertices.size() * sizeof(float));
    m_ref_ibo->SetData(m_indices.data(), m_indices.size() * sizeof(unsigned int));
}

void ChunkMesh::GenerateGeometry(const ChunkContext& chunkContext) {
    Chunk chunk = chunkContext.Center;
    
    if (chunk.GetBlock(0, 0, 0).GetType() == BlockType::Grass)
        std::cout << "Grass!" << std::endl;
    else
        std::cout << "NoGrass" << std::endl;

    int cordX = chunk.GetPosition().x;
    int cordY = chunk.GetPosition().y;
    int cordZ = chunk.GetPosition().z;

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
            if (ShouldRenderFace(chunkContext, x, y, z, dir))
                AddFace(x+cordX, y+cordY, z+cordZ, dir);
        }

    }
}

bool ChunkMesh::ShouldRenderFace(const ChunkContext& ctx, int32_t x, int32_t y, int32_t z, Direction direction) {
    const Chunk chunk = ctx.Center;
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
                return isAir(0, y, z, ctx.Right);
            }
            return !chunk.GetBlock(x + 1, y, z).IsSolid();
        }
        case Direction::Left : { 
            if (x + 1 >= CHUNK_SIZE_X) {
                return isAir(CHUNK_SIZE_X-1, y, z, ctx.Left);
            }
            return !chunk.GetBlock(x - 1, y, z).IsSolid();
        }
        case Direction::Top : { 
            if (x + 1 >= CHUNK_SIZE_X) {
                return isAir(x, 0, z, ctx.Top);
            }
            return !chunk.GetBlock(x, y + 1, z).IsSolid();
        }
        case Direction::Bottom : { 
            if (x + 1 >= CHUNK_SIZE_X) {
                return isAir(0, CHUNK_SIZE_Y-1, z, ctx.Bottom);
            }
            return !chunk.GetBlock(x, y - 1, z).IsSolid();
        }
        case Direction::Front : { 
            if (x + 1 >= CHUNK_SIZE_X) {
                return isAir(x, y, 0, ctx.Front);
            }
            return !chunk.GetBlock(x, y, z + 1).IsSolid();
        }
        case Direction::Back : { 
            if (x + 1 >= CHUNK_SIZE_X) {
                return isAir(x, y, CHUNK_SIZE_Z-1, ctx.Back);
            }
            return !chunk.GetBlock(x, y, z - 1).IsSolid();
        }
    }

    return false;
}

void ChunkMesh::AddFace(float x, float y, float z, Direction direction) {
    switch (direction) {
        case Direction::Right : {
            m_vertices.insert(m_vertices.end(), {
                x+1, y,   z,
                x+1, y,   z+1,
                x+1, y+1, z+1,
                x+1, y+1, z
            });

            break;
        }

        case Direction::Left : {
            m_vertices.insert(m_vertices.end(), {
                x, y,   z,
                x, y+1, z,
                x, y+1, z+1,
                x, y,   z+1
            });

            break;
        }

        case Direction::Top : {
            m_vertices.insert(m_vertices.end(), {
                x,   y+1, z,
                x+1, y+1, z,
                x+1, y+1, z+1,
                x,   y+1, z+1
            });

            break;
        }

        case Direction::Bottom : {
            m_vertices.insert(m_vertices.end(), {
                x,   y, z,
                x+1, y, z,
                x+1, y, z+1,
                x,   y, z+1
            });

            break;
        }

        case Direction::Front : {
            m_vertices.insert(m_vertices.end(), {
                x,   y,   z+1,
                x+1, y,   z+1,
                x+1, y+1, z+1,
                x,   y+1, z+1
            });

            break;
        }

        case Direction::Back : {
            m_vertices.insert(m_vertices.end(), {
                x,   y,   z,
                x,   y+1, z,
                x+1, y+1, z,
                x+1, y,   z
            });

            break;
        }
    }

    m_indices.insert(m_indices.end(), {
        offset, offset+1, offset+2,
        offset+2, offset+3, offset
    });

    offset += 4;
}

