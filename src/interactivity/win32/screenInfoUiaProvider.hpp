/*++
Copyright (c) Microsoft Corporation

Module Name:
- screenInfoUiaProvider.hpp

Abstract:
- This module provides UI Automation access to the screen buffer to
  support both automation tests and accessibility (screen reading)
  applications.
- Based on examples, sample code, and guidance from
  https://msdn.microsoft.com/en-us/library/windows/desktop/ee671596(v=vs.85).aspx

Author(s):
- Michael Niksa (MiNiksa)     2017
- Austin Diviness (AustDi)    2017
--*/

#pragma once

// Forward declare, prevent circular ref.
class SCREEN_INFORMATION;

namespace Microsoft
{
    namespace Console
    {
        namespace Interactivity
        {
            namespace Win32
            {
                class Window;

                class WindowUiaProvider;

                class ScreenInfoUiaProvider final : public IRawElementProviderSimple,
                                                    public IRawElementProviderFragment,
                                                    public ITextProvider
                {
                public:
                    ScreenInfoUiaProvider(_In_ WindowUiaProvider* const pUiaParent);
                    virtual ~ScreenInfoUiaProvider();

                    // IUnknown methods
                    IFACEMETHODIMP_(ULONG) AddRef();
                    IFACEMETHODIMP_(ULONG) Release();
                    IFACEMETHODIMP QueryInterface(_In_ REFIID riid,
                                                  _COM_Outptr_result_maybenull_ void** ppInterface);

                    // IRawElementProviderSimple methods
                    IFACEMETHODIMP get_ProviderOptions(_Out_ ProviderOptions* pOptions);
                    IFACEMETHODIMP GetPatternProvider(_In_ PATTERNID iid,
                                                      _COM_Outptr_result_maybenull_ IUnknown** ppInterface);
                    IFACEMETHODIMP GetPropertyValue(_In_ PROPERTYID idProp,
                                                    _Out_ VARIANT* pVariant);
                    IFACEMETHODIMP get_HostRawElementProvider(_COM_Outptr_result_maybenull_ IRawElementProviderSimple** ppProvider);

                    // IRawElementProviderFragment methods
                    IFACEMETHODIMP Navigate(_In_ NavigateDirection direction,
                                            _COM_Outptr_result_maybenull_ IRawElementProviderFragment** ppProvider);
                    IFACEMETHODIMP GetRuntimeId(_Outptr_result_maybenull_ SAFEARRAY** ppRuntimeId);
                    IFACEMETHODIMP get_BoundingRectangle(_Out_ UiaRect* pRect);
                    IFACEMETHODIMP GetEmbeddedFragmentRoots(_Outptr_result_maybenull_ SAFEARRAY** ppRoots);
                    IFACEMETHODIMP SetFocus();
                    IFACEMETHODIMP get_FragmentRoot(_COM_Outptr_result_maybenull_ IRawElementProviderFragmentRoot** ppProvider);

                    // ITextProvider
                    IFACEMETHODIMP GetSelection(_Outptr_result_maybenull_ SAFEARRAY** ppRetVal);
                    IFACEMETHODIMP GetVisibleRanges(_Outptr_result_maybenull_ SAFEARRAY** ppRetVal);
                    IFACEMETHODIMP RangeFromChild(_In_ IRawElementProviderSimple* childElement,
                                                  _COM_Outptr_result_maybenull_ ITextRangeProvider** ppRetVal);
                    IFACEMETHODIMP RangeFromPoint(_In_ UiaPoint point,
                                                  _COM_Outptr_result_maybenull_ ITextRangeProvider** ppRetVal);
                    IFACEMETHODIMP get_DocumentRange(_COM_Outptr_result_maybenull_ ITextRangeProvider** ppRetVal);
                    IFACEMETHODIMP get_SupportedTextSelection(_Out_ SupportedTextSelection* pRetVal);

                private:

                    // Ref counter for COM object
                    ULONG _cRefs;

                    WindowUiaProvider* const _pUiaParent;
                    bool _focusEventFiring;

                    const COORD _getScreenBufferCoords() const;
                    static SCREEN_INFORMATION* const _getScreenInfo();
                    static IConsoleWindow* const _getIConsoleWindow();
                };
            }
        }
    }
}
