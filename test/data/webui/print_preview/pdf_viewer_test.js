// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/* Suite of tests verifying the PDF viewer as served by Print Preview's data
 * source works as expected. */

import 'chrome://print/pdf/elements/viewer-page-indicator.js';

import {PDFCreateOutOfProcessPlugin} from 'chrome://print/pdf/pdf_scripting_api.js';
import {assert} from 'chrome://resources/js/assert.m.js';
import {assertEquals, assertFalse, assertTrue} from '../chai_assert.js';
import {eventToPromise} from '../test_util.m.js';

window.pdf_viewer_test = {};
pdf_viewer_test.suiteName = 'PdfViewerTest';
/** @enum {string} */
pdf_viewer_test.TestNames = {
  Basic: 'basic',
  PageIndicator: 'page indicator',
};

suite(pdf_viewer_test.suiteName, function() {
  setup(function() {
    document.body.innerHTML = '';
  });

  test(assert(pdf_viewer_test.TestNames.Basic), async () => {
    const plugin = PDFCreateOutOfProcessPlugin(
        'chrome://print/test.pdf', 'chrome://print/pdf');

    const loaded = eventToPromise('load', plugin);
    document.body.appendChild(plugin);
    await loaded;
    const viewerDocument = plugin.contentDocument;

    const verifyElement = id => {
      const element = viewerDocument.querySelector(`viewer-${id}`);
      assertTrue(!!element);
      assertEquals(id, element.id);
    };

    ['zoom-toolbar', 'error-screen', 'page-indicator'].forEach(
        id => verifyElement(id));
    // Should also have the sizer and content divs
    assertTrue(!!viewerDocument.querySelector('#sizer'));
    assertTrue(!!viewerDocument.querySelector('#content'));

    // These elements don't exist in Print Preview's viewer.
    ['viewer-pdf-toolbar', 'viewer-form-warning'].forEach(
        name => assertFalse(!!viewerDocument.querySelector(name)));
  });

  test(assert(pdf_viewer_test.TestNames.PageIndicator), function() {
    const indicator = document.createElement('viewer-page-indicator');
    document.body.appendChild(indicator);

    // Assumes label is index + 1 if no labels are provided
    indicator.index = 2;
    assertEquals('3', indicator.label);

    // If labels are provided, uses the index to get the label.
    indicator.pageLabels = ['1', '3', '5'];
    assertEquals('5', indicator.label);
  });
});
