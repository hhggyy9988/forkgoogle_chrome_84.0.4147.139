// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_SEARCH_COMMON_FILE_ICON_UTIL_H_
#define CHROME_BROWSER_UI_APP_LIST_SEARCH_COMMON_FILE_ICON_UTIL_H_

#include "base/files/file_path.h"
#include "base/macros.h"
#include "ui/gfx/image/image_skia.h"

namespace app_list {
namespace internal {

enum class IconType {
  AUDIO,
  ARCHIVE,
  CHART,
  EXCEL,
  FOLDER,
  FORM,
  GDOC,
  GDRAW,
  GENERIC,
  GSHEET,
  GSITE,
  GSLIDES,
  GTABLE,
  IMAGE,
  MAP,
  PDF,
  PPT,
  SCRIPT,
  SITES,
  TINI,
  VIDEO,
  WORD,
};

IconType GetIconTypeForPath(const base::FilePath& filepath);
int GetResourceIdForIconType(IconType icon);
int GetChipResourceIdForIconType(IconType icon);
}  // namespace internal

gfx::ImageSkia GetIconForPath(const base::FilePath& filepath);
gfx::ImageSkia GetChipIconForPath(const base::FilePath& filepath);

}  // namespace app_list

#endif  // CHROME_BROWSER_UI_APP_LIST_SEARCH_COMMON_FILE_ICON_UTIL_H_
