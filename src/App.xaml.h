#pragma once

#include "App.xaml.g.h"
#include "Test.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}
