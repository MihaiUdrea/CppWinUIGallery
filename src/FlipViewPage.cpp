#include "pch.h"

#include "FlipViewPage.h"
#if __has_include("FlipViewPage.g.cpp")
#include "FlipViewPage.g.cpp"
#endif

#if __has_include("FlipItem.g.cpp")
#include "FlipItem.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinUIGallery::implementation
{
int32_t FlipViewPage::MyProperty()
{
    throw hresult_not_implemented();
}

void FlipViewPage::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}

FlipItem::FlipItem(hstring image, hstring name)
{
    this->m_image = image;
    this->m_name = name;
}

void FlipViewPage::FlipView_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                   winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    auto items = single_threaded_observable_vector<CppWinUIGallery::FlipItem>();
    items.Append(make<FlipItem>(L"ms-appx:///Assets/ai_logo.png", L"Cliff"));

    /*auto item = make<FlipItem>();
    items.Append(item);*/
    StoreFlipView().ItemsSource(items);
}

} // namespace winrt::CppWinUIGallery::implementation
