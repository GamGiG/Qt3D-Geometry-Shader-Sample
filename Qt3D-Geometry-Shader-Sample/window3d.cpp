#include "window3d.h"

Window3D::Window3D()
    : Qt3DExtras::Qt3DWindow()
{
    initClearColor();
    initRootEntity();
    initCamera();
}

Qt3DRender::QCamera* Window3D::getCamera()
{
    return defaultCamera;
}

Qt3DCore::QEntity* Window3D::getRootEntity()
{
    return rootEntity;
}

void Window3D::initCamera()
{
    defaultCamera = this->camera();
    defaultCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);

    QVector3D position = QVector3D(0, 10, 0);
    QVector3D up = QVector3D(1, 0, 0);
    QVector3D center = QVector3D(0, 0, 0);

    defaultCamera->setPosition(position);
    defaultCamera->setUpVector(up);
    defaultCamera->setViewCenter(center);
    defaultCamera->setAspectRatio(1);
    defaultCamera->setFieldOfView(60);
    defaultCamera->setFarPlane(100.0f);
    defaultCamera->setNearPlane(1.0f);
}

void Window3D::initRootEntity()
{
    rootEntity = new Qt3DCore::QEntity();
    this->setRootEntity(rootEntity);
}

void Window3D::initClearColor()
{
    this->defaultFrameGraph()->setClearColor(QColor::fromRgbF(0.1f, 0.2f, 0.3f));
}
