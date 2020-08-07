#include "window3d.h"

Window3D::Window3D()
    : Qt3DExtras::Qt3DWindow()
{
    initClearColor();
    initRootEntity();
    initScene();
    initCamera();
    initController();
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
    this->defaultFrameGraph()->setClearColor(QColor::fromRgbF(0.1f, 0.2f, 0.3f, 0.0f));
}

void Window3D::initScene()
{
    sceneEntity = new Qt3DCore::QEntity(rootEntity);

    initLight();
    createBigPlane();
    createRandomArrayCustomPlanes(10000);
    createRandomArrayCustomWalls(10);
}

void Window3D::initLight()
{
    Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(sceneEntity);

    Qt3DRender::QDirectionalLight* directionalLight = new Qt3DRender::QDirectionalLight(lightEntity);
    directionalLight->setColor(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
    directionalLight->setWorldDirection(QVector3D(-1.0f, -1.0f, -1.0f));
    lightEntity->addComponent(directionalLight);
}

void Window3D::createSphere(QVector3D position)
{
    Qt3DCore::QEntity* sphereEntity = new Qt3DCore::QEntity(sceneEntity);
    Qt3DExtras::QSphereMesh* sphereMesh = new Qt3DExtras::QSphereMesh(sphereEntity);
    sphereMesh->setRadius(1.0f);
    sphereMesh->setSlices(24);

    Qt3DExtras::QPhongMaterial* phongMaterial = new Qt3DExtras::QPhongMaterial(sphereEntity);
    phongMaterial->setDiffuse(QColor::fromRgbF(0.3f, 0.2f, 0.1f));

    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform(sphereEntity);
    transform->setTranslation(position);

    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(phongMaterial);
    sphereEntity->addComponent(transform);
}

void Window3D::createCustomPlane(QVector3D position)
{
    CustomPlane* sphereEntity = new CustomPlane(QVector3D(0.0f, 0.0f, 0.0f), sceneEntity);

    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform(sphereEntity);
    transform->setTranslation(position);

    if (PlaneMaterial::Instance == nullptr) {
        PlaneMaterial* material = new PlaneMaterial(nullptr);
        sphereEntity->addComponent(material);
    } else {
        sphereEntity->addComponent(PlaneMaterial::Instance);
    }

    sphereEntity->addComponent(transform);

}

void Window3D::createBigPlane()
{
    Qt3DCore::QEntity* entityPlane = new Qt3DCore::QEntity(sceneEntity);
    Qt3DExtras::QPlaneMesh* meshPlane = new Qt3DExtras::QPlaneMesh(entityPlane);
    meshPlane->setWidth(100.0);
    meshPlane->setHeight(100.0);
    meshPlane->setMeshResolution(QSize(2, 2));

    Qt3DExtras::QPhongMaterial* phongMaterial = new Qt3DExtras::QPhongMaterial(entityPlane);
    phongMaterial->setDiffuse(QColor::fromRgbF(0.3f, 0.2f, 0.1f));
    phongMaterial->setAmbient(QColor::fromRgbF(0.3f, 0.2f, 0.1f));

    entityPlane->addComponent(meshPlane);
    entityPlane->addComponent(phongMaterial);
}

void Window3D::createRandomCustomsPlanes(int count)
{
    for (int i = 0; i < count; i++) {
        double x = 100.0 * (QRandomGenerator::global()->generateDouble() - 0.5);
        double y = 100.0 * (QRandomGenerator::global()->generateDouble() - 0.5);
        createCustomPlane(QVector3D(x, 0, y));
    }
}

void Window3D::createRandomArrayCustomPlanes(int count)
{
    CustomPlanes* customPlanes = new CustomPlanes(count, sceneEntity);

    if (PlaneMaterial::Instance == nullptr) {
        PlaneMaterial* material = new PlaneMaterial(nullptr);
        customPlanes->addComponent(material);
    } else {
        customPlanes->addComponent(PlaneMaterial::Instance);
    }

    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform(customPlanes);
    transform->setTranslation(QVector3D(0.0, 0.0, 0.0));

    customPlanes->addComponent(transform);
}

void Window3D::createRandomArrayCustomWalls(int count)
{
    customWalls = new CustomWalls(count, sceneEntity);

    if (WallsMaterial::Instance == nullptr) {
        WallsMaterial* material = new WallsMaterial(nullptr);
        customWalls->addComponent(material);
    } else {
        customWalls->addComponent(WallsMaterial::Instance);
    }

    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform(customWalls);
    transform->setTranslation(QVector3D(0.0, 0.0, 0.0));

    customWalls->addComponent(transform);
}

void Window3D::initController()
{
    Qt3DExtras::QOrbitCameraController* controller = new Qt3DExtras::QOrbitCameraController(rootEntity);
    controller->setCamera(defaultCamera);
}
