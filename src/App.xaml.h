#pragma once

#include "AnimatedLogo.h"
#include "App.xaml.g.h"
#include "TransparentLottie.h"

#include "SettingsCardControl.h"

namespace winrt::CppWinUIGallery::implementation
{
struct App : AppT<App>
{
    App();

    void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const &);

    winrt::Microsoft::UI::Xaml::Window GetWindow()
    {
        return window;
    }

  private:
    winrt::Microsoft::UI::Xaml::Window window{nullptr};
};
} // namespace winrt::CppWinUIGallery::implementation
