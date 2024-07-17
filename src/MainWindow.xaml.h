#pragma once

#include "MainWindow.g.h"
#include <vector>
#include <string>

namespace winrt::CppWinUIGallery::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
    private:
        const std::vector<std::string> &navViewElementsList = {
            "Home",

            "Design guidance",
            "Color",
            // ...

            "Basic input",
            "Button"
            // ...
        };

    public:

        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void NavView_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);
        void NavView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void NavViewSearchBox_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
