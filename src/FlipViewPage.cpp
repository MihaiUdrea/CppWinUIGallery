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

    // if (auto item = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ListViewItem", StoreListView()))
    //     item.Width(600);
    // else
    //     throw std::invalid_argument("NO SUCH ITEM WAS FOUND");
    //
    // if (auto image = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.Image", StoreListView()))
    //{
    //     auto border = image.Parent().as<FrameworkElement>();
    //     border.Width(600);
    // }
    // else
    //     throw std::invalid_argument("NO SUCH ITEM WAS FOUND");
}

void FlipViewPage::StoreListView_SelectionChanged(
    winrt::Windows::Foundation::IInspectable const &sender,
    winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const &e)
{
    auto selectedIndex = StoreListView().SelectedIndex();

    if (auto scrollViewer = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ScrollViewer", StoreListView())
                                .as<Controls::ScrollViewer>())
    {
        if (selectedIndex > lastIndex)
        {
            scrollViewer.ChangeView(scrollViewer.HorizontalOffset() + 270.0, 0.0, 1.0);
            elementPosition += 270.0;
        }

        else if (selectedIndex < lastIndex)
        {
            scrollViewer.ChangeView(scrollViewer.HorizontalOffset() - 270.0, 0.0, 1.0);
            elementPosition -= 270.0;
        }

        DispatcherTimer dispatherTimer;
        dispatherTimer.Tick([this, selectedIndex, scrollViewer, dispatherTimer](auto, auto) {
            for (int index = 0; index < selectedIndex - 1; index++)
            {
                auto item = items.GetAt(0);
                lastIndex--;
                items.RemoveAt(0);
                items.Append(item);
                scrollViewer.ChangeView(scrollViewer.HorizontalOffset() - 270.0, 0.0, 1.0, true);
                int foo = 1;

                // double horizontalOffset = scrollViewer.HorizontalOffset();
                // double viewportWidth = scrollViewer.ViewportWidth();
                // double elementWitdth = 270.0;

                // Get the position of the element relative to the ScrollViewer
                // Media::GeneralTransform transform = item.TransformToVisual(scrollViewer);
                // Windows::Foundation::Point elementPosition =
                //    transform.TransformPoint(Windows::Foundation::Point(0, 0)); // Top-left corner of the element

                // bool IsInVisualFromLeft = elementPosition + elementWitdth > horizontalOffset;
                // IsInVisualFromLeft;
                // if (!IsInVisualFromLeft)
                //{
                //     items.RemoveAt(0);
                //     items.Append(item);
                // }
            }
            dispatherTimer.Stop();
        });
        dispatherTimer.Interval(Windows::Foundation::TimeSpan(1000000));
        dispatherTimer.Start();
    }
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

    // if (auto firstItem = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ListViewItem", StoreListView()))
    //     firstItem.Width(270);
    // else
    //     throw std::invalid_argument("NO SUCH ITEM WAS FOUND");
    //
    // if (auto firstImage = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.Image", StoreListView()))
    //{
    //     auto border = firstImage.Parent().as<FrameworkElement>();
    //     border.Width(270);
    // }
    // else
    //     throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

    lastIndex = selectedIndex;
}

void FlipViewPage::StoreListView_PointerWheelChanged(winrt::Windows::Foundation::IInspectable const &sender,
                                                     winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const &e)
{
    auto pointer = e.GetCurrentPoint(nullptr);
    auto delta = pointer.Properties().MouseWheelDelta();

    if (delta < 0) // Mouse Down
    {
        // DispatcherTimer dispatherTimer;
        // dispatherTimer.Tick([this, dispatherTimer](auto, auto) {
        //     StoreListView().SelectedIndex(lastIndex + 1);
        //     dispatherTimer.Stop();
        // });
        // dispatherTimer.Interval(Windows::Foundation::TimeSpan(1000000));
        // dispatherTimer.Start();

        DispatcherQueue().TryEnqueue([this]() { StoreListView().SelectedIndex(lastIndex + 1); });
    }
    else
    {
        int foo = 1;
    }

    e.Handled(true);
}

} // namespace winrt::CppWinUIGallery::implementation
