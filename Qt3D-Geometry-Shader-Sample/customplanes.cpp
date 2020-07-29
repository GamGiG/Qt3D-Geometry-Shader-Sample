#include "customplanes.h"

CustomPlanes::CustomPlanes(int count, Qt3DCore::QNode *parent)
     : Qt3DCore::QEntity(parent)
     , count(count)
{    
    initGeometry();

    //initGeometry2();
}

void CustomPlanes::initGeometry()
{
    QByteArray pointsData;
    pointsData.resize(count * 3 * sizeof(float));

    float* rawPointsData = reinterpret_cast<float *>(pointsData.data());

    for (int i = 0; i < count; i++) {
        double x = 100.0 * (QRandomGenerator::global()->generateDouble() - 0.5);
        double y = 100.0 * (QRandomGenerator::global()->generateDouble() - 0.5);

        rawPointsData[i * 3 + 0] = (float)x;
        rawPointsData[i * 3 + 1] = 0.1f;
        rawPointsData[i * 3 + 2] = (float)y;
    }

    QByteArray indexData;
    indexData.resize(count * sizeof(uint));

    uint* rawIndexData;
    rawIndexData = reinterpret_cast<uint *>(indexData.data());

    for (uint i = 0; i < count; i++) {
        rawIndexData[i] = i;
    }

    Qt3DRender::QGeometryRenderer *customRenderer = new Qt3DRender::QGeometryRenderer();
    Qt3DRender::QGeometry *customGeometry = new Qt3DRender::QGeometry(customRenderer);

    //вершинный и индексный буффер
    Qt3DRender::QBuffer *vertexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, customGeometry);
    Qt3DRender::QBuffer *indexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, customGeometry);

    vertexBuffer->setData(pointsData);
    indexBuffer->setData(indexData);

    //атрибут вершин
    Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute();
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setDataType(Qt3DRender::QAttribute::Float);
    positionAttribute->setDataSize(3);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(count);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());

    //атрибут индексов
    Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute();
    indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setDataType(Qt3DRender::QAttribute::UnsignedInt);
    indexAttribute->setDataSize(1);
    indexAttribute->setByteOffset(0);
    indexAttribute->setByteStride(sizeof(uint));
    indexAttribute->setCount(count);

    //установка атрибутов геометрии
    customGeometry->addAttribute(positionAttribute);
    customGeometry->addAttribute(indexAttribute);

    //установка геометрии рендереру
    customRenderer->setInstanceCount(1);
    customRenderer->setFirstVertex(0);
    customRenderer->setFirstInstance(0);
    customRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
    customRenderer->setGeometry(customGeometry);

    this->addComponent(customRenderer);
}

void CustomPlanes::initGeometry2()
{
    QByteArray pointsData;
    pointsData.resize(1 * 3 * sizeof(float));

    float* rawPointsData = reinterpret_cast<float *>(pointsData.data());

    for (int i = 0; i < 1; i++) {
        double x = 100.0 * (QRandomGenerator::global()->generateDouble() - 0.5);
        double y = 100.0 * (QRandomGenerator::global()->generateDouble() - 0.5);

        rawPointsData[i * 3 + 0] = (float)x;
        rawPointsData[i * 3 + 1] = 0.0f;
        rawPointsData[i * 3 + 2] = (float)y;
    }

    QByteArray indexData;
    indexData.resize(count * sizeof(ushort));

    ushort* rawIndexData;
    rawIndexData = reinterpret_cast<ushort *>(indexData.data());

    for (ushort i = 0; i < 1; i++) {
        rawIndexData[i] = i;
    }

    Qt3DRender::QGeometryRenderer *customRenderer = new Qt3DRender::QGeometryRenderer(this);
    Qt3DRender::QGeometry *customGeometry = new Qt3DRender::QGeometry(customRenderer);

    //вершинный и индексный буффер
    Qt3DRender::QBuffer *pointsBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, customGeometry);
    Qt3DRender::QBuffer *indexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, customGeometry);

    pointsBuffer->setData(pointsData);
    indexBuffer->setData(indexData);

    //атрибут вершин
    Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute();
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(pointsBuffer);
    positionAttribute->setDataType(Qt3DRender::QAttribute::Float);
    positionAttribute->setDataSize(3);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(1);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());

    //атрибут индексов
    Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute();
    indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setDataType(Qt3DRender::QAttribute::UnsignedShort);
    indexAttribute->setDataSize(1);
    indexAttribute->setByteOffset(0);
    indexAttribute->setByteStride(sizeof(ushort));
    indexAttribute->setCount(1);

    //установка атрибутов геометрии
    customGeometry->addAttribute(positionAttribute);
    customGeometry->addAttribute(indexAttribute);

    //установка геометрии рендереру
    customRenderer->setInstanceCount(1);
    customRenderer->setFirstVertex(0);
    customRenderer->setFirstInstance(0);
    customRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
    customRenderer->setGeometry(customGeometry);

    this->addComponent(customRenderer);
}
