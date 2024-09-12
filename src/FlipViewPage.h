#pragma once

#include "FlipItem.g.h"
#include "FlipViewPage.g.h"

namespace winrt::CppWinUIGallery::implementation
{
struct FlipViewPage : FlipViewPageT<FlipViewPage>
{

    FlipViewPage()
    {
        InitializeComponent();
        Init();
    };

    void Init();
    int32_t MyProperty();
    void MyProperty(int32_t value);
    void FlipView_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                         winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);

    void StoreListView_SelectionChanged(winrt::Windows::Foundation::IInspectable const &sender,
                                        winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const &e);

    Microsoft::UI::Xaml::FrameworkElement SearchSubItemInTree(hstring subItemClassName,
                                                              Microsoft::UI::Xaml::FrameworkElement item);

  private:
    decltype(single_threaded_observable_vector<FlipItem>()) items = single_threaded_observable_vector<FlipItem>();
public:
    void StoreListView_PointerWheelChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
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
