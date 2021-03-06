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

        QVector2D center = generateRandomVector2D();
        QVector2D wh = generateRandomVector2D(0.5f) + QVector2D(0.6f, 0.6f);
        float h = generateRandomFloat(5.0f);

        CustomWall* customWall0 = new CustomWall(QVector2D(center.x() - wh.x(), center.y() - wh.y()), QVector2D(center.x() - wh.x(), center.y() + wh.y()), h, this);
        CustomWall* customWall1 = new CustomWall(QVector2D(center.x() - wh.x(), center.y() + wh.y()), QVector2D(center.x() + wh.x(), center.y() + wh.y()), h, this);
        CustomWall* customWall2 = new CustomWall(QVector2D(center.x() + wh.x(), center.y() + wh.y()), QVector2D(center.x() + wh.x(), center.y() - wh.y()), h, this);
        CustomWall* customWall3 = new CustomWall(QVector2D(center.x() + wh.x(), center.y() - wh.y()), QVector2D(center.x() - wh.x(), center.y() - wh.y()), h, this);

        customWalls.insert(customWall0->getUUID(), customWall0);
        customWalls.insert(customWall1->getUUID(), customWall1);
        customWalls.insert(customWall2->getUUID(), customWall2);
        customWalls.insert(customWall3->getUUID(), customWall3);
    }
}

//add wall
void CustomWalls::AddWall(CustomWall *wall)
{
    customWalls.insert(wall->getUUID(), wall);
    initGeometry();
}

void CustomWalls::AddWalls(QList<CustomWall *> walls)
{
    for (int i = 0; i < walls.count(); i++) {
        customWalls.insert(walls[i]->getUUID(), walls[i]);
    }
    initGeometry();
}

void CustomWalls::initGeometry()
{
    int count = customWalls.count();
    int count_floats_in_wall = (3 + 1) * 2;
    int count_of_floats = count * count_floats_in_wall;

    //POINTS
    QByteArray pointsData;
    pointsData.resize((count_of_floats) * sizeof(float));

    float* rawPointsData = reinterpret_cast<float *>(pointsData.data());

    QList<QString> keys = customWalls.keys();
    for (int i = 0; i < count; i++) {
        CustomWall* customWall = customWalls[keys[i]];

        rawPointsData[i * count_floats_in_wall + 0] = customWall->getP0().x();
        rawPointsData[i * count_floats_in_wall + 1] = 0.0f;
        rawPointsData[i * count_floats_in_wall + 2] = customWall->getP0().y();
        rawPointsData[i * count_floats_in_wall + 3] = customWall->getH();

        rawPointsData[i * count_floats_in_wall + 4] = customWall->getP1().x();
        rawPointsData[i * count_floats_in_wall + 5] = 0.0f;
        rawPointsData[i * count_floats_in_wall + 6] = customWall->getP1().y();
        rawPointsData[i * count_floats_in_wall + 7] = customWall->getH();

    }

    //INDEX
    QByteArray indexData;
    indexData.resize(count * 2 * sizeof(uint));

    uint* rawIndexData;
    rawIndexData = reinterpret_cast<uint *>(indexData.data());

    for (uint i = 0; i < (uint)count * 2u; i++) {
        rawIndexData[i] = i;
    }

    if (customRenderer != nullptr) {
        delete customRenderer;
    }

    customRenderer = new Qt3DRender::QGeometryRenderer(this);
    Qt3DRender::QGeometry *customGeometry = new Qt3DRender::QGeometry(customRenderer);

    //вершинный и индексный буффер
    Qt3DRender::QBuffer *vertexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, customGeometry);
    Qt3DRender::QBuffer *indexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, customGeometry);

    vertexBuffer->setData(pointsData);
    indexBuffer->setData(indexData);

    //атрибут вершин
    Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute(customGeometry);
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setDataType(Qt3DRender::QAttribute::Float);
    positionAttribute->setDataSize(3);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(4 * sizeof(float));
    positionAttribute->setCount(count * 2);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());

    //атрибут высот
    Qt3DRender::QAttribute *heightAttribute = new Qt3DRender::QAttribute(customGeometry);
    heightAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    heightAttribute->setBuffer(vertexBuffer);
    heightAttribute->setDataType(Qt3DRender::QAttribute::Float);
    heightAttribute->setDataSize(1);
    heightAttribute->setByteOffset(3 * sizeof(float));
    heightAttribute->setByteStride(4 * sizeof(float));
    heightAttribute->setCount(count * 2);
    heightAttribute->setName("height");

    //атрибут индексов
    Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute(customGeometry);
    indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setDataType(Qt3DRender::QAttribute::UnsignedInt);
    indexAttribute->setDataSize(1);
    indexAttribute->setByteOffset(0);
    indexAttribute->setByteStride(sizeof(uint));
    indexAttribute->setCount(count * 2);

    //установка атрибутов геометрии
    customGeometry->addAttribute(positionAttribute);
    customGeometry->addAttribute(heightAttribute);
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
