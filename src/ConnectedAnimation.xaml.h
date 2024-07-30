#pragma once

#include "ConnectedAnimation.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct ConnectedAnimation : ConnectedAnimationT<ConnectedAnimation>
    {
        ConnectedAnimation()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void OnPointerExit(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void OnPointerEnter(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        bool m_hovered = false;
        bool m_pointerInside = false;  // Track whether the pointer is inside the element

    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct ConnectedAnimation : ConnectedAnimationT<ConnectedAnimation, implementation::ConnectedAnimation>
    {
    };
}
