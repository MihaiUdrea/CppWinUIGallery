#pragma once

#include "PhotoGallery.g.h"

namespace winrt::CppWinUIGallery::implementation
{
struct PhotoGallery : PhotoGalleryT<PhotoGallery>
{
    PhotoGallery()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    int32_t MyProperty();
    void MyProperty(int32_t value);
    void ThemeButton_Click(winrt::Windows::Foundation::IInspectable const &sender,
                           winrt::Microsoft::UI::Xaml::RoutedEventArgs const &args);

    /*void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);*/
};
} // namespace winrt::CppWinUIGallery::implementation

namespace winrt::CppWinUIGallery::factory_implementation
{
struct PhotoGallery : PhotoGalleryT<PhotoGallery, implementation::PhotoGallery>
{
};
} // namespace winrt::CppWinUIGallery::factory_implementation
