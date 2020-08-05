#include "customwalls.h"

CustomWall::CustomWall(QVector2D p0, QVector2D p1, float h, QObject* parent)
    : p0(p0)
    , p1(p1)
    , h(h)
    , QObject(parent)
{
    uuid = QUuid::createUuid().toString();
}

QString CustomWall::getUUID()
{
    return uuid;
}

QVector2D CustomWall::getP0()
{
    return p0;
}

QVector2D CustomWall::getP1()
{
    return p1;
}

float CustomWall::getH()
{
    return h;
}

CustomWalls::CustomWalls(int count, Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
{
    initCustomRandomWalls(count);
    initGeometry();
}

void CustomWalls::initCustomRandomWalls(int count)
{
    for (int i = 0; i < count; i++) {

        qDebug() << QString("%1 из %2").arg(i).arg(count);
        QVector2D center = generateRandomVector2D();
        QVector2D wh = generateRandomVector2D(0.5f) + QVector2D(0.6f, 0.6f);
        CustomWall* customWall0 = new CustomWall(QVector2D(center.x() - wh.x(), center.y() - wh.y()), QVector2D(center.x() - wh.x(), center.y() + wh.y()), generateRandomFloat(), this);
        CustomWall* customWall1 = new CustomWall(QVector2D(center.x() - wh.x(), center.y() + wh.y()), QVector2D(center.x() + wh.x(), center.y() + wh.y()), generateRandomFloat(), this);
        CustomWall* customWall2 = new CustomWall(QVector2D(center.x() + wh.x(), center.y() + wh.y()), QVector2D(center.x() + wh.x(), center.y() - wh.y()), generateRandomFloat(), this);
        CustomWall* customWall3 = new CustomWall(QVector2D(center.x() + wh.x(), center.y() - wh.y()), QVector2D(center.x() - wh.x(), center.y() - wh.y()), generateRandomFloat(), this);

        customWalls.insert(customWall0->getUUID(), customWall0);
        customWalls.insert(customWall1->getUUID(), customWall1);
        customWalls.insert(customWall2->getUUID(), customWall2);
        customWalls.insert(customWall3->getUUID(), customWall3);
    }
}

void CustomWalls::initGeometry()
{
    int count = customWalls.count();
    int count_floats_in_wall = 3 * 2;
    int count_of_floats = count * count_floats_in_wall;

    QByteArray pointsData;
    pointsData.resize(count_of_floats * sizeof(float));

    float* rawPointsData = reinterpret_cast<float *>(pointsData.data());

    QList<QString> keys = customWalls.keys();
    for (int i = 0; i < count; i++) {
        QString uuid = keys[i];
        CustomWall* customWall = customWalls[uuid];

        rawPointsData[i * count_floats_in_wall + 0] = customWall->getP0().x();
        rawPointsData[i * count_floats_in_wall + 1] = 0.0f;
        rawPointsData[i * count_floats_in_wall + 2] = customWall->getP0().y();
        rawPointsData[i * count_floats_in_wall + 3] = customWall->getP1().x();
        rawPointsData[i * count_floats_in_wall + 4] = 0.0f;
        rawPointsData[i * count_floats_in_wall + 5] = customWall->getP1().y();

        qDebug() << QString("RAW %1 из %2").arg(i).arg(count);
    }

    QByteArray indexData;
    indexData.resize(count * 2 * sizeof(uint));

    uint* rawIndexData;
    rawIndexData = reinterpret_cast<uint *>(indexData.data());

    for (uint i = 0; i < (uint)count * 2u; i++) {
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
    indexAttribute->setCount(count * 2);

    //установка атрибутов геометрии
    customGeometry->addAttribute(positionAttribute);
    customGeometry->addAttribute(indexAttribute);

    //установка геометрии рендереру
    customRenderer->setInstanceCount(1);
    customRenderer->setFirstVertex(0);
    customRenderer->setFirstInstance(0);
    customRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    customRenderer->setGeometry(customGeometry);

    this->addComponent(customRenderer);
}

QVector2D CustomWalls::generateRandomVector2D(float max)
{
    float x = max * (float)(QRandomGenerator::global()->generateDouble() - 0.5);
    float y = max * (float)(QRandomGenerator::global()->generateDouble() - 0.5);

    return QVector2D(x, y);
}

float CustomWalls::generateRandomFloat(float max)
{
    return max * (float)(QRandomGenerator::global()->generateDouble());
}
