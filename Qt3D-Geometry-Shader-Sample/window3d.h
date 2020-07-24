#ifndef WINDOW3D_H
#define WINDOW3D_H

#include <Qt3DExtras/Qt3DWindow>

#include <Qt3DRender/QCamera>

#include <Qt3DExtras/QForwardRenderer>

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

    void initCamera();
    void initRootEntity();
    void initClearColor();
};

#endif // WINDOW3D_H
