#pragma once

#include "SurfaceDial.g.h"

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
    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct SurfaceDial : SurfaceDialT<SurfaceDial, implementation::SurfaceDial>
    {
    };
}
