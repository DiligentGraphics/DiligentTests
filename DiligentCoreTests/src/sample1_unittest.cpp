// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.

// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:


// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.
#include <iostream>
#include <vector>

#ifdef WIN32
#   include <Windows.h>
#   include <dxgi1_2.h>
#   include <atlcomcli.h>
#   include <d3d11.h>
#include <D3Dcompiler.h>

static const char* PSSource = R"(#ifndef _HLSL_DEFINITIONS_
#define _HLSL_DEFINITIONS_

#define HLSL

#define NDC_MIN_Z 0.0 // Minimal z in the normalized device space

#define F3NDC_XYZ_TO_UVD_SCALE float3(0.5, -0.5, 1.0)

float2 NormalizedDeviceXYToTexUV( float2 f2ProjSpaceXY )
{
    return float2(0.5,0.5) + float2(0.5,-0.5) * f2ProjSpaceXY.xy;
}

float NormalizedDeviceZToDepth(float fNDC_Z)
{
    return fNDC_Z;
}

float DepthToNormalizedDeviceZ(float fDepth)
{
    return fDepth;
}

// Relational and logical operators
#define Less(x,y) ((x)<(y))
#define LessEqual(x,y) ((x)<=(y))
#define Greater(x,y) ((x)>(y))
#define GreaterEqual(x,y) ((x)>=(y))
#define Equal(x,y) ((x)==(y))
#define NotEqual(x,y) ((x)!=(y))
#define Not(x) (!(x))
#define And(x,y) ((x)&&(y))
#define Or(x,y) ((x)||(y))

float4 BoolToFloat( bool4 b4 )
{
    return float4(b4.x ? 1.0 : 0.0,
                  b4.y ? 1.0 : 0.0,
                  b4.z ? 1.0 : 0.0,
                  b4.w ? 1.0 : 0.0);
}
float3 BoolToFloat( bool3 b3 )
{
    return float3(b3.x ? 1.0 : 0.0,
                  b3.y ? 1.0 : 0.0,
                  b3.z ? 1.0 : 0.0);
}
float2 BoolToFloat( bool2 b2 )
{
    return float2(b2.x ? 1.0 : 0.0,
                  b2.y ? 1.0 : 0.0);
}
float BoolToFloat( bool b )
{
    return b.x ? 1.0 : 0.0;
}

#define MATRIX_ELEMENT(mat, row, col) mat[row][col]

float4x4 MatrixFromRows(float4 row0, float4 row1, float4 row2, float4 row3)
{
    return float4x4(row0, row1, row2, row3);
}

float3x3 MatrixFromRows(float3 row0, float3 row1, float3 row2)
{
    return float3x3(row0, row1, row2);
}

float2x2 MatrixFromRows(float2 row0, float2 row1)
{
    return float2x2(row0, row1);
}

#endif // _HLSL_DEFINITIONS_

Texture2D g_tex2D_Static;
Texture2D g_tex2D_Mut;
Texture2D g_tex2D_MutArr[2];
Texture2D g_tex2D_Dyn;
Texture2D g_tex2D_DynArr[2];
Texture2D g_tex2D_StaticArr[2];

SamplerState g_tex2D_Static_sampler;
SamplerState g_tex2D_Mut_sampler;
SamplerState g_tex2D_Dyn_sampler;
SamplerState g_tex2D_MutArr_sampler;
SamplerState g_tex2D_DynArr_sampler;
SamplerState g_tex2D_StaticArr_sampler;

cbuffer UniformBuff_Stat
{
    float4 g_f4Color0;
}

cbuffer UniformBuff_Stat2
{
    float4 g_f4Color01;
}

cbuffer UniformBuff_Mut
{
    float4 g_f4Color1;
}

cbuffer UniformBuff_Dyn
{
    float4 g_f4Color2;
}

RWTexture2D<float4 /*format=rgba32f*/> g_rwtex2D_Static;
RWTexture2D<float4 /*format=rgba32f*/> g_rwtex2D_Static2;
RWTexture2D<float4 /*format=rgba32f*/>  g_rwtex2D_Mut;
RWTexture2D<float4 /*format=rgba32f*/>  g_rwtex2D_Dyn;

RWByteAddressBuffer g_rwBuff_Static;
RWBuffer<float4> g_rwBuff_Mut;
RWBuffer<float4> g_rwBuff_Dyn;

Buffer<float4> g_Buffer_Static;
Buffer<float4> g_Buffer_StaticArr[2];
ByteAddressBuffer g_Buffer_Mut;
Buffer<float4> g_Buffer_MutArr[2];
Buffer<float4> g_Buffer_Dyn;
Buffer<float4> g_Buffer_DynArr[2];

struct VSOut
{
    float4 f4Position : SV_Position;
    float4 f4Color	: COLOR;
};

 
float4 main(VSOut In) : SV_Target
{
    float4 Color = In.f4Color;
    Color += g_tex2D_Static.SampleLevel(g_tex2D_Static_sampler, float2(0.5,0.5), 0.0);
    Color += g_tex2D_StaticArr[0].SampleLevel(g_tex2D_StaticArr_sampler, float2(0.5,0.5), 0.0) + g_tex2D_StaticArr[1].SampleLevel(g_tex2D_StaticArr_sampler, float2(0.5,0.5), 0.0);
    Color += g_tex2D_Mut.SampleLevel(g_tex2D_Mut_sampler, float2(0.5,0.5), 0.0);
    Color += g_tex2D_MutArr[0].SampleLevel(g_tex2D_MutArr_sampler, float2(0.5,0.5), 0.0) + g_tex2D_MutArr[1].SampleLevel(g_tex2D_MutArr_sampler, float2(0.5,0.5), 0.0);
    Color += g_tex2D_Dyn.SampleLevel(g_tex2D_Dyn_sampler, float2(0.5,0.5), 0.0);
    Color += g_tex2D_DynArr[0].SampleLevel(g_tex2D_DynArr_sampler, float2(0.5,0.5), 0.0) + g_tex2D_DynArr[1].SampleLevel(g_tex2D_DynArr_sampler, float2(0.5,0.5), 0.0);
    Color += g_f4Color0 + g_f4Color01 + g_f4Color1 + g_f4Color2;
    Color += g_rwtex2D_Static.Load(int2(0,0)) + g_rwtex2D_Mut.Load(int2(0,0)) + g_rwtex2D_Dyn.Load(uint2(0,0)) + g_rwtex2D_Static2.Load(uint2(0,0));
    Color += asfloat(g_rwBuff_Static.Load(0)) + g_rwBuff_Mut.Load(0) + g_rwBuff_Dyn.Load(0);

    Color += g_Buffer_Static.Load(0);
    Color += g_Buffer_StaticArr[0].Load(0) + g_Buffer_StaticArr[1].Load(0);
    Color += asfloat(g_Buffer_Mut.Load(0));
    Color += g_Buffer_MutArr[0].Load(0) + g_Buffer_MutArr[1].Load(0);
    Color += g_Buffer_Dyn.Load(0);
    Color += g_Buffer_DynArr[0].Load(0) + g_Buffer_DynArr[1].Load(0);

    return Color;
}
)";


class ComErrorDesc
{
public:
    ComErrorDesc(HRESULT hr)
    {
        auto NumCharsWritten = FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            m_Msg,
            _countof(m_Msg),
            NULL);

        if (NumCharsWritten == 0)
        {
            strcpy_s(m_Msg, _countof(m_Msg), "Unknown error");
        }
        else
        {
            auto nLen = strlen(m_Msg);
            if (nLen > 1 && m_Msg[nLen - 1] == '\n')
            {
                m_Msg[nLen - 1] = 0;
                if (m_Msg[nLen - 2] == '\r')
                {
                    m_Msg[nLen - 2] = 0;
                }
            }
        }
    }

    const char* Get() { return m_Msg; }

private:
    char m_Msg[4096];
};

class D3DIncludeImpl : public ID3DInclude
{
public:
    D3DIncludeImpl()
    {
    }

    STDMETHOD(Open)
    (THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes)
    {
        return S_OK;
    }

    STDMETHOD(Close)
    (THIS_ LPCVOID pData)
    {
        return S_OK;
    }
};

static HRESULT CompileShader(const char*                      Source,
    LPCSTR                           strFunctionName,
    const D3D_SHADER_MACRO*          pDefines,
    LPCSTR                           profile,
    ID3DBlob**                       ppBlobOut,
    ID3DBlob**                       ppCompilerOutput)
{
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    // Set the D3D10_SHADER_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows
    // the shaders to be optimized and to run exactly the way they will run in
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#else
    // Warning: do not use this flag as it causes shader compiler to fail the compilation and
    // report strange errors:
    // dwShaderFlags |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif
    HRESULT hr;
    //	do
    //	{
    auto SourceLen = strlen(Source);

    D3DIncludeImpl IncludeImpl;
    hr = D3DCompile(Source, SourceLen, NULL, pDefines, &IncludeImpl, strFunctionName, profile, dwShaderFlags, 0, ppBlobOut, ppCompilerOutput);

    //		if( FAILED(hr) || errors )
    //		{
    //			if( FAILED(hr)
    //#if PLATFORM_WIN32
    //                && IDRETRY != MessageBoxW( NULL, L"Failed to compile shader", L"FX Error", MB_ICONERROR | (Source == nullptr ? MB_ABORTRETRYIGNORE : 0) )
    //#endif
    //                )
    //			{
    //				break;
    //			}
    //		}
    //	} while( FAILED(hr) );
    return hr;
}

class Direct3DTest
{
public:
    Direct3DTest()
    {
        std::cout << "Initializing Direct3D...\n";
        FindCompatibleAdapters();
    }

    std::vector<CComPtr<IDXGIAdapter1>> FindCompatibleAdapters()
    {
        std::vector<CComPtr<IDXGIAdapter1>> DXGIAdapters;

        CComPtr<IDXGIFactory2> pFactory;
        if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory2), (void**)&pFactory)))
        {
            std::cout << "Failed to create DXGI Factory";
            return std::move(DXGIAdapters);
        }
        else
        {
            std::cout << "Successfully created DXGI Factory\n";
        }
        CComPtr<IDXGIAdapter1> pDXIAdapter;
        CComPtr<IDXGIAdapter1> pWarpAdapter;

        auto d3dFeatureLevel = D3D_FEATURE_LEVEL_11_0;
        UINT adapter = 0;
        for (; pFactory->EnumAdapters1(adapter, &pDXIAdapter) != DXGI_ERROR_NOT_FOUND; ++adapter, pDXIAdapter.Release())
        {
            DXGI_ADAPTER_DESC1 AdapterDesc;
            pDXIAdapter->GetDesc1(&AdapterDesc);
            char DescriptionMB[_countof(AdapterDesc.Description)];
            WideCharToMultiByte(CP_ACP, 0, AdapterDesc.Description, -1, DescriptionMB, _countof(DescriptionMB), NULL, FALSE);
            std::cout << "Found adapter '" << DescriptionMB << "' (" << AdapterDesc.DedicatedVideoMemory / (1 << 20) << ") MB\n";
            auto hr = D3D11CreateDevice(
                nullptr,
                D3D_DRIVER_TYPE_NULL, // There is no need to create a real hardware device.
                0,
                0,                 // Flags.
                &d3dFeatureLevel,     // Feature levels.
                1,                 // Number of feature levels
                D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION for Windows Store apps.
                nullptr,           // No need to keep the D3D device reference.
                nullptr,           // Feature level of the created adapter.
                nullptr            // No need to keep the D3D device context reference.
            );
            bool IsCompatibleAdapter = SUCCEEDED(hr);
            if (IsCompatibleAdapter)
            {
                DXGIAdapters.emplace_back(pDXIAdapter);
            }
            if (AdapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                pWarpAdapter = pDXIAdapter;
            }
        }

        CComPtr<ID3D11Device> pDevice;
        HRESULT hr;
        if (pWarpAdapter)
        {
            std::cout << "Using SW adapter " << pWarpAdapter << "\n";
            hr = D3D11CreateDevice(
                pWarpAdapter,
                D3D_DRIVER_TYPE_UNKNOWN, // There is no need to create a real hardware device.
                0,
                0,                 // Flags.
                &d3dFeatureLevel,     // Feature levels.
                1,                 // Number of feature levels
                D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION for Windows Store apps.
                &pDevice,
                nullptr,           // Feature level of the created adapter.
                nullptr            // No need to keep the D3D device context reference.
            );
        }
        else
        {
            std::cout << "Creating D3D_DRIVER_TYPE_WARP adapter\n";
            hr = D3D11CreateDevice(
                nullptr,
                D3D_DRIVER_TYPE_WARP, // There is no need to create a real hardware device.
                0,
                0,                 // Flags.
                &d3dFeatureLevel,     // Feature levels.
                1,                 // Number of feature levels
                D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION for Windows Store apps.
                &pDevice,
                nullptr,           // Feature level of the created adapter.
                nullptr            // No need to keep the D3D device context reference.
            );
        }

        if (SUCCEEDED(hr))
        {
            std::cout << "Successfully created WARP adapter!\n";
            auto FL = pDevice->GetFeatureLevel();
            std::cout << "Device feature level: ";
            switch (FL)
            {
            case D3D_FEATURE_LEVEL_10_0: std::cout << "10_0"; break;
            case D3D_FEATURE_LEVEL_10_1: std::cout << "10_1"; break;
            case D3D_FEATURE_LEVEL_11_0: std::cout << "11_0"; break;
            case D3D_FEATURE_LEVEL_11_1: std::cout << "11_1"; break;
            case D3D_FEATURE_LEVEL_12_0: std::cout << "12_0"; break;
            case D3D_FEATURE_LEVEL_12_1: std::cout << "12_1"; break;
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "Unable to create WARP adapter :(\n";
        }

        CComPtr<ID3DBlob> ShaderByteCode;
        CComPtr<ID3DBlob> errors;
        hr = CompileShader(PSSource, "main", nullptr, "ps_5_0", &ShaderByteCode, &errors);
        const char* CompilerMsg = errors ? reinterpret_cast<const char*>(errors->GetBufferPointer()) : nullptr;
        if (SUCCEEDED(hr))
        {
            std::cout << "Successfully compiled the shader!\n";
        }
        else
        {
            std::cout << "Failed to compile the shader :(\n";
            if (CompilerMsg != nullptr)
            {
                std::cout << "Compiler output:\n" << CompilerMsg;
            }
        }

        CComPtr<ID3D11PixelShader> PixelShader;
        hr = pDevice->CreatePixelShader(ShaderByteCode->GetBufferPointer(), ShaderByteCode->GetBufferSize(), NULL, &PixelShader);
        if (SUCCEEDED(hr))
        {
            std::cout << "Successfully created the pixel shader!\n";
        }
        else
        {
            ComErrorDesc HRErr(hr);
            std::cout << "Failed to create the pixelshader :(\n" << HRErr.Get() << "\n";

        }

        return std::move(DXGIAdapters);
    }

    static Direct3DTest g_D3DTest;
};
Direct3DTest Direct3DTest::g_D3DTest;
#endif

#include <limits.h>
#include "sample1.h"
#include "gtest/gtest.h"
namespace {

    // Step 2. Use the TEST macro to define your tests.
    //
    // TEST has two parameters: the test case name and the test name.
    // After using the macro, you should define your test logic between a
    // pair of braces.  You can use a bunch of macros to indicate the
    // success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
    // examples of such macros.  For a complete list, see gtest.h.
    //
    // <TechnicalDetails>
    //
    // In Google Test, tests are grouped into test cases.  This is how we
    // keep test code organized.  You should put logically related tests
    // into the same test case.
    //
    // The test case name and the test name should both be valid C++
    // identifiers.  And you should not use underscore (_) in the names.
    //
    // Google Test guarantees that each test you define is run exactly
    // once, but it makes no guarantee on the order the tests are
    // executed.  Therefore, you should write your tests in such a way
    // that their results don't depend on their order.
    //
    // </TechnicalDetails>


    // Tests Factorial().

    // Tests factorial of negative numbers.
    TEST(FactorialTest, Negative) {
        // This test is named "Negative", and belongs to the "FactorialTest"
        // test case.
        EXPECT_EQ(1, Factorial(-5));
        EXPECT_EQ(1, Factorial(-1));
        EXPECT_GT(Factorial(-10), 0);

        // <TechnicalDetails>
        //
        // EXPECT_EQ(expected, actual) is the same as
        //
        //   EXPECT_TRUE((expected) == (actual))
        //
        // except that it will print both the expected value and the actual
        // value when the assertion fails.  This is very helpful for
        // debugging.  Therefore in this case EXPECT_EQ is preferred.
        //
        // On the other hand, EXPECT_TRUE accepts any Boolean expression,
        // and is thus more general.
        //
        // </TechnicalDetails>
    }

    // Tests factorial of 0.
    TEST(FactorialTest, Zero) {
        EXPECT_EQ(1, Factorial(0));
    }

    // Tests factorial of positive numbers.
    TEST(FactorialTest, Positive) {
        EXPECT_EQ(1, Factorial(1));
        EXPECT_EQ(2, Factorial(2));
        EXPECT_EQ(6, Factorial(3));
        EXPECT_EQ(40320, Factorial(8));
    }


    // Tests IsPrime()

    // Tests negative input.
    TEST(IsPrimeTest, Negative) {
        // This test belongs to the IsPrimeTest test case.

        EXPECT_FALSE(IsPrime(-1));
        EXPECT_FALSE(IsPrime(-2));
        EXPECT_FALSE(IsPrime(INT_MIN));
    }

    // Tests some trivial cases.
    TEST(IsPrimeTest, Trivial) {
        EXPECT_FALSE(IsPrime(0));
        EXPECT_FALSE(IsPrime(1));
        EXPECT_TRUE(IsPrime(2));
        EXPECT_TRUE(IsPrime(3));
    }

    // Tests positive input.
    TEST(IsPrimeTest, Positive) {
        EXPECT_FALSE(IsPrime(4));
        EXPECT_TRUE(IsPrime(5));
        EXPECT_FALSE(IsPrime(6));
        EXPECT_TRUE(IsPrime(23));
    }
}  // namespace

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
