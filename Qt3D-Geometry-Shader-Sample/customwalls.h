#ifndef CUSTOMWALLS_H
#define CUSTOMWALLS_H

#include <QUuid>
#include <QRandomGenerator>
#include <QByteArray>

#include <QVector3D>
#include <QVector2D>

#include <Qt3DCore/QEntity>

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>

class CustomWall : public QObject
{
    Q_OBJECT
public:
    CustomWall(QVector2D p0, QVector2D p1, float h, QObject *parent = nullptr);
    QString getUUID();

    QVector2D getP0();
    QVector2D getP1();
    float getH();

private:
    QString uuid;

    QVector2D p0;
    QVector2D p1;

    float h;

signals:
    void wallChanged();
};

class CustomWalls : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    CustomWalls(int count = 100, Qt3DCore::QNode* parent = nullptr);

    static QVector2D generateRandomVector2D(float max = 100.0f);
    static float generateRandomFloat(float max = 1.0f);
private:
    QMap<QString, CustomWall*> customWalls;
    void initCustomRandomWalls(int count);

    void initGeometry();


};

#endif // CUSTOMWALLS_H
