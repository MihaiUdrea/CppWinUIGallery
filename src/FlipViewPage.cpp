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

Microsoft::UI::Xaml::FrameworkElement FlipViewPage::SearchSubItemInTree(hstring subItemClassName, FrameworkElement item)
{

    FrameworkElement currentItem = nullptr;
    if (get_class_name(item) == subItemClassName)
        return item;

    for (int index = 0; index < Media::VisualTreeHelper::GetChildrenCount(item); index++)
    {
        auto subitem = Media::VisualTreeHelper::GetChild(item, index);
        currentItem = SearchSubItemInTree(subItemClassName, subitem.as<FrameworkElement>());
        if (currentItem != nullptr)
            return currentItem;
    }

    return nullptr;
}

void FlipViewPage::FlipView_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                   winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{

    if (auto item = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ListViewItem", StoreListView()))
        item.Width(600);
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

    if (auto image = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.Image", StoreListView()))
    {
        auto border = image.Parent().as<FrameworkElement>();
        border.Width(600);
    }
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");
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

    if (auto item = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ListViewItem", StoreListView()))
        item.Width(600);
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

    if (auto image = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.Image", StoreListView()))
    {
        auto border = image.Parent().as<FrameworkElement>();
        border.Width(600);
    }
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");
}

void FlipViewPage::Init()
{

    items.Append(make<FlipItem>(L"ms-appx:///Assets/ai_logo.png", L"Cliff"));
    items.Append(make<FlipItem>(L"ms-appx:///Assets/awr_logo.png", L"Cliff"));
    items.Append(make<FlipItem>(L"ms-appx:///Assets/clang_logo.png", L"Cliff"));
    items.Append(make<FlipItem>(L"ms-appx:///Assets/caphyon_logo.png", L"Cliff"));

    /*auto item = make<FlipItem>();
    items.Append(item);*/
    StoreListView().ItemsSource(items);
}

} // namespace winrt::CppWinUIGallery::implementation
