/*
 *  Copyright (C) 2005-2020 Team Kodi (https://kodi.tv)
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include <avif/avif.h>
#include <stdint.h>

#include <kodi/addon-instance/ImageDecoder.h>

class ATTRIBUTE_HIDDEN AvifPicture : public kodi::addon::CInstanceImageDecoder
{
public:
  AvifPicture(KODI_HANDLE instance, const std::string& version)
    : CInstanceImageDecoder(instance, version)
  {
  }

  virtual ~AvifPicture()
  {
    if (image)
      avifImageDestroy(image);
    if (decoder)
      avifDecoderDestroy(decoder);

  }

  bool LoadImageFromMemory(unsigned char* buffer, unsigned int bufSize,
                           unsigned int& width, unsigned int& height) override
  {
    decoder = avifDecoderCreate();
    avifROData raw;
    raw.data = buffer;
    raw.size = bufSize;
    image = avifImageCreateEmpty();
    avifResult decodeResult = avifDecoderRead(decoder, image, &raw);
    if (decodeResult == AVIF_RESULT_OK) {
      width = image->width;
      height = image->height;
      return true;
    }
    return false;
  }

  bool Decode(unsigned char *pixels,
              unsigned int width, unsigned int height,
              unsigned int pitch, ImageFormat format) override
  {
    avifRGBImage rgb;
    avifRGBImageSetDefaults(&rgb, image);
    if (format  == ADDON_IMG_FMT_A8R8G8B8)
      rgb.format = AVIF_RGB_FORMAT_BGRA;
    else
      rgb.format = AVIF_RGB_FORMAT_RGB;
    rgb.depth = 8;
    rgb.pixels = pixels;
    rgb.rowBytes = pitch;
    avifImageYUVToRGB(image, &rgb);
    return true;
  }

private:
  avifDecoder* decoder = nullptr;
  avifImage* image = nullptr;
};

class ATTRIBUTE_HIDDEN CMyAddon : public kodi::addon::CAddonBase
{
public:
  CMyAddon() { }
  ADDON_STATUS CreateInstance(int instanceType, const std::string& instanceID, KODI_HANDLE instance, const std::string& version, KODI_HANDLE& addonInstance) override
  {
    if (instanceType == ADDON_INSTANCE_IMAGEDECODER)
    {
      addonInstance = new AvifPicture(instance, version);
      return ADDON_STATUS_OK;
    }

    return ADDON_STATUS_NOT_IMPLEMENTED;
  }
};

ADDONCREATOR(CMyAddon);
