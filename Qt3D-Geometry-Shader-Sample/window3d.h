#ifndef WINDOW3D_H
#define WINDOW3D_H

#include <Qt3DCore/QTransform>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QSphereMesh>

#include <Qt3DRender/QCamera>
#include <Qt3DRender/QDirectionalLight>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>

#include "spherematerial.h"
#include "customsphere.h"

class Window3D : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    Window3D();

    Qt3DCore::QEntity* getRootEntity();
    Qt3DRender::QCamera* getCamera();

private:
    Qt3DRender::QCamera* defaultCamera;
    Qt3DCore::QEntity* rootEntity;
    Qt3DCore::QEntity* sceneEntity;

    void initCamera();
    void initRootEntity();
    void initClearColor();
    void initLight();

    void initScene();
    void createSphere(QVector3D position);
    void createCustomSphere(QVector3D position);
};

#endif // WINDOW3D_H
