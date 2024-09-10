#pragma once

#include "FlipItem.g.h"
#include "FlipViewPage.g.h"

namespace winrt::CppWinUIGallery::implementation
{
struct FlipViewPage : FlipViewPageT<FlipViewPage>
{

    FlipViewPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    int32_t MyProperty();
    void MyProperty(int32_t value);
    void FlipView_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                         winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);


};

struct FlipItem : FlipItemT<FlipItem>
{
    FlipItem() = default;
    FlipItem(hstring image, hstring name);

    hstring Image()
    {
        return m_image;
    }
    void Image(hstring const &value)
    {
        m_image = value;
    }

    hstring Name()
    {
        return m_name;
    }
    void Name(hstring const &value)
    {
        m_name = value;
    }

  private:
    hstring m_image{L""};
    hstring m_name{L""};
};

} // namespace winrt::CppWinUIGallery::implementation

namespace winrt::CppWinUIGallery::factory_implementation
{
struct FlipViewPage : FlipViewPageT<FlipViewPage, implementation::FlipViewPage>
{
};

struct FlipItem : FlipItemT<FlipItem, implementation::FlipItem>
{
};

} // namespace winrt::CppWinUIGallery::factory_implementation
