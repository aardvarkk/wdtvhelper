#ifndef MIRROR_H
#define MIRROR_H

#include <QUrl>

class Mirror
{
public:
    Mirror();

    enum MirrorType
    {
      kUnknown     = 0,
      kXMLFiles    = 1 << 0,
      kBannerFiles = 1 << 1,
      kZipFiles    = 1 << 2
    };

    QUrl url;
    MirrorType mirror_type;

};

#endif // MIRROR_H
