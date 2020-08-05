#include "wallsmaterial.h"

WallsMaterial* WallsMaterial::Instance = nullptr;
WallsGeometryEffect* WallsMaterial::Effect = nullptr;

WallsMaterial::WallsMaterial(Qt3DCore::QNode *parent)
    : Qt3DRender::QMaterial(parent)
{
    if (Instance == nullptr)
    {
        if (Effect == nullptr) {
            Effect = new WallsGeometryEffect(this);
            this->setEffect(Effect);
        }

        Qt3DRender::QTextureImage* textureImage = new Qt3DRender::QTextureImage();
        textureImage->setSource(QUrl("qrc:/Images/Images/texture_0.png"));

        Qt3DRender::QTexture2D* texture = new Qt3DRender::QTexture2D(this);
        texture->setGenerateMipMaps(true);

        texture->setFormat(Qt3DRender::QAbstractTexture::RGBAFormat);
        texture->addTextureImage(textureImage);

        Qt3DRender::QParameter* textureParameter = new Qt3DRender::QParameter(QStringLiteral("texture_diffuse1"), texture);

        this->addParameter(textureParameter);

        Instance=this;

        this->setShareable(true);
    }
}

