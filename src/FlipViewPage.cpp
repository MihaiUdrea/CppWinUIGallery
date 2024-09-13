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

Microsoft::UI::Xaml::FrameworkElement FlipViewPage::SearchSubItemInTree(hstring subItemClassName, FrameworkElement item,
                                                                        int &count, int subItemIndex)
{

    FrameworkElement currentItem = nullptr;
    if (get_class_name(item) == subItemClassName)
        return item;

    for (int index = 0; index < Media::VisualTreeHelper::GetChildrenCount(item); index++)
    {
        auto subitem = Media::VisualTreeHelper::GetChild(item, index);
        currentItem = SearchSubItemInTree(subItemClassName, subitem.as<FrameworkElement>(), count, subItemIndex);
        if (currentItem != nullptr)
        {
            if (subItemIndex == count)
                return currentItem;
            else
                count++; //  Found a suitable item, but not with the requested index
        }
    }

    return nullptr;
}

void FlipViewPage::FlipView_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                   winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    int count = 0;
    if (auto item = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ListViewItem", StoreListView(), count))
        item.Width(600);
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

    if (auto image = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.Image", StoreListView(), count))
    {
        auto border = image.Parent().as<FrameworkElement>();
        border.Width(600);
    }
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

    int last = items.Size() - 1;
    auto item = items.GetAt(last);
    items.RemoveAt(last);
    items.InsertAt(0, item);
}

void FlipViewPage::StoreListView_SelectionChanged(
    winrt::Windows::Foundation::IInspectable const &sender,
    winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const &e)
{
    auto selectedIndex = StoreListView().SelectedIndex();
    int count = 0;
    if (auto scrollViewer = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ScrollViewer", StoreListView(), count)
                                .as<Controls::ScrollViewer>())
    {
        if (selectedIndex > lastIndex)
        {
            scrollViewer.ChangeView(scrollViewer.HorizontalOffset() + 600.0, 0.0, 1.0);
            elementPosition += 600.0;

            DispatcherTimer dispatherTimer;
            dispatherTimer.Tick([this, selectedIndex, scrollViewer, dispatherTimer](auto, auto) {
                for (int index = 0; index < selectedIndex - 1; index++)
                {
                    auto item = items.GetAt(0);
                    lastIndex--;
                    items.RemoveAt(0);
                    items.Append(item);
                    scrollViewer.ChangeView(scrollViewer.HorizontalOffset() - 600.0, 0.0, 1.0, true);

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

        else if (selectedIndex < lastIndex)
        {
            scrollViewer.ChangeView(scrollViewer.HorizontalOffset() - 600.0, 0.0, 1.0);
            elementPosition -= 600.0;

            DispatcherTimer dispatherTimer;
            dispatherTimer.Tick([this, selectedIndex, scrollViewer, dispatherTimer](auto, auto) {
                if (selectedIndex == 0)
                {
                    int last = items.Size() - 1;
                    for (int index = last; index > selectedIndex + 2; index--)
                    {
                        auto item = items.GetAt(last);
                        lastIndex++;
                        items.RemoveAt(last);
                        items.InsertAt(0, item);
                        scrollViewer.ChangeView(scrollViewer.HorizontalOffset() - 600.0, 0.0, 1.0, true);

                        // double horizontalOffset = scrollViewer.HorizontalOffset();
                        // double viewportWidth = scrollViewer.ViewportWidth();
                        // double elementWitdth = 270.0;

                        // Get the position of the element relative to the ScrollViewer
                        // Media::GeneralTransform transform = item.TransformToVisual(scrollViewer);
                        // Windows::Foundation::Point elementPosition =
                        //    transform.TransformPoint(Windows::Foundation::Point(0, 0)); // Top-left corner of the
                        //    element

                        // bool IsInVisualFromLeft = elementPosition + elementWitdth > horizontalOffset;
                        // IsInVisualFromLeft;
                        // if (!IsInVisualFromLeft)
                        //{
                        //     items.RemoveAt(0);
                        //     items.Append(item);
                        // }
                    }
                    dispatherTimer.Stop();
                }
            });
            dispatherTimer.Interval(Windows::Foundation::TimeSpan(1000000));
            dispatherTimer.Start();
        }
    }
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");
    count = 0;
    if (auto item =
            SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ListViewItem", StoreListView(), count, selectedIndex))
        item.Width(600);
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

    count = 0;
    if (auto image = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.Image", StoreListView(), count, selectedIndex))
    {
        auto border = image.Parent().as<FrameworkElement>();
        border.Width(600);
    }
    else
        throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

    if (lastIndex >= 0)
    {
        count = 0;
        if (auto item =
                SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.ListViewItem", StoreListView(), count, lastIndex))
            item.Width(270);
        else
            throw std::invalid_argument("NO SUCH ITEM WAS FOUND");

        count = 0;
        if (auto image = SearchSubItemInTree(L"Microsoft.UI.Xaml.Controls.Image", StoreListView(), count, lastIndex))
        {
            auto border = image.Parent().as<FrameworkElement>();
            border.Width(270);
        }
        else
            throw std::invalid_argument("NO SUCH ITEM WAS FOUND");
    }

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
        DispatcherQueue().TryEnqueue([this]() { StoreListView().SelectedIndex(lastIndex - 1); });
    }

    e.Handled(true);
}

} // namespace winrt::CppWinUIGallery::implementation
