#ifndef WINDOW3D_H
#define WINDOW3D_H

#include <QRandomGenerator>

#include <Qt3DCore/QTransform>

#include <Qt3DRender/QCamera>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DRender/QSortPolicy>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPlaneMesh>

#include "planematerial.h"
#include "customplane.h"
#include "customplanes.h"

#include "wallsmaterial.h"
#include "customwalls.h"

class Window3D : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    Window3D();

    Qt3DCore::QEntity* getRootEntity();
    Qt3DRender::QCamera* getCamera();

    CustomWalls* customWalls;

private:
    Qt3DRender::QCamera* defaultCamera;
    Qt3DCore::QEntity* rootEntity;
    Qt3DCore::QEntity* sceneEntity;

    void initCamera();
    void initRootEntity();
    void initClearColor();
    void initLight();
    void initController();

    void initScene();

    void createBigPlane();
    void createSphere(QVector3D position);
    void createCustomPlane(QVector3D position);
    void createRandomCustomsPlanes(int count = 10);
    void createRandomArrayCustomPlanes(int count = 10);
    void createRandomArrayCustomWalls(int count = 10);
};

#endif // WINDOW3D_H
