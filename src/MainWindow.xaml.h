    #pragma once

#include "MainWindow.g.h"


namespace winrt::CppWinUIGallery::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {

    private:
        std::vector<std::string> navViewElementsList;
        std::set<std::string> navViewVisibleElements; // memorise elements by their content

    public:

        MainWindow();

        int32_t MyProperty();
        void MyProperty(int32_t value);
        //void OnLaunched(LaunchActivatedEventArgs const& e) override;
        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        //Custom title bar
        void AppTitleBar_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void AppTitleBar_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
        Windows::Graphics::RectInt32 GetRect(winrt::Windows::Foundation::Rect bounds, double scale);
        void SetRegionsForCustomTitleBar();

        //Navview frame page opening
        void NavView_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);
        void NavView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);


        //Search box with folding navview
        bool isSubstring(const std::string& mainString, const std::string& subString);
        bool NavViewSearchBox_SuitableItemFound(winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem navItem, std::vector<std::string> splitText);
        void NavViewSearchBox_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
        
        
        void TitleBar_BackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ContentFrame_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void LottieButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        bool isPressed = false;

    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
