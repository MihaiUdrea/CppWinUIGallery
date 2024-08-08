#include "pch.h"
#include "LottieIcon.xaml.h"
#if __has_include("LottieIcon.g.cpp")
#include "LottieIcon.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::CppWinUIGallery::implementation
{
    int32_t LottieIcon::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void LottieIcon::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    
}
