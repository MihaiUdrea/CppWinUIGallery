#include "pch.h"
#include "ToggleSwitchPage.xaml.h"
#if __has_include("ToggleSwitchPage.g.cpp")
#include "ToggleSwitchPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;

namespace winrt::CppWinUIGallery::implementation
{
    int32_t ToggleSwitchPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ToggleSwitchPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ToggleSwitchPage::SubscriptionToggleSwitch_Toggled(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto toggleSwitch = SubscriptionToggleSwitch();
        auto subscriptionBorder = SubscriptionText().Parent().as<Border>();
        auto perpetualBorder = PerpetualText().Parent().as<Border>();

        SolidColorBrush greenBrush{ Colors::Green() };
        SolidColorBrush blueBrush{ Colors::Blue() };
        SolidColorBrush whiteBrush{ Colors::White() };
        auto customColor = Windows::UI::ColorHelper::FromArgb(58, 56, 245, 212);
        SolidColorBrush customBrush{ customColor };

        if (toggleSwitch.IsOn())
        {
            subscriptionBorder.Background(customBrush);
            perpetualBorder.Background(blueBrush);
            perpetualBorder.Child().as<TextBlock>().Foreground(whiteBrush);
        }
        else
        {
            subscriptionBorder.Background(greenBrush);
            subscriptionBorder.Child().as<TextBlock>().Foreground(whiteBrush);
            perpetualBorder.Background(customBrush);
        }
    }

    void ToggleSwitchPage::ShowSourceCode_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowHideButton();
        auto textBox = SourceCodeTextBox();
        auto cppTextBox = CppCodeTextBox();
        auto cppButton = ShowCppButton(); // Ensure ShowCppButton is correctly named and initialized

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide C++ code if visible
            if (cppTextBox.Visibility() == Visibility::Visible)
            {
                cppTextBox.Visibility(Visibility::Collapsed);
                cppButton.Content(box_value(L"Show C++"));
            }

            // Show XAML source code
            hstring xamlSourceCode = L"<!-- XAML code here -->";
            textBox.Text(xamlSourceCode);
            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide XAML"));
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show XAML"));
        }
    }

    void ToggleSwitchPage::ShowCppCode_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowCppButton(); // Make sure the button is named correctly
        auto textBox = CppCodeTextBox();
        auto xamlTextBox = SourceCodeTextBox();
        auto xamlButton = ShowHideButton(); // Ensure ShowHideButton is correctly named and initialized

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide XAML code if visible
            if (xamlTextBox.Visibility() == Visibility::Visible)
            {
                xamlTextBox.Visibility(Visibility::Collapsed);
                xamlButton.Content(box_value(L"Show XAML"));
            }

            // Show C++ source code
            hstring cppSourceCode = L"// C++ code here";
            textBox.Text(cppSourceCode);
            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide C++"));
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show C++"));
        }
    }
}
