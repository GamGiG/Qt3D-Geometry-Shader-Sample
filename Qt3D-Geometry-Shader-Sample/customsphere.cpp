#include "customsphere.h"

CustomSphere::CustomSphere(QVector3D position, Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , position(position)
{
    initGeometry(position);
}

void CustomSphere::initGeometry(QVector3D position)
{
    QByteArray pointsData;
    pointsData.resize(3 * sizeof(float));

    float* rawPointsData = reinterpret_cast<float *>(pointsData.data());
    rawPointsData[0] = position.x();
    rawPointsData[1] = position.y();
    rawPointsData[2] = position.z();

    QByteArray indexData;
    indexData.resize(1 * sizeof(ushort));

    Qt3DRender::QGeometryRenderer *customRenderer = new Qt3DRender::QGeometryRenderer();
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
