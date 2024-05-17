#include "mesh.h"

void Material::SetToProgram(const Program* program) const {
    int textureCount = 0;
    if (diffuse) {
        glActiveTexture(GL_TEXTURE0 + textureCount);
        program->SetUniform("material.diffuse", textureCount);
        diffuse->Bind();
        textureCount++;
    }
    if (specular) {
        glActiveTexture(GL_TEXTURE0 + textureCount);
        program->SetUniform("material.specular", textureCount);
        specular->Bind();
        textureCount++;
    }
    glActiveTexture(GL_TEXTURE0);
    program->SetUniform("material.shininess", shininess);
}

MeshUPtr Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, uint32_t primitiveType) {
    auto mesh = MeshUPtr(new Mesh());
    mesh->Init(vertices, indices, primitiveType);
    return std::move(mesh);
}

void Mesh::Init(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, uint32_t primitiveType) {
    m_vertexLayout = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices.data(), sizeof(Vertex), vertices.size());
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices.data(), sizeof(uint32_t), indices.size());

    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
    m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, normal));
    m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, texCoord));
}

void Mesh::Draw(const Program* program) const {
    m_vertexLayout->Bind();
    if (m_material) {
        m_material->SetToProgram(program);
    }
    glDrawElements(m_primitiveType, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
}

MeshUPtr Mesh::CreateBox() {
    std::vector<Vertex> vertices = { // pos.xyz, normal.xyz, texcoord.uv
        Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
        Vertex { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f) },

        Vertex { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f) },
        Vertex { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f) },

        Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
        Vertex { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f) },

        Vertex { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
        Vertex { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f) },

        Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
        Vertex { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f) },

        Vertex { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
        Vertex { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
    };
        
    std::vector<uint32_t> indices = {
        0,  2,  1,  2,  0,  3,
        4,  5,  6,  6,  7,  4,
        8,  9, 10, 10, 11,  8,
        12, 14, 13, 14, 12, 15,
        16, 17, 18, 18, 19, 16,
        20, 22, 21, 22, 20, 23,
    };

    return Create(vertices, indices, GL_TRIANGLES);
}

MeshUPtr Mesh::CreatePlane() {
    std::vector<Vertex> vertices = {
        Vertex { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3( 0.0f,  0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        Vertex { glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3( 0.0f,  0.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3( 0.0f,  0.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3( 0.0f,  0.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
    };

    std::vector<uint32_t> indices = {
        0,  1,  2,  2,  3,  0,
    };

    return Create(vertices, indices, GL_TRIANGLES);
}

void triangles(int level, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c,
                     std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, int& numVert) {
    if (level <= 0) {
        vertices.push_back(Vertex{ a, glm::normalize(a), glm::vec2(0.0f, 0.0f) });
        vertices.push_back(Vertex{ b, glm::normalize(b), glm::vec2(0.0f, 0.0f) });
        vertices.push_back(Vertex{ c, glm::normalize(c), glm::vec2(0.0f, 0.0f) });

        indices.push_back(numVert++);
        indices.push_back(numVert++);
        indices.push_back(numVert++);
    } else {
        glm::vec3 ab = glm::normalize(a + b);
        glm::vec3 bc = glm::normalize(b + c);
        glm::vec3 ca = glm::normalize(c + a);

        triangles(level - 1, a, ab, ca, vertices, indices, numVert);
        triangles(level - 1, b, bc, ab, vertices, indices, numVert);
        triangles(level - 1, c, ca, bc, vertices, indices, numVert);
        triangles(level - 1, ab, bc, ca, vertices, indices, numVert);
    }
}

MeshUPtr Mesh::CreateSphere() {
    int level = 4;
    std::vector<glm::vec3> v = {
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { -1.0f, 0.0f, 0.0f },
        { 0.0f, -1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, -1.0f }
    };

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    int numVert = 0;

    triangles(level, v[0], v[1], v[4], vertices, indices, numVert);
    triangles(level, v[1], v[2], v[4], vertices, indices, numVert);
    triangles(level, v[2], v[3], v[4], vertices, indices, numVert);
    triangles(level, v[3], v[0], v[4], vertices, indices, numVert);
    triangles(level, v[1], v[0], v[5], vertices, indices, numVert);
    triangles(level, v[2], v[1], v[5], vertices, indices, numVert);
    triangles(level, v[3], v[2], v[5], vertices, indices, numVert);
    triangles(level, v[0], v[3], v[5], vertices, indices, numVert);

    return Create(vertices, indices, GL_TRIANGLES);
}

// MeshUPtr Mesh::CreateSphere() {
//     std::vector<Vertex> vertices;
//     std::vector<uint32_t> indices;
//     float radius = 1.0f;
//     int numSegments = 32;
//
//     for (int y = 0; y <= numSegments; ++y) {
//         for (int x = 0; x <= numSegments; ++x) {
//             float xSegment = static_cast<float>(x) / static_cast<float>(numSegments);
//             float ySegment = static_cast<float>(y) / static_cast<float>(numSegments);
//             float xPos = radius * std::cos(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>());
//             float yPos = radius * std::cos(ySegment * glm::pi<float>());
//             float zPos = radius * std::sin(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>());

//             vertices.push_back(Vertex{
//                 glm::vec3(xPos, yPos, zPos),
//                 glm::normalize(glm::vec3(xPos, yPos, zPos)),
//                 glm::vec2(xSegment, ySegment)
//             });
//         }
//     }

//     for (int y = 0; y < numSegments; ++y) {
//         for (int x = 0; x < numSegments; ++x) {
//             indices.push_back((y + 1) * (numSegments + 1) + x);
//             indices.push_back(y * (numSegments + 1) + x);
//             indices.push_back(y * (numSegments + 1) + x + 1);

//             indices.push_back((y + 1) * (numSegments + 1) + x);
//             indices.push_back(y * (numSegments + 1) + x + 1);
//             indices.push_back((y + 1) * (numSegments + 1) + x + 1);
//         }
//     }

//     return Create(vertices, indices, GL_TRIANGLES);
// }