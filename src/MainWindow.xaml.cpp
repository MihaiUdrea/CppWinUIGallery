#include "pch.h"

#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "winrt\Windows.Foundation.Collections.h"

// #include <algorithm>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Input;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
MainWindow::MainWindow()
{
    InitializeComponent();
    ExtendsContentIntoTitleBar(true);
    this->AppWindow().TitleBar().PreferredHeightOption(Microsoft::UI::Windowing::TitleBarHeightOption::Standard);

    // THIS IS NOT WORKING ON CURRENT WINDOWS APP SDK VERSION
    // WARNING GetForCurrentView automatically throws an exception as the method is no longer supported
    // Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().SetPreferredMinSize(Windows::Foundation::Size(500,
    // 300));
}

int32_t MainWindow::MyProperty()
{
    throw hresult_not_implemented();
}

void MainWindow::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}

void MainWindow::AppTitleBar_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                    winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    if (Application::Current().RequestedTheme() == ApplicationTheme::Dark)
    {
        AppWindow().TitleBar().ButtonForegroundColor(Microsoft::UI::Colors::White());
        AppWindow().TitleBar().ButtonHoverForegroundColor(Microsoft::UI::Colors::White());
        AppWindow().TitleBar().ButtonHoverBackgroundColor(Windows::UI::Color{100, 90, 90, 90});
    }
    else
    {
        AppWindow().TitleBar().ButtonForegroundColor(Microsoft::UI::Colors::Black());
        AppWindow().TitleBar().ButtonHoverForegroundColor(Microsoft::UI::Colors::Black());
        AppWindow().TitleBar().ButtonHoverBackgroundColor(Windows::UI::Color{100, 191, 191, 191});
    }

    if (ExtendsContentIntoTitleBar() == true)
    {
        // Set the initial interactive regions
        SetRegionsForCustomTitleBar();
    }
}

void MainWindow::AppTitleBar_SizeChanged(winrt::Windows::Foundation::IInspectable const &sender,
                                         winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const &e)
{

    if (ExtendsContentIntoTitleBar() == true)
    {
        // Set the interactive regions for app size modification.
        SetRegionsForCustomTitleBar();
    }
}

Windows::Graphics::RectInt32 MainWindow::GetRect(winrt::Windows::Foundation::Rect bounds, double scale)
{
    winrt::Windows::Graphics::RectInt32 rect;

    rect.X = (int)round(bounds.X * scale);
    rect.Y = (int)round(bounds.Y * scale);
    rect.Width = (int)round(bounds.Width * scale);
    rect.Height = (int)round(bounds.Height * scale);

    return rect;
}

void MainWindow::SetRegionsForCustomTitleBar()
{
    double scaleAdjustment = AppTitleBar().XamlRoot().RasterizationScale();
    auto m_AppWindow = this->AppWindow();

    Windows::Foundation::Rect bounds;
    std::vector<Windows::Graphics::RectInt32> rects;

    // Setting sstem capture buttons margin

    AppTitleBar().Margin(ThicknessHelper::FromLengths(0, 0, m_AppWindow.TitleBar().RightInset(), 0));
    AppTitleBar().Width(m_AppWindow.ClientSize().Width - m_AppWindow.TitleBar().RightInset());

    // Setting custom tall title bar drag region

    auto transform = AppTitleBar().TransformToVisual(nullptr);
    bounds = transform.TransformBounds(
        Windows::Foundation::Rect{0, 0, (float)AppTitleBar().ActualWidth(), (float)AppTitleBar().ActualHeight()});

    Windows::Graphics::RectInt32 TitleBarRect = GetRect(bounds, scaleAdjustment);

    rects = {TitleBarRect};
    auto rectArray = array_view<Windows::Graphics::RectInt32>(rects);

    this->AppWindow().TitleBar().SetDragRectangles(rectArray);

    rects.clear();

    // Setting back button custom nno-dragable region

    transform = TitleBar_BackButton().TransformToVisual(nullptr);

    bounds = transform.TransformBounds(Windows::Foundation::Rect{0, 0, (float)TitleBar_BackButton().ActualWidth(),
                                                                 (float)TitleBar_BackButton().ActualHeight()});

    Windows::Graphics::RectInt32 BackButtonRect = GetRect(bounds, scaleAdjustment);

    rects = {BackButtonRect};
    rectArray = array_view<Windows::Graphics::RectInt32>(rects);

    InputNonClientPointerSource nonClientInputSrc = InputNonClientPointerSource::GetForWindowId(this->AppWindow().Id());
    nonClientInputSrc.SetRegionRects(NonClientRegionKind::Passthrough, rectArray);
}

void MainWindow::TitleBar_BackButton_Click(winrt::Windows::Foundation::IInspectable const &sender,
                                           winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    if (ContentFrame().CanGoBack())
        ContentFrame().GoBack();
    if (!ContentFrame().CanGoBack())
    {
        // TitleBar_BackButton().Foreground(Media::SolidColorBrush(Microsoft::UI::Colors::Gray()));  Not usable for
        // light mode
        TitleBar_BackButton().IsEnabled(false);
    }
}

void MainWindow::ContentFrame_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                     winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    ContentFrame().Navigate(Windows::UI::Xaml::Interop::TypeName{NavHomePage().Tag().as<hstring>()});
    NavView().SelectedItem(NavHomePage());
}

void MainWindow::NavView_ItemInvoked(
    winrt::Microsoft::UI::Xaml::Controls::NavigationView const &sender,
    winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const &args)
{
    auto myTag = args.InvokedItemContainer().Tag();

    if (auto hstr = myTag.try_as<hstring>())
    {
        // OutputDebugString(L"is a hstring!");
        // The try_as<winrt::hstring>() method tries to cast the IInspectable object (in this case the tag) to a
        // winrt::hstring. If successful, it returns a winrt::hstring object.

        // winrt::CppWinUIGallery::HomePage l;
        const hstring FILEPATH = myTag.as<hstring>();

        auto v = single_threaded_vector<IInspectable>();
        v.Append(Root());
        v.Append(AppWindow().TitleBar());
        ContentFrame().Navigate(Windows::UI::Xaml::Interop::TypeName{FILEPATH}, v);
        if (ContentFrame().CanGoBack())
        {
            // TitleBar_BackButton().Foreground(Media::SolidColorBrush(Microsoft::UI::Colors::White())); Not usable for
            // light mode
            TitleBar_BackButton().IsEnabled(true);
        }
    }
}

void MainWindow::NavView_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    for (auto item : NavView().MenuItems())
    {
        if (auto navItem = item.try_as<Controls::NavigationViewItem>())
        {

            auto text = navItem.Content().as<hstring>();
            auto str = to_string(text);
            navViewElementsList.push_back(str);
        }
    }

    for (auto el : navViewElementsList)
        navViewVisibleElements.insert(el);

    auto mySettinhsItem = NavView().SettingsItem().as<FrameworkElement>();
    mySettinhsItem.Tag(box_value(L"CppWinUIGallery.SettingsPage"));
}

bool MainWindow::isSubstring(const std::string &mainString, const std::string &subString)
{
    // using find method to check if subString is
    // a substring of mainString

    if (mainString.find(subString) != std::string::npos)
        return true;
    return false;
}

bool MainWindow::NavViewSearchBox_SuitableItemFound(Controls::NavigationViewItem navItem,
                                                    std::vector<std::string> splitText)
{
    auto element = to_string(navItem.Content().as<hstring>());

    std::string lowerElement;
    lowerElement.resize(element.size());
    std::transform(element.begin(), element.end(), lowerElement.begin(), ::tolower);

    for (auto myInput : splitText)
    {
        // Convert user input to lowercase for non-case sensitive search
        std::transform(myInput.begin(), myInput.end(), myInput.begin(), ::tolower);

        if (isSubstring(lowerElement, myInput))
        {
            return true;
        }
    }
    return false;
}

void MainWindow::NavViewSearchBox_TextChanged(
    winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const &sender,
    winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const &args)
{
    // Since selecting an item will also change the text,
    // only listen to changes caused by user entering text.

    // Controls::ControlTemplate myTemplate;
    // myTemplate.TargetType(Windows::UI::Xaml::Interop::TypeName{ L"AutoSuggestBox" });

    auto overlayIcon = NavviewSearchBox().GetTemplateChild(L"searchIconOverlay").as<Controls::TextBlock>();

    if (args.Reason() == winrt::Microsoft::UI::Xaml::Controls::AutoSuggestionBoxTextChangeReason::UserInput)
    {
        std::vector<std::string> suitableItems;

        std::vector<std::string> splitText;
        auto senderText = to_string(sender.Text());

        if (senderText == "")
        {
            overlayIcon.Visibility(Visibility::Visible);
        }
        else
        {
            overlayIcon.Visibility(Visibility::Collapsed);
        }

        // Convert sender text to lowercase
        std::transform(senderText.begin(), senderText.end(), senderText.begin(), ::tolower);

        std::string delimiter = " ";
        std::size_t pos = 0;
        while ((pos = senderText.find(delimiter)) != std::string::npos)
        {
            splitText.push_back(senderText.substr(0, pos)); // split text by " " character
            senderText.erase(0, pos + delimiter.length());
        }
        // Add the last word
        splitText.push_back(senderText);

        for (auto item : NavView().MenuItems())
        {
            if (auto navItem = item.try_as<Controls::NavigationViewItem>())
            {

                if (NavViewSearchBox_SuitableItemFound(navItem, splitText))
                    suitableItems.push_back(to_string(navItem.Content().as<hstring>()));

                if (navItem.MenuItems().Size() > 0)
                {
                    for (auto subItem : navItem.MenuItems())
                    {
                        if (auto subNavItem = subItem.try_as<Controls::NavigationViewItem>())
                        {
                            if (NavViewSearchBox_SuitableItemFound(subNavItem, splitText))
                                suitableItems.push_back(to_string(subNavItem.Content().as<hstring>()));
                        }
                    }
                }
            }
        }

        navViewVisibleElements.clear();

        for (auto item : suitableItems)
        {
            navViewVisibleElements.insert(item);
        }

        for (auto item : NavView().MenuItems())
        {
            // Try to cast the item to a NavigationViewItem

            if (auto navItem = item.try_as<Controls::NavigationViewItem>())
            {

                bool subItemIsVisible = false;

                for (auto subItem : navItem.MenuItems())
                {
                    // Try to cast the item to a NavigationViewItem

                    if (auto navSubItem = subItem.try_as<Controls::NavigationViewItem>())
                    {
                        auto text = to_string(navSubItem.Content().as<hstring>());
                        if (auto search = navViewVisibleElements.find(text); search != navViewVisibleElements.end())
                        {
                            // item is visible
                            navSubItem.Visibility(Visibility::Visible);
                            subItemIsVisible = true;
                        }
                        else
                            navSubItem.Visibility(Visibility::Collapsed);
                    }
                }

                if (subItemIsVisible)
                {
                    navItem.Visibility(Visibility::Visible);
                    navItem.IsExpanded(true);
                }

                else
                {
                    auto text = to_string(navItem.Content().as<hstring>());
                    if (auto search = navViewVisibleElements.find(text); search != navViewVisibleElements.end())
                    {
                        // item is visible
                        navItem.Visibility(Visibility::Visible);
                    }
                    else
                        navItem.Visibility(Visibility::Collapsed);
                }

                if (senderText == "")
                    navItem.IsExpanded(false);
            }
        }

        // if (suitableItems.size() == 0)
        //     suitableItems.push_back("No items found!");
        // std::vector<winrt::hstring>s;
        // auto col = winrt::single_threaded_observable_vector<winrt::hstring>(std::move(s));
        //
        // for (const auto& el : suitableItems) {
        //     col.Append(to_hstring(el));
        // }
        // sender.ItemsSource(col);
    }
}

void MainWindow::SearchBox_KeyDown(winrt::Windows::Foundation::IInspectable const &sender,
                                   winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const &e)
{
    auto mySearchBox = NavviewSearchBox().GetTemplateChild(L"SearchBox").as<Controls::AutoSuggestBox>();
    auto overlayIcon = NavviewSearchBox().GetTemplateChild(L"searchIconOverlay").as<Controls::TextBlock>();

    overlayIcon.Visibility(Visibility::Collapsed); // Responsive

    if (mySearchBox.Text() == L"" && e.Key() == Windows::System::VirtualKey::Back)
        overlayIcon.Visibility(Visibility::Visible);
}

void MainWindow::SearchBox_GotFocus(winrt::Windows::Foundation::IInspectable const &sender,
                                    winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    auto mySearchBox = NavviewSearchBox().GetTemplateChild(L"SearchBox").as<Controls::AutoSuggestBox>();
    auto overlayIcon = NavviewSearchBox().GetTemplateChild(L"searchIconOverlay").as<Controls::TextBlock>();

    if (mySearchBox.Text() != L"") //             ICON OVERLAY BUG: After being in out of focus with an element selected
                                   //             inside the search box, when being selected back on focus the Text
                                   //             atribute behaves like if it contains an empty string
        overlayIcon.Visibility(Visibility::Collapsed);
}

void MainWindow::SearchBox_LostFocus(winrt::Windows::Foundation::IInspectable const &sender,
                                     winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    auto overlayIcon = NavviewSearchBox().GetTemplateChild(L"searchIconOverlay").as<Controls::TextBlock>();
    overlayIcon.Visibility(Visibility::Visible);
}

void MainWindow::LottieButton_Click(IInspectable const &sender, RoutedEventArgs const &e)
{

    AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"NormalToPointerOver_End");

    if (isPressed)
    {
        AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"NormalToPointerOver_End");
        isPressed = false;
    }
    else
    {
        AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"PointerOverToPressed_End");
        isPressed = true;
    }
}

} // namespace winrt::CppWinUIGallery::implementation
