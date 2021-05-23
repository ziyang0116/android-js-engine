package com.facebook.jni;/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import com.facebook.proguard.annotations.DoNotStrip;

@DoNotStrip
public class UnknownCppException extends com.facebook.jni.CppException {
  @DoNotStrip
  public UnknownCppException() {
    super("Unknown");
  }

  @DoNotStrip
  public UnknownCppException(String message) {
    super(message);
  }
}
