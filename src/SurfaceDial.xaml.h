#pragma once

#include "SurfaceDial.g.h"
#include "winrt/Windows.System.Threading.h"
#include "winrt/Windows.UI.Xaml.Controls.h"
#include "winrt/Windows.UI.Xaml.Input.h"
#include "winrt/Windows.UI.Xaml.Shapes.h"
#include "winrt/Windows.UI.Xaml.Media.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.UI.Xaml.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct SurfaceDial : SurfaceDialT<SurfaceDial>
    {
        SurfaceDial()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void hoverSection_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void hoverSection_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        winrt::Microsoft::UI::Xaml::DispatcherTimer m_timer{ nullptr };
        winrt::Microsoft::UI::Xaml::Shapes::Path m_previousMenuSection{ nullptr };
        void UpdateApplicationName(hstring const& sectionName);

    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct SurfaceDial : SurfaceDialT<SurfaceDial, implementation::SurfaceDial>
    {
    };
}
