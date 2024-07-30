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

    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct ConnectedAnimation : ConnectedAnimationT<ConnectedAnimation, implementation::ConnectedAnimation>
    {
    };
}
