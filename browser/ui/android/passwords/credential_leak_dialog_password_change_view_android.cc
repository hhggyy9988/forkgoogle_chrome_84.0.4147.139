// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/android/passwords/credential_leak_dialog_password_change_view_android.h"
#include <cstdint>

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/strings/string16.h"
#include "base/strings/utf_string_conversions.h"
#include "chrome/android/chrome_jni_headers/CredentialLeakDialogPasswordChangeBridge_jni.h"
#include "chrome/browser/password_manager/chrome_password_manager_client.h"
#include "chrome/browser/password_manager/credential_leak_password_change_controller_android.h"
#include "chrome/grit/generated_resources.h"
#include "components/password_manager/core/browser/password_form_manager_for_ui.h"
#include "components/password_manager/core/common/password_manager_pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/strings/grit/components_strings.h"
#include "content/public/browser/web_contents.h"
#include "ui/android/window_android.h"
#include "ui/base/l10n/l10n_util.h"

CredentialLeakDialogPasswordChangeViewAndroid::
    CredentialLeakDialogPasswordChangeViewAndroid(
        CredentialLeakPasswordChangeControllerAndroid* controller)
    : controller_(controller) {}

CredentialLeakDialogPasswordChangeViewAndroid::
    ~CredentialLeakDialogPasswordChangeViewAndroid() {
  Java_CredentialLeakDialogPasswordChangeBridge_destroy(
      base::android::AttachCurrentThread(), java_object_);
}

void CredentialLeakDialogPasswordChangeViewAndroid::Show(
    ui::WindowAndroid* window_android) {
  JNIEnv* env = base::android::AttachCurrentThread();
  java_object_.Reset(Java_CredentialLeakDialogPasswordChangeBridge_create(
      env, window_android->GetJavaObject(), reinterpret_cast<intptr_t>(this)));

  Java_CredentialLeakDialogPasswordChangeBridge_showDialog(
      env, java_object_,
      base::android::ConvertUTF16ToJavaString(env, controller_->GetTitle()),
      base::android::ConvertUTF16ToJavaString(env,
                                              controller_->GetDescription()),
      base::android::ConvertUTF16ToJavaString(
          env, controller_->GetAcceptButtonLabel()),
      controller_->ShouldShowCancelButton()
          ? base::android::ConvertUTF16ToJavaString(
                env, controller_->GetCancelButtonLabel())
          : nullptr);
}

void CredentialLeakDialogPasswordChangeViewAndroid::Accepted(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  controller_->OnAcceptDialog();
}

void CredentialLeakDialogPasswordChangeViewAndroid::Cancelled(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  controller_->OnCancelDialog();
}

void CredentialLeakDialogPasswordChangeViewAndroid::Closed(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  controller_->OnCloseDialog();
}
