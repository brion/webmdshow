// Copyright (c) 2010 The WebM project authors. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS.  All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.

#include <windows.h>
#include <windowsx.h>
#include <mfapi.h>
#include <mferror.h>
#include <mfidl.h>

#include <comdef.h>
#include <string>

#include "debugutil.hpp"
#include "eventutil.hpp"
#include "comreg.hpp"
#include "comdllwrapper.hpp"
#include "gtest/gtest.h"
#include "mfobjwrapper.hpp"
#include "tests/mfdllpaths.hpp"
#include "webmtypes.hpp"

using WebmMfUtil::MfByteStreamHandlerWrapper;
using WebmTypes::CLSID_WebmMfByteStreamHandler;
using WebmTypes::CLSID_WebmMfVp8Dec;
using WebmTypes::CLSID_WebmMfVorbisDec;

HRESULT mf_startup()
{
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr))
    {
        DBGLOG("ERROR, MFStartup failed, hr=" << hr);
    }
    return hr;
}

HRESULT mf_shutdown()
{
    HRESULT hr = MFShutdown();
    if (FAILED(hr))
    {
        DBGLOG("ERROR, MFShutdown failed, hr=" << hr);
    }
    return hr;
}

TEST(MfObjWrapperBasic, CreateMfByteStreamHandlerWrapper)
{
    MfByteStreamHandlerWrapper* ptr_mf_bsh = NULL;
    ASSERT_EQ(S_OK,
        MfByteStreamHandlerWrapper::Create(WEBM_SOURCE_PATH,
                                           CLSID_WebmMfByteStreamHandler,
                                           &ptr_mf_bsh));
    ASSERT_EQ(0, ptr_mf_bsh->Release());
}

TEST(MfObjWrapperBasic, CreateVp8DecTransformWrapper)
{
    WebmMfUtil::MfTransformWrapper mf_transform;
    ASSERT_EQ(S_OK, mf_transform.Create(VP8DEC_PATH, CLSID_WebmMfVp8Dec));
}

TEST(MfObjWrapperBasic, CreateVorbisDecTransformWrapper)
{
    WebmMfUtil::MfTransformWrapper mf_transform;
    ASSERT_EQ(S_OK, mf_transform.Create(VORBISDEC_PATH,
                                        CLSID_WebmMfVorbisDec));
}

TEST(MfByteStreamHandlerWrapper, LoadFile)
{
    ASSERT_EQ(S_OK, mf_startup());
    MfByteStreamHandlerWrapper* ptr_mf_bsh = NULL;
    ASSERT_EQ(S_OK,
        MfByteStreamHandlerWrapper::Create(WEBM_SOURCE_PATH,
                                           CLSID_WebmMfByteStreamHandler,
                                           &ptr_mf_bsh));
    ASSERT_EQ(S_OK, ptr_mf_bsh->OpenURL(L"C:\\src\\media\\fg.webm"));
    ASSERT_EQ(0, ptr_mf_bsh->Release());
    ASSERT_EQ(S_OK, mf_shutdown());
}