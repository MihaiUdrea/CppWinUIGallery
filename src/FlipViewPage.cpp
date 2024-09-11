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

    items.Append(make<FlipItem>(L"ms-appx:///Assets/ai_logo.png", L"Cliff"));
    items.Append(make<FlipItem>(L"ms-appx:///Assets/awr_logo.png", L"Cliff"));
    items.Append(make<FlipItem>(L"ms-appx:///Assets/clang_logo.png", L"Cliff"));
    items.Append(make<FlipItem>(L"ms-appx:///Assets/caphyon_logo.png", L"Cliff"));

    /*auto item = make<FlipItem>();
    items.Append(item);*/
    StoreListView().ItemsSource(items);

    auto firstItem = items.First();
}

void FlipViewPage::StoreListView_SelectionChanged(
    winrt::Windows::Foundation::IInspectable const &sender,
    winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const &e)
{
    auto selectedIndex = StoreListView().SelectedIndex();
    for (int index = 0; index < selectedIndex; index++)
    {
        auto item = items.GetAt(0);
        items.RemoveAt(0);
        items.Append(item);
    }
    auto item = Media::VisualTreeHelper::GetChild(StoreListView(), 0);
    auto subItem = Media::VisualTreeHelper::GetChild(item, 0);
    auto sub2 = Media::VisualTreeHelper::GetChild(subItem, 0);
    auto sub3 = Media::VisualTreeHelper::GetChild(sub2, 0);
    auto sub4 = Media::VisualTreeHelper::GetChild(sub3, 0);
    auto sub5 = Media::VisualTreeHelper::GetChild(sub4, 0);
    auto sub6 = Media::VisualTreeHelper::GetChild(sub5, 1);
    auto sub7 = Media::VisualTreeHelper::GetChild(sub6, 0);
    auto sub6Cnt = Media::VisualTreeHelper::GetChildrenCount(sub6);
    auto sub8 = Media::VisualTreeHelper::GetChild(sub7, 0);
    auto sub7Cnt = Media::VisualTreeHelper::GetChildrenCount(sub7);
    auto sub9 = Media::VisualTreeHelper::GetChild(sub8, 0);
    auto sub9a = Media::VisualTreeHelper::GetChild(sub8, 1);
    auto sub9b = Media::VisualTreeHelper::GetChild(sub8, 2);
    auto sub8Cnt = Media::VisualTreeHelper::GetChildrenCount(sub8);
    // auto sub10 = Media::VisualTreeHelper::GetChild(sub9, 0);

    auto c = get_class_name(sub9);
    c = get_class_name(sub9a);
    // c = get_class_name(sub9b);
    c = get_class_name(Media::VisualTreeHelper::GetChild(sub9a, 0));
    auto image = Media::VisualTreeHelper::GetChild(sub9a, 0).as<Microsoft::UI::Xaml::Controls::Image>();
    c;
    auto frameworkElement = sub7.as<winrt::Microsoft::UI::Xaml::Controls::ListViewItem>();
    frameworkElement.Width(600);
    auto frameworkElement1 = sub9a.as<winrt::Microsoft::UI::Xaml::Controls::Border>();
    auto findEl = frameworkElement1.FindName(L"myImage");
    findEl;
    frameworkElement1.Background(Microsoft::UI::Xaml::Media::SolidColorBrush(Microsoft::UI::Colors::Red()));
    // auto frameworkElement2 = sub10.as<winrt::Microsoft::UI::Xaml::Controls::Image>();
    auto border = image.Parent().as<Microsoft::UI::Xaml::Controls::Border>();
    border.Width(600);
    //  winrt::microsoft::UI::Xaml::Media::ScaleTransform scaleTransform;
    //  scaleTransform.ScaleX(450);
    //  frameworkElement.RenderTransform(scaleTransform);
    //  firstItem.Width(600.0);
}

} // namespace winrt::CppWinUIGallery::implementation
